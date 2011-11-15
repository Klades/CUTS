// -*- C++ -*-

//=============================================================================
/**
 * @file        CUTE_Dialog.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CUTE_DIALOG_H_
#define _CUTS_CUTE_DIALOG_H_

#include "cuts/config.h"
#include "resource.h"
#include "Interpreter_List.h"

/**
 * @class CUTE_Dialog
 *
 * The main dialog for CUTE.
 */
class CUTS_CUTE_Dialog : public CDialog
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]     parent        The parent window.
   */
  CUTS_CUTE_Dialog (CWnd * parent = 0);

  /// Destructor.
  virtual ~CUTS_CUTE_Dialog (void);

  /**
   * Data exchange method for tranfering information to and from
   * the dialog box controls.
   *
   * @param[in]     pDX         Pointer to the data exchange.
   */
  virtual void DoDataExchange (CDataExchange * pDX);

  virtual BOOL OnInitDialog (void);

  void interpreter_list (CUTS_CUTE_Interpreter_List * list = 0);

  CUTS_CUTE_Interpreter_List * interpreter_list (void);

  const CString & selected_interpreter (void) const;

  const CString & configuration_filename (void) const;

  const CString & parameters (void) const;

  int option (void) const;

private:
  void on_click_browse (void);
  void on_generate_click (void);
  void on_interpret_click (void);

  DECLARE_MESSAGE_MAP ();

  CUTS_CUTE_Interpreter_List * list_;

  CComboBox interpreter_list_;

  CEdit config_;

  CString selected_interpeter_;

  CString config_file_;

  CString parameters_;

  int option_;
};

#if defined (__CUTS_INLINE__)
#include "CUTE_Dialog.inl"
#endif

#endif  // !defined _CUTS_CUTE_DIALOG_H_

