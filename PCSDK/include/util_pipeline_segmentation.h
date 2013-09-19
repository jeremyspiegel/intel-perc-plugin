/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "util_pipeline_stackable.h"
#include "pxcsegmentation.h"

class UtilPipelineSegmentation:protected UtilPipelineStackable {
public:

	UtilPipelineSegmentation(UtilPipelineStackable *next=0);

	virtual void  EnableSegmentation(pxcUID iuid=0);
	virtual void  EnableSegmentation(pxcCHAR *name);
    virtual void  PauseSegmentation(bool pause) { m_pause=pause; }
	virtual void  OnSegmentationSetup(PXCSegmentation::ProfileInfo * /*pinfo*/) {}

	virtual PXCSegmentation*	QuerySegmentation(void)	{ return m_segmentation; }
	virtual void	            SetSegmentationBlendMode(PXCSegmentation::BlendMode mode);
	virtual pxcStatus			SetSegmentationBGImage(PXCImage* bgImage);
	virtual	PXCImage*			QuerySegmentationImage();
	virtual PXCImage*			QuerySegmentationBlendedImage();

protected:
	PXCSession *					m_session;
	PXCSegmentation*				m_segmentation;
	PXCSegmentation::ProfileInfo	m_segmentation_pinfo;
	bool							m_segmentation_enabled;
	int								m_segmentation_stream_index;
	PXCSession::ImplDesc			m_segmentation_mdesc;
    bool                            m_pause;

	bool							m_enableBlend;
	PXCSegmentation::BlendMode		m_mode; 
	PXCSmartPtr<PXCImage>			m_segImage;
	PXCSmartPtr<PXCImage>			m_bgImage;
	PXCSmartPtr<PXCImage>			m_blendedImage;

	virtual bool      StackableCreate(PXCSession *session);
	virtual pxcStatus StackableSearchProfiles(UtilCapture *capture, std::vector<PXCCapture::VideoStream::DataDesc*> &vinputs, int vidx, std::vector<PXCCapture::AudioStream::DataDesc*> &ainputs, int aidx);
	virtual bool      StackableSetProfile(UtilCapture *capture);
	virtual bool      StackableReadSample(UtilCapture *capture,PXCSmartArray<PXCImage> &images, PXCSmartSPArray &sps,pxcU32 isps);
	virtual void      StackableCleanUp(void);
};

