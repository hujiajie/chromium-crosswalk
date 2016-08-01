// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/webcl/WebCLBufferAdaptor.h"

#include "modules/webcl/WebCLBuffer.h"
#include "wtf/RefPtr.h"

namespace blink {

WebCLBufferAdaptor* WebCLBufferAdaptor::create(WebCLBuffer* impl)
{
    return new WebCLBufferAdaptor(impl);
}

WebCLBufferAdaptor::WebCLBufferAdaptor(WebCLBuffer* impl)
    : WebCLMemoryObjectAdaptor(impl)
{
}

WebCLBufferAdaptor::~WebCLBufferAdaptor()
{
}

WebCLBufferAdaptor* WebCLBufferAdaptor::createSubBuffer(unsigned memFlags, unsigned origin, unsigned sizeInBytes, ExceptionState& exceptionState)
{
    WebCLBuffer* impl = toWebCLImpl<WebCLBuffer>();
    RefPtr<WebCLBuffer> buffer = impl->createSubBuffer(memFlags, origin, sizeInBytes, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return buffer->toWebCLAdaptor<WebCLBuffer>();
}

} // namespace blink
