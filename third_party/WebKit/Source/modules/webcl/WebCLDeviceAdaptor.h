// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLDeviceAdaptor_h
#define WebCLDeviceAdaptor_h

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/Nullable.h"
#include "bindings/core/v8/ScriptValue.h"
#include "bindings/core/v8/ScriptWrappable.h"
#include "bindings/core/v8/V8Binding.h"
#include "modules/webcl/WebCLScriptWrappableAdaptor.h"
#include "platform/heap/Handle.h"
#include "wtf/Vector.h"
#include "wtf/text/WTFString.h"

namespace blink {

class ScriptState;
class V8WebCLDevice;
class WebCLDevice;

class WebCLDeviceAdaptor final : public GarbageCollectedFinalized<WebCLDeviceAdaptor>, public WebCLScriptWrappableAdaptor<WebCLDevice>, public ScriptWrappable {
    DEFINE_WRAPPERTYPEINFO();
public:
    static WebCLDeviceAdaptor* create(WebCLDevice*);
    ~WebCLDeviceAdaptor();

    ScriptValue getInfo(ScriptState*, unsigned name, ExceptionState&);
    Nullable<Vector<String>> getSupportedExtensions();
    bool enableExtension(const String& extensionName);

    DEFINE_INLINE_TRACE() { }

private:
    WebCLDeviceAdaptor(WebCLDevice*);
};

// It seems that the binding generator has limited support for the 'ImplementedAs'
// IDL attribute that 'WebCLDevice' is sometimes misused instead of 'WebCLDeviceAdaptor'.
// The following works as an ugly hack to make the compiler happy.

template<>
class HeapVector<Member<WebCLDevice>> {
public:
    explicit HeapVector(const HeapVector<Member<WebCLDeviceAdaptor>>&);
    operator HeapVector<Member<WebCLDeviceAdaptor>>();
    operator Nullable<HeapVector<Member<WebCLDeviceAdaptor>>>();

private:
    PersistentHeapVector<Member<WebCLDeviceAdaptor>> m_deviceAdaptors;
};

template<>
HeapVector<Member<WebCLDevice>> toMemberNativeArray<WebCLDevice, V8WebCLDevice>(v8::Local<v8::Value>, int argumentIndex, v8::Isolate*, ExceptionState&);

} // namespace blink

#endif // WebCLDeviceAdaptor_h
