/* 
 * GStreamer
 * Copyright (C) 2013 Matthew Waters <ystreet00@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __GST_GL_FRAMEBUFFER_H__
#define __GST_GL_FRAMEBUFFER_H__

#include <gst/gl/gstgl_fwd.h>

G_BEGIN_DECLS

GType gst_gl_framebuffer_get_type (void);

#define GST_TYPE_GL_FRAMEBUFFER             (gst_gl_framebuffer_get_type())
#define GST_GL_FRAMEBUFFER(obj)             (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_GL_FRAMEBUFFER,GstGLFramebuffer))
#define GST_GL_FRAMEBUFFER_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST((klass), GST_TYPE_GL_FRAMEBUFFER,GstGLFramebufferClass))
#define GST_IS_GL_FRAMEBUFFER(obj)          (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_GL_FRAMEBUFFER))
#define GST_IS_GL_FRAMEBUFFER_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE((klass), GST_TYPE_GL_FRAMEBUFFER))
#define GST_GL_FRAMEBUFFER_CAST(obj)        ((GstGLFramebuffer*)(obj))

typedef struct _GstGLFramebufferClass GstGLFramebufferClass;
typedef struct _GstGLFramebufferPrivate GstGLFramebufferPrivate;

/**
 * GstGLFramebufferFunc:
 * @data: user data
 *
 * callback definition for operating through a Framebuffer object
 */
typedef gboolean (*GstGLFramebufferFunc) (gpointer stuff);

struct _GstGLFramebuffer
{
  GstObject             object;

  GstGLContext *context;

  /* <private> */
  guint fbo_id;
  GArray *attachments;

  gpointer          _padding[GST_PADDING];

  GstGLFramebufferPrivate  *priv;
};

struct _GstGLFramebufferClass
{
  GstObjectClass object_class;

  gpointer          _padding[GST_PADDING];
};

GstGLFramebuffer *      gst_gl_framebuffer_new                      (GstGLContext *context);
GstGLFramebuffer *      gst_gl_framebuffer_new_with_default_depth   (GstGLContext *context,
                                                                     guint width,
                                                                     guint height);

guint                   gst_gl_framebuffer_get_id                   (GstGLFramebuffer * fb);

void                    gst_gl_framebuffer_attach                   (GstGLFramebuffer * fb,
                                                                     guint attachment_point,
                                                                     GstGLBaseMemory * mem);
void                    gst_gl_framebuffer_bind                     (GstGLFramebuffer * fb);
void                    gst_gl_context_clear_framebuffer            (GstGLContext * context);

void                    gst_gl_framebuffer_get_effective_dimensions (GstGLFramebuffer * fb,
                                                                     guint * width,
                                                                     guint * height);

gboolean                gst_gl_context_check_framebuffer_status     (GstGLContext * context);

gboolean                gst_gl_framebuffer_draw_to_texture          (GstGLFramebuffer * fb,
                                                                     GstGLMemory * mem,
                                                                     GstGLFramebufferFunc cb,
                                                                     gpointer user_data);

#ifdef G_DEFINE_AUTOPTR_CLEANUP_FUNC
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GstGLFramebuffer, gst_object_unref)
#endif

G_END_DECLS

#endif
