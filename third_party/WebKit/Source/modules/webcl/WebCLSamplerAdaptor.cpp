// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/webcl/WebCLSamplerAdaptor.h"

#include "modules/webcl/WebCLSampler.h"

namespace blink {

WebCLSamplerAdaptor* WebCLSamplerAdaptor::create(WebCLSampler* impl)
{
    return new WebCLSamplerAdaptor(impl);
}

WebCLSamplerAdaptor::WebCLSamplerAdaptor(WebCLSampler* impl)
    : WebCLScriptWrappableAdaptor<WebCLSampler>(impl)
{
}

WebCLSamplerAdaptor::~WebCLSamplerAdaptor()
{
}

ScriptValue WebCLSamplerAdaptor::getInfo(ScriptState* scriptState, unsigned name, ExceptionState& exceptionState)
{
    WebCLSampler* impl = toWebCLImpl();
    return impl->getInfo(scriptState, name, exceptionState);
}

void WebCLSamplerAdaptor::release()
{
    WebCLSampler* impl = toWebCLImpl();
    impl->release();
}

} // namespace blink
