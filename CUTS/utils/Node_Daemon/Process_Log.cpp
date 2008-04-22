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

#ifdef min
#undef min
#endif

#include <algorithm>

#define ENTRY_BUFFER_SIZE  10

static const char * TEMP_FILENAME = "cutsnode_d.tmp";

//=============================================================================
/**
 * @struct Find_By_PID
 *
 * Functor for locating a Process_Log_Entry by its pid_t.
 */
//=============================================================================

struct Find_By_PID
{
  /**
   * Constructor
   *
   * @param[in]       pid           Id of the process
   */
  inline Find_By_PID (pid_t pid)
    : pid_ (pid)
  {

  }

  /**
   * Functor operator.
   *
   * @param[in]     ple       Current element from a collection.
   * @retval        true      The pid of the \ple is a match.
   * @retval        false     The pid of the \ple is not a match.
   */
  inline bool operator () (const CUTS_Process_Info & info)
  {
    return this->pid_ == info.pid_;
  }

private:
  /// Process id in question.
  pid_t pid_;
};

//=============================================================================
/*
 * Process_Log
 */
//=============================================================================

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
process_spawn (const CUTS_Process_Info & info)
{
  ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->lock_, false);

  // We are going to open the file for writing and append the
  // new information to the end of the <logfile>. We will have
  // a seperate thread that will "clean" the <logfile> periodically.

  std::ofstream logfile;
  //logfile.open (this->log_file_.c_str (),
  //              std::ios_base::out |
  //              std::ios_base::binary |
  //              std::ios_base::app);

  //if (!logfile.is_open ())
  //{
  //  ACE_ERROR_RETURN ((LM_ERROR,
  //                     "*** error (process log): failed to open file %s\n",
  //                     this->log_file_.c_str ()),
  //                     false);
  //}

  //// Write the process id.
  //logfile.write (reinterpret_cast <const char *> (&info.pid_),
  //               sizeof (pid_t));

  //// Write the state of process log.
  //logfile.write (reinterpret_cast <const char *> (&info.state_), 
  //               sizeof (char));

  //// Write the name to the log.
  //size_t length = info.id_.length ();

  //logfile.write (reinterpret_cast <const char *> (&length),
  //               sizeof (size_t));

  //logfile.write (info.id_.c_str (), length + 1);

  //// Write the executable name to the log.
  //length = info.options_..length ();

  //logfile.write (reinterpret_cast <const char *> (&length),
  //               sizeof (size_t));

  //logfile.write (info.exec_.c_str (), length + 1);

  //// Write the arguments to the log.
  //length = info.args_.length ();

  //logfile.write (reinterpret_cast <const char *> (&length),
  //               sizeof (size_t));

  //logfile.write (info.args_.c_str (), length + 1);

  // Close the log file.
  logfile.close ();

  return logfile.good ();
}

//
// process_exit
//
bool Process_Log::process_exit (pid_t pid)
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
                       "*** error (process log): failed to open file %s\n",
                       this->log_file_.c_str ()),
                       false);
  }

  // Temporary variables for searching the log file.
  pid_t tmppid;
  char state;
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

    // Read the state.
    logfile.read (&state, sizeof (char));

    // Bypass the name of the process.
    logfile.read (reinterpret_cast <char *> (&length), sizeof (size_t)); 
    logfile.seekg (length + 1, std::ios_base::cur);

    // Bypass the executable name of the process.
    logfile.read (reinterpret_cast <char *> (&length), sizeof (size_t)); 
    logfile.seekg (length + 1, std::ios_base::cur);

    // Bypass the arguments of the process.
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
                "*** error (process log): failed to create file %s\n",
                log_file));
  }
}

//
// get_active_processes
//
bool Process_Log::
get_active_processes (CUTS_Process_Info_Set & list)
{
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
                       "(%N:%l) file %s does not exist\n",
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
                       "(%N:%l) failed to open temporary file for copying\n"),
                       false);
  }

  size_t entry_count, count = 0;
  bool error = false;

  //do
  //{
  //  entry_count = this->batch_read (logfile, buffer, ENTRY_BUFFER_SIZE);

  //  for (size_t i = 0; i < entry_count; i ++)
  //  {
  //    // We only care to copy over the active processes.
  //    if (buffer[i].active_)
  //    {
  //      tmpfile.write (reinterpret_cast <char *> (&buffer[i]),
  //                     sizeof (Process_Log_Entry));

  //      // Something bad has happened and we need to just stop
  //      // and abort the cleaning operation.
  //      if (tmpfile.bad ())
  //      {
  //        ACE_ERROR ((LM_ERROR,
  //                    "*** error (process log): error occured while clean "
  //                    "file; aborting...\n"));
  //        error = true;
  //        break;
  //      }

  //      ++ count;
  //    }
  //  }
  //} while (entry_count != 0);

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
