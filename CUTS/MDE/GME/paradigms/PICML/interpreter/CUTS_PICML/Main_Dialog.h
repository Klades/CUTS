// -*- C++ -*-

//=============================================================================
/**
 * @file      Main_Dialog.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_PICML_MAIN_DIALOG_H_
#define _CUTS_PICML_MAIN_DIALOG_H_

// Forward decl.
struct CUTS_BE_Options;

#include "be/BE_Manager_Factory_Repo.h"

// Forward decl.
class CUTS_BE_Manager_Factory;

namespace CUTS
{
  // Forward decl.
  class Configuration;

  // Forward decl.
  class Generator_Description;
}

//=============================================================================
/**
 * @class Main_Dialog
 *
 * Main dialog for the CUTS PICML interpreter.
 */
//=============================================================================

class Main_Dialog : public CDialog
{
public:
  /**
   * Main constructor.
   *
   * @param[in]     options       The backend options.
   * @param[in]     parent        Parent of the dialog.
   */
  Main_Dialog (CUTS_BE_Options * options,
               CWnd * parent = 0);

  /// Destructor.
  virtual ~Main_Dialog (void);

  /**
   * Get the selected manager factory for model generation. This
   * factory pointer will be one located in the factory repository
   * used in the constructor.
   *
   * @return        Pointer to the manager factory.
   */
  CUTS_BE_Manager_Factory * factory (void) const;

protected:
  /// Handle the initialize dialog method.
  virtual BOOL OnInitDialog (void);

  /// Handle the data exchange message.
  void DoDataExchange (CDataExchange * pDX);

  /// Handle the WM_COMMAND message.
  afx_msg BOOL OnCommand (WPARAM wParam, LPARAM lParam);

  afx_msg void On_BE_List_SelChange (void);

private:
  DECLARE_MESSAGE_MAP ();

  void load_backend_generator (const CUTS::Generator_Description & desc);

  void init_generators (const CUTS::Configuration & config);

  int resolve_CUTS_ROOT (std::string & root);

  /// Pointer to the backend options.
  CUTS_BE_Options * options_;

  /// The selected backend module.
  CUTS_BE_Manager_Factory * factory_;

  /// Factory repository for the GUI.
  CUTS_BE_Manager_Factory_Repo factory_repo_;

  /// The backend list box control.
  CListBox be_list_;
};

#endif  // !defined _CUTS_PICML_MAIN_DIALOG_H_
