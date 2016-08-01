// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/webcl/WebCLPlatformAdaptor.h"

#include "modules/webcl/WebCLDevice.h"
#include "modules/webcl/WebCLDeviceAdaptor.h"
#include "modules/webcl/WebCLPlatform.h"
#include "wtf/RefPtr.h"

namespace blink {

WebCLPlatformAdaptor* WebCLPlatformAdaptor::create(WebCLPlatform* impl)
{
    return new WebCLPlatformAdaptor(impl);
}

WebCLPlatformAdaptor::WebCLPlatformAdaptor(WebCLPlatform* impl)
    : WebCLScriptWrappableAdaptor<WebCLPlatform>(impl)
{
}

WebCLPlatformAdaptor::~WebCLPlatformAdaptor()
{
}

ScriptValue WebCLPlatformAdaptor::getInfo(ScriptState* scriptState, unsigned name, ExceptionState& exceptionState)
{
    WebCLPlatform* impl = toWebCLImpl();
    return impl->getInfo(scriptState, name, exceptionState);
}

HeapVector<Member<WebCLDeviceAdaptor>> WebCLPlatformAdaptor::getDevices(ExceptionState& exceptionState)
{
    WebCLPlatform* impl = toWebCLImpl();
    Vector<RefPtr<WebCLDevice>> devices = impl->getDevices(exceptionState);
    if (exceptionState.hadException())
        return HeapVector<Member<WebCLDeviceAdaptor>>();
    HeapVector<Member<WebCLDeviceAdaptor>> deviceAdaptors;
    for (auto device : devices)
        deviceAdaptors.append(device->toWebCLAdaptor());
    return deviceAdaptors;
}

HeapVector<Member<WebCLDeviceAdaptor>> WebCLPlatformAdaptor::getDevices(unsigned deviceType, ExceptionState& exceptionState)
{
    WebCLPlatform* impl = toWebCLImpl();
    Vector<RefPtr<WebCLDevice>> devices = impl->getDevices(deviceType, exceptionState);
    if (exceptionState.hadException())
        return HeapVector<Member<WebCLDeviceAdaptor>>();
    HeapVector<Member<WebCLDeviceAdaptor>> deviceAdaptors;
    for (auto device : devices)
        deviceAdaptors.append(device->toWebCLAdaptor());
    return deviceAdaptors;
}

Nullable<Vector<String>> WebCLPlatformAdaptor::getSupportedExtensions()
{
    WebCLPlatform* impl = toWebCLImpl();
    return impl->getSupportedExtensions();
}

bool WebCLPlatformAdaptor::enableExtension(const String& extensionName)
{
    WebCLPlatform* impl = toWebCLImpl();
    return impl->enableExtension(extensionName);
}

} // namespace blink
