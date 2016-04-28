// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLKernelAdaptor_h
#define WebCLKernelAdaptor_h

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/ScriptValue.h"
#include "bindings/core/v8/ScriptWrappable.h"
#include "modules/webcl/WebCLScriptWrappableAdaptor.h"
#include "platform/heap/Handle.h"

namespace blink {

class ScriptState;
class WebCLDeviceAdaptor;
class WebCLKernel;
class WebCLKernelArgInfoAdaptor;

class WebCLKernelAdaptor final : public GarbageCollectedFinalized<WebCLKernelAdaptor>, public WebCLScriptWrappableAdaptor<WebCLKernel>, public ScriptWrappable {
    DEFINE_WRAPPERTYPEINFO();
public:
    static WebCLKernelAdaptor* create(WebCLKernel*);
    ~WebCLKernelAdaptor();

    ScriptValue getInfo(ScriptState*, unsigned name, ExceptionState&);
    ScriptValue getWorkGroupInfo(ScriptState*, WebCLDeviceAdaptor*, unsigned name, ExceptionState&);
    WebCLKernelArgInfoAdaptor* getArgInfo(unsigned index, ExceptionState&);
    void setArg(unsigned index, const ScriptValue&, ExceptionState&);
    void release();

    DEFINE_INLINE_TRACE() { }

private:
    WebCLKernelAdaptor(WebCLKernel*);
};

} // namespace blink

#endif // WebCLKernelAdaptor_h
