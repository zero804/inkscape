#define __DIALOG_EVENTS_C__

/*
 * Event handler for dialog windows
 *
 * Authors:
 *   bulia byak <bulia@dr.com>
 *
 * Copyright (C) 2003 authors
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#include <config.h>

#include <glib.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtksignal.h>
#include "helper/window.h"
#include "widgets/sp-widget.h"
#include "macros.h"
#include "inkscape.h"
#include <gtk/gtk.h>
#include "desktop-events.h"
#include "desktop.h"

#include "dialog-events.h"

gboolean
sp_dialog_event_handler (GtkWindow *win, GdkEvent *event, gpointer data)
{
	gboolean ret = FALSE; 
	GtkWindow *w;
	SPDesktopWidget *dtw;

	switch (event->type) {
	case GDK_KEY_PRESS:
		switch (event->key.keyval) {
		case GDK_Escape: 
			gtk_widget_destroy ((GtkWidget *) win);
			ret = TRUE; 
			break;
		default: 
			if (w = gtk_window_get_transient_for ((GtkWindow *) win)) {
				dtw = g_object_get_data (G_OBJECT (w), "desktopwidget");
				inkscape_activate_desktop (dtw->desktop);
				gtk_propagate_event (GTK_WIDGET (dtw->canvas), event);
				ret = TRUE; 
			}
			break;
		}
	}
	return ret; 
}

void
sp_transientize (GtkWidget * dialog)
{
	// if there's an active canvas, attach dialog to it as a transient:
	if (SP_ACTIVE_DESKTOP && g_object_get_data (G_OBJECT (SP_ACTIVE_DESKTOP), "window")) 
		gtk_window_set_transient_for ((GtkWindow *) dialog, (GtkWindow *) g_object_get_data (G_OBJECT (SP_ACTIVE_DESKTOP), "window"));
}
