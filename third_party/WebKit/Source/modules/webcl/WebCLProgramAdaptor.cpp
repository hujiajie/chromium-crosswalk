// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/webcl/WebCLProgramAdaptor.h"

#include "modules/webcl/WebCLCallback.h"
#include "modules/webcl/WebCLDevice.h"
#include "modules/webcl/WebCLDeviceAdaptor.h"
#include "modules/webcl/WebCLKernel.h"
#include "modules/webcl/WebCLKernelAdaptor.h"
#include "modules/webcl/WebCLProgram.h"
#include "wtf/RefPtr.h"
#include "wtf/Vector.h"

namespace blink {

WebCLProgramAdaptor* WebCLProgramAdaptor::create(WebCLProgram* impl)
{
    return new WebCLProgramAdaptor(impl);
}

WebCLProgramAdaptor::WebCLProgramAdaptor(WebCLProgram* impl)
    : WebCLScriptWrappableAdaptor<WebCLProgram>(impl)
{
}

WebCLProgramAdaptor::~WebCLProgramAdaptor()
{
}

ScriptValue WebCLProgramAdaptor::getInfo(ScriptState* scriptState, unsigned name, ExceptionState& exceptionState)
{
    WebCLProgram* impl = toWebCLImpl();
    return impl->getInfo(scriptState, name, exceptionState);
}

ScriptValue WebCLProgramAdaptor::getBuildInfo(ScriptState* scriptState, WebCLDeviceAdaptor* deviceAdaptor, unsigned name, ExceptionState& exceptionState)
{
    WebCLProgram* impl = toWebCLImpl();
    WebCLDevice* device = deviceAdaptor->toWebCLImpl();
    return impl->getBuildInfo(scriptState, device, name, exceptionState);
}

void WebCLProgramAdaptor::build(ExceptionState& exceptionState)
{
    WebCLProgram* impl = toWebCLImpl();
    impl->build(emptyString(), nullptr, exceptionState);
}

void WebCLProgramAdaptor::build(const Nullable<HeapVector<Member<WebCLDeviceAdaptor>>>& deviceAdaptors, ExceptionState& exceptionState)
{
    WebCLProgram* impl = toWebCLImpl();
    Vector<RefPtr<WebCLDevice>> devices;
    if (deviceAdaptors) {
        for (auto deviceAdaptor : deviceAdaptors.get())
            devices.append(deviceAdaptor->toWebCLImpl());
    }
    impl->build(devices, emptyString(), nullptr, exceptionState);
}

void WebCLProgramAdaptor::build(const Nullable<HeapVector<Member<WebCLDeviceAdaptor>>>& deviceAdaptors, const String& options, WebCLCallback* whenFinished, ExceptionState& exceptionState)
{
    WebCLProgram* impl = toWebCLImpl();
    Vector<RefPtr<WebCLDevice>> devices;
    if (deviceAdaptors) {
        for (auto deviceAdaptor : deviceAdaptors.get())
            devices.append(deviceAdaptor->toWebCLImpl());
    }
    impl->build(devices, options, whenFinished, exceptionState);
}

WebCLKernelAdaptor* WebCLProgramAdaptor::createKernel(const String& kernelName, ExceptionState& exceptionState)
{
    WebCLProgram* impl = toWebCLImpl();
    RefPtr<WebCLKernel> kernel = impl->createKernel(kernelName, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return kernel->toWebCLAdaptor();
}

HeapVector<Member<WebCLKernelAdaptor>> WebCLProgramAdaptor::createKernelsInProgram(ExceptionState& exceptionState)
{
    WebCLProgram* impl = toWebCLImpl();
    Vector<RefPtr<WebCLKernel>> kernels = impl->createKernelsInProgram(exceptionState);
    if (exceptionState.hadException())
        return HeapVector<Member<WebCLKernelAdaptor>>();
    HeapVector<Member<WebCLKernelAdaptor>> kernelAdaptors;
    for (auto kernel : kernels)
        kernelAdaptors.append(kernel->toWebCLAdaptor());
    return kernelAdaptors;
}

void WebCLProgramAdaptor::release()
{
    WebCLProgram* impl = toWebCLImpl();
    impl->release();
}

} // namespace blink
