#ifndef SP_CURSOR_H
#define SP_CURSOR_H

#include <gdk/gdk.h>

void sp_cursor_bitmap_and_mask_from_xpm (GdkBitmap **bitmap, GdkBitmap **mask, gchar **xpm);
GdkCursor * sp_cursor_new_from_xpm (gchar ** xpm, gint hot_x, gint hot_y);

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
