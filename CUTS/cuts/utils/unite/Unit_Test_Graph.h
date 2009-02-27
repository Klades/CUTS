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

#include "boost/graph/adjacency_list.hpp"
#include "ace/SStringfwd.h"

// Forward decl.
class CUTS_Log_Format;

/**
 * @class CUTS_Unit_Test_Graph
 */
class CUTS_Unit_Test_Graph
{
public:
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

  /// Default constructor.
  CUTS_Unit_Test_Graph (void);

  /// Desturctor.
  ~CUTS_Unit_Test_Graph (void);

  bool insert (CUTS_Log_Format * format);

  bool connect (const ACE_CString & src, const ACE_CString & dst);

  const graph_type graph (void) const;

private:
  graph_type graph_;
};

#endif  // !defined _CUTS_UNITE_UNIT_TEST_GRAPH_H_
