// Copyright (C) 2011 Samsung Electronics Corporation. All rights reserved.
// Copyright (C) 2015 Intel Corporation All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "bindings/modules/v8/V8WebCLPlatform.h"
#include "core/webcl/WebCLException.h"
#include "modules/webcl/WebCL.h"
#include "modules/webcl/WebCLContext.h"
#include "modules/webcl/WebCLDevice.h"
#include "modules/webcl/WebCLOpenCL.h"

namespace blink {

WebCLDevice::~WebCLDevice()
{
    // Unlike WebCLContext / WebCLCommandQueue / WebCLProgram / ...,
    // WebCLDevice does not need to call a release() method here:
    // 1) OpenCL 1.1 runtime has no clReleaseDevice() or an alternative, so
    //    there's no need to release the device.
    // 2) The OpenCL 1.2 (or above) spec implies that clReleaseDevice() is only
    //    meaningful for sub devices, but no sub device is created in our WebCL
    //    1.0 implementation.
}

PassRefPtr<WebCLDevice> WebCLDevice::create(cl_device_id deviceId)
{
    return adoptRef(new WebCLDevice(deviceId, nullptr));
}

PassRefPtr<WebCLDevice> WebCLDevice::create(cl_device_id deviceId, WebCLPlatform* platform)
{
    return adoptRef(new WebCLDevice(deviceId, platform));
}

ScriptValue WebCLDevice::getInfo(ScriptState* scriptState, unsigned name, ExceptionState& es)
{
    v8::Handle<v8::Object> creationContext = scriptState->context()->Global();
    v8::Isolate* isolate = scriptState->isolate();

    if (!m_clDeviceId) {
        es.throwWebCLException(WebCLException::INVALID_DEVICE, WebCLException::invalidDeviceMessage);
        return ScriptValue(scriptState, v8::Null(isolate));
    }

    if (!WebCLInputChecker::isValidDeviceInfoType(name)) {
        es.throwWebCLException(WebCLException::INVALID_VALUE, WebCLException::invalidValueMessage);
        return ScriptValue(scriptState, v8::Null(isolate));
    }

    switch (name) {
    case CL_DEVICE_AVAILABLE:
    case CL_DEVICE_COMPILER_AVAILABLE:
    case CL_DEVICE_IMAGE_SUPPORT:
    case CL_DEVICE_ERROR_CORRECTION_SUPPORT:
    case CL_DEVICE_HOST_UNIFIED_MEMORY:
    case CL_DEVICE_ENDIAN_LITTLE:
        {
            cl_bool info = getInfo<cl_bool>(name, es);
            return ScriptValue(scriptState, v8::Boolean::New(isolate, static_cast<bool>(info)));
        }
    case CL_DEVICE_VENDOR_ID:
    case CL_DEVICE_MAX_COMPUTE_UNITS:
    case CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS:
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR:
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT:
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT:
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG:
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT:
    case CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR:
    case CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT:
    case CL_DEVICE_NATIVE_VECTOR_WIDTH_INT:
    case CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG:
    case CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT:
    case CL_DEVICE_MAX_CLOCK_FREQUENCY:
    case CL_DEVICE_ADDRESS_BITS:
    case CL_DEVICE_MAX_READ_IMAGE_ARGS:
    case CL_DEVICE_MAX_WRITE_IMAGE_ARGS:
    case CL_DEVICE_MAX_SAMPLERS:
    case CL_DEVICE_MEM_BASE_ADDR_ALIGN:
    case CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE:
    case CL_DEVICE_MAX_CONSTANT_ARGS:
        {
            cl_uint info = getInfo<cl_uint>(name, es);
            return ScriptValue(scriptState, v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned>(info)));
        }
    case CL_DEVICE_MAX_MEM_ALLOC_SIZE:
    case CL_DEVICE_GLOBAL_MEM_CACHE_SIZE:
    case CL_DEVICE_GLOBAL_MEM_SIZE:
    case CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE:
    case CL_DEVICE_LOCAL_MEM_SIZE:
        {
            cl_ulong info = getInfo<cl_ulong>(name, es);
            return ScriptValue(scriptState, v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned>(info)));
        }
    case CL_DEVICE_MAX_WORK_GROUP_SIZE:
    case CL_DEVICE_IMAGE2D_MAX_WIDTH:
    case CL_DEVICE_IMAGE2D_MAX_HEIGHT:
    case CL_DEVICE_IMAGE3D_MAX_WIDTH:
    case CL_DEVICE_IMAGE3D_MAX_HEIGHT:
    case CL_DEVICE_IMAGE3D_MAX_DEPTH:
    case CL_DEVICE_MAX_PARAMETER_SIZE:
    case CL_DEVICE_PROFILING_TIMER_RESOLUTION:
        {
            size_t info = getInfo<size_t>(name, es);
            return ScriptValue(scriptState, v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned>(info)));
        }
    case CL_DEVICE_TYPE:
        {
            cl_device_type info = getInfo<cl_device_type>(name, es);
            return ScriptValue(scriptState, v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned>(info)));
        }
    case CL_DEVICE_SINGLE_FP_CONFIG:
        {
            cl_device_fp_config info = getInfo<cl_device_fp_config>(name, es);
            return ScriptValue(scriptState, v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned>(info)));
        }
    case CL_DEVICE_GLOBAL_MEM_CACHE_TYPE:
        {
            cl_device_mem_cache_type info = getInfo<cl_device_mem_cache_type>(name, es);
            return ScriptValue(scriptState, v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned>(info)));
        }
    case CL_DEVICE_LOCAL_MEM_TYPE:
        {
            cl_device_local_mem_type info = getInfo<cl_device_local_mem_type>(name, es);
            return ScriptValue(scriptState, v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned>(info)));
        }
    case CL_DEVICE_EXECUTION_CAPABILITIES:
        {
            cl_device_exec_capabilities info = getInfo<cl_device_exec_capabilities>(name, es);
            return ScriptValue(scriptState, v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned>(info)));
        }
    case CL_DEVICE_QUEUE_PROPERTIES:
        {
            cl_command_queue_properties info = getInfo<cl_command_queue_properties>(name, es);
            return ScriptValue(scriptState, v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned>(info)));
        }
    case CL_DEVICE_PROFILE:
    case CL_DEVICE_VERSION:
    case CL_DEVICE_OPENCL_C_VERSION:
    case CL_DEVICE_NAME:
    case CL_DEVICE_VENDOR:
    case CL_DRIVER_VERSION:
    case CL_DEVICE_EXTENSIONS:
        {
            String info = getInfo<String>(name, es);
            return ScriptValue(scriptState, v8String(isolate, info));
        }
    case CL_DEVICE_MAX_WORK_ITEM_SIZES:
        {
            Vector<size_t> info = getInfo<Vector<size_t>>(name, es);
            return ScriptValue(scriptState, toV8(info, creationContext, isolate));
        }
    case CL_DEVICE_PLATFORM:
        {
            RefPtr<WebCLPlatform> info = getInfo<RefPtr<WebCLPlatform>>(name, es);
            return ScriptValue(scriptState, toV8(info, creationContext, isolate));
        }
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE:
    case CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE:
        {
            cl_uint info = 0;
            if (m_extension.isEnabledExtension("KHR_fp64")) {
                cl_int status = clGetDeviceInfo(m_clDeviceId, name, sizeof(cl_uint), &info, nullptr);
                if (status != CL_SUCCESS) {
                    WebCLException::throwException(status, es);
                }
            }
            return ScriptValue(scriptState, v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned>(info)));
        }
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF:
    case CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF:
        {
            cl_uint info = 0;
            if (m_extension.isEnabledExtension("KHR_fp16")) {
                cl_int status = clGetDeviceInfo(m_clDeviceId, name, sizeof(cl_uint), &info, nullptr);
                if (status != CL_SUCCESS) {
                    WebCLException::throwException(status, es);
                }
            }
            return ScriptValue(scriptState, v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned>(info)));
        }
    default:
        es.throwWebCLException(WebCLException::FAILURE, WebCLException::failureMessage);
        return ScriptValue(scriptState, v8::Null(isolate));
    }
}

