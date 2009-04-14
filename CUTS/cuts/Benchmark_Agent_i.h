// -*- C++ -*-

//=============================================================================
/**
 * @file    Benchmark_Agent_i.h
 *
 * $Id$
 *
 * @author  James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BENCHMARK_AGENT_T_H_
#define _CUTS_BENCHMARK_AGENT_T_H_

#include "Benchmark_Agent.h"
#include "idl/CUTSS.h"

//=============================================================================
/**
 * @class Benchmark_Agent_i
 */
//=============================================================================

class CUTS_Export Benchmark_Agent_i :
  virtual public ::POA_CUTS::Benchmark_Agent,
  public CUTS_Benchmark_Agent
{
public:
  /// Constructor.
  Benchmark_Agent_i (void);

  /// Destructor.
  virtual ~Benchmark_Agent_i (void);

  /// Get the performance data from the Benchmark_Agent
  virtual void collect_performance_data (CUTS::Component_Metric_out data);
};

#if defined (__CUTS_INLINE__)
#include "cuts/Benchmark_Agent_i.inl"
#endif

#endif  // !defined _CUTS_BENCHMARK_AGENT_T_H_
