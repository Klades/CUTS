// $Id$

#include "StdAfx.h"
#include "Resource.h"
#include "Main_Dialog.h"
#include "Utils/Utils.h"
#include "modelgen.h"

#include "be/BE_Options.h"
#include "be/BE_Manager_Factory.h"

#include "XSCRT/utils/File_Reader_T.h"
#include "XSCRT/utils/XML_Schema_Resolver_T.h"

#include "boost/bind.hpp"

#include "ace/Env_Value_T.h"
#include "ace/OS_NS_string.h"

#include <strstream>
#include <algorithm>

#define CUTS_BE_CUTS_CONFIG     "cuts.config"

BEGIN_MESSAGE_MAP (Main_Dialog, CDialog)
  ON_LBN_SELCHANGE (IDC_BE_LIST, On_BE_List_SelChange)
END_MESSAGE_MAP ()

//
// Main_Dialog
//
Main_Dialog::Main_Dialog (CUTS_BE_Options * options,
                          CWnd * parent)
: CDialog (IDD_MAINDIALOG, parent),
  options_ (options),
  factory_ (0)
{

}

//
// ~Main_Dialog
//
Main_Dialog::~Main_Dialog (void)
{

}

//
// OnInitDialog
//
BOOL Main_Dialog::OnInitDialog (void)
{
  // Let the base class perform its initialization.
  CDialog::OnInitDialog ();

  // Get the CUTS_ROOT environment variable. We need this to locate
  // the default/user configuration values.
  std::string CUTS_ROOT;

  if (this->resolve_CUTS_ROOT (CUTS_ROOT) == 0)
  {
    try
    {
      // Create the user and default configuration.
      std::ostringstream cuts_config, cuts_schema;
      cuts_config << CUTS_ROOT << "/bin/" << CUTS_BE_CUTS_CONFIG;
      cuts_schema << CUTS_ROOT << "/etc/schemas/";

      // Create the file reader for the configuration file.
      XSCRT::utils::File_Reader_T <
        CUTS::Configuration> reader (&CUTS::reader::modelgen);

      reader.parser ()->setEntityResolver (
        XSCRT::utils::xml_schema_resolver (
          XSCRT::utils::Basic_Resolver_T <char> (cuts_schema.str ().c_str ())));

      // Discard comment nodes in the document.
      if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMComments, false))
        reader.parser ()->setFeature (xercesc::XMLUni::fgDOMComments, false);

      // Disable datatype normalization. The XML 1.0 attribute value
      // normalization always occurs though.
      if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMDatatypeNormalization, true))
        reader.parser ()->setFeature (xercesc::XMLUni::fgDOMDatatypeNormalization, true);

      // Do not create EntityReference nodes in the DOM tree. No
      // EntityReference nodes will be created, only the nodes
      // corresponding to their fully expanded substitution text will be
      // created.
      if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMEntities, false))
        reader.parser ()->setFeature (xercesc::XMLUni::fgDOMEntities, false);

      // Perform Namespace processing.
      if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMNamespaces, true))
        reader.parser ()->setFeature (xercesc::XMLUni::fgDOMNamespaces, true);

      // Do not include ignorable whitespace in the DOM tree.
      if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMWhitespaceInElementContent, false))
        reader.parser ()->setFeature (xercesc::XMLUni::fgDOMWhitespaceInElementContent, false);

      // Perform Validation
      if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMValidation, true))
        reader.parser ()->setFeature (xercesc::XMLUni::fgDOMValidation, true);

      // Enable the GetParser()'s schema support.
      if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgXercesSchema, true))
        reader.parser ()->setFeature (xercesc::XMLUni::fgXercesSchema, true);

      // Enable full schema constraint checking, including checking which
      // may be time-consuming or memory intensive. Currently, particle
      // unique attribution constraint checking and particle derivation
      // restriction checking are controlled by this option.
      if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgXercesSchemaFullChecking, true))
        reader.parser ()->setFeature (xercesc::XMLUni::fgXercesSchemaFullChecking, true);

      // The GetParser() will treat validation error as fatal and will exit.
      if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgXercesValidationErrorAsFatal, false))
        reader.parser ()->setFeature (xercesc::XMLUni::fgXercesValidationErrorAsFatal, false);

      CUTS::Configuration config;

      // Open the default configuration.
      if (reader.read (cuts_config.str ().c_str ()))
      {
        // Read the default configuration.
        reader >>= config;

        // Load the generators from the configuration.
        this->init_generators (config);
      }
      else
      {
        ::AfxMessageBox ("Failed to open configuration file",
                         MB_OK | MB_ICONERROR);
      }
    }
    catch (const xercesc::DOMException & ex)
    {
      ::AfxMessageBox (reinterpret_cast <LPCTSTR> (ex.getMessage ()),
                      MB_OK | MB_ICONERROR);
    }
    catch (const xercesc::XMLException & )
    {
      ::AfxMessageBox ("Caught XML exception", MB_OK | MB_ICONERROR);
    }
    catch (...)
    {
      ::AfxMessageBox ("Caught unknown exception", MB_OK | MB_ICONERROR);
    }
  }
  else
  {
    ::AfxMessageBox ("Failed to load configuration file",
                     MB_OK | MB_ICONWARNING);
  }

  // Load backend generators from parsed file.
  return TRUE;
}

