// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLKernelArgInfoAdaptor_h
#define WebCLKernelArgInfoAdaptor_h

#include "bindings/core/v8/ScriptWrappable.h"
#include "modules/webcl/WebCLScriptWrappableAdaptor.h"
#include "platform/heap/Handle.h"
#include "wtf/text/WTFString.h"

namespace blink {

class WebCLKernelArgInfo;

class WebCLKernelArgInfoAdaptor final : public GarbageCollectedFinalized<WebCLKernelArgInfoAdaptor>, public WebCLScriptWrappableAdaptor<WebCLKernelArgInfo>, public ScriptWrappable {
    DEFINE_WRAPPERTYPEINFO();
public:
    static WebCLKernelArgInfoAdaptor* create(WebCLKernelArgInfo*);
    ~WebCLKernelArgInfoAdaptor();

    const String& name();
    const String& typeName();
    const String& addressQualifier();
    const String& accessQualifier();

    DEFINE_INLINE_TRACE() { }

private:
    WebCLKernelArgInfoAdaptor(WebCLKernelArgInfo*);
};

} // namespace blink

#endif // WebCLKernelArgInfoAdaptor_h
