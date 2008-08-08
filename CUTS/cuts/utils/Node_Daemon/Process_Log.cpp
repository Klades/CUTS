// $Id$

#include "Process_Log.h"

#if !defined (__CUTS_INLINE__)
#include "Process_Log.inl"
#endif

#include "ace/Guard_T.h"
#include "ace/Log_Msg.h"
#include "ace/OS_NS_stdio.h"
#include "ace/OS_NS_unistd.h"
#include "ace/streams.h"

static const char * TEMP_FILENAME = "cutsnode_d.tmp";

//
// Process_Log
//
Process_Log::Process_Log (void)
{

}

//
// Process_Log
//
Process_Log::Process_Log (const char * log)
: log_file_ (log)
{

}

//
// ~Process_Log
//
Process_Log::~Process_Log (void)
{

}

//
// process_spawn
//
bool Process_Log::
process_insert (CUTS_Process_Info & info)
{
  ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->lock_, false);

  // We are going to open the file for writing and append the
  // new information to the end of the <logfile>. We will have
  // a seperate thread that will "clean" the <logfile> periodically.

  std::ofstream logfile;

  logfile.open (this->log_file_.c_str (),
                std::ios_base::out |
                std::ios_base::binary |
                std::ios_base::app);

  if (!logfile.is_open ())
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - failed to open file %s\n",
                       this->log_file_.c_str ()),
                       false);
  }

  // Write the process id.
  logfile.write (reinterpret_cast <const char *> (&info.pid_),
                 sizeof (pid_t));

  // Write the state of process log.
  logfile.write (reinterpret_cast <const char *> (&info.state_),
                 sizeof (char));


  // Write the remaining information about the process to the log.
  this->write_string (logfile, info.id_);
  this->write_string (logfile, info.options_.command_line_buf ());
  this->write_string (logfile, info.options_.working_directory ());

  // Close the log file.
  logfile.close ();
  return logfile.good ();
}

//
// process_exit
//
bool Process_Log::process_remove (pid_t pid)
{
  ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->lock_, false);

  // Open the log file for processing. We want to overwrite any
  // inactive processes before appending to the file.
  // proce

  std::fstream logfile;
  logfile.open (this->log_file_.c_str (),
                std::ios_base::in |
                std::ios_base::out |
                std::ios_base::binary);

  if (!logfile.is_open ())
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - failed to open file %s\n",
                       this->log_file_.c_str ()),
                       false);
  }

  // Temporary variables for searching the log file.
  char state;
  pid_t tmppid;
  size_t length;

  while (!logfile.eof ())
  {
    // Read the process id.
    logfile.read (reinterpret_cast <char *> (&tmppid), sizeof (pid_t));

    if (pid == tmppid)
    {
      // Move the put pointer.
      logfile.seekp (logfile.tellg (), std::ios_base::beg);

      // Write the new state of the process.
      state = 0;
      logfile.write (&state, sizeof (char));

      // We can exit this control loop.
      break;
    }

    // Bypass the state of the process.
    logfile.seekg (1, std::ios_base::cur);

    // Bypass the name of the process.
    logfile.read (reinterpret_cast <char *> (&length), sizeof (size_t));
    logfile.seekg (length + 1, std::ios_base::cur);

    // Bypass the command-line of the process.
    logfile.read (reinterpret_cast <char *> (&length), sizeof (size_t));
    logfile.seekg (length + 1, std::ios_base::cur);

    // Bypass the working directory of the process.
    logfile.read (reinterpret_cast <char *> (&length), sizeof (size_t));
    logfile.seekg (length + 1, std::ios_base::cur);
  }

  // Close the log file.
  logfile.close ();
  return logfile.good ();
}

//
// log_file
//
void Process_Log::log_file (const char * log_file)
{
  // Verify that the file exists.
  std::ofstream logfile;
  logfile.open (log_file, std::ios_base::in | std::ios_base::binary);

  if (!logfile.is_open ())
  {
    // Ok, we need to create a new file!!
    logfile.open (log_file, std::ios_base::out | std::ios_base::binary);
  }

  if (logfile.is_open ())
  {
    // Great, we have a valid file!!!
    logfile.close ();

    this->log_file_ = log_file;
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - failed to create file %s\n",
                log_file));
  }
}

