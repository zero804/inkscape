#define __SP_PNG_WRITE_C__

/*
 * PNG file format utilities
 *
 * Authors:
 *   Lauris Kaplinski <lauris@kaplinski.com>
 *   Whoever wrote this example in libpng documentation
 *
 * Copyright (C) 1999-2002 authors
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <interface.h>
#include <libnr/nr-pixops.h>
#include <libnr/nr-translate-scale-ops.h>
#include <glib/gmessages.h>
#include <png.h>
#include "png-write.h"
#include "io/sys.h"
#include <display/nr-arena-item.h>
#include <display/nr-arena.h>
#include <document.h>
#include <sp-item.h>
#include <sp-root.h>
#include <sp-defs.h>
#include "prefs-utils.h"

/* This is an example of how to use libpng to read and write PNG files.
 * The file libpng.txt is much more verbose then this.  If you have not
 * read it, do so first.  This was designed to be a starting point of an
 * implementation.  This is not officially part of libpng, and therefore
 * does not require a copyright notice.
 *
 * This file does not currently compile, because it is missing certain
 * parts, like allocating memory to hold an image.  You will have to
 * supply these parts to get it to compile.  For an example of a minimal
 * working PNG reader/writer, see pngtest.c, included in this distribution.
 */

static unsigned int const MAX_STRIPE_SIZE = 1024*1024;

struct SPEBP {
    int width, height, sheight;
    guchar r, g, b, a;
    NRArenaItem *root; // the root arena item to show; it is assumed that all unneeded items are hidden
    guchar *px;
    unsigned (*status)(float, void *);
    void *data;
};

/* write a png file */

typedef struct SPPNGBD {
    guchar const *px;
    int rowstride;
} SPPNGBD;

static bool
sp_png_write_rgba_striped(gchar const *filename, int width, int height, double xdpi, double ydpi,
                          int (* get_rows)(guchar const **rows, int row, int num_rows, void *data),
                          void *data)
{
    struct SPEBP *ebp = (struct SPEBP *) data;
    FILE *fp;
    png_structp png_ptr;
    png_infop info_ptr;
    png_color_8 sig_bit;
    png_text text_ptr[3];
    png_uint_32 r;

    g_return_val_if_fail(filename != NULL, false);

    /* open the file */

    Inkscape::IO::dump_fopen_call(filename, "M");
    fp = Inkscape::IO::fopen_utf8name(filename, "wb");
    g_return_val_if_fail(fp != NULL, false);

    /* Create and initialize the png_struct with the desired error handler
     * functions.  If you want to use the default stderr and longjump method,
     * you can supply NULL for the last three parameters.  We also check that
     * the library version is compatible with the one used at compile time,
     * in case we are using dynamically linked libraries.  REQUIRED.
     */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (png_ptr == NULL) {
        fclose(fp);
        return false;
    }

    /* Allocate/initialize the image information data.  REQUIRED */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_write_struct(&png_ptr, NULL);
        return false;
    }

    /* Set error handling.  REQUIRED if you aren't supplying your own
     * error hadnling functions in the png_create_write_struct() call.
     */
    if (setjmp(png_ptr->jmpbuf)) {
        /* If we get here, we had a problem reading the file */
        fclose(fp);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return false;
    }

    /* set up the output control if you are using standard C streams */
    png_init_io(png_ptr, fp);

    /* Set the image information here.  Width and height are up to 2^31,
     * bit_depth is one of 1, 2, 4, 8, or 16, but valid values also depend on
     * the color_type selected. color_type is one of PNG_COLOR_TYPE_GRAY,
     * PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE, PNG_COLOR_TYPE_RGB,
     * or PNG_COLOR_TYPE_RGB_ALPHA.  interlace is either PNG_INTERLACE_NONE or
     * PNG_INTERLACE_ADAM7, and the compression_type and filter_type MUST
     * currently be PNG_COMPRESSION_TYPE_BASE and PNG_FILTER_TYPE_BASE. REQUIRED
     */
    png_set_IHDR(png_ptr, info_ptr,
                 width,
                 height,
                 8, /* bit_depth */
                 PNG_COLOR_TYPE_RGB_ALPHA,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE,
                 PNG_FILTER_TYPE_BASE);

    /* otherwise, if we are dealing with a color image then */
    sig_bit.red = 8;
    sig_bit.green = 8;
    sig_bit.blue = 8;
    /* if the image has an alpha channel then */
    sig_bit.alpha = 8;
    png_set_sBIT(png_ptr, info_ptr, &sig_bit);

    /* Made by Inkscape comment */
    text_ptr[0].key = "Software";
    text_ptr[0].text = "www.inkscape.org";
    text_ptr[0].compression = PNG_TEXT_COMPRESSION_NONE;
    png_set_text(png_ptr, info_ptr, text_ptr, 1);

    /* other optional chunks like cHRM, bKGD, tRNS, tIME, oFFs, pHYs, */
    /* note that if sRGB is present the cHRM chunk must be ignored
     * on read and must be written in accordance with the sRGB profile */
    png_set_pHYs(png_ptr, info_ptr, unsigned(xdpi / 0.0254 + 0.5), unsigned(ydpi / 0.0254 + 0.5), PNG_RESOLUTION_METER);

    /* Write the file header information.  REQUIRED */
    png_write_info(png_ptr, info_ptr);

    /* Once we write out the header, the compression type on the text
     * chunks gets changed to PNG_TEXT_COMPRESSION_NONE_WR or
     * PNG_TEXT_COMPRESSION_zTXt_WR, so it doesn't get written out again
     * at the end.
     */

    /* set up the transformations you want.  Note that these are
     * all optional.  Only call them if you want them.
     */

    /* --- CUT --- */

    /* The easiest way to write the image (you may have a different memory
     * layout, however, so choose what fits your needs best).  You need to
     * use the first method if you aren't handling interlacing yourself.
     */

    png_bytep* row_pointers = new png_bytep[ebp->sheight];

    r = 0;
    while (r < static_cast< png_uint_32 > (height) ) {
        int n = get_rows((unsigned char const **) row_pointers, r, height-r, data);
        if (!n) break;
        png_write_rows(png_ptr, row_pointers, n);
        r += n;
    }

    delete[] row_pointers;

    /* You can write optional chunks like tEXt, zTXt, and tIME at the end
     * as well.
     */

    /* It is REQUIRED to call this to finish writing the rest of the file */
    png_write_end(png_ptr, info_ptr);

    /* if you allocated any text comments, free them here */

    /* clean up after the write, and free any memory allocated */
    png_destroy_write_struct(&png_ptr, &info_ptr);

    /* close the file */
    fclose(fp);

    /* that's it */
    return true;
}


