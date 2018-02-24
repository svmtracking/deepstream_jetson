/**
 * Copyright (c) 2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 *
 */

#ifndef __GST_DSOPENALPR_H__
#define __GST_DSOPENALPR_H__

#include <gst/base/gstbasetransform.h>
#include <gst/video/video.h>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "nvbuf_utils.h"
#include "gstnvivameta_api.h"
#include "dsopenalpr_lib/dsopenalpr_lib.h"

/* Package and library details required for plugin_init */
#define PACKAGE "dsopenalpr"
#define VERSION "1.0"
#define LICENSE "Proprietary"
#define DESCRIPTION "OpenALPR plugin for integration with DeepStream on Jetson"
#define BINARY_PACKAGE "DeepStream 3rdparty OpenALPR plugin"
#define URL "http://www.openalpr.com/"


G_BEGIN_DECLS
/* Standard boilerplate stuff */
typedef struct _GstDsOpenalpr GstDsOpenalpr;
typedef struct _GstDsOpenalprClass GstDsOpenalprClass;

/* Standard boilerplate stuff */
#define GST_TYPE_DSOPENALPR (gst_dsopenalpr_get_type())
#define GST_DSOPENALPR(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_DSOPENALPR,GstDsOpenalpr))
#define GST_DSOPENALPR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_DSOPENALPR,GstDsOpenalprClass))
#define GST_DSOPENALPR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), GST_TYPE_DSOPENALPR, GstDsOpenalprClass))
#define GST_IS_DSOPENALPR(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_DSOPENALPR))
#define GST_IS_DSOPENALPR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_DSOPENALPR))
#define GST_DSOPENALPR_CAST(obj)  ((GstDsOpenalpr *)(obj))

struct _GstDsOpenalpr {
  GstBaseTransform base_trans;

  DsOpenalprCtx *dsopenalprlib_ctx;

  // Unique ID of the element. The labels generated by the element will be
  // updated at index `unique_id` of label_info array in ROIMeta_Params.
  guint unique_id;

  // Frame number of the current input buffer
  guint64 frame_num;

  // DMABUF FD of the scratch conversion buffer
  gint conv_dmabuf_fd;

  // OpenCV mat to remove padding and convert RGBA to RGB
  cv::Mat *cvmat;

  // Input video info (resolution, color format, framerate, etc)
  GstVideoInfo video_info;

  // Resolution at which frames/objects should be processed
  gint processing_width;
  gint processing_height;

  // Boolean indicating if entire frame or cropped objects should be processed
  gboolean process_full_frame;

  // Boolean signalling EOS has been recieved by the element.
  gboolean got_eos;
};

// Boiler plate stuff
struct _GstDsOpenalprClass {
  GstBaseTransformClass parent_class;
};

GType gst_dsopenalpr_get_type (void);

G_END_DECLS

#endif /* __GST_DSOPENALPR_H__ */