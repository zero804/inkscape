#ifndef __SP_WINDOW_H__
#define __SP_WINDOW_H__

/*
 * Generic window implementation
 *
 * Author:
 *   Lauris Kaplinski <lauris@kaplinski.com>
 *
 * This code is in public domain
 */

#include <gtk/gtkwidget.h>

GtkWidget *sp_window_new (const gchar *title, unsigned int resizeable);

#endif

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=c++:expandtab:shiftwidth=4:tabstop=8:softtabstop=4 :
