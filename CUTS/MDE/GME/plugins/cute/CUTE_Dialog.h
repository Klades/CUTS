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
#include "ace/Unbounded_Set.h"
#include "ace/SString.h"

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

  void interpreter_list (ACE_Unbounded_Set <ACE_CString> * list = 0);

  ACE_Unbounded_Set <ACE_CString> * interpreter_list (void);

private:
  void on_click_browse (void);

  DECLARE_MESSAGE_MAP ();

  ACE_Unbounded_Set <ACE_CString> * list_;

  CComboBox interpreter_list_;

  CEdit config_;
};

#if defined (__CUTS_INLINE__)
#include "CUTE_Dialog.inl"
#endif

#endif  // !defined _CUTS_CUTE_DIALOG_H_

