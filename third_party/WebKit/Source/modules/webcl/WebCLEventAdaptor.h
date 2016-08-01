// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLEventAdaptor_h
#define WebCLEventAdaptor_h

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/Nullable.h"
#include "bindings/core/v8/ScriptValue.h"
#include "bindings/core/v8/ScriptWrappable.h"
#include "bindings/core/v8/V8Binding.h"
#include "modules/webcl/WebCLScriptWrappableAdaptor.h"
#include "platform/heap/Handle.h"

namespace blink {

class ScriptState;
class V8WebCLEvent;
class WebCLCallback;
class WebCLEvent;

class WebCLEventAdaptor : public GarbageCollectedFinalized<WebCLEventAdaptor>, public WebCLScriptWrappableAdaptor<WebCLEvent>, public ScriptWrappable {
    DEFINE_WRAPPERTYPEINFO();
public:
    static WebCLEventAdaptor* create();
    static WebCLEventAdaptor* create(WebCLEvent*);
    virtual ~WebCLEventAdaptor();

    ScriptValue getInfo(ScriptState*, unsigned name, ExceptionState&);
    ScriptValue getProfilingInfo(ScriptState*, unsigned name, ExceptionState&);
    void setCallback(unsigned commandExecCallbackType, WebCLCallback*, ExceptionState&);
    void release();

    DEFINE_INLINE_VIRTUAL_TRACE() { }

protected:
    WebCLEventAdaptor(WebCLEvent*);
};

// It seems that the binding generator has limited support for the 'ImplementedAs'
// IDL attribute that 'WebCLEvent' is sometimes misused instead of 'WebCLEventAdaptor'.
// The following works as an ugly hack to make the compiler happy.

template<>
class HeapVector<Member<WebCLEvent>> {
public:
    explicit HeapVector(const HeapVector<Member<WebCLEventAdaptor>>&);
    operator HeapVector<Member<WebCLEventAdaptor>>();
    operator Nullable<HeapVector<Member<WebCLEventAdaptor>>>();

private:
    PersistentHeapVector<Member<WebCLEventAdaptor>> m_eventAdaptors;
};

template<>
HeapVector<Member<WebCLEvent>> toMemberNativeArray<WebCLEvent, V8WebCLEvent>(v8::Local<v8::Value>, int argumentIndex, v8::Isolate*, ExceptionState&);

} // namespace blink

#endif // WebCLEventAdaptor_h
