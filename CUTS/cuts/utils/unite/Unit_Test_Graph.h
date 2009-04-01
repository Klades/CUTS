// -*- C++ -*-

//=============================================================================
/**
 * @file        Unit_Test_Graph.h
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

// Forward decl.
class CUTS_Log_Format;

/**
 * @class CUTS_Unit_Test_Graph
 */
class CUTS_UNITE_Export CUTS_Unit_Test_Graph
{
public:
  /// Type definition of the map type.
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                CUTS_Log_Format *,
                                ACE_Null_Mutex> formats_type;

  struct log_format_t
  {
    typedef boost::vertex_property_tag kind;
  };

  typedef
    boost::property <log_format_t, CUTS_Log_Format *,
    boost::property <boost::vertex_name_t, ACE_CString> > property_type;

  typedef boost::adjacency_list <boost::vecS,
                                 boost::vecS,
                                 boost::directedS,
                                 property_type> graph_type;

  typedef boost::graph_traits <graph_type>::vertex_iterator vertex_iterator;

  /// Default constructor.
  CUTS_Unit_Test_Graph (void);

  /**
   * Initializing constructor
   *
   * @param[in]         name        Name of the graph.
   */
  CUTS_Unit_Test_Graph (const ACE_CString & name);

  /// Desturctor.
  ~CUTS_Unit_Test_Graph (void);

  bool create_log_format (const ACE_CString & name);

  bool create_log_format (const ACE_CString & name, CUTS_Log_Format *& format);

  const CUTS_Log_Format * log_format (vertex_iterator) const;

  /**
   * Associate two log formats, i.e., define causality.
   *
   * @param[in]         src           Source log format
   * @param[in]         dst           Destination log format
   */
  bool connect (const ACE_CString & src, const ACE_CString & dst);

  const graph_type graph (void) const;

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


private:
  /// Name of the unit test graph.
  ACE_CString name_;

  /// The underlying graph representation.
  graph_type graph_;

  /// The log formats for the unit test.
  formats_type formats_;
};

#if defined (__CUTS_INLINE__)
#include "Unit_Test_Graph.inl"
#endif

#endif  // !defined _CUTS_UNITE_UNIT_TEST_GRAPH_H_
