// $Id$

#include "Test_Configuration_File.h"

#if !defined (__CUTS_INLINE__)
#include "Test_Configuration_File.inl"
#endif

#include "cuts/utils/Property_Map.h"
#include "cuts/utils/Text_Processor.h"
#include "ace/Env_Value_T.h"
#include "ace/FILE_Connector.h"
#include "ace/Process.h"
#include "ace/SString.h"
#include <sstream>

//
// configure
//
void CUTS_Test_Configuration_File::configure (void)
{
  CUTS_TEST_TRACE ("CUTS_Test_Configuration_File::configure (void)");

  ACE_Env_Value <char *> CUTS_ROOT ("CUTS_ROOT", "");

  std::ostringstream schemas_dir;
  schemas_dir << CUTS_ROOT << "/etc/schemas/";
  this->br_.path (schemas_dir.str ().c_str ());

  // Configure the entity resolver.
  this->parser_->setEntityResolver (&this->resolver_);
  this->parser_->setCreateCommentNodes (false);
  this->parser_->setCreateEntityReferenceNodes (false);
  this->parser_->setDoNamespaces (true);
  this->parser_->setIncludeIgnorableWhitespace (false);
  this->parser_->setValidationScheme (AbstractDOMParser::Val_Auto);
  this->parser_->setDoSchema (true);
  this->parser_->setValidationSchemaFullChecking (true);
  this->parser_->setValidationConstraintFatal (false);
}

//
// load
//
bool CUTS_Test_Configuration_File::load (const ACE_CString & str)
{
  // First, read the configuration file.
  if (!reader_type::read (str.c_str ()))
    return false;

  // Convert the XML document into its object format.
  *this >>= this->config_;
  return true;
}

//
// get_startup_process
//
int CUTS_Test_Configuration_File::
get_startup_process (ACE_Process_Options & options)
{
  if (this->config_.startup_p ())
    return this->load_process_options (this->config_.startup (), options);

  return -1;
}

//
// get_shutdown_process
int CUTS_Test_Configuration_File::
get_shutdown_process (ACE_Process_Options & options)
{
  if (this->config_.shutdown_p ())
    return this->load_process_options (this->config_.shutdown (), options);

  return -1;
}

//
// load_process_options
//
int CUTS_Test_Configuration_File::
load_process_options (const CUTS::processOptions & po,
                      ACE_Process_Options & options)
{
  ACE_CString result;
  CUTS_Text_Processor processor (this->props_);

  // First, set the command-line for the process options.
  std::ostringstream ostr;
  ostr << po.executable ();

  if (po.arguments_p ())
    ostr << " " << po.arguments ();

  if (processor.evaluate (ostr.str ().c_str (), result) == -1)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to evaluate command-line\n"),
                       -1);
  }

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - setting command-line to: %s\n",
              result.c_str ()));

  options.command_line (result.c_str ());

  // Next, set the working directory for the options.
  if (po.workingdirectory_p ())
  {
    if (processor.evaluate (po.workingdirectory ().c_str (), result) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to evaluate working directory\n"),
                         -1);
    }

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - setting working directory to: %s\n",
                result.c_str ()));

    options.working_directory (result.c_str ());
  }

  // Next, redirect the output/error streams.
  ACE_FILE_IO stderr_handle;
  ACE_FILE_IO stdout_handle;

  ACE_FILE_Connector disk;
  ACE_FILE_Addr file_addr;

  if (po.output_p ())
  {
    // Preprocess the output filename.
    if (processor.evaluate (po.output ().c_str (), result) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to evaluate output filename\n"),
                         -1);
    }

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - setting output filename to: %s\n",
                result.c_str ()));

    // Open the file for the process.
    file_addr.set (result.c_str ());

    if (disk.connect (stdout_handle, file_addr) == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to open file %s\n",
                  file_addr.get_path_name ()));
    }
  }

  if (po.error_p ())
  {
    // Preprocess the error filename.
    if (processor.evaluate (po.error ().c_str (), result) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to evaluate error filename\n"),
                         -1);
    }

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - setting error filename to: %s\n",
                result.c_str ()));

    // Open the file for the process.
    file_addr.set (result.c_str ());

    if (disk.connect (stderr_handle, file_addr) == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - failed to open file %s\n",
                  file_addr.get_path_name ()));
    }
  }

  // Set the handles for the process.
  options.set_handles (ACE_INVALID_HANDLE,
                       stdout_handle.get_handle (),
                       stderr_handle.get_handle ());

  return -1;
}
