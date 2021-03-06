#ifndef __SP_STAR_CONTEXT_H__
#define __SP_STAR_CONTEXT_H__

/*
 * Star drawing context
 *
 * Authors:
 *   Mitsuru Oka <oka326@parkcity.ne.jp>
 *   Lauris Kaplinski <lauris@kaplinski.com>
 *
 * Copyright (C) 1999-2002 Lauris Kaplinski
 * Copyright (C) 2001-2002 Mitsuru Oka
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#include "event-context.h"

#define SP_TYPE_STAR_CONTEXT (sp_star_context_get_type ())
#define SP_STAR_CONTEXT(obj) (GTK_CHECK_CAST ((obj), SP_TYPE_STAR_CONTEXT, SPStarContext))
#define SP_STAR_CONTEXT_CLASS(klass) (GTK_CHECK_CLASS_CAST ((klass), SP_TYPE_STAR_CONTEXT, SPStarContextClass))
#define SP_IS_STAR_CONTEXT(obj) (GTK_CHECK_TYPE ((obj), SP_TYPE_STAR_CONTEXT))
#define SP_IS_STAR_CONTEXT_CLASS(klass) (GTK_CHECK_CLASS_TYPE ((klass), SP_TYPE_STAR_CONTEXT))

typedef struct _SPStarContext SPStarContext;
typedef struct _SPStarContextClass SPStarContextClass;

struct _SPStarContext {
	SPEventContext event_context;
	SPItem *item;
	NRPointF center;

	/* Number of corners */
	gint magnitude;
	/* Outer/inner radius ratio */
	gdouble proportion;
};

struct _SPStarContextClass {
	SPEventContextClass parent_class;
};

GtkType sp_star_context_get_type (void);

#endif
