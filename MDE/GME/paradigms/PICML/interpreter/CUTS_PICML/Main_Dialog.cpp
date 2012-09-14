// $Id$

#include "StdAfx.h"
#include "Resource.h"
#include "Main_Dialog.h"

#include "boost/bind.hpp"
#include "Utils/Utils.h"

#include <algorithm>

BEGIN_MESSAGE_MAP (Main_Dialog, CDialog)
  ON_BN_CLICKED (IDC_BROWSE, on_browse_clicked)
END_MESSAGE_MAP ()

//
// Main_Dialog
//
Main_Dialog::Main_Dialog (CWnd * parent)
: CDialog (IDD_MAINDIALOG, parent)
{

}

//
// ~Main_Dialog
//
Main_Dialog::~Main_Dialog (void)
{

}

/**
 * @struct add_string_t
 */
struct add_string_t
{
  add_string_t (CComboBox & item)
    : item_ (item),
      index_ (0)
  {

  }

  void operator () (const CString & iter)
  {
    int index = this->item_.AddString (iter);

    if (index >= 0)
      this->item_.SetItemData (index, this->index_ ++);
  }

private:
  /// The current index for the string.
  int index_;

  /// Target combobox for inserting strings.
  CComboBox & item_;
};

//
// OnInitDialog
//
BOOL Main_Dialog::OnInitDialog (void)
{
  CDialog::OnInitDialog ();

  // Insert the backend strings into the list box.
  std::for_each (this->opts_.backends_.begin (),
                 this->opts_.backends_.end (),
                 add_string_t (this->generators_));

  return TRUE;
}

//
// DoDataExchange
//
void Main_Dialog::DoDataExchange (CDataExchange * pDX)
{
  // Let the base class handle its business first.
  CDialog::DoDataExchange (pDX);

  // Exchange the text for the output directory.
  DDX_Text (pDX, IDC_OUTPUTDIR, this->opts_.output_dir_);

  if (pDX->m_bSaveAndValidate)
  {
    // We need to validate the output directory. The output directory
    // is invalid if it is empty. Eventually, we want to make sure
    // the output directory exists.
    this->opts_.output_dir_.Trim ();

    if (this->opts_.output_dir_.GetLength () == 0)
    {
      ::AfxMessageBox ("Output directory is empty", MB_ICONEXCLAMATION);

      // Set the focus of the control and change to fail state.
      this->GetDlgItem (IDC_OUTPUTDIR)->SetFocus ();
      pDX->Fail ();
    }
  }

  // We need to exchange data with the list box control. If we are
  // actually saving data from the control and the user has selected
  // to generate source, we need to save the manager factory.
  DDX_Control (pDX, IDC_CODEGEN, this->generators_);

  if (pDX->m_bSaveAndValidate)
  {
    DDX_CBIndex (pDX, IDC_CODEGEN, this->opts_.selected_backend_);

    if (this->opts_.selected_backend_ < 0)
    {
      ::AfxMessageBox ("Please select backend generator", MB_ICONEXCLAMATION);

      // Set the focus of the control and change to fail state.
      this->GetDlgItem (IDC_CODEGEN)->SetFocus ();
      pDX->Fail ();
    }
  }
  else
    this->generators_.SetCurSel (this->opts_.selected_backend_);

  // Get the remaining control values.
  DDX_Check (pDX, IDC_ICCM_COMPLIANT, this->opts_.iccm_compliant_);
}

//
// on_browse_clicked
//
void Main_Dialog::on_browse_clicked (void)
{
  CString outdir;
  std::string path;

  // Get the current output directory.
  this->GetDlgItemText (IDC_OUTPUTDIR, outdir);

  // Let the user select the new output path and store it back
  // into this dialog if the user clicks <OK>.
  if (Utils::getPath ("Select the output directory:", path, outdir.GetBuffer ()))
    this->SetDlgItemText (IDC_OUTPUTDIR, path.c_str ());
}
