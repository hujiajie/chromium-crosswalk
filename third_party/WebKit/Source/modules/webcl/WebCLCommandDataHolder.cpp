// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/webcl/WebCLCommandDataHolder.h"

#include "core/dom/DOMArrayBufferView.h"
#include "core/html/HTMLCanvasElement.h"
#include "core/html/HTMLImageElement.h"
#include "core/html/ImageData.h"
#include "modules/webcl/WebCLBuffer.h"
#include "modules/webcl/WebCLEvent.h"

namespace blink {

WebCLWriteBufferCommandDataHolder::WebCLWriteBufferCommandDataHolder(
    PassRefPtr<WebCLBuffer> buffer, PassRefPtr<DOMArrayBufferView> arrayBufferView,
    const Vector<RefPtr<WebCLEvent>>& eventWaitList)
    : m_buffer(buffer)
    , m_arrayBufferView(arrayBufferView)
    , m_eventWaitList(eventWaitList)
{
}

WebCLWriteBufferCommandDataHolder::WebCLWriteBufferCommandDataHolder(
    PassRefPtr<WebCLBuffer> buffer, PassRefPtrWillBeRawPtr<HTMLCanvasElement> htmlCanvasElement,
    const Vector<RefPtr<WebCLEvent>>& eventWaitList)
    : m_buffer(buffer)
    , m_htmlCanvasElement(htmlCanvasElement)
    , m_eventWaitList(eventWaitList)
{
}

WebCLWriteBufferCommandDataHolder::WebCLWriteBufferCommandDataHolder(
    PassRefPtr<WebCLBuffer> buffer, PassRefPtrWillBeRawPtr<HTMLImageElement> htmlImageElement,
    const Vector<RefPtr<WebCLEvent>>& eventWaitList)
    : m_buffer(buffer)
    , m_htmlImageElement(htmlImageElement)
    , m_eventWaitList(eventWaitList)
{
}

WebCLWriteBufferCommandDataHolder::WebCLWriteBufferCommandDataHolder(
    PassRefPtr<WebCLBuffer> buffer, ImageData* imageData,
    const Vector<RefPtr<WebCLEvent>>& eventWaitList)
    : m_buffer(buffer)
    , m_imageData(imageData)
    , m_eventWaitList(eventWaitList)
{
}

WebCLWriteBufferCommandDataHolder::~WebCLWriteBufferCommandDataHolder()
{
}

WebCLCommandDataHolder::WebCLCommandDataHolder(PassOwnPtr<WebCLWriteBufferCommandDataHolder> data)
    : m_writeBufferCommandDataHolder(data)
{
}

WebCLCommandDataHolder::~WebCLCommandDataHolder()
{
}

} // namespace blink
