// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLScriptWrappable_h
#define WebCLScriptWrappable_h

#include "bindings/core/v8/ToV8.h"
#include "modules/webcl/WebCLTypeTraits.h"
#include "platform/heap/Handle.h"
#include "wtf/TypeTraits.h"

namespace blink {

class WebCLScriptWrappableBase {
protected:
    WebCLScriptWrappableBase() { }
    ~WebCLScriptWrappableBase() { }
};

template<typename T>
class WebCLScriptWrappable : public WebCLScriptWrappableBase {
public:
    template<typename U = T>
    typename WebCLTypeTraits<U>::AdaptorType* toWebCLAdaptor()
    {
        if (!m_adaptor)
            m_adaptor = WebCLTypeTraits<U>::AdaptorType::create(static_cast<U*>(this));
        return static_cast<typename WebCLTypeTraits<U>::AdaptorType*>(m_adaptor.get());
    }

protected:
    WebCLScriptWrappable() { }
    ~WebCLScriptWrappable() { }

private:
    WeakPersistent<typename WebCLTypeTraits<T>::AdaptorType> m_adaptor;
};

template<typename T>
inline v8::Local<v8::Value> toV8(T* impl, v8::Local<v8::Object> creationContext, v8::Isolate* isolate, EnsurePtrConvertibleArgDecl(T, WebCLScriptWrappableBase))
{
    return toV8(impl->template toWebCLAdaptor<T>(), creationContext, isolate);
}

} // namespace blink

#endif // WebCLScriptWrappable_h
