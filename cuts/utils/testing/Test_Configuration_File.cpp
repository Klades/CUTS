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


/**
 * @struct append_command
 *
 * Functor for Appending a command to the command list.
 */

struct append_command
{
  typedef CUTS::CommandList::command_iterator::value_type value_type;

  append_command (CUTS_Command_Options_List & testops)
    : testops_ (testops)
  {

  }

  void operator () (const value_type & value)
  {
    CUTS_Command_Options opts;

    // Initialize the command options.
    opts.name_ = value->id ().c_str ();
    opts.exec_ = value->executable ().c_str ();

    if (value->arguments_p ())
      opts.args_  = value->arguments ().c_str ();

    if (value->workingdirectory_p ())
      opts.cwd_ = value->workingdirectory ().c_str ();

    if (value->delay_p ())
      opts.delay_.set (value->delay ());

    if (value->waitforcompletion_p ())
      opts.wait_for_completion_ = value->waitforcompletion ();

    if (value->output_p ())
      opts.stdout_ = value->output ().c_str ();

    if (value->error_p ())
      opts.stderr_ = value->error ().c_str ();

    // Append the command options to the list.
    int retval;

    retval = this->testops_.append (opts);

    if (0 != retval)
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to add %s to %s command list\n"),
                  opts.name_.c_str (), ACE_TEXT ("testops")));
  }

  private:
    CUTS_Command_Options_List & testops_;
};


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
// get_testops
//
int CUTS_Test_Configuration_File::
get_testops (CUTS_Command_Options_List & testops)
{
  /// Create a command option for each command in the
  /// file and append it to the command list
  if (this->config_.testops_p ())
  {
    std::for_each (this->config_.testops ().begin_command (),
                   this->config_.testops ().end_command (),
                   append_command (testops));
  }

  /// Now populate each ACE_Process_Option in the command using the
  /// data gathered in the previous step.

  CUTS_Command_Options_List::ITERATOR iter (testops);

  for (; !iter.done (); ++ iter)
  {
    ACE_CString result;
    ACE_Process_Options * options = &((*iter).item_.options_);
    CUTS_Command_Options * cmd_options = &((*iter).item_);

    CUTS_Text_Processor processor (this->props_);

    /// First the command and its arguments

    std::ostringstream ostr;
    ostr << cmd_options->exec_;

    if (!cmd_options->args_.is_empty ())
      ostr << " " << cmd_options->args_;

    if (!processor.evaluate (ostr.str ().c_str (), result))
      ACE_ERROR_RETURN ((LM_ERROR,
                        "%T (%t) - %M - failed to evaluate command-line\n"),
                        -1);

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - setting command-line to: %s\n",
                result.c_str ()));

    options->command_line (result.c_str ());

    // Next, set the working directory for the options.
    if (!cmd_options->cwd_.is_empty ())
    {
      if (!processor.evaluate (cmd_options->cwd_.c_str (), result))
        ACE_ERROR_RETURN ((LM_ERROR,
                          "%T (%t) - %M - failed to evaluate working directory\n"),
                          -1);

      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - setting working directory to: %s\n",
                  result.c_str ()));

      options->working_directory (result.c_str ());

    }

    // Next, redirect the output/error streams.
    ACE_FILE_IO stderr_handle;
    ACE_FILE_IO stdout_handle;

    ACE_FILE_Connector disk;
    ACE_FILE_Addr file_addr;

    if (!cmd_options->stdout_.is_empty ())
    {
      // Preprocess the output filename.
      if (!processor.evaluate (cmd_options->stdout_.c_str (), result))
        ACE_ERROR_RETURN ((LM_ERROR,
                          "%T (%t) - %M - failed to evaluate output filename\n"),
                          -1);

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

    if (!cmd_options->stderr_.is_empty ())
    {
      // Preprocess the output filename.
      if (!processor.evaluate (cmd_options->stderr_.c_str (), result))
        ACE_ERROR_RETURN ((LM_ERROR,
                          "%T (%t) - %M - failed to evaluate output filename\n"),
                          -1);

        ACE_DEBUG ((LM_DEBUG,
                    "%T (%t) - %M - setting output filename to: %s\n",
                    result.c_str ()));

        // Open the file for the process.
        file_addr.set (result.c_str ());

        if (disk.connect (stderr_handle, file_addr) == -1)
        {
              ACE_ERROR ((LM_ERROR,
                          "%T (%t) - %M - failed to open file %s\n",
                          file_addr.get_path_name ()));
        }
    }

    options->set_handles (ACE_INVALID_HANDLE,
                          stdout_handle.get_handle (),
                          stderr_handle.get_handle ());

  }

  return 0;
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

  if (!processor.evaluate (ostr.str ().c_str (), result))
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to evaluate command-line\n"),
                       -1);

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - setting command-line to: %s\n",
              result.c_str ()));

  options.command_line (result.c_str ());

  // Next, set the working directory for the options.
  if (po.workingdirectory_p ())
  {
    if (!processor.evaluate (po.workingdirectory ().c_str (), result))
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to evaluate working directory\n"),
                         -1);

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
    if (!processor.evaluate (po.output ().c_str (), result))
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to evaluate output filename\n"),
                         -1);

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
    if (!processor.evaluate (po.error ().c_str (), result))
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to evaluate error filename\n"),
                         -1);

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