//
// DoDataExchange
//
void Main_Dialog::DoDataExchange (CDataExchange * pDX)
{
  // Let the base class handle its business first.
  CDialog::DoDataExchange (pDX);

  // Exchange all data in the dialog with the necesary controls.
  int option = 0;
  DDX_Radio (pDX, IDC_OPERATION, option);

  CUTS_BE_OPTIONS ()->option_ =
    static_cast <CUTS_BE_Options::Menu_Option> (option);

  // Since we aren't saving the data, we need to initialize
  // <outdir> with the data to store in the control.
  CString outdir;

  if (!pDX->m_bSaveAndValidate)
    outdir = CUTS_BE_OPTIONS ()->output_directory_.c_str ();

  DDX_Text (pDX, IDC_OUTPUTDIR, outdir);

  if (pDX->m_bSaveAndValidate)
  {
    // We need to validate the output directory. The output directory
    // is invalid if it is empty. Eventually, we want to make sure
    // the output directory exists.
    outdir.Trim ();

    if (option == CUTS_BE_Options::OPT_GENERATE_SOURCE &&
        outdir.GetLength () == 0)
    {
      ::AfxMessageBox ("Please select a valid output directory",
                      MB_ICONEXCLAMATION);

      // Set the focus of the control and change to fail state.
      this->GetDlgItem (IDC_OUTPUTDIR)->SetFocus ();
      pDX->Fail ();
    }

    // Save the output directory in the cache.
    CUTS_BE_OPTIONS ()->output_directory_ = outdir;
  }

  // We need to exchange data with the list box control. If we are
  // actually saving data from the control and the user has selected
  // to generate source, we need to save the manager factory.
  DDX_Control (pDX, IDC_BE_LIST, this->be_list_);

  if (CUTS_BE_OPTIONS ()->option_ == CUTS_BE_Options::OPT_GENERATE_SOURCE &&
      pDX->m_bSaveAndValidate)
  {
    int index = this->be_list_.GetCurSel ();

    if (index != LB_ERR)
    {
      this->factory_ =
        (CUTS_BE_Manager_Factory *) this->be_list_.GetItemData (index);
    }
    else
    {
      ::AfxMessageBox ("Please select a backend for generating implementation",
                       MB_OK | MB_ICONEXCLAMATION);

      this->GetDlgItem (IDC_BE_LIST)->SetFocus ();
      pDX->Fail ();
    }
  }
}

