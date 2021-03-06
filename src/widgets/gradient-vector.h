#ifndef __SP_GRADIENT_VECTOR_H__
#define __SP_GRADIENT_VECTOR_H__

/*
 * Gradient vector selection widget
 *
 * Author:
 *   Lauris Kaplinski <lauris@kaplinski.com>
 *
 * Copyright (C) 2001-2002 Lauris Kaplinski
 * Copyright (C) 2001 Ximian, Inc.
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#include <glib.h>

G_BEGIN_DECLS

#include <gtk/gtkvbox.h>
#include "../forward.h"

typedef struct _SPGradientVectorSelector SPGradientVectorSelector;
typedef struct _SPGradientVectorSelectorClass SPGradientVectorSelectorClass;

#define SP_TYPE_GRADIENT_VECTOR_SELECTOR (sp_gradient_vector_selector_get_type ())
#define SP_GRADIENT_VECTOR_SELECTOR(o) (GTK_CHECK_CAST ((o), SP_TYPE_GRADIENT_VECTOR_SELECTOR, SPGradientVectorSelector))
#define SP_GRADIENT_VECTOR_SELECTOR_CLASS(k) (GTK_CHECK_CLASS_CAST ((k), SP_TYPE_GRADIENT_VECTOR_SELECTOR, SPGradientVectorSelectorClass))
#define SP_IS_GRADIENT_VECTOR_SELECTOR(o) (GTK_CHECK_TYPE ((o), SP_TYPE_GRADIENT_VECTOR_SELECTOR))
#define SP_IS_GRADIENT_VECTOR_SELECTOR_CLASS(k) (GTK_CHECK_CLASS_TYPE ((k), SP_TYPE_GRADIENT_VECTOR_SELECTOR))

struct _SPGradientVectorSelector {
	GtkVBox vbox;

	guint idlabel : 1;

	SPDocument *doc;
	SPGradient *gr;

	/* Vector menu */
	GtkWidget *menu;
};

struct _SPGradientVectorSelectorClass {
	GtkVBoxClass parent_class;

	void (* vector_set) (SPGradientVectorSelector *gvs, SPGradient *gr);
};

GtkType sp_gradient_vector_selector_get_type (void);

GtkWidget *sp_gradient_vector_selector_new (SPDocument *doc, SPGradient *gradient);

void sp_gradient_vector_selector_set_gradient (SPGradientVectorSelector *gvs, SPDocument *doc, SPGradient *gr);

SPDocument *sp_gradient_vector_selector_get_document (SPGradientVectorSelector *gvs);
SPGradient *sp_gradient_vector_selector_get_gradient (SPGradientVectorSelector *gvs);

/* fixme: rethink this (Lauris) */
GtkWidget *sp_gradient_vector_editor_new (SPGradient *gradient);

G_END_DECLS

#endif
