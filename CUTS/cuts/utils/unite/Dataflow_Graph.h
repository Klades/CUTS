// -*- C++ -*-

//=============================================================================
/**
 * @file        Dataflow_Graph.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_UNIT_TEST_GRAPH_H_
#define _CUTS_UNITE_UNIT_TEST_GRAPH_H_

#include "ace/Hash_Map_Manager.h"
#include "ace/Null_Mutex.h"
#include "ace/SString.h"
#include "boost/graph/adjacency_list.hpp"
#include "Unite_export.h"
//#include "Log_Format.h"

// Forward decl.
class CUTS_Log_Format;
class CUTS_Log_Format_Adapter;

/**
 * @ingroup UNITE_Core
 *
 * @class CUTS_Unit_Test_Graph_Traits
 *
 * Traits for the unit test graph.
 */
class CUTS_Unit_Test_Graph_Traits
{
public:
  struct log_format_t
  {
    typedef boost::vertex_property_tag kind;
  };

  typedef
    boost::property <boost::vertex_name_t, ACE_CString,
    boost::property <log_format_t, CUTS_Log_Format *> >
    property_type;
};

/// Type defintion of the graph type.
typedef
  boost::adjacency_list <boost::vecS,
                         boost::vecS,
                         boost::directedS,
                         CUTS_Unit_Test_Graph_Traits::property_type>
                         CUTS_Unit_Test_Graph_Type;

/**
 * @class CUTS_Dataflow_Graph
 *
 * Dependency graph between the log formats for a unit test.
 */
class CUTS_UNITE_Export CUTS_Dataflow_Graph
{
public:
  /// Type definition to the vertex descriptor.
  typedef boost::graph_traits <CUTS_Unit_Test_Graph_Type>::vertex_descriptor vertex_descriptor;

  /// Type definition to the vertex descriptor.
  typedef boost::graph_traits <CUTS_Unit_Test_Graph_Type>::vertex_iterator vertex_iterator;

  /// Type definition of the edge descriptor.
  typedef boost::graph_traits <CUTS_Unit_Test_Graph_Type>::edge_descriptor edge_descriptor;

  //typedef std::auto_ptr<CUTS_Log_Format_Adapter> adapter_ptr;

  /// Default constructor.
  CUTS_Dataflow_Graph (void);

  /**
   * Initializing constructor
   *
   * @param[in]         name        Name of the graph.
   */
  CUTS_Dataflow_Graph (const ACE_CString & name);

  /// Desturctor.
  ~CUTS_Dataflow_Graph (void);

  bool create_log_format (const ACE_CString & name);

  bool create_log_format (const ACE_CString & name, CUTS_Log_Format *& format);

  /**
   * Associate two log formats, i.e., define causality.
   *
   * @param[in]         src           Source log format
   * @param[in]         dst           Destination log format
   */
  bool connect (const ACE_CString & src, const ACE_CString & dst);

  /**
   * Get the name of the graph.
   *
   * @return          The name of the graph.
   */
  const ACE_CString & name (void) const;

  /**
   * Set the name of the graph.
   *
   * @param[in]       name        The new name of the graph
   */
  void name (const ACE_CString & name);

  CUTS_Log_Format * get_log_format (vertex_descriptor vertex) const;

  CUTS_Log_Format * get_log_format (vertex_iterator iter) const;

  void get_process_order (std::vector <vertex_descriptor> & list) const;

  const CUTS_Unit_Test_Graph_Type & graph (void) const;

  CUTS_Log_Format_Adapter * adapter(void);

  void adapter(CUTS_Log_Format_Adapter *adapter);

private:
  void normalize_name (void);

  /// Name of the unit test graph.
  ACE_CString name_;

  CUTS_Unit_Test_Graph_Type graph_;

  /// Type definition of the vertex cache.
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                vertex_descriptor,
                                ACE_Null_Mutex> VERTEX_MAP;

  /// Local cache of the vertices.
  VERTEX_MAP vertices_;

  CUTS_Log_Format_Adapter * adapter_;
};

#if defined (__CUTS_INLINE__)
#include "Dataflow_Graph.inl"
#endif

#endif  // !defined _CUTS_UNITE_UNIT_TEST_GRAPH_H_