/**
 *
 */
static int
sp_export_get_rows(guchar const **rows, int row, int num_rows, void *data)
{
    struct SPEBP *ebp = (struct SPEBP *) data;

    if (ebp->status) {
        if (!ebp->status((float) row / ebp->height, ebp->data)) return 0;
    }

    num_rows = MIN(num_rows, ebp->sheight);
    num_rows = MIN(num_rows, ebp->height - row);

    /* Set area of interest */
    // bbox is now set to the entire image to prevent discontinuities
    // in the image when blur is used (the borders may still be a bit
    // off, but that's less noticeable).
    NRRectL bbox;
    bbox.x0 = 0;
    bbox.y0 = 0;//row;
    bbox.x1 = ebp->width;
    bbox.y1 = ebp->height;//row + num_rows;
    /* Update to renderable state */
    NRGC gc(NULL);
    nr_matrix_set_identity(&gc.transform);

    nr_arena_item_invoke_update(ebp->root, &bbox, &gc,
           NR_ARENA_ITEM_STATE_ALL, NR_ARENA_ITEM_STATE_NONE);

    NRPixBlock pb;
    nr_pixblock_setup_extern(&pb, NR_PIXBLOCK_MODE_R8G8B8A8N,
                             bbox.x0, row/*bbox.y0*/, bbox.x1, row + num_rows/*bbox.y1*/,
                             ebp->px, 4 * ebp->width, FALSE, FALSE);

    for (int r = 0; r < num_rows; r++) {
        guchar *p = NR_PIXBLOCK_PX(&pb) + r * pb.rs;
        for (int c = 0; c < ebp->width; c++) {
            *p++ = ebp->r;
            *p++ = ebp->g;
            *p++ = ebp->b;
            *p++ = ebp->a;
        }
    }

    /* Render */
    nr_arena_item_invoke_render(NULL, ebp->root, &bbox, &pb, 0);

    for (int r = 0; r < num_rows; r++) {
        rows[r] = NR_PIXBLOCK_PX(&pb) + r * pb.rs;
    }

    nr_pixblock_release(&pb);

    return num_rows;
}

/**
 * Hide all items that are not listed in list, recursively, skipping groups and defs.
 */
static void
hide_other_items_recursively(SPObject *o, GSList *list, unsigned dkey)
{
    if ( SP_IS_ITEM(o)
         && !SP_IS_DEFS(o)
         && !SP_IS_ROOT(o)
         && !SP_IS_GROUP(o)
         && !g_slist_find(list, o) )
    {
        sp_item_invoke_hide(SP_ITEM(o), dkey);
    }

    // recurse
    if (!g_slist_find(list, o)) {
        for (SPObject *child = sp_object_first_child(o) ; child != NULL; child = SP_OBJECT_NEXT(child) ) {
            hide_other_items_recursively(child, list, dkey);
        }
    }
}


