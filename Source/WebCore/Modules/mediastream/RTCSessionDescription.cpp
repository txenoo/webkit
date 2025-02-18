/*
 * Copyright (C) 2012 Google Inc. All rights reserved.
 * Copyright (C) 2013 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer
 *    in the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of Google Inc. nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
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

#include "config.h"
#include "RTCSessionDescription.h"

#if ENABLE(WEB_RTC)

#include "Dictionary.h"
#include "ExceptionCode.h"

namespace WebCore {

static bool parseTypeString(const String& string, RTCSessionDescription::SdpType& outType)
{
    if (string == "offer")
        outType = RTCSessionDescription::SdpType::Offer;
    else if (string == "pranswer")
        outType = RTCSessionDescription::SdpType::Pranswer;
    else if (string == "answer")
        outType = RTCSessionDescription::SdpType::Answer;
    else if (string == "rollback")
        outType = RTCSessionDescription::SdpType::Rollback;
    else
        return false;

    return true;
}

ExceptionOr<Ref<RTCSessionDescription>> RTCSessionDescription::create(const Dictionary& dictionary)
{
    String typeString;
    // Dictionary member type is required.
    if (!dictionary.get("type", typeString))
        return Exception { TypeError };

    SdpType type;
    if (!parseTypeString(typeString, type))
        return Exception { TypeError };

    String sdp;
    dictionary.get("sdp", sdp);

    return adoptRef(*new RTCSessionDescription(type, sdp));
}

Ref<RTCSessionDescription> RTCSessionDescription::create(SdpType type, const String& sdp)
{
    return adoptRef(*new RTCSessionDescription(type, sdp));
}

RTCSessionDescription::RTCSessionDescription(SdpType type, const String& sdp)
    : m_type(type)
    , m_sdp(sdp)
{
}

} // namespace WebCore

#endif // ENABLE(WEB_RTC)
