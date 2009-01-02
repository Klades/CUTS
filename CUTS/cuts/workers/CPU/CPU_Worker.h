// -*- C++ -*-

//=============================================================================
/**
 * @file    CPUWorker.h
 *
 * $Id$
 *
 * This file contains the default CPU worker in CUTS.
 *
 * @author James H. Hill <hillj@isis.vanderbilt.edu>
 */
//=============================================================================

#ifndef _CUTS_CPU_WORKER_H_
#define _CUTS_CPU_WORKER_H_

#include "CPU_Worker_export.h"
#include "CPU_Worker_T.h"
#include "ace/Hash_Map_Manager_T.h"
#include "ace/High_Res_Timer.h"
#include "ace/Null_Mutex.h"

/**
 * @struct CUTS_Basic_CPU_Worker
 */
struct CUTS_Basic_CPU_Worker
{
  inline void perform_work (void)
  {
    this->timer_.start ();
  }

private:
  ACE_High_Res_Timer timer_;
};

/**
 * @class CUTS_CPU_Worker
 *
 * Basic worker that burns CPU time. The CPU worker is designed to
 * occupy the CPU for the specified number of milliseconds. It does
 * not take into account CPU utilization, or monitor it.
 */
class CUTS_CPU_WORKER_Export CUTS_CPU_Worker :
  public CUTS_CPU_Worker_T <CUTS_Basic_CPU_Worker>
{
public:
  /// Constructor.
  CUTS_CPU_Worker (void);

  /// Destructor.
  virtual ~CUTS_CPU_Worker (void);
};

/**
 * @class CUTS_LD_CPU_Worker
 *
 * Load-dependent CPU workload generator.In order to correctly use
 * this workload generator, you must first load its profile. Afterwards,
 * you use the profile_run () method to execute workload base on
 * some key. If you do not want to execute a load-dependent workload,
 * then use the run () method.
 */
class CUTS_CPU_WORKER_Export CUTS_LD_CPU_Worker :
  public CUTS_CPU_Worker
{
public:
  /// Default constructor
  CUTS_LD_CPU_Worker (void);

  /// Destructor.
  virtual ~CUTS_LD_CPU_Worker (void);

  /**
   * Load a workload profile for the CPU worker
   *
   * @param[in]       profile         Location of the profile
   * @retval          0               Successfully loaded profile
   * @retval          -1              Failed to load profile
   */
  int load_profile (const ACE_CString & profile);

  /**
   * Execute time on the CPU.
   *
   * @param[in]       key             Key to execute
   */
  int profile_run (const ACE_CString & key);

private:
  /// Type definition of the map type.
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                double,
                                ACE_Null_Mutex> map_type;

  /// Profile for the load-dependent workload generator.
  map_type profile_;
};

CUTS_WORKER_FACTORY_EXPORT_DECL (CUTS_CPU_WORKER_Export);

#if defined (__CUTS_INLINE__)
#include "CPU_Worker.inl"
#endif

#endif  // !defined _CUTS_CPU_WORKER_H_
