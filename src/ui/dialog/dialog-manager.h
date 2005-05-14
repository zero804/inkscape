/**
 * \brief Object for managing a set of dialogs, including their signals and
 *        construction/caching/destruction of them.
 *
 * Author:
 *   Bryce W. Harrington <bryce@bryceharrington.org>
 *   Jon Phillips <jon@rejon.org>
 *   
 * Copyright (C) 2004 Bryce Harrington
 * Copyright (C) 2005 Jon Phillips
 * 
 * Released under GNU GPL.  Read the file 'COPYING' for more information.
 */

#ifndef INKSCAPE_UI_DIALOG_MANAGER_H
#define INKSCAPE_UI_DIALOG_MANAGER_H

#include "dialog.h"
#include <map>

namespace Inkscape {
namespace UI {
namespace Dialog {

class DialogManager {
public:
    DialogManager();
    virtual ~DialogManager();

    sigc::signal<void> show_dialogs;
    sigc::signal<void> show_f12;
    sigc::signal<void> hide_dialogs;
    sigc::signal<void> hide_f12;
    sigc::signal<void> transientize;

    /* generic dialog management start */
    typedef std::map<GQuark, Dialog*>    DialogMap;

    Dialog *getDialog(gchar const* dlgName); 
    Dialog *getDialog(GQuark dlgName); 
    void    addDialog(gchar const* dlgName, Dialog * dlg);
    void    addDialog(GQuark dlgName, Dialog * dlg);
    bool    deleteDialog(gchar const* dlgName);
    bool    deleteDialog(GQuark dlgName);
    void    deleteAllDialogs(); 
    /* generic dialog management end */

    Dialog *getAboutDialog();
    Dialog *getAlignAndDistributeDialog();
    Dialog *getInkscapePreferencesDialog();
    Dialog *getDocumentPreferencesDialog();
    Dialog *getDebugDialog();
    Dialog *getExportDialog();
    Dialog *getExtensionEditorDialog();
    Dialog *getFillAndStrokeDialog();
    Dialog *getFindDialog();
    Dialog *getLayerEditorDialog();
    Dialog *getMessagesDialog();
    Dialog *getObjectPropertiesDialog();
    Dialog *getTextPropertiesDialog();
    Dialog *getTraceDialog();
    Dialog *getTransformDialog();
    Dialog *getTransformationDialog();
    Dialog *getXmlEditorDialog();
    Dialog *getMemoryDialog();

protected:
    DialogManager(DialogManager const &d);
    DialogManager& operator=(DialogManager const &d);

    DialogManager::DialogMap    _dialog_map; // internal storage for dialogs

    Dialog            *_about_dialog;
    Dialog            *_align_and_distribute_dialog;
    Dialog            *_inkscape_preferences_dialog;
    Dialog            *_debug_dialog;
    Dialog            *_document_preferences_dialog;
    Dialog            *_export_dialog;
    Dialog            *_extension_editor_dialog;
    Dialog            *_fill_and_stroke_dialog;
    Dialog            *_find_dialog;
    Dialog            *_layer_editor_dialog;
    Dialog            *_messages_dialog;
    Dialog            *_object_properties_dialog;
    Dialog            *_text_properties_dialog;
    Dialog            *_trace_dialog;
    Dialog            *_transformation_dialog;
    Dialog            *_xml_editor_dialog;
    Dialog            *_memory_dialog;
};

} // namespace Dialog
} // namespace UI
} // namespace Inkscape

#endif //INKSCAPE_UI_DIALOG_MANAGER_H

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
