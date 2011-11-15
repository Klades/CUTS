// -*- C++ -*-

//=============================================================================
/**
 * @file          Datatype_Ports.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_MPI_DATATYPE_PORT_MANAGER_H_
#define _CUTS_MPI_DATATYPE_PORT_MANAGER_H_

#include "mpi.h"
#include "cuts/config.h"
#include "ace/Hash_Map_Manager_T.h"
#include "ace/Null_Mutex.h"

// Forward decl.
class CUTS_Benchmark_Agent;

// Forward decl.
class CUTS_Port_Agent;

//=============================================================================
/**
 * @class CUTS_MPI_Datatype_Port_Manager
 */
//=============================================================================

class CUTS_MPI_Datatype_Port_Manager
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       agent       Benchmark agent assigned to manager.
   */
  CUTS_MPI_Datatype_Port_Manager (CUTS_Benchmark_Agent * agent);

  /// Destructor.
  ~CUTS_MPI_Datatype_Port_Manager (void);

  /**
   * Get the port agent for the specified data type. If the agent
   * for the datatype does not exist, then one is created.
   *
   * @return          Pointer to the port agent.
   */
  CUTS_Port_Agent * get (MPI_Datatype datatype);

  int install (MPI_Datatype datatype,
               CUTS_Port_Agent ** agent = 0);

  int install (MPI_Datatype datatype,
               const ACE_CString & name,
               CUTS_Port_Agent ** agent = 0);

  /**
   * Get port agent from the manager. The caller has the option of
   * creating the agent if it does not exist.
   */
  int find (MPI_Datatype datatype,
            CUTS_Port_Agent * & agent) const;

private:
  int init (void);


  /// Pointer to the benchmark agent.
  CUTS_Benchmark_Agent * agent_;

  /// Type definition of datatype to port agent mapping.
  typedef
    ACE_Hash_Map_Manager <MPI_Datatype, CUTS_Port_Agent *, ACE_Null_Mutex>
    MPI_Datatype_Map;

  /// Mapping of datatypes to port agents.
  MPI_Datatype_Map datatype_map_;
};

#if defined (__CUTS_INLINE__)
#include "Datatype_Port_Manager.inl"
#endif

#endif  // !defined _CUTS_MPI_DATATYPE_PORT_MANAGER_H_
