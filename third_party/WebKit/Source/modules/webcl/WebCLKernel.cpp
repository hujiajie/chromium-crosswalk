// Copyright (C) 2011 Samsung Electronics Corporation. All rights reserved.
// Copyright (C) 2015 Intel Corporation All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "bindings/core/v8/V8ArrayBufferView.h"
#include "bindings/modules/v8/V8WebCLContext.h"
#include "bindings/modules/v8/V8WebCLMemoryObject.h"
#include "bindings/modules/v8/V8WebCLProgram.h"
#include "bindings/modules/v8/V8WebCLSampler.h"
#include "core/dom/DOMArrayBufferView.h"
#include "core/dom/DOMTypedArray.h"
#include "core/webcl/WebCLException.h"
#include "modules/webcl/WebCL.h"
#include "modules/webcl/WebCLBuffer.h"
#include "modules/webcl/WebCLDevice.h"
#include "modules/webcl/WebCLImage.h"
#include "modules/webcl/WebCLKernel.h"
#include "modules/webcl/WebCLKernelArgInfo.h"
#include "modules/webcl/WebCLOpenCL.h"

namespace blink {

WebCLKernel::~WebCLKernel()
{
    release();
    ASSERT(!m_clKernel);
}

PassRefPtr<WebCLKernel> WebCLKernel::create(cl_kernel kernel, PassRefPtr<WebCLContext> context, PassRefPtr<WebCLProgram> program)
{
    return adoptRef(new WebCLKernel(kernel, context, program));
}

ScriptValue WebCLKernel::getInfo(ScriptState* scriptState, int kernelInfo, ExceptionState& es)
{
    v8::Handle<v8::Object> creationContext = scriptState->context()->Global();
    v8::Isolate* isolate = scriptState->isolate();

    if (isReleased()) {
        es.throwWebCLException(WebCLException::INVALID_KERNEL, WebCLException::invalidKernelMessage);
        return ScriptValue(scriptState, v8::Null(isolate));
    }

    int status;
    switch (kernelInfo) {
    case CL_KERNEL_NUM_ARGS:
        {
            cl_uint info;
            status = getInfo(kernelInfo, info);
            if (status != WebCLException::SUCCESS)
                WebCLException::throwException(status, es);
            return ScriptValue(scriptState, v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned>(info)));
        }
    case CL_KERNEL_FUNCTION_NAME:
        {
            String info;
            status = getInfo(kernelInfo, info);
            if (status != WebCLException::SUCCESS)
                WebCLException::throwException(status, es);
            return ScriptValue(scriptState, v8String(isolate, info));
        }
    case CL_KERNEL_CONTEXT:
        return ScriptValue(scriptState, toV8(context(), creationContext, isolate));
    case CL_KERNEL_PROGRAM:
        return ScriptValue(scriptState, toV8(program(), creationContext, isolate));
    default:
        es.throwWebCLException(WebCLException::INVALID_VALUE, WebCLException::invalidValueMessage);
        return ScriptValue(scriptState, v8::Null(isolate));
    }
}

ScriptValue WebCLKernel::getWorkGroupInfo(ScriptState* scriptState, WebCLDevice* device, int paramName, ExceptionState& es)
{
    v8::Handle<v8::Object> creationContext = scriptState->context()->Global();
    v8::Isolate* isolate = scriptState->isolate();

    if (isReleased()) {
        es.throwWebCLException(WebCLException::INVALID_KERNEL, WebCLException::invalidKernelMessage);
        return ScriptValue(scriptState, v8::Null(isolate));
    }

    Vector<RefPtr<WebCLDevice>> deviceList = context()->devices();
    if (device) {
        size_t i;
        for (i = 0; i < deviceList.size(); i ++) {
            if (device == deviceList[i])
                break;
        }

        if (i == deviceList.size()) {
            es.throwWebCLException(WebCLException::INVALID_DEVICE, WebCLException::invalidDeviceMessage);
            return ScriptValue(scriptState, v8::Null(isolate));
        }
    }

    if (!device && deviceList.size() != 1) {
        es.throwWebCLException(WebCLException::INVALID_DEVICE, WebCLException::invalidDeviceMessage);
        return ScriptValue(scriptState, v8::Null(isolate));
    }

    int status;
    switch (paramName) {
    case CL_KERNEL_LOCAL_MEM_SIZE:
    case CL_KERNEL_PRIVATE_MEM_SIZE:
        {
            cl_ulong info;
            status = getWorkGroupInfo(device, paramName, info);
            if (status != WebCLException::SUCCESS)
                WebCLException::throwException(status, es);
            return ScriptValue(scriptState, v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned>(info)));
        }
    case CL_KERNEL_WORK_GROUP_SIZE:
    case CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE:
        {
            size_t info;
            status = getWorkGroupInfo(device, paramName, info);
            if (status != WebCLException::SUCCESS)
                WebCLException::throwException(status, es);
            return ScriptValue(scriptState, v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned>(info)));
        }
    case CL_KERNEL_COMPILE_WORK_GROUP_SIZE:
        {
            Vector<size_t> info;
            status = getWorkGroupInfo(device, paramName, info);
            if (status != WebCLException::SUCCESS)
                WebCLException::throwException(status, es);
            return ScriptValue(scriptState, toV8(info, creationContext, isolate));
        }
    default:
        es.throwWebCLException(WebCLException::INVALID_VALUE, WebCLException::invalidValueMessage);
        return ScriptValue(scriptState, v8::Null(isolate));
    }
}

