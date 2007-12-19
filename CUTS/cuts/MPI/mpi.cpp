// $Id$

#include "mpi.h"
#include "MPI_Env.h"
#include "Datatype_Port_Manager.h"
#include "cuts/Activation_Record.h"
#include "cuts/Port_Agent.h"
#include "cuts/Thread_Activation_Record.h"
#include "ace/Log_Msg.h"
#include "ace/OS_NS_sys_time.h"

//
// MPI_Init
//
int MPI_Init (int * argc, char *** argv)
{
  // Initialize the MPI infrastructure first.
  int retval = PMPI_Init (argc, argv);

  if (retval == MPI_SUCCESS)
  {
    // Initialize the CUTS profiling infrastructure.
    retval = CUTS_MPI_ENV ()->init (*argc, *argv);
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (cutsmpi): MPI_Init failed\n"));
  }

  return retval;
}

//
// MPI_Finalize
//
int MPI_Finalize (void)
{
  // First, finalize the CUTS environment for MPI. This means
  // finalizing the singleton and then deleting it.
  int retval = CUTS_MPI_ENV ()->fini ();
  CUTS_MPI_Env::close_singleton ();

  // New, we can finalize the MPI environment.
  return PMPI_Finalize ();
}

//
// MPI_Recv
//
int MPI_Recv (void * buf,
              int count,
              MPI_Datatype datatype,
              int source,
              int tag,
              MPI_Comm comm,
              MPI_Status * status)
{
  ACE_DEBUG ((LM_TRACE, "entering MPI_Recv\n"));

  // Get the port agent for the datatype. We then need to allocate
  // a new record from the port agent.
  CUTS_Port_Agent * agent = CUTS_MPI_ENV ()->datatype_mgr ().get (datatype);
  CUTS_Activation_Record * record = agent->record_alloc ();

  // Install the record in TSS.
  CUTS_Activation_Record * old_record =
    CUTS_Thread_Activation_Record::set_record (record);

  // Open the record for writing.
  record->open (source);

  // Record the start time of receiving. This will be used
  // as the 'queue' time for the event.
  ACE_Time_Value start_time = ACE_OS::gettimeofday ();

  MPI_Status tmp_status;
  int retval = PMPI_Recv (buf, count, datatype, source, tag, comm, &tmp_status);

  // Record the stop time of receiving the data. Then calculate
  // how long we waited to receive data.
  ACE_Time_Value stop_time = ACE_OS::gettimeofday ();
  record->queue_time (stop_time - start_time);

  // Make sure we have the correct owner of the record.
  if (source == MPI_ANY_SOURCE)
    record->owner (tmp_status.MPI_SOURCE);

  // Save the status for the caller, if necessary.
  if (status != MPI_STATUS_IGNORE)
    *status = tmp_status;

  if (old_record->is_open ())
  {
    old_record->close ();
    agent->record_free (old_record);
  }

  return retval;
}

//
// MPI_Send
//
int MPI_Send (void * buf,
              int count,
              MPI_Datatype datatype,
              int dest,
              int tag,
              MPI_Comm comm)
{
  // Get the current record.
  CUTS_Activation_Record * record = CUTS_THR_ACTIVATION_RECORD ();

  return PMPI_Send (buf, count, datatype, dest, tag, comm);
}
