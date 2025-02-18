/*
 * Copyright (C) 2012-2014 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(VIDEO_TRACK)

#include "InbandTextTrack.h"
#include "TextTrackCueGeneric.h"
#include "WebVTTParser.h"

namespace WebCore {

class Document;
class InbandTextTrackPrivate;

class GenericTextTrackCueMap {
public:
    void add(GenericCueData&, TextTrackCueGeneric&);

    void remove(TextTrackCue&);
    void remove(GenericCueData&);

    GenericCueData* find(TextTrackCue&);
    TextTrackCueGeneric* find(GenericCueData&);

private:
    using CueToDataMap = HashMap<RefPtr<TextTrackCue>, RefPtr<GenericCueData>>;
    using CueDataToCueMap = HashMap<RefPtr<GenericCueData>, RefPtr<TextTrackCueGeneric>>;

    CueToDataMap m_cueToDataMap;
    CueDataToCueMap m_dataToCueMap;
};

class InbandGenericTextTrack final : public InbandTextTrack, private WebVTTParserClient {
public:
    static Ref<InbandGenericTextTrack> create(ScriptExecutionContext*, TextTrackClient*, PassRefPtr<InbandTextTrackPrivate>);
    virtual ~InbandGenericTextTrack();

private:
    InbandGenericTextTrack(ScriptExecutionContext*, TextTrackClient*, PassRefPtr<InbandTextTrackPrivate>);

    void addGenericCue(InbandTextTrackPrivate*, PassRefPtr<GenericCueData>) final;
    void updateGenericCue(InbandTextTrackPrivate*, GenericCueData*) final;
    void removeGenericCue(InbandTextTrackPrivate*, GenericCueData*) final;
    ExceptionOr<void> removeCue(TextTrackCue&) final;

    PassRefPtr<TextTrackCueGeneric> createCue(PassRefPtr<GenericCueData>);
    void updateCueFromCueData(TextTrackCueGeneric*, GenericCueData*);

    WebVTTParser& parser();
    void parseWebVTTCueData(InbandTextTrackPrivate*, const ISOWebVTTCue&) final;
    void parseWebVTTFileHeader(InbandTextTrackPrivate*, String) final;

    void newCuesParsed() final;
    void newRegionsParsed() final;
    void fileFailedToParse() final;

    GenericTextTrackCueMap m_cueMap;
    std::unique_ptr<WebVTTParser> m_webVTTParser;
};

} // namespace WebCore

#endif
