/*
 * Copyright (C) 2014 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(ASYNC_SCROLLING)

#include "ScrollingStateTree.h"
#include "ScrollingTree.h"
#include <wtf/PassRefPtr.h>
#include <wtf/RefPtr.h>

namespace WebCore {

class AsyncScrollingCoordinator;

class ScrollingTreeIOS : public ScrollingTree {
public:
    static Ref<ScrollingTreeIOS> create(AsyncScrollingCoordinator*);
    virtual ~ScrollingTreeIOS();

    // No wheel events on iOS
    void handleWheelEvent(const PlatformWheelEvent&) override { }
    EventResult tryToHandleWheelEvent(const PlatformWheelEvent&) override { return DidNotHandleEvent; }

    void invalidate() override;

private:
    explicit ScrollingTreeIOS(AsyncScrollingCoordinator*);
    bool isScrollingTreeIOS() const override { return true; }

    PassRefPtr<ScrollingTreeNode> createScrollingTreeNode(ScrollingNodeType, ScrollingNodeID) override;

    void scrollingTreeNodeDidScroll(ScrollingNodeID, const FloatPoint& scrollPosition, const Optional<FloatPoint>& layoutViewportOrigin, ScrollingLayerPositionAction = ScrollingLayerPositionAction::Sync) override;

    void currentSnapPointIndicesDidChange(WebCore::ScrollingNodeID, unsigned horizontal, unsigned vertical) override;

    FloatRect fixedPositionRect() override;

    RefPtr<AsyncScrollingCoordinator> m_scrollingCoordinator;
};

} // namespace WebCore

SPECIALIZE_TYPE_TRAITS_SCROLLING_TREE(WebCore::ScrollingTreeIOS, isScrollingTreeIOS())

#endif // ENABLE(ASYNC_SCROLLING)
