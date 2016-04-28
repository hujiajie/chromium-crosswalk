// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLPlatformAdaptor_h
#define WebCLPlatformAdaptor_h

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/Nullable.h"
#include "bindings/core/v8/ScriptValue.h"
#include "bindings/core/v8/ScriptWrappable.h"
#include "modules/webcl/WebCLScriptWrappableAdaptor.h"
#include "platform/heap/Handle.h"
#include "wtf/Vector.h"
#include "wtf/text/WTFString.h"

namespace blink {

class ScriptState;
class WebCLDeviceAdaptor;
class WebCLPlatform;

class WebCLPlatformAdaptor final : public GarbageCollectedFinalized<WebCLPlatformAdaptor>, public WebCLScriptWrappableAdaptor<WebCLPlatform>, public ScriptWrappable {
    DEFINE_WRAPPERTYPEINFO();
public:
    static WebCLPlatformAdaptor* create(WebCLPlatform*);
    ~WebCLPlatformAdaptor();

    ScriptValue getInfo(ScriptState*, unsigned name, ExceptionState&);
    HeapVector<Member<WebCLDeviceAdaptor>> getDevices(ExceptionState&);
    HeapVector<Member<WebCLDeviceAdaptor>> getDevices(unsigned deviceType, ExceptionState&);
    Nullable<Vector<String>> getSupportedExtensions();
    bool enableExtension(const String& extensionName);

    DEFINE_INLINE_TRACE() { }

private:
    WebCLPlatformAdaptor(WebCLPlatform*);
};

} // namespace blink

#endif // WebCLPlatformAdaptor_h
