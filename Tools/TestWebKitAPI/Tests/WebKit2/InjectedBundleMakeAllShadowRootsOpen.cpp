/*
 * Copyright (C) 2010,　2016 Apple Inc. All rights reserved.
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

#include "config.h"

#if WK_HAVE_C_SPI

#include "PlatformUtilities.h"
#include "PlatformWebView.h"
#include "Test.h"
#include <WebKit/WKRetainPtr.h>

namespace TestWebKitAPI {

static unsigned testNumber = 0;
static bool done;

static void runJavaScriptAlert(WKPageRef page, WKStringRef alertText, WKFrameRef frame, const void* clientInfo)
{
    ASSERT_NOT_NULL(frame);

    EXPECT_EQ(page, WKFrameGetPage(frame));
    switch (++testNumber) {
    case 1:
        EXPECT_WK_STREQ("PASS: shadowRoot created in injected bundle", alertText);
        break;
    case 2:
        EXPECT_WK_STREQ("PASS: shadowRoot created by normal world", alertText);
        break;
    case 3:
        EXPECT_WK_STREQ("PASS: query method exists", alertText);
        break;
    case 4:
        EXPECT_WK_STREQ("PASS: query method was not present in the normal world", alertText);
        break;
    case 5:
        EXPECT_WK_STREQ("Found:1,2,3,4,5,6", alertText);
        break;
    case 6:
        EXPECT_WK_STREQ("Found:2,3,4", alertText);
        done = true;
        break;
    }
}

TEST(WebKit2, InjectedBundleMakeAllShadowRootOpenTest)
{
    WKRetainPtr<WKPageGroupRef> pageGroup(AdoptWK, WKPageGroupCreateWithIdentifier(WKStringCreateWithUTF8CString("InjectedBundleMakeAllShadowRootOpenTestPageGroup")));

    WKRetainPtr<WKContextRef> context(AdoptWK, Util::createContextForInjectedBundleTest("InjectedBundleMakeAllShadowRootOpenTest", pageGroup.get()));
    PlatformWebView webView(context.get(), pageGroup.get());

    WKPageUIClientV0 uiClient;
    memset(&uiClient, 0, sizeof(uiClient));

    uiClient.base.version = 0;
    uiClient.runJavaScriptAlert = runJavaScriptAlert;

    WKPageSetPageUIClient(webView.page(), &uiClient.base);

    WKRetainPtr<WKURLRef> url(AdoptWK, Util::createURLForResource("closed-shadow-tree-test", "html"));
    WKPageLoadURL(webView.page(), url.get());

    Util::run(&done);
}
    
} // namespace TestWebKitAPI

#endif
