// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLMemoryObjectAdaptor_h
#define WebCLMemoryObjectAdaptor_h

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/ScriptValue.h"
#include "bindings/core/v8/ScriptWrappable.h"
#include "modules/webcl/WebCLScriptWrappableAdaptor.h"
#include "platform/heap/Handle.h"

namespace blink {

class ScriptState;
class WebCLMemoryObject;

class WebCLMemoryObjectAdaptor : public GarbageCollectedFinalized<WebCLMemoryObjectAdaptor>, public WebCLScriptWrappableAdaptor<WebCLMemoryObject>, public ScriptWrappable {
    DEFINE_WRAPPERTYPEINFO();
public:
    static WebCLMemoryObjectAdaptor* create(WebCLMemoryObject*);
    virtual ~WebCLMemoryObjectAdaptor();

    ScriptValue getInfo(ScriptState*, unsigned name, ExceptionState&);
    void release();

    DEFINE_INLINE_VIRTUAL_TRACE() { }

protected:
    WebCLMemoryObjectAdaptor(WebCLMemoryObject*);
};

} // namespace blink

#endif // WebCLMemoryObjectAdaptor_h
