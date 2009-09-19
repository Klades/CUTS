// -*- C++ -*-

//=============================================================================
/**
 * @file        Unit_Test_Graph_Builder.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_UNIT_TEST_GRAPH_BUILDER_H_
#define _CUTS_UNITE_UNIT_TEST_GRAPH_BUILDER_H_

#include "cuts-unite.h"
#include "cuts/config.h"

// Forward decl.
class CUTS_Dataflow_Graph;

// Forward decl.
class CUTS_Log_Format;

// Forward decl.
class CUTS_Log_Format_Relation;

/**
 * @class CUTS_Dataflow_Graph_Builder
 *
 * Helper class that converts the datagraph in a XML file into
 * a CUTS_Dataflow_Graph object.
 */
class CUTS_UNITE_XML_Export CUTS_Dataflow_Graph_Builder
{
public:
  /// Default constructor.
  CUTS_Dataflow_Graph_Builder (void);

  /// Destructor.
  ~CUTS_Dataflow_Graph_Builder (void);

  /**
   * Build the unit test graph for the given data graph. The data
   * graph is read from a XML document.
   *
   * @param[in]       datagraph       The source datagraph
   * @param[out]      graph           The target unit test graph
   */
  bool build (const ::CUTS::XML::datagraphType & datagraph,
              CUTS_Dataflow_Graph & graph);
};

#if defined (__CUTS_INLINE__)
#include "Dataflow_Graph_Builder.inl"
#endif

#endif  // !defined _CUTS_UNITE_UNIT_TEST_GRAPH_BUILDER_H_
