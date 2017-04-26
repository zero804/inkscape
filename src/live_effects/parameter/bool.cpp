/*
 * Copyright (C) Johan Engelen 2007 <j.b.c.engelen@utwente.nl>
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#include "ui/widget/registered-widget.h"
#include "live_effects/parameter/bool.h"
#include "live_effects/effect.h"
#include "svg/svg.h"
#include "svg/stringstream.h"
#include "widgets/icon.h"
#include "inkscape.h"
#include "verbs.h"
#include "helper-fns.h"
#include <glibmm/i18n.h>

namespace Inkscape {

namespace LivePathEffect {

BoolParam::BoolParam( const Glib::ustring& label, const Glib::ustring& tip,
                      const Glib::ustring& key, Inkscape::UI::Widget::Registry* wr,
                      Effect* effect, bool default_value , bool no_widget)
    : Parameter(label, tip, key, wr, effect), value(default_value), defvalue(default_value), hide_widget(no_widget)
{
}

BoolParam::~BoolParam()
{
}

void
BoolParam::param_set_default()
{
    param_setValue(defvalue);
}

void 
BoolParam::param_update_default(bool default_value)
{
    defvalue = default_value;
}

void 
BoolParam::param_update_default(const gchar * default_value)
{
    param_update_default(helperfns_read_bool(default_value, defvalue));
}

bool
BoolParam::param_readSVGValue(const gchar * strvalue)
{
    param_setValue(helperfns_read_bool(strvalue, defvalue));
    return true; // not correct: if value is unacceptable, should return false!
}

gchar *
BoolParam::param_getSVGValue() const
{
    gchar * str = g_strdup(value ? "true" : "false");
    return str;
}

Gtk::Widget *
BoolParam::param_newWidget()
{
    if(!hide_widget){
        Inkscape::Preferences *prefs = Inkscape::Preferences::get();
        Glib::ustring effectkey = (Glib::ustring)Inkscape::LivePathEffect::LPETypeConverter.get_key(param_effect->effectType());
        Glib::ustring pref_path = (Glib::ustring)"/live_effects/" +
                                    effectkey +
                                   (Glib::ustring)"/" + 
                                   (Glib::ustring)param_key;
        Glib::ustring label = param_label;
        if(prefs->getEntry(pref_path).isValid()){
            label = (Glib::ustring)"* " + param_label;
        }
        Inkscape::UI::Widget::RegisteredCheckButton * checkwdg = Gtk::manage(
            new Inkscape::UI::Widget::RegisteredCheckButton( label,
                                                             param_tooltip,
                                                             param_key,
                                                             *param_wr,
                                                             false,
                                                             param_effect->getRepr(),
                                                             param_effect->getSPDoc()) );

        checkwdg->setActive(value);
        checkwdg->setProgrammatically = false;
        checkwdg->set_undo_parameters(SP_VERB_DIALOG_LIVE_PATH_EFFECT, _("Change bool parameter"));
        param_effect->upd_params = false;
        return dynamic_cast<Gtk::Widget *> (checkwdg);
    } else {
        return NULL;
    }
}

void
BoolParam::param_setValue(bool newvalue)
{
    param_effect->upd_params = true;
    value = newvalue;
}

} /* namespace LivePathEffect */

} /* namespace Inkscape */

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4 :