#if CPU(BIG_ENDIAN)
inline void swapElementsForBigEndian(size_t& arrayLength, DOMArrayBufferView* bufferView, Vector<unsigned>& uLongBuffer) {
    for (size_t i = 0; i < arrayLength * 2; i += 2) {
        unsigned low, high;
        low = static_cast<Uint32Array*>(bufferView->view())->item(i);
        high = static_cast<Uint32Array*>(bufferView->view())->item(i + 1);
        uLongBuffer[i / 2] = ((unsigned)low << 32) | high;
    }
}
#endif

WebCLKernelArgInfo* WebCLKernel::getArgInfo(unsigned index, ExceptionState& es)
{
    if (!WebCLInputChecker::isValidKernelArgIndex(this, index)) {
        es.throwWebCLException(WebCLException::INVALID_ARG_INDEX, WebCLException::invalidArgIndexMessage);
        return nullptr;
    }

    return m_argumentInfoProvider->argumentsInfo().at(index).get();
}

void WebCLKernel::setArg(unsigned index, const ScriptValue& value, ExceptionState& es)
{
    v8::Isolate* isolate = value.isolate();
    v8::Handle<v8::Value> object(value.v8Value());
    if (V8WebCLMemoryObject::hasInstance(object, isolate)) {
        WebCLMemoryObject* memoryObject;
        memoryObject = V8WebCLMemoryObject::toImplWithTypeCheck(isolate, object);
        setArg(index, memoryObject, es);
        return;
    }

    if (V8WebCLSampler::hasInstance(object, isolate)) {
        WebCLSampler* sampler;
        sampler = V8WebCLSampler::toImplWithTypeCheck(isolate, object);
        setArg(index, sampler, es);
        return;
    }

    if (V8ArrayBufferView::hasInstance(object, isolate)) {
        DOMArrayBufferView* arrayBufferView;
        arrayBufferView = object->IsArrayBufferView() ? V8ArrayBufferView::toImpl(v8::Handle<v8::ArrayBufferView>::Cast(object)) : 0;
        setArg(index, arrayBufferView, es);
        return;
    }

    es.throwWebCLException(WebCLException::INVALID_ARG_VALUE, WebCLException::invalidArgValueMessage);
}

void WebCLKernel::setArg(unsigned index, WebCLMemoryObject* object, ExceptionState& es)
{
    if (isReleased()) {
        es.throwWebCLException(WebCLException::INVALID_KERNEL, WebCLException::invalidKernelMessage);
        return;
    }

    cl_mem clObject = nullptr;
    if (object) {
        clObject = object->getMem();
        if (!clObject) {
            es.throwWebCLException(WebCLException::INVALID_MEM_OBJECT, WebCLException::invalidMemObjectMessage);
            return;
        }
    }

    WebCLKernelArgInfo* argInfo = getArgInfo(index, es);
    if (!argInfo || (object->type() == WebCLMemoryObject::IMAGE && argInfo->type() != WebCLKernelArgInfo::IMAGE) || (object->type() == WebCLMemoryObject::BUFFER && (argInfo->addressQualifier().isEmpty() || argInfo->type() != WebCLKernelArgInfo::BUFFER))) {
        es.throwWebCLException(WebCLException::INVALID_ARG_VALUE, WebCLException::invalidArgIndexMessage);
        return;
    }

    cl_int err = clSetKernelArg(m_clKernel, index, sizeof(cl_mem), &clObject);
    if (err != CL_SUCCESS)
        WebCLException::throwException(err, es);
    else
        argInfo->setAssociated(true);
}