/**
 * Export the given document as a Portable Network Graphics (PNG) file.
 *
 * \return true if succeeded, false if an error occurred.
 */
bool
sp_export_png_file(SPDocument *doc, gchar const *filename,
                   double x0, double y0, double x1, double y1,
                   unsigned width, unsigned height, double xdpi, double ydpi,
                   unsigned long bgcolor,
                   unsigned (*status)(float, void *),
                   void *data, bool force_overwrite,
                   GSList *items_only)
{
    g_return_val_if_fail(doc != NULL, false);
    g_return_val_if_fail(filename != NULL, false);
    g_return_val_if_fail(width >= 1, false);
    g_return_val_if_fail(height >= 1, false);

    if (!force_overwrite && !sp_ui_overwrite_file(filename)) {
        return false;
    }

    // export with maximum blur rendering quality
    int saved_quality = prefs_get_int_attribute("options.blurquality", "value", 0);
    prefs_set_int_attribute("options.blurquality", "value", 2);

    sp_document_ensure_up_to_date(doc);

    /* Go to document coordinates */
    {
        gdouble const t = y0;
        y0 = sp_document_height(doc) - y1;
        y1 = sp_document_height(doc) - t;
    }

    /*
     * 1) a[0] * x0 + a[2] * y1 + a[4] = 0.0
     * 2) a[1] * x0 + a[3] * y1 + a[5] = 0.0
     * 3) a[0] * x1 + a[2] * y1 + a[4] = width
     * 4) a[1] * x0 + a[3] * y0 + a[5] = height
     * 5) a[1] = 0.0;
     * 6) a[2] = 0.0;
     *
     * (1,3) a[0] * x1 - a[0] * x0 = width
     * a[0] = width / (x1 - x0)
     * (2,4) a[3] * y0 - a[3] * y1 = height
     * a[3] = height / (y0 - y1)
     * (1) a[4] = -a[0] * x0
     * (2) a[5] = -a[3] * y1
     */

    NR::Matrix const affine(NR::translate(-x0, -y0)
                            * NR::scale(width / (x1 - x0),
                                        height / (y1 - y0)));

    //SP_PRINT_MATRIX("SVG2PNG", &affine);

    struct SPEBP ebp;
    ebp.width  = width;
    ebp.height = height;
    ebp.r      = NR_RGBA32_R(bgcolor);
    ebp.g      = NR_RGBA32_G(bgcolor);
    ebp.b      = NR_RGBA32_B(bgcolor);
    ebp.a      = NR_RGBA32_A(bgcolor);

    /* Create new arena */
    NRArena *const arena = NRArena::create();
    unsigned const dkey = sp_item_display_key_new(1);

    /* Create ArenaItems and set transform */
    ebp.root = sp_item_invoke_show(SP_ITEM(sp_document_root(doc)), arena, dkey, SP_ITEM_SHOW_DISPLAY);
    nr_arena_item_set_transform(NR_ARENA_ITEM(ebp.root), affine);

    // We show all and then hide all items we don't want, instead of showing only requested items,
    // because that would not work if the shown item references something in defs
    if (items_only) {
        hide_other_items_recursively(sp_document_root(doc), items_only, dkey);
    }

    ebp.status = status;
    ebp.data   = data;

    bool write_status;
    if (width * height < 65536 / 4) {
        ebp.px = nr_pixelstore_64K_new(FALSE, 0);
        ebp.sheight = height;
        write_status = sp_png_write_rgba_striped(filename, width, height, xdpi, ydpi, sp_export_get_rows, &ebp);
        nr_pixelstore_64K_free(ebp.px);
    } else {
        ebp.sheight = MAX(1,MIN(MAX_STRIPE_SIZE / (4 * width),height));
        ebp.px = g_new(guchar, 4 * width * ebp.sheight);
        write_status = sp_png_write_rgba_striped(filename, width, height, xdpi, ydpi, sp_export_get_rows, &ebp);
        g_free(ebp.px);
    }

    // Hide items
    sp_item_invoke_hide(SP_ITEM(sp_document_root(doc)), dkey);

    /* Free Arena and ArenaItem */
    nr_arena_item_unref(ebp.root);
    nr_object_unref((NRObject *) arena);

    // restore saved blur quality
    prefs_set_int_attribute("options.blurquality", "value", saved_quality);

    return write_status;
}


/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:encoding=utf-8:textwidth=99 :
