/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012-2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include <list>
#include <vector>
#include "pxcsession.h"

class UtilCmdLine {
public:

    UtilCmdLine(PXCSession *session, pxcUID iuid=0);
    bool Parse(const pxcCHAR *options, int argc, pxcCHAR *argv[]);

    std::list<std::pair<PXCSizeU32,pxcU32> >   m_csize;
    std::list<std::pair<PXCSizeU32,pxcU32> >   m_dsize;
    pxcUID      m_iuid;
    pxcU32      m_nframes;
    pxcCHAR     *m_sdname;
    pxcU32      m_nchannels;
    pxcU32      m_sampleRate;
    pxcF32      m_volume;
    std::vector<pxcCHAR*> m_grammar;
    pxcCHAR     *m_recordedFile;
    pxcBool     m_realtime;
    pxcCHAR     *m_ttstext;
    pxcEnum     m_language;
    bool        m_bRecord;
    pxcCHAR     *m_traceFile;
    pxcU32      m_eos;
	bool		m_bFace;
	bool		m_bGesture;
	bool		m_bVoice;

protected:
    PXCSession      *m_session;
};