void WebCLKernel::setArg(unsigned index, WebCLSampler* sampler, ExceptionState& es)
{
    if (isReleased()) {
        es.throwWebCLException(WebCLException::INVALID_KERNEL, WebCLException::invalidKernelMessage);
        return;
    }

    cl_sampler clSamplerId = nullptr;
    if (sampler) {
        clSamplerId = sampler->getSampler();
        if (!clSamplerId) {
            es.throwWebCLException(WebCLException::INVALID_MEM_OBJECT, WebCLException::invalidMemObjectMessage);
            return;
        }
    }

    WebCLKernelArgInfo* argInfo = getArgInfo(index, es);
    if (!argInfo || argInfo->type() != WebCLKernelArgInfo::SAMPLER) {
        es.throwWebCLException(WebCLException::INVALID_ARG_VALUE, WebCLException::invalidArgIndexMessage);
        return;
    }
    cl_int err = clSetKernelArg(m_clKernel, index, sizeof(cl_sampler), &clSamplerId);
    if (err != CL_SUCCESS)
        WebCLException::throwException(err, es);
    else
        argInfo->setAssociated(true);
}

void WebCLKernel::setArg(unsigned index, DOMArrayBufferView* data, ExceptionState& es)
{
    if (isReleased()) {
        es.throwWebCLException(WebCLException::INVALID_KERNEL, WebCLException::invalidKernelMessage);
        return;
    }

    if (!WebCLInputChecker::isValidKernelArgIndex(this, index)) {
        es.throwWebCLException(WebCLException::INVALID_ARG_INDEX, WebCLException::invalidArgIndexMessage);
        return;
    }

    cl_int err = CL_SUCCESS;
    WebCLKernelArgInfo* argInfo = getArgInfo(index, es);
    const String& accessQualifier = argInfo->addressQualifier();
    bool hasLocalQualifier = accessQualifier == "local";
    if (hasLocalQualifier) {
        if (data->type() != DOMArrayBufferView::TypeUint32) {
            es.throwWebCLException(WebCLException::INVALID_ARG_VALUE, WebCLException::invalidArgValueMessage);
            return;
        }

        Uint32Array* typedArray = static_cast<Uint32Array*>(data->view());
        if (typedArray->length() != 1) {
            es.throwWebCLException(WebCLException::INVALID_ARG_VALUE, WebCLException::invalidArgValueMessage);
            return;
        }

        unsigned* value = static_cast<Uint32Array*>(data->view())->data();
        err = clSetKernelArg(m_clKernel, index, static_cast<size_t>(value[0]), 0);
        if (err != CL_SUCCESS)
            WebCLException::throwException(err, es);
        else
            argInfo->setAssociated(true);

        return;
    }

    void* bufferData = 0;
    size_t arrayLength = 0;
    Vector<unsigned> uLongBuffer;
    int type = argInfo->type();
    switch(data->type()) {
    case (DOMArrayBufferView::TypeFloat64): // DOUBLE
        if (type != WebCLKernelArgInfo::DOUBLE) {
            es.throwWebCLException(WebCLException::INVALID_ARG_VALUE, WebCLException::invalidArgValueMessage);
            return;
        }
        bufferData = static_cast<Float64Array*>(data->view())->data();
        arrayLength = data->byteLength() / 8;
        break;
    case (DOMArrayBufferView::TypeFloat32): // FLOAT
        if (type != WebCLKernelArgInfo::FLOAT) {
            es.throwWebCLException(WebCLException::INVALID_ARG_VALUE, WebCLException::invalidArgValueMessage);
            return;
        }
        bufferData = static_cast<Float32Array*>(data->view())->data();
        arrayLength = data->byteLength() / 4;
        break;
    case (DOMArrayBufferView::TypeUint32): // UINT
        if (!(type == WebCLKernelArgInfo::UINT || type == WebCLKernelArgInfo::ULONG)) {
            es.throwWebCLException(WebCLException::INVALID_ARG_VALUE, WebCLException::invalidArgValueMessage);
            return;
        }
        bufferData = static_cast<Uint32Array*>(data->view())->data();
        arrayLength = data->byteLength() / 4;
        if (type == WebCLKernelArgInfo::LONG) {
            arrayLength = arrayLength / 2;
#if CPU(BIG_ENDIAN)
            uLongBuffer.resize(arrayLength);
            swapElementsForBigEndian(arrayLength, bufferView, uLongBuffer);
            bufferData = uLongBuffer.data();
#endif
        }
        break;
    case (DOMArrayBufferView::TypeInt32):  // INT
        if (!(type == WebCLKernelArgInfo::INT || type == WebCLKernelArgInfo::LONG)) {
            es.throwWebCLException(WebCLException::INVALID_ARG_VALUE, WebCLException::invalidArgValueMessage);
            return;
        }
        bufferData = static_cast<Int32Array*>(data->view())->data();
        arrayLength = data->byteLength() / 4;

        if (type == WebCLKernelArgInfo::LONG)
            arrayLength = arrayLength / 2;
        break;
    case (DOMArrayBufferView::TypeUint16): // USHORT
        if (type != WebCLKernelArgInfo::USHORT) {
            es.throwWebCLException(WebCLException::INVALID_ARG_VALUE, WebCLException::invalidArgValueMessage);
            return;
        }
        bufferData = static_cast<Uint16Array*>(data->view())->data();
        arrayLength = data->byteLength() / 2;
        break;
    case (DOMArrayBufferView::TypeInt16): // SHORT
        if (type != WebCLKernelArgInfo::SHORT) {
            es.throwWebCLException(WebCLException::INVALID_ARG_VALUE, WebCLException::invalidArgValueMessage);
            return;
        }
        bufferData = static_cast<Int16Array*>(data->view())->data();
        arrayLength = data->byteLength() / 2;
        break;
    case (DOMArrayBufferView::TypeUint8): // UCHAR
        if (type != WebCLKernelArgInfo::UCHAR) {
            es.throwWebCLException(WebCLException::INVALID_ARG_VALUE, WebCLException::invalidArgValueMessage);
            return;
        }
        bufferData = static_cast<Uint8Array*>(data->view())->data();
        arrayLength = data->byteLength() / 1;
        break;
    case (DOMArrayBufferView::TypeInt8): // CHAR
        if (type != WebCLKernelArgInfo::CHAR) {
            es.throwWebCLException(WebCLException::INVALID_ARG_VALUE, WebCLException::invalidArgValueMessage);
            return;
        }
        bufferData = static_cast<Int8Array*>(data->view())->data();
        arrayLength = data->byteLength() / 1;
        break;
    default:
        es.throwWebCLException(WebCLException::INVALID_ARG_VALUE, WebCLException::invalidArgValueMessage);
        return;
    }

    size_t bufferDataSize = data->byteLength();
    err = clSetKernelArg(m_clKernel, index, bufferDataSize, bufferData);

    if (err != CL_SUCCESS)
        WebCLException::throwException(err, es);
    else
        argInfo->setAssociated(true);
}

