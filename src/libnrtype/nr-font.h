#ifndef __NR_FONT_H__
#define __NR_FONT_H__

/*
 * Typeface and script library
 *
 * Authors:
 *   Lauris Kaplinski <lauris@kaplinski.com>
 *
 * This code is in public domain
 */

struct NRFont;

#include <libnrtype/nr-typeface.h>
#include <libnrtype/nr-rasterfont.h>

struct NRFont {
	unsigned int refcount;
	NRFont *next;
	NRTypeFace *face;
	unsigned int metrics : 2;
	float size;
};

#define NR_FONT_SIZE(f) (((NRFont *) f)->size)
#define NR_FONT_TYPEFACE(f) (((NRFont *) f)->face)
#define NR_FONT_NUM_GLYPHS(f) (((NRFont *) f)->face->nglyphs)

NRFont *nr_font_ref (NRFont *font);
NRFont *nr_font_unref (NRFont *font);

NRBPath *nr_font_glyph_outline_get (NRFont *font, unsigned int glyph, NRBPath *d, unsigned int ref);
void nr_font_glyph_outline_unref (NRFont *font, unsigned int glyph);

NR::Point nr_font_glyph_advance_get (NRFont *font, unsigned int glyph);
NRRect *nr_font_glyph_area_get (NRFont *font, unsigned int glyph, NRRect *area);

NRRasterFont *nr_rasterfont_new (NRFont *font, NR::Matrix const transform);

/* Generic implementation */

NRFont *nr_font_generic_new (NRTypeFace *tf, unsigned int metrics, NR::Matrix const transform);
void nr_font_generic_free (NRFont *font);

NRBPath *nr_font_generic_glyph_outline_get (NRFont *font, unsigned int glyph, NRBPath *d, unsigned int ref);
void nr_font_generic_glyph_outline_unref (NRFont *font, unsigned int glyph);
NR::Point nr_font_generic_glyph_advance_get (NRFont *font, unsigned int glyph);
NRRect *nr_font_generic_glyph_area_get (NRFont *font, unsigned int glyph, NRRect *area);

NRRasterFont *nr_font_generic_rasterfont_new (NRFont *font, NR::Matrix const transform);
void nr_font_generic_rasterfont_free (NRRasterFont *rf);

#endif
