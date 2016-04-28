// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLScriptWrappableAdaptor_h
#define WebCLScriptWrappableAdaptor_h

#include "wtf/RefPtr.h"

namespace blink {

template<typename T>
class WebCLScriptWrappableAdaptor {
public:
    template<typename U = T>
    U* toWebCLImpl()
    {
        return static_cast<U*>(m_impl.get());
    }

protected:
    explicit WebCLScriptWrappableAdaptor(T* impl)
    {
        m_impl = impl;
    }
    ~WebCLScriptWrappableAdaptor() { }

private:
    RefPtr<T> m_impl;
};

} // namespace blink

#endif // WebCLScriptWrappableAdaptor_h
