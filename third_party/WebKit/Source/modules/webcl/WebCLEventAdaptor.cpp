// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/webcl/WebCLEventAdaptor.h"

#include "bindings/modules/v8/V8WebCLEvent.h"
#include "modules/webcl/WebCLCallback.h"
#include "modules/webcl/WebCLEvent.h"
#include "wtf/RefPtr.h"

namespace blink {

WebCLEventAdaptor* WebCLEventAdaptor::create()
{
    RefPtr<WebCLEvent> event = WebCLEvent::create();
    return event->toWebCLAdaptor();
}

WebCLEventAdaptor* WebCLEventAdaptor::create(WebCLEvent* impl)
{
    return new WebCLEventAdaptor(impl);
}

WebCLEventAdaptor::WebCLEventAdaptor(WebCLEvent* impl)
    : WebCLScriptWrappableAdaptor<WebCLEvent>(impl)
{
}

WebCLEventAdaptor::~WebCLEventAdaptor()
{
}

ScriptValue WebCLEventAdaptor::getInfo(ScriptState* scriptState, unsigned name, ExceptionState& exceptionState)
{
    WebCLEvent* impl = toWebCLImpl();
    return impl->getInfo(scriptState, name, exceptionState);
}

ScriptValue WebCLEventAdaptor::getProfilingInfo(ScriptState* scriptState, unsigned name, ExceptionState& exceptionState)
{
    WebCLEvent* impl = toWebCLImpl();
    return impl->getProfilingInfo(scriptState, name, exceptionState);
}

void WebCLEventAdaptor::setCallback(unsigned commandExecCallbackType, WebCLCallback* notify, ExceptionState& exceptionState)
{
    WebCLEvent* impl = toWebCLImpl();
    impl->setCallback(commandExecCallbackType, notify, exceptionState);
}

void WebCLEventAdaptor::release()
{
    WebCLEvent* impl = toWebCLImpl();
    impl->release();
}

HeapVector<Member<WebCLEvent>>::HeapVector(const HeapVector<Member<WebCLEventAdaptor>>& eventAdaptors)
    : m_eventAdaptors(eventAdaptors)
{
}

HeapVector<Member<WebCLEvent>>::operator HeapVector<Member<WebCLEventAdaptor>>()
{
    return m_eventAdaptors;
}

HeapVector<Member<WebCLEvent>>::operator Nullable<HeapVector<Member<WebCLEventAdaptor>>>()
{
    return m_eventAdaptors;
}

template<>
HeapVector<Member<WebCLEvent>> toMemberNativeArray<WebCLEvent>(v8::Local<v8::Value> value, int argumentIndex, v8::Isolate* isolate, ExceptionState& exceptionState)
{
    HeapVector<Member<WebCLEventAdaptor>> eventAdaptors = toMemberNativeArray<WebCLEventAdaptor>(value, argumentIndex, isolate, exceptionState);
    return HeapVector<Member<WebCLEvent>>(eventAdaptors);
}

} // namespace blink