//
// OnCommand
//
BOOL Main_Dialog::OnCommand (WPARAM wParam, LPARAM lParam)
{
  switch (LOWORD (wParam))
  {
  case IDC_COWORKER_IMPL:
    // Enable the following controls
    this->GetDlgItem (IDC_OUTPUTDIR)->EnableWindow ();
    this->GetDlgItem (IDC_BROWSE)->EnableWindow ();

    this->GetDlgItem (IDC_BE_LIST)->EnableWindow ();
    this->GetDlgItem (IDC_BE_DESCRIPTION)->EnableWindow ();
    break;

  case IDC_OPERATION:
    // Disable the following controls.
    this->GetDlgItem (IDC_OUTPUTDIR)->EnableWindow (FALSE);
    this->GetDlgItem (IDC_BROWSE)->EnableWindow (FALSE);

    this->GetDlgItem (IDC_BE_LIST)->EnableWindow (FALSE);
    this->GetDlgItem (IDC_BE_DESCRIPTION)->EnableWindow (FALSE);
    break;

  case IDC_BROWSE:
    {
      CString outdir;
      std::string path;

      // Get the current output directory.
      this->GetDlgItemText (IDC_OUTPUTDIR, outdir);

      // Let the user select the new output path and store it back
      // into this dialog if the user clicks <OK>.
      if (Utils::getPath ("Select the output directory:",
                          path,
                          outdir.GetBuffer ()))
      {
        this->SetDlgItemText (IDC_OUTPUTDIR, path.c_str ());
      }
    }
    break;

  default:
    return CDialog::OnCommand (wParam, lParam);
  }

  return TRUE;
}

//
// manager_factory
//
CUTS_BE_Manager_Factory * Main_Dialog::factory (void) const
{
  return this->factory_;
}

//
// On_BE_List_SelChange
//
void Main_Dialog::On_BE_List_SelChange (void)
{
  // Get the current selection.
  int index = this->be_list_.GetCurSel ();

  if (index != LB_ERR)
  {
    // Get the data for the select item. The data is actually the
    // factory object we initially stored with the item.
    CUTS_BE_Manager_Factory * factory =
      (CUTS_BE_Manager_Factory *) this->be_list_.GetItemData (index);

    if (factory != 0)
    {
      // Update the description for the select item.
      this->SetDlgItemText (IDC_BE_DESCRIPTION,
                            factory->description ());
    }
    else
    {
      ::AfxMessageBox ("Selected item not properly initialized",
                       MB_OK | MB_ICONERROR);
    }
  }
}

//
// init_generators
//
void Main_Dialog::
init_generators (const CUTS::Configuration & config)
{
  if (config.backend_p ())
  {
    std::for_each (config.backend ().begin_generator (),
                   config.backend ().end_generator (),
                   boost::bind (&Main_Dialog::load_backend_generator,
                                this,
                                _1));
  }
}

//
// load_backend_generator
//
void Main_Dialog::
load_backend_generator (const CUTS::Generator_Description & desc)
{
  // Temporary variable for the generator's factory.
  CUTS_BE_Manager_Factory * factory = 0;

  // Load the backend manager factory.
  if (this->factory_repo_.load (desc.id (), desc.location (), factory))
  {
    // Insert name of factory into listbox.
    int index = this->be_list_.InsertString (-1, factory->name ());

    if (index != LB_ERR)
    {
      this->be_list_.SetItemDataPtr (index, factory);
    }
    else
    {
      // Display an error message to the user.
      std::ostringstream ostr;
      ostr
        << "Failed to add <" << factory->name ()
        << "> to backend list";

      ::AfxMessageBox (ostr.str ().c_str (),
                        MB_ICONEXCLAMATION | MB_OK);
    }
  }
  else
  {
    // Display an error message for the user.
    std::ostringstream ostr;
    ostr << "Failed to load backend <" << desc.id () << ">";

    ::AfxMessageBox (ostr.str ().c_str (),
                     MB_ICONEXCLAMATION | MB_OK);
  }
}

//
// resolve_CUTS_ROOT
//
int Main_Dialog::resolve_CUTS_ROOT (std::string & root)
{
  // Get the install location of CUTS from the Windows registry.
  char path [MAX_PATH];
  long path_size = sizeof (char) * sizeof (path);

  if (::RegQueryValue (HKEY_LOCAL_MACHINE,
                       "Software\\CUTS",
                       path,
                       &path_size) == ERROR_SUCCESS)
  {
    root = path;
  }
  else
  {
    ACE_Env_Value <const char *> CUTS_ROOT ("CUTS_ROOT", "");
    root = CUTS_ROOT;
  }

  return 0;
}

