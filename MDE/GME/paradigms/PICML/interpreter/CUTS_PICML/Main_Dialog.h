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

#include <string>
#include <vector>

/**
 * @class Main_Dialog
 *
 * Main dialog for the CUTS code generator interpreter. It allows
 * the end user to select target directory for generation and the
 * backend generator to execute.
 */
class Main_Dialog : public CDialog
{
public:
  /**
   * @struct Options
   *
   * Configuration options for the dialog.
   */
  struct Options
  {
    /// Output directory for the code generation.
    CString output_dir_;

    /// List of backends to display.
    std::vector <CString> backends_;

    /// The selected backend from the list of backends.
    int selected_backend_;
  };

  /**
   * Main constructor.
   *
   * @param[in]     options       The backend options.
   * @param[in]     parent        Parent of the dialog.
   */
  Main_Dialog (CWnd * parent = 0);

  /// Destructor.
  virtual ~Main_Dialog (void);

  /// Configuration options for the dialog.
  Options opts_;

protected:
  /// Handle the initialize dialog method.
  virtual BOOL OnInitDialog (void);

  /// Handle the data exchange message.
  void DoDataExchange (CDataExchange * pDX);

  /// Handle the user clicking the browse button.
  afx_msg void on_browse_clicked (void);

private:
  /// Declaration of the message map.
  DECLARE_MESSAGE_MAP ();

  /// List of generators for the combo box.
  CComboBox generators_;
};

#endif  // !defined _CUTS_PICML_MAIN_DIALOG_H_
