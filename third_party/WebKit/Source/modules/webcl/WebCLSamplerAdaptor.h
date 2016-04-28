// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLSamplerAdaptor_h
#define WebCLSamplerAdaptor_h

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/ScriptValue.h"
#include "bindings/core/v8/ScriptWrappable.h"
#include "modules/webcl/WebCLScriptWrappableAdaptor.h"
#include "platform/heap/Handle.h"

namespace blink {

class ScriptState;
class WebCLSampler;

class WebCLSamplerAdaptor final : public GarbageCollectedFinalized<WebCLSamplerAdaptor>, public WebCLScriptWrappableAdaptor<WebCLSampler>, public ScriptWrappable {
    DEFINE_WRAPPERTYPEINFO();
public:
    static WebCLSamplerAdaptor* create(WebCLSampler*);
    ~WebCLSamplerAdaptor();

    ScriptValue getInfo(ScriptState*, unsigned name, ExceptionState&);
    void release();

    DEFINE_INLINE_TRACE() { }

private:
    WebCLSamplerAdaptor(WebCLSampler*);
};

} // namespace blink

#endif // WebCLSamplerAdaptor_h
