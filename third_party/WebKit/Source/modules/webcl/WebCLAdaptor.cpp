// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/webcl/WebCLAdaptor.h"

#include "modules/webcl/WebCL.h"
#include "modules/webcl/WebCLCallback.h"
#include "modules/webcl/WebCLContext.h"
#include "modules/webcl/WebCLContextAdaptor.h"
#include "modules/webcl/WebCLDevice.h"
#include "modules/webcl/WebCLDeviceAdaptor.h"
#include "modules/webcl/WebCLEvent.h"
#include "modules/webcl/WebCLEventAdaptor.h"
#include "modules/webcl/WebCLPlatform.h"
#include "modules/webcl/WebCLPlatformAdaptor.h"
#include "wtf/RefPtr.h"

namespace blink {

WebCLAdaptor* WebCLAdaptor::create(WebCL* impl)
{
    return new WebCLAdaptor(impl);
}

WebCLAdaptor::WebCLAdaptor(WebCL* impl)
    : WebCLScriptWrappableAdaptor<WebCL>(impl)
{
}

WebCLAdaptor::~WebCLAdaptor()
{
}

HeapVector<Member<WebCLPlatformAdaptor>> WebCLAdaptor::getPlatforms(ExceptionState& exceptionState)
{
    WebCL* impl = toWebCLImpl();
    Vector<RefPtr<WebCLPlatform>> platforms = impl->getPlatforms(exceptionState);
    if (exceptionState.hadException())
        return HeapVector<Member<WebCLPlatformAdaptor>>();
    HeapVector<Member<WebCLPlatformAdaptor>> platformAdaptors;
    for (auto platform : platforms)
        platformAdaptors.append(platform->toWebCLAdaptor());
    return platformAdaptors;
}

WebCLContextAdaptor* WebCLAdaptor::createContext(ExceptionState& exceptionState)
{
    WebCL* impl = toWebCLImpl();
    RefPtr<WebCLContext> context = impl->createContext(exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return context->toWebCLAdaptor();
}

WebCLContextAdaptor* WebCLAdaptor::createContext(unsigned deviceType, ExceptionState& exceptionState)
{
    WebCL* impl = toWebCLImpl();
    RefPtr<WebCLContext> context = impl->createContext(deviceType, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return context->toWebCLAdaptor();
}

WebCLContextAdaptor* WebCLAdaptor::createContext(WebCLPlatformAdaptor* platformAdaptor, ExceptionState& exceptionState)
{
    WebCL* impl = toWebCLImpl();
    WebCLPlatform* platform = platformAdaptor->toWebCLImpl();
    RefPtr<WebCLContext> context = impl->createContext(platform, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return context->toWebCLAdaptor();
}

WebCLContextAdaptor* WebCLAdaptor::createContext(WebCLPlatformAdaptor* platformAdaptor, unsigned deviceType, ExceptionState& exceptionState)
{
    WebCL* impl = toWebCLImpl();
    WebCLPlatform* platform = platformAdaptor->toWebCLImpl();
    RefPtr<WebCLContext> context = impl->createContext(platform, deviceType, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return context->toWebCLAdaptor();
}

WebCLContextAdaptor* WebCLAdaptor::createContext(WebCLDeviceAdaptor* deviceAdaptor, ExceptionState& exceptionState)
{
    WebCL* impl = toWebCLImpl();
    WebCLDevice* device = deviceAdaptor->toWebCLImpl();
    RefPtr<WebCLContext> context = impl->createContext(device, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return context->toWebCLAdaptor();
}

WebCLContextAdaptor* WebCLAdaptor::createContext(const HeapVector<Member<WebCLDeviceAdaptor>>& deviceAdaptors, ExceptionState& exceptionState)
{
    WebCL* impl = toWebCLImpl();
    Vector<RefPtr<WebCLDevice>> devices;
    for (auto deviceAdaptor : deviceAdaptors)
        devices.append(deviceAdaptor->toWebCLImpl());
    RefPtr<WebCLContext> context = impl->createContext(devices, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return context->toWebCLAdaptor();
}

Nullable<Vector<String>> WebCLAdaptor::getSupportedExtensions()
{
    WebCL* impl = toWebCLImpl();
    return impl->getSupportedExtensions();
}

bool WebCLAdaptor::enableExtension(const String& extensionName)
{
    WebCL* impl = toWebCLImpl();
    return impl->enableExtension(extensionName);
}

void WebCLAdaptor::waitForEvents(const HeapVector<Member<WebCLEventAdaptor>>& eventAdaptors, WebCLCallback* callback, ExceptionState& exceptionState)
{
    WebCL* impl = toWebCLImpl();
    Vector<RefPtr<WebCLEvent>> events;
    for (auto eventAdaptor : eventAdaptors)
        events.append(eventAdaptor->toWebCLImpl());
    impl->waitForEvents(events, callback, exceptionState);
}

void WebCLAdaptor::releaseAll()
{
    WebCL* impl = toWebCLImpl();
    impl->releaseAll();
}

} // namespace blink
