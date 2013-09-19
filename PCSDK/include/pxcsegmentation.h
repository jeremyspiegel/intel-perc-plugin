 /*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/

/** @file pxcsegmentation.h
    Defines the PXCSegmentation interface, which programs may use for 3D segmentation.
*/
#pragma once
#include "pxcsession.h"
#include "pxccapture.h"
#pragma warning(push)
#pragma warning(disable:4201) /* nameless structs/unions */

/**
    This class defines a standard interface for 3D segmentation algorithms. 
*/
class PXCSegmentation:public PXCBase {
public:
    PXC_CUID_OVERWRITE(PXC_UID('S','E','G','M'));

	/// Face detection mode
	enum FaceMode {
        FACE_ANY=0,               // No face detection, or enabled by application via SetROIRegions
        FACE_ALG_DEFAULT,         // Use the segmentation algorithm default face detection 
    };

	/// Blend mode for post-segmentation processing
	enum BlendMode {
		BLEND_ANY,                // No blending
		BLEND_BG_WHITE,           // Fill background of color image with WHITE color
		BLEND_BG_BLUE,            // Fill background of color image with BLUE color
		BLEND_BG_IMAGE,           // Blend the segment with a given image as background
		BLEND_ALPHA_CHANNEL,      // Fill segment to alpha channel with gray contour
	};

    /// The Mask data structure
    struct Segment {
        pxcU64  timeStamp;            // Time stamp in 100ns when the mask is corresponding to
        pxcU32  user;                 // reserved; must be zero
        pxcU32  reserved[8];
    };

    /// 3D Segmentation configuration structure
    struct ProfileInfo {
        /// parameters that cannot be modified after initilization
        PXCCapture::VideoStream::DataDesc   inputs;     // Module input requirements
        FaceMode							faceMode;   // Face detection mode

        /// paramters that can be modified during loop (per frame)
        pxcU32		maxDepthThreshold;                  // Maximal depth threshold value in mm
        pxcU32		minDepthThreshold;                  // Minimal depth threshold value in mm
        pxcF32		filterFactor;				        // Value in range [0,1]: higher value for better fingers, lower value for better hair.  
        pxcU32		contourSmoothness;                  // Contour smoothness in # of pixels
        pxcU32		minPerimeter;                       // Minimum length of blob perimeters, in # of pixels.
		BlendMode	blendMode;							// Blending mode

        pxcU32  reserved[32];                           // 0 - reserved for module specific parameters
    };

    /// Get available configuration(s).
    /// pidx        Zero-based index to enumerate all available configurations
    /// pinfo       The configuration structure, to be returned.
    virtual pxcStatus PXCAPI QueryProfile(pxcU32 pidx, ProfileInfo *pinfo)=0;

    /// Get the current working configuration
    /// pinfo       The configuration structure, to be returned.
    pxcStatus __inline QueryProfile(ProfileInfo *pinfo) { return QueryProfile((pxcU32)WORKING_PROFILE,pinfo); }

    /// Set the working configuration
    /// pinfo       The configuration structure
    virtual pxcStatus PXCAPI SetProfile(ProfileInfo *pinfo)=0;

    /// Set ROI region
    virtual pxcStatus PXCAPI SetROIRegions(pxcU32 nregions, PXCRectU32 *regions)=0;

    /// Get the segment data
    /// idx         reserved; must be zero
    /// data        The Segment data structure, to be returned
    virtual pxcStatus PXCAPI QuerySegmentData(pxcU32 /*idx*/, Segment * /*data*/) {return PXC_STATUS_ITEM_UNAVAILABLE;}

    /// Process the input image(s) for 3D segmentation.
    /// in_images   The input image arrays: color + depth
    /// seg_image   The output segmentation image
    /// sp          The sync point, to be returned
    virtual pxcStatus PXCAPI SegmentImageAsync(PXCImage *in_images[], PXCImage **seg_image, PXCScheduler::SyncPoint **sp)=0;

	/// Blend/Mask background with color, or a given image.
    /// color_image		The input color image
	/// seg_image		The input segmentation image
	/// bg_image		The input background image to be blended
	/// blended_image   The output blended image
    /// sp				The sync point, to be returned
	virtual pxcStatus PXCAPI BlendImageAsync(PXCImage *color_image, PXCImage *seg_image, PXCImage *bg_image, PXCImage **blended_image, PXCScheduler::SyncPoint **sp)=0;
};