//
// get_active_processes
//
bool Process_Log::
get_active_processes (CUTS_Process_Info_Set & list)
{
  ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->lock_, false);

  // Open the log file for processing. We want to overwrite any
  // inactive processes before appending to the file.
  std::ifstream logfile;
  logfile.open (this->log_file_.c_str (),
                std::ios_base::in | std::ios_base::binary);

  if (!logfile.is_open ())
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - file %s does not exist\n",
                       this->log_file_.c_str ()),
                       false);
  }


  CUTS_Process_Info * info = 0;
  ACE_Auto_Ptr <CUTS_Process_Info> auto_clean (info);

  ACE_CString command_line;
  ACE_CString working_directory;

  while (!logfile.eof ())
  {
    if (info == 0)
    {
      ACE_NEW_NORETURN (info, CUTS_Process_Info ());
      auto_clean.reset (info);
    }

    if (info != 0)
    {
      // Read the information about the current process.
      logfile.read (reinterpret_cast <char *> (&info->pid_), sizeof (pid_t));
      logfile.read (&info->state_, sizeof (char));

      this->read_string (logfile, info->id_);
      this->read_string (logfile, command_line);
      this->read_string (logfile, working_directory);

      if (info->state_ == 1)
      {
        // Save the remaining information about the process.
        info->options_.command_line (command_line.c_str ());
        info->options_.working_directory (working_directory.c_str ());

        // Insert the process information into the listing.
        if (list.insert (info) == 0)
          auto_clean.release ();
      }
    }
  }

  return true;
}


//
// clean
//
bool Process_Log::clean (size_t * active_count)
{
  ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->lock_, false);

  // Open the log file for processing. We want to overwrite any
  // inactive processes before appending to the file.
  std::ifstream logfile;
  logfile.open (this->log_file_.c_str (),
                std::ios_base::in | std::ios_base::binary);

  if (!logfile.is_open ())
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - file %s does not exist\n",
                       this->log_file_.c_str ()),
                       false);
  }

  ofstream tmpfile;
  tmpfile.open (TEMP_FILENAME,
                std::ios_base::out |
                std::ios_base::binary |
                std::ios_base::trunc);

  if (!tmpfile.is_open ())
  {
    logfile.close ();
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - failed to open temporary file for copying\n"),
                       false);
  }

  size_t count = 0;
  bool error = false;

  // Temporary variables for searching the log file.
  char state;
  pid_t pid;
  ACE_CString name, command_line, working_directory;

  while (!logfile.eof ())
  {
    // Read the information about the current process.
    logfile.read (reinterpret_cast <char *> (&pid), sizeof (pid_t));
    logfile.read (&state, sizeof (char));

    this->read_string (logfile, name);
    this->read_string (logfile, command_line);
    this->read_string (logfile, working_directory);

    // We need to write the process's information to the temp file
    // if it's still in an active state.
    if (state == 1)
    {
      tmpfile.write (reinterpret_cast <char *> (&pid), sizeof (pid_t));
      tmpfile.write (&state, sizeof (char));

      this->write_string (tmpfile, name);
      this->write_string (tmpfile, command_line);
      this->write_string (tmpfile, working_directory);

      // Increment the active process counter.
      if (tmpfile.good ())
        ++ count;
    }
  }

  // Close both files then replace the old file w/ the new file
  // if we did not experience any errors.
  logfile.close ();
  tmpfile.close ();

  if (!error)
    ACE_OS::rename (TEMP_FILENAME, this->log_file_.c_str ());
  else
    ACE_OS::unlink (TEMP_FILENAME);

  // Save the count for the callee.
  if (active_count != 0)
    *active_count = count;

  return !error;
}

//
// read_string
//
int Process_Log::
read_string (std::ifstream & file, ACE_CString & str)
{
  // Read the length of the string.
  size_t length;
  file.read (reinterpret_cast <char *> (&length), sizeof (size_t));

  // Read the contents of the string.
  char * ptr = 0;
  ACE_NEW_RETURN (ptr, char [length + 1], -1);

  ACE_Auto_Array_Ptr <char> data (ptr);
  file.read (ptr, length + 1);

  // Save the data in the string.
  str.set (data.release (), length, false);
  return 0;
}

//
// write_string
//
int Process_Log::
write_string (std::ofstream & file, const char * str, size_t length)
{
  // Write the length of the string.
  file.write (reinterpret_cast <char *> (&length), sizeof (size_t));

  // Write the contents of the string, including it's NULL terminator.
  file.write (str, length + 1);
  return 0;
}
