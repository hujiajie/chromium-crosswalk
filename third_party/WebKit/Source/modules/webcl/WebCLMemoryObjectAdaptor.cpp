// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/webcl/WebCLMemoryObjectAdaptor.h"

#include "modules/webcl/WebCLMemoryObject.h"

namespace blink {

WebCLMemoryObjectAdaptor* WebCLMemoryObjectAdaptor::create(WebCLMemoryObject* impl)
{
    return new WebCLMemoryObjectAdaptor(impl);
}

WebCLMemoryObjectAdaptor::WebCLMemoryObjectAdaptor(WebCLMemoryObject* impl)
    : WebCLScriptWrappableAdaptor<WebCLMemoryObject>(impl)
{
}

WebCLMemoryObjectAdaptor::~WebCLMemoryObjectAdaptor()
{
}

ScriptValue WebCLMemoryObjectAdaptor::getInfo(ScriptState* scriptState, unsigned name, ExceptionState& exceptionState)
{
    WebCLMemoryObject* impl = toWebCLImpl();
    return impl->getInfo(scriptState, name, exceptionState);
}

void WebCLMemoryObjectAdaptor::release()
{
    WebCLMemoryObject* impl = toWebCLImpl();
    impl->release();
}

} // namespace blink
