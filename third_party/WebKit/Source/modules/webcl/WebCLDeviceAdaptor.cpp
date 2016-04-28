// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/webcl/WebCLDeviceAdaptor.h"

#include "bindings/modules/v8/V8WebCLDevice.h"
#include "modules/webcl/WebCLDevice.h"

namespace blink {

WebCLDeviceAdaptor* WebCLDeviceAdaptor::create(WebCLDevice* impl)
{
    return new WebCLDeviceAdaptor(impl);
}

WebCLDeviceAdaptor::WebCLDeviceAdaptor(WebCLDevice* impl)
    : WebCLScriptWrappableAdaptor<WebCLDevice>(impl)
{
}

WebCLDeviceAdaptor::~WebCLDeviceAdaptor()
{
}

ScriptValue WebCLDeviceAdaptor::getInfo(ScriptState* scriptState, unsigned name, ExceptionState& exceptionState)
{
    WebCLDevice* impl = toWebCLImpl();
    return impl->getInfo(scriptState, name, exceptionState);
}

Nullable<Vector<String>> WebCLDeviceAdaptor::getSupportedExtensions()
{
    WebCLDevice* impl = toWebCLImpl();
    return impl->getSupportedExtensions();
}

bool WebCLDeviceAdaptor::enableExtension(const String& extensionName)
{
    WebCLDevice* impl = toWebCLImpl();
    return impl->enableExtension(extensionName);
}

HeapVector<Member<WebCLDevice>>::HeapVector(const HeapVector<Member<WebCLDeviceAdaptor>>& deviceAdaptors)
    : m_deviceAdaptors(deviceAdaptors)
{
}

HeapVector<Member<WebCLDevice>>::operator HeapVector<Member<WebCLDeviceAdaptor>>()
{
    return m_deviceAdaptors;
}

HeapVector<Member<WebCLDevice>>::operator Nullable<HeapVector<Member<WebCLDeviceAdaptor>>>()
{
    return m_deviceAdaptors;
}

template<>
HeapVector<Member<WebCLDevice>> toMemberNativeArray<WebCLDevice>(v8::Local<v8::Value> value, int argumentIndex, v8::Isolate* isolate, ExceptionState& exceptionState)
{
    HeapVector<Member<WebCLDeviceAdaptor>> deviceAdaptors = toMemberNativeArray<WebCLDeviceAdaptor>(value, argumentIndex, isolate, exceptionState);
    return HeapVector<Member<WebCLDevice>>(deviceAdaptors);
}

} // namespace blink
