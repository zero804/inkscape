#ifndef __SP_GUIDELINE_H__
#define __SP_GUIDELINE_H__

/*
 * Infinite horizontal/vertical line; the visual representation of SPGuide.
 *
 * Author:
 *   Lauris Kaplinski <lauris@kaplinski.com>
 *
 * Copyright (C) 2000-2002 Lauris Kaplinski
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#include "sp-canvas.h"



#define SP_TYPE_GUIDELINE (sp_guideline_get_type ())
#define SP_GUIDELINE(o) (GTK_CHECK_CAST ((o), SP_TYPE_GUIDELINE, SPGuideLine))
#define SP_IS_GUIDELINE(o) (GTK_CHECK_TYPE ((o), SP_TYPE_GUIDELINE))

struct SPGuideLine {
	SPCanvasItem item;

	guint32 rgba;

	int position;

	unsigned int vertical : 1;
	unsigned int sensitive : 1;
};

struct SPGuideLineClass {
	SPCanvasItemClass parent_class;
};

GType sp_guideline_get_type (void);

SPCanvasItem *sp_guideline_new (SPCanvasGroup *parent, double position, unsigned int vertical);

void sp_guideline_set_position (SPGuideLine *gl, double position);
void sp_guideline_set_color (SPGuideLine *gl, unsigned int rgba);
void sp_guideline_set_sensitive (SPGuideLine *gl, int sensitive);



#endif
