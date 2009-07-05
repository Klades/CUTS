// -*- C++ -*-

//=============================================================================
/**
 * @file        Process_Dependency_Graph.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_PROCESS_DEPENDENCY_GRAPH_H_
#define _CUTS_PROCESS_DEPENDENCY_GRAPH_H_

#include "ace/Hash_Map_Manager.h"
#include "ace/Null_Mutex.h"
#include "ace/SString.h"
#include "boost/graph/adjacency_list.hpp"
#include "cuts/config.h"

// Forward decl.
class CUTS_Process_Options;

/**
 * @class CUTS_Process_Dependency_Graph_Traits
 *
 * Traits for the process dependency graph.
 */
class CUTS_Process_Dependency_Graph_Traits
{
public:
  struct process_opts_t
  {
    typedef boost::vertex_property_tag kind;
  };

  typedef
    boost::property <boost::vertex_name_t, ACE_CString,
    boost::property <process_opts_t, CUTS_Process_Options *> > property_type;
};

/// Type definition of process dependency graph base type.
typedef boost::adjacency_list <boost::vecS,
                               boost::vecS,
                               boost::directedS,
                               CUTS_Process_Dependency_Graph_Traits::property_type>
                               CUTS_Process_Dependency_Graph_Base;

/**
 * @class CUTS_Process_Dependency_Graph
 *
 * Simple class for constructing a dependency graph of traits. This
 * will help the CUTS_Virtual_Env spawn processes in the correct order.
 */
class CUTS_Process_Dependency_Graph :
  public CUTS_Process_Dependency_Graph_Base
{
public:
  /// Type definition of the graph type.
  typedef CUTS_Process_Dependency_Graph_Base graph_type;

  /// Type definition to the vertex descriptor.
  typedef boost::graph_traits <graph_type>::vertex_descriptor vertex_descriptor;

  /// Type definition of the edge descriptor.
  typedef boost::graph_traits <graph_type>::edge_descriptor edge_descriptor;

  /// Default constructor.
  CUTS_Process_Dependency_Graph (void);

  /// Number vertices in the graph.
  CUTS_Process_Dependency_Graph (size_t vertices);

  /// Desturctor.
  ~CUTS_Process_Dependency_Graph (void);

  /**
   * Insert a new process in the graph.
   *
   * @param[in]         name        Name of the process
   * @param[in]         opts        Process options to insert
   */
  int insert (const char * name, CUTS_Process_Options * opts);

  /**
   * @overload
   */
  int insert (const ACE_CString & name, CUTS_Process_Options * opts);

  /**
   * Create a dependency between to processes. In this method, the
   * source process depends on the destination process.
   *
   * @param[in]         src             Source process
   * @param[in]         dst             Destination proess
   */
  int connect (const char * src, const char * dst);

  /**
   * @overloaded
   */
  int connect (const ACE_CString & src, const ACE_CString & dst);

  /**
   * Get the execution order of the dependency graph. The \a sorted_list
   * will contain the order to execute process so that each process
   * that depends on other process has those processes executed first.
   *
   * @param[out]        sorted_list     Sort list of process
   */
  void get_execution_order (std::vector <vertex_descriptor> & sorted_list);

private:
  /// Type definition of the vertex cache.
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                vertex_descriptor,
                                ACE_Null_Mutex> VERTEX_MAP;

  /// Local cache of the vertices.
  VERTEX_MAP vertices_;
};

#if defined (__CUTS_INLINE__)
#include "Process_Dependency_Graph.inl"
#endif

#endif  // !defined _CUTS_UNITE_UNIT_TEST_GRAPH_H_
