/*
 *  Copyright (C) 2013 Nokia Corporation and/or its subsidiary(-ies).
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef RTCDataChannelHandlerMock_h
#define RTCDataChannelHandlerMock_h

#if ENABLE(WEB_RTC)

#include "RTCDataChannelHandler.h"
#include "RTCPeerConnectionHandler.h"
#include "TimerEventBasedMock.h"

namespace WebCore {

class RTCDataChannelHandlerMock final : public RTCDataChannelHandler, public TimerEventBasedMock {
public:
    RTCDataChannelHandlerMock(const String&, const RTCDataChannelInit&);
    virtual ~RTCDataChannelHandlerMock() { }

    void setClient(RTCDataChannelHandlerClient*) override;

    bool sendStringData(const String&) override;
    bool sendRawData(const char*, size_t) override;
    void close() override;

private:
    RTCDataChannelHandlerClient* m_client;

    String m_label;
    String m_protocol;
};

} // namespace WebCore

#endif // ENABLE(WEB_RTC)

#endif // RTCDataChannelHandlerMock_h