void WebCLKernel::setArg(unsigned index, size_t argSize, const void* argValue, ExceptionState& es)
{
    if (isReleased()) {
        es.throwWebCLException(WebCLException::INVALID_KERNEL, WebCLException::invalidKernelMessage);
        return;
    }

    if (!WebCLInputChecker::isValidKernelArgIndex(this, index)) {
        es.throwWebCLException(WebCLException::INVALID_ARG_INDEX, WebCLException::invalidArgIndexMessage);
        return;
    }

    cl_int err = CL_SUCCESS;
    WebCLKernelArgInfo* argInfo = getArgInfo(index, es);
    err = clSetKernelArg(m_clKernel, index, argSize, argValue);

    if (err != CL_SUCCESS)
        WebCLException::throwException(err, es);
    else
        argInfo->setAssociated(true);
}

void WebCLKernel::release()
{
    if (isReleased())
        return;

    cl_int err = clReleaseKernel(m_clKernel);
    if (err != CL_SUCCESS)
        ASSERT_NOT_REACHED();

    m_clKernel = 0;
}

unsigned WebCLKernel::associatedArguments()
{
    unsigned count = 0;
    for (unsigned i = 0; i < m_argumentInfoProvider->numberOfArguments(); i ++) {
        if (m_argumentInfoProvider->argumentsInfo()[i]->isAssociated())
            count ++;
    }
    return count;
}

int WebCLKernel::getInfo(unsigned name, String& info)
{
    ASSERT(!isReleased());

    int status = getInfoCustom(name, info);
    if (status != WebCLException::INVALID_VALUE)
        return status;

    size_t sizeInBytes = 0;
    status = clGetKernelInfo(m_clKernel, name, 0, nullptr, &sizeInBytes);
    if (status == WebCLException::SUCCESS && sizeInBytes >= sizeof(char) && sizeInBytes % sizeof(char) == 0) {
        char* stringBuffer = new char[sizeInBytes / sizeof(char)];
        status = clGetKernelInfo(m_clKernel, name, sizeInBytes, stringBuffer, nullptr);
        if (status == WebCLException::SUCCESS)
            info = stringBuffer;
        delete [] stringBuffer;
        return status;
    }

    return WebCLException::FAILURE;
}

PassRefPtr<WebCLProgram> WebCLKernel::program()
{
    ASSERT(!isReleased());

    return m_program;
}

WebCLKernel::WebCLKernel(cl_kernel kernel, PassRefPtr<WebCLContext> context, PassRefPtr<WebCLProgram> program)
    : WebCLObject(context)
    , m_program(program)
    , m_clKernel(kernel)
{
    m_argumentInfoProvider = adoptPtr(new WebCLKernelArgInfoProvider(this));
}

} // namespace blink
