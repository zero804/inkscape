#ifndef INKSCAPE_LPE_EXPRESSION_H
#define INKSCAPE_LPE_EXPRESSION_H

/** \file
 * Implementation of an effect similar to Expression, see lpe-expression.cpp
 */

/*
 * Authors:
 *   Johan Engelen
*
* Copyright (C) Johan Engelen 2007 <j.b.c.engelen@utwente.nl>
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#include "live_effects/effect.h"
#include "live_effects/parameter/path.h"
#include "live_effects/parameter/parameter.h"
#include "live_effects/parameter/bool.h"
#include "live_effects/parameter/random.h"

namespace Inkscape {
namespace LivePathEffect {

class LPECurveStitch : public Effect {
public:
    LPECurveStitch(LivePathEffectObject *lpeobject);
    ~LPECurveStitch();

    std::vector<Geom::Path> doEffect (std::vector<Geom::Path> & path_in);

private:
    PathParam strokepath;
    ScalarParam nrofpaths;
    RandomParam startpoint_variation;
    RandomParam endpoint_variation;
    ScalarParam prop_scale;
    BoolParam scale_y_rel;

    LPECurveStitch(const LPECurveStitch&);
    LPECurveStitch& operator=(const LPECurveStitch&);
};

} //namespace LivePathEffect
} //namespace Inkscape

#endif
