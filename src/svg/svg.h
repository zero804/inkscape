#ifndef __SP_SVG_H__
#define __SP_SVG_H__

/*
 * SVG data parser
 *
 * Authors:
 *   Lauris Kaplinski <lauris@kaplinski.com>
 *
 * Copyright (C) 1999-2002 Lauris Kaplinski
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */
#include <glib.h>
#include <libnr/nr-types.h>
#include <svg/svg-types.h>



/* Generic */

unsigned int sp_svg_boolean_read (const gchar *str, unsigned int *val);

/*
 * These are very-very simple:
 * - they accept everything libc strtod accepts
 * - no valid end character checking
 * Return FALSE and let val untouched on error
 */
 
unsigned int sp_svg_number_read_f (const gchar *str, float *val);
unsigned int sp_svg_number_read_d (const gchar *str, double *val);

/*
 * No buffer overflow checking is done, so better wrap them if needed
 */

unsigned int sp_svg_number_write_i (gchar *buf, int val);
unsigned int sp_svg_number_write_d (gchar *buf, double val, unsigned int tprec, unsigned int fprec, unsigned int padf);
unsigned int sp_svg_number_write_de (gchar *buf, double val, unsigned int tprec, unsigned int padf);

/* Length */

/*
 * Parse number with optional unit specifier:
 * - for px, pt, pc, mm, cm, computed is final value accrding to SVG spec
 * - for em, ex, and % computed is left untouched
 * - % is divided by 100 (i.e. 100% is 1.0)
 * !isalnum check is done at the end
 * Any return value pointer can be NULL
 */

unsigned int sp_svg_length_read (const gchar *str, SPSVGLength *length);
unsigned int sp_svg_length_read_lff (const gchar *str, unsigned long *unit, float *value, float *computed);
unsigned int sp_svg_length_read_ldd (const gchar *str, unsigned long *unit, double *value, double *computed);

void sp_svg_length_set (SPSVGLength *length, unsigned long unit, float value, float computed);
void sp_svg_length_unset (SPSVGLength *length, unsigned long unit, float value, float computed);
void sp_svg_length_update (SPSVGLength *length, double em, double ex, double scale);

unsigned int sp_svg_transform_read (const gchar *str, NRMatrix *transform);

unsigned int sp_svg_transform_write (gchar *str, unsigned int size, NRMatrix *transform);

double sp_svg_read_percentage (const char * str, double def);
int sp_svg_write_percentage (char * buf, int buflen, double val);

unsigned int sp_svg_read_color (const gchar * str, unsigned int def);
int sp_svg_write_color (char * buf, int buflen, unsigned int color);

/* NB! As paths can be long, we use here dynamic string */

#include <libart_lgpl/art_bpath.h>

ArtBpath * sp_svg_read_path (const char * str);
char * sp_svg_write_path (const ArtBpath * bpath);



#endif
