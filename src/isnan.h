#ifndef __ISNAN_H__
#define __ISNAN_H__

/*
 * Temporary fix for various misdefinitions of isnan().
 * isnan() is becoming undef'd in some .h files. 
 * #include this last in your .cpp file to get it right.
 *
 * Authors:
 *   Inkscape groupies and obsessive-compulsives
 *
 * Copyright (C) 2004 authors
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#include <math.h>



#ifdef __APPLE__

/* MacOSX definition */
#define isNaN(a) (__isnan(a))
#define isFinite(a) (__isfinite(a))

#else

#ifdef WIN32

/* Win32 definition */
#define isNaN(a) (_isnan(a))
#define isFinite(a) (std::isfinite(a))

#else

/* Linux definition */
#define isNaN(a) (isnan(a))
#define isFinite(a) (std::isfinite(a))

#endif /* WIN32 */

#endif /* __APPLE__ */





#endif /* __ISNAN_H__ */



