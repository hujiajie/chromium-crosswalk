// Copyright (C) 2011 Samsung Electronics Corporation. All rights reserved.
// Copyright (C) 2015 Intel Corporation All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLMemoryObject_h
#define WebCLMemoryObject_h

#include "core/webcl/WebCLException.h"
#include "modules/webcl/WebCLConfig.h"
#include "modules/webcl/WebCLObject.h"
#include "modules/webcl/WebCLOpenCL.h"

#include <wtf/PassRefPtr.h>
#include <wtf/RefCounted.h>

namespace blink {

class ExceptionState;
class WebCL;
class WebCLContext;

class WebCLMemoryObject : public WebCLObject, public ScriptWrappable {
    DEFINE_WRAPPERTYPEINFO();
public:
    ~WebCLMemoryObject() override;
    static PassRefPtr<WebCLMemoryObject> create(cl_mem, PassRefPtr<WebCLContext>);

    ScriptValue getInfo(ScriptState*, int, ExceptionState&);
    void release() override;

    cl_mem getMem() const { return m_clMem; }
    bool isReleased() const { return !m_clMem; }

    template<typename T>
    int getInfo(unsigned name, T& info)
    {
        ASSERT(!isReleased());

        int status = getInfoCustom(name, info);
        if (status != WebCLException::INVALID_VALUE)
            return status;

        return clGetMemObjectInfo(m_clMem, name, sizeof(T), &info, nullptr);
    }
    PassRefPtr<WebCLMemoryObject> associatedMemObject();

protected:
    WebCLMemoryObject(cl_mem, PassRefPtr<WebCLContext>, WebCLMemoryObject* parentBuffer = nullptr);

    template<typename T>
    int getInfoCustom(unsigned name, T& info)
    {
        return WebCLException::INVALID_VALUE;
    }

    WebCLMemoryObject* m_parentMemObject;
    cl_mem m_clMem;
};

} // namespace blink

#endif // WebCLMemoryObject_h
