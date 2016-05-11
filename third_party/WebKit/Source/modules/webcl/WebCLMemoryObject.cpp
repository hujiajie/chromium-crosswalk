// Copyright (C) 2011 Samsung Electronics Corporation. All rights reserved.
// Copyright (C) 2015 Intel Corporation All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/webcl/WebCLMemoryObject.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/ScriptState.h"
#include "bindings/core/v8/ToV8.h"
#include "modules/webcl/WebCLContext.h"
#include "wtf/RefPtr.h"

namespace blink {

WebCLMemoryObject::~WebCLMemoryObject()
{
    release();
    ASSERT(!m_clMem);
}

PassRefPtr<WebCLMemoryObject> WebCLMemoryObject::create(cl_mem mem, PassRefPtr<WebCLContext> context)
{
    return adoptRef(new WebCLMemoryObject(mem, context));
}

ScriptValue WebCLMemoryObject::getInfo(ScriptState* scriptState, int paramName, ExceptionState& es)
{
    v8::Handle<v8::Object> creationContext = scriptState->context()->Global();
    v8::Isolate* isolate = scriptState->isolate();

    if (isReleased()) {
        es.throwWebCLException(WebCLException::InvalidMemObject, WebCLException::invalidMemObjectMessage);
        return ScriptValue(scriptState, v8::Null(isolate));
    }

    int status;
    switch (paramName) {
    case CL_MEM_SIZE:
    case CL_MEM_OFFSET:
        {
            size_t info;
            status = getInfo(paramName, info);
            if (status != WebCLException::Success)
                WebCLException::throwException(status, es);
            return ScriptValue(scriptState, v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned>(info)));
        }
    case CL_MEM_TYPE:
        {
            cl_mem_object_type info;
            status = getInfo(paramName, info);
            if (status != WebCLException::Success)
                WebCLException::throwException(status, es);
            return ScriptValue(scriptState, v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned>(info)));
        }
    case CL_MEM_FLAGS:
        {
            cl_mem_flags info;
            status = getInfo(paramName, info);
            if (status != WebCLException::Success)
                WebCLException::throwException(status, es);
            return ScriptValue(scriptState, v8::Integer::NewFromUnsigned(isolate, static_cast<unsigned>(info)));
        }
    case CL_MEM_CONTEXT:
        return ScriptValue(scriptState, toV8(context(), creationContext, isolate));
    case CL_MEM_ASSOCIATED_MEMOBJECT:
        {
            RefPtr<WebCLMemoryObject> memoryObject = associatedMemObject();
            if (!memoryObject)
                return ScriptValue(scriptState, v8::Null(isolate));
            return ScriptValue(scriptState, toV8(memoryObject, creationContext, isolate));
        }
    default:
        es.throwWebCLException(WebCLException::InvalidValue, WebCLException::invalidValueMessage);
        return ScriptValue(scriptState, v8::Null(isolate));
    }
}

void WebCLMemoryObject::release()
{
    if (isReleased())
        return;

    cl_int err = clReleaseMemObject(m_clMem);
    if (err != CL_SUCCESS)
        ASSERT_NOT_REACHED();

    m_clMem = 0;
}

PassRefPtr<WebCLMemoryObject> WebCLMemoryObject::associatedMemObject()
{
    ASSERT(!isReleased());

    return m_parentMemObject;
}

WebCLMemoryObject::WebCLMemoryObject(cl_mem mem, PassRefPtr<WebCLContext> context, WebCLMemoryObject* parentBuffer)
    : WebCLObject(context)
    , m_parentMemObject(parentBuffer)
    , m_clMem(mem)
{
}

} // namespace blink
