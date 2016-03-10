// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLCommandDataHolder_h
#define WebCLCommandDataHolder_h

#include "platform/heap/Handle.h"
#include "wtf/PassOwnPtr.h"
#include "wtf/PassRefPtr.h"
#include "wtf/RefPtr.h"
#include "wtf/Vector.h"

namespace blink {

class DOMArrayBufferView;
class HTMLCanvasElement;
class HTMLImageElement;
class ImageData;
class WebCLBuffer;
class WebCLEvent;

class WebCLWriteBufferCommandDataHolder {
public:
    template<typename T>
    static PassOwnPtr<WebCLWriteBufferCommandDataHolder> create(PassRefPtr<WebCLBuffer> buffer,
        T* hostPtr, const Vector<RefPtr<WebCLEvent>>& eventWaitList)
    {
        return adoptPtr(new WebCLWriteBufferCommandDataHolder(buffer, hostPtr, eventWaitList));
    }

    template<typename T>
    static PassOwnPtr<WebCLWriteBufferCommandDataHolder> create(PassRefPtr<WebCLBuffer> buffer,
        PassRefPtr<T> hostPtr, const Vector<RefPtr<WebCLEvent>>& eventWaitList)
    {
        return adoptPtr(new WebCLWriteBufferCommandDataHolder(buffer, hostPtr, eventWaitList));
    }

#if ENABLE(OILPAN)
    template<typename T>
    static PassOwnPtr<WebCLWriteBufferCommandDataHolder> create(PassRefPtr<WebCLBuffer> buffer,
        PassRefPtrWillBeRawPtr<T> hostPtr, const Vector<RefPtr<WebCLEvent>>& eventWaitList)
    {
        return adoptPtrWillBeNoop(new WebCLWriteBufferCommandDataHolder(buffer, hostPtr, eventWaitList));
    }
#endif

    ~WebCLWriteBufferCommandDataHolder();

private:
    WebCLWriteBufferCommandDataHolder(PassRefPtr<WebCLBuffer>, PassRefPtr<DOMArrayBufferView>,
        const Vector<RefPtr<WebCLEvent>>&);
    WebCLWriteBufferCommandDataHolder(PassRefPtr<WebCLBuffer>, PassRefPtrWillBeRawPtr<HTMLCanvasElement>,
        const Vector<RefPtr<WebCLEvent>>&);
    WebCLWriteBufferCommandDataHolder(PassRefPtr<WebCLBuffer>, PassRefPtrWillBeRawPtr<HTMLImageElement>,
        const Vector<RefPtr<WebCLEvent>>&);
    WebCLWriteBufferCommandDataHolder(PassRefPtr<WebCLBuffer>, ImageData*,
        const Vector<RefPtr<WebCLEvent>>&);

    RefPtr<WebCLBuffer> m_buffer;

    // Only one of the following should ever be in use at any given time.
    RefPtr<DOMArrayBufferView> m_arrayBufferView;
    RefPtrWillBePersistent<HTMLCanvasElement> m_htmlCanvasElement;
    RefPtrWillBePersistent<HTMLImageElement> m_htmlImageElement;
    Persistent<ImageData> m_imageData;

    Vector<RefPtr<WebCLEvent>> m_eventWaitList;
};

class WebCLCommandDataHolder {
public:
    template<typename T>
    static PassOwnPtr<WebCLCommandDataHolder> create(PassOwnPtr<T> data)
    {
        return adoptPtr(new WebCLCommandDataHolder(data));
    }
    ~WebCLCommandDataHolder();

private:
    explicit WebCLCommandDataHolder(PassOwnPtr<WebCLWriteBufferCommandDataHolder>);

    // Only one of the following should ever be in use at any given time.
    OwnPtr<WebCLWriteBufferCommandDataHolder> m_writeBufferCommandDataHolder;
};

} // namespace blink

#endif // WebCLCommandDataHolder_h