void WebCLDevice::cacheDeviceExtensions()
{
    char deviceString[MULTI_EXTENSIONS_LENGTH] = "";
    Vector<String> extensions;

    if (!m_clDeviceId)
        return;

    cl_int err = clGetDeviceInfo(m_clDeviceId, CL_DEVICE_EXTENSIONS, sizeof(deviceString), &deviceString, nullptr);

    if (err != CL_SUCCESS)
        return;

    String temp = String(deviceString);
    temp.split(' ', extensions);

    for (auto extension : extensions) {
        if (!extension.containsOnlyWhitespace())
            m_extension.addSupportedCLExtension(String(extension));
    }
}

bool WebCLDevice::enableExtension(const String& name)
{
    return m_extension.enableExtension(name);
}

Vector<String> WebCLDevice::getSupportedExtensions()
{
    return m_extension.getSupportedExtensions();
}

void WebCLDevice::getEnabledExtensions(HashSet<String>& extensions)
{
    m_extension.getEnabledExtensions(extensions);
}

int WebCLDevice::getAsSpecialInfo(cl_device_exec_capabilities& info, unsigned name)
{
    if (name != CL_DEVICE_EXECUTION_CAPABILITIES)
        return WebCLException::INVALID_VALUE;
    info = CL_EXEC_KERNEL;
    return WebCLException::SUCCESS;
}

int WebCLDevice::getAsSpecialInfo(String& info, unsigned name)
{
    switch (name) {
    case CL_DEVICE_PROFILE:
        info = "WEBCL_PROFILE";
        return WebCLException::SUCCESS;
    case CL_DEVICE_VERSION:
        info = "WebCL 1.0";
        return WebCLException::SUCCESS;
    case CL_DEVICE_OPENCL_C_VERSION:
        info = "WebCL C 1.0";
        return WebCLException::SUCCESS;
    default:
        return WebCLException::INVALID_VALUE;
    }
}

int WebCLDevice::getAsSpecialInfo(RefPtr<WebCLPlatform>& info, unsigned name)
{
    if (name != CL_DEVICE_PLATFORM)
        return WebCLException::INVALID_VALUE;
    info = m_platform;
    return WebCLException::SUCCESS;
}

int WebCLDevice::getAsOrdinaryInfo(String& info, unsigned name)
{
    int status;
    size_t sizeInBytes = 0;

    status = clGetDeviceInfo(m_clDeviceId, name, 0, nullptr, &sizeInBytes);
    if (status == WebCLException::SUCCESS && sizeInBytes >= sizeof(char) && sizeInBytes % sizeof(char) == 0) {
        char* stringInfo = new char[sizeInBytes / sizeof(char)];
        status = clGetDeviceInfo(m_clDeviceId, name, sizeInBytes, stringInfo, nullptr);
        if (status == WebCLException::SUCCESS)
            info = stringInfo;
        delete [] stringInfo;
        return status;
    }

    return WebCLException::FAILURE;
}

WebCLDevice::WebCLDevice(cl_device_id device, WebCLPlatform* platform)
    : m_platform(platform)
    , m_clDeviceId(device)
{
    cacheDeviceExtensions();
}

} // namespace blink
