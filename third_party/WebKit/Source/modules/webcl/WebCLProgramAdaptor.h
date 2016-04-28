// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLProgramAdaptor_h
#define WebCLProgramAdaptor_h

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/Nullable.h"
#include "bindings/core/v8/ScriptValue.h"
#include "bindings/core/v8/ScriptWrappable.h"
#include "modules/webcl/WebCLScriptWrappableAdaptor.h"
#include "platform/heap/Handle.h"
#include "wtf/text/WTFString.h"

namespace blink {

class ScriptState;
class WebCLCallback;
class WebCLDeviceAdaptor;
class WebCLKernelAdaptor;
class WebCLProgram;

class WebCLProgramAdaptor final : public GarbageCollectedFinalized<WebCLProgramAdaptor>, public WebCLScriptWrappableAdaptor<WebCLProgram>, public ScriptWrappable {
    DEFINE_WRAPPERTYPEINFO();
public:
    static WebCLProgramAdaptor* create(WebCLProgram*);
    ~WebCLProgramAdaptor();

    ScriptValue getInfo(ScriptState*, unsigned name, ExceptionState&);
    ScriptValue getBuildInfo(ScriptState*, WebCLDeviceAdaptor*, unsigned name, ExceptionState&);
    void build(ExceptionState&);
    void build(const Nullable<HeapVector<Member<WebCLDeviceAdaptor>>>&, ExceptionState&);
    void build(const Nullable<HeapVector<Member<WebCLDeviceAdaptor>>>&, const String& options, WebCLCallback*, ExceptionState&);
    WebCLKernelAdaptor* createKernel(const String& kernelName, ExceptionState&);
    HeapVector<Member<WebCLKernelAdaptor>> createKernelsInProgram(ExceptionState&);
    void release();

    DEFINE_INLINE_TRACE() { }

private:
    WebCLProgramAdaptor(WebCLProgram*);
};

} // namespace blink

#endif // WebCLProgramAdaptor_h
