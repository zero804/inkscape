/*
 * Inkscape::Debug::SimpleEvent - trivial implementation of Debug::Event
 *
 * Authors:
 *   MenTaLguY <mental@rydia.net>
 *
 * Copyright (C) 2005 MenTaLguY
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#ifndef SEEN_INKSCAPE_DEBUG_SIMPLE_EVENT_H
#define SEEN_INKSCAPE_DEBUG_SIMPLE_EVENT_H

#include "debug/event.h"

namespace Inkscape {

namespace Debug {

class SimpleEvent : public Event {
public:
    SimpleEvent(Util::SharedCStringPtr name) : _name(name) {}
    SimpleEvent(char const *name) : _name(Util::SharedCStringPtr::copy(name)) {}

    Util::SharedCStringPtr name() const { return _name; }
    unsigned propertyCount() const { return 0; }
    PropertyPair property(unsigned property) const { return PropertyPair(); }

private:
    Util::SharedCStringPtr _name;
};

}

}

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
