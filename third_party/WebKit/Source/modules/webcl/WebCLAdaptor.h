// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLAdaptor_h
#define WebCLAdaptor_h

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/Nullable.h"
#include "bindings/core/v8/ScriptWrappable.h"
#include "modules/webcl/WebCLScriptWrappableAdaptor.h"
#include "platform/heap/Handle.h"
#include "wtf/Vector.h"
#include "wtf/text/WTFString.h"

namespace blink {

class WebCL;
class WebCLCallback;
class WebCLContextAdaptor;
class WebCLDeviceAdaptor;
class WebCLEventAdaptor;
class WebCLPlatformAdaptor;

class WebCLAdaptor final : public GarbageCollectedFinalized<WebCLAdaptor>, public WebCLScriptWrappableAdaptor<WebCL>, public ScriptWrappable {
    DEFINE_WRAPPERTYPEINFO();
public:
    static WebCLAdaptor* create(WebCL*);
    ~WebCLAdaptor();

    HeapVector<Member<WebCLPlatformAdaptor>> getPlatforms(ExceptionState&);
    WebCLContextAdaptor* createContext(ExceptionState&);
    WebCLContextAdaptor* createContext(unsigned deviceType, ExceptionState&);
    WebCLContextAdaptor* createContext(WebCLPlatformAdaptor*, ExceptionState&);
    WebCLContextAdaptor* createContext(WebCLPlatformAdaptor*, unsigned deviceType, ExceptionState&);
    WebCLContextAdaptor* createContext(WebCLDeviceAdaptor*, ExceptionState&);
    WebCLContextAdaptor* createContext(const HeapVector<Member<WebCLDeviceAdaptor>>&, ExceptionState&);
    Nullable<Vector<String>> getSupportedExtensions();
    bool enableExtension(const String& extensionName);
    void waitForEvents(const HeapVector<Member<WebCLEventAdaptor>>&, WebCLCallback*, ExceptionState&);
    void releaseAll();

    DEFINE_INLINE_TRACE() { }

private:
    WebCLAdaptor(WebCL*);
};

} // namespace blink

#endif // WebCLAdaptor_h
