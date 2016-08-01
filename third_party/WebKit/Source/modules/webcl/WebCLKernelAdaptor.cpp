// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/webcl/WebCLKernelAdaptor.h"

#include "modules/webcl/WebCLDevice.h"
#include "modules/webcl/WebCLDeviceAdaptor.h"
#include "modules/webcl/WebCLKernel.h"
#include "modules/webcl/WebCLKernelArgInfo.h"
#include "modules/webcl/WebCLKernelArgInfoAdaptor.h"
#include "wtf/RefPtr.h"

namespace blink {

WebCLKernelAdaptor* WebCLKernelAdaptor::create(WebCLKernel* impl)
{
    return new WebCLKernelAdaptor(impl);
}

WebCLKernelAdaptor::WebCLKernelAdaptor(WebCLKernel* impl)
    : WebCLScriptWrappableAdaptor<WebCLKernel>(impl)
{
}

WebCLKernelAdaptor::~WebCLKernelAdaptor()
{
}

ScriptValue WebCLKernelAdaptor::getInfo(ScriptState* scriptState, unsigned name, ExceptionState& exceptionState)
{
    WebCLKernel* impl = toWebCLImpl();
    return impl->getInfo(scriptState, name, exceptionState);
}

ScriptValue WebCLKernelAdaptor::getWorkGroupInfo(ScriptState* scriptState, WebCLDeviceAdaptor* deviceAdaptor, unsigned name, ExceptionState& exceptionState)
{
    WebCLKernel* impl = toWebCLImpl();
    WebCLDevice* device = deviceAdaptor->toWebCLImpl();
    return impl->getWorkGroupInfo(scriptState, device, name, exceptionState);
}

WebCLKernelArgInfoAdaptor* WebCLKernelAdaptor::getArgInfo(unsigned index, ExceptionState& exceptionState)
{
    WebCLKernel* impl = toWebCLImpl();
    RefPtr<WebCLKernelArgInfo> kernelArgInfo = impl->getArgInfo(index, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return kernelArgInfo->toWebCLAdaptor();
}

void WebCLKernelAdaptor::setArg(unsigned index, const ScriptValue& value, ExceptionState& exceptionState)
{
    WebCLKernel* impl = toWebCLImpl();
    impl->setArg(index, value, exceptionState);
}

void WebCLKernelAdaptor::release()
{
    WebCLKernel* impl = toWebCLImpl();
    impl->release();
}

} // namespace blink
