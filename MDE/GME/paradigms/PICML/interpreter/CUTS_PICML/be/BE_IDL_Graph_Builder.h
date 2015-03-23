// -*- C++ -*-

//=============================================================================
/**
 * @file      CUTS_BE_IDL_Graph_Builder.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_IDL_GRAPH_BUILDER_H_
#define _CUTS_BE_IDL_GRAPH_BUILDER_H_

#include "PICML/PICML.h"
#include "PICML/Visitor.h"
#include "BE_IDL_Graph.h"

/**
 * @class CUTS_BE_IDL_Graph_Builder
 *
 * Visitor that builds an dependency graph for the IDL files in
 * a project.
 */
class CUTS_BE_Export CUTS_BE_IDL_Graph_Builder : public PICML::Visitor
{
public:
  /// Default constructor.
  CUTS_BE_IDL_Graph_Builder (CUTS_BE_IDL_Graph & graph);

  /// Destructor.
  virtual ~CUTS_BE_IDL_Graph_Builder (void);

  /// Visit the RootFolder of a PICML model.
  void visit_RootFolder (PICML::RootFolder_in);

  /// Visit InterfaceDefinitions folder in a PICML model.
  void visit_InterfaceDefinitions (PICML::InterfaceDefinitions_in);

  /// Visit a File in a PICML model.
  void visit_File (PICML::File_in);

  /// Visit a FileRef in a PICML model.
  void visit_FileRef (PICML::FileRef_in f);

  /// Visit a Package in a PICML model.
  void visit_Package (PICML::Package_in);

  /// Visit a Component in a PICML model.
  void visit_Component (PICML::Component_in);

  /// Visit an Object in a PICML model.
  void visit_Object (PICML::Object_in);

  /// Visit an InEventPort of a PICML model.
  void visit_InEventPort (PICML::InEventPort_in);

  /// Visit an OutEventPort of a PICML model.
  void visit_OutEventPort (PICML::OutEventPort_in);

  /// Visit an ProvidedRequestPort of a PICML model.
  void visit_ProvidedRequestPort (PICML::ProvidedRequestPort_in);

  /// Visit an RequiredRequestPort of a PICML model.
  void visit_RequiredRequestPort (PICML::RequiredRequestPort_in);

  /// Visit an Event in a PICML model.
  void visit_Event (PICML::Event_in);

  /// Visit a Providable element in a PICML model.
  void visit_Providable (PICML::Provideable_in);

  /// Visit a Supports element in a PICML model.
  void visit_Supports (PICML::Supports_in);

  /// Visit a ReadonlyAttribute in a PICML model.
  void visit_ReadonlyAttribute (PICML::ReadonlyAttribute_in);

  /// Visit a Member in a PICML model.
  void visit_Member (PICML::Member_in m);

  /// Visit a Aggregate in the PICML model
  void visit_Aggregate (PICML::Aggregate_in m);

private:
  /// Visit a NameType element in a PICML model.
  void visit_NamedType (PICML::NamedType_in type);

  /**
   * Get the parent file of a named type.
   *
   * @param[in]     type      The source named type.
   * @return        The parent of the named type.
   */
  PICML::File NamedType_parent (const PICML::NamedType_in type);

  /// Target IDL graph.
  CUTS_BE_IDL_Graph & graph_;

  /// The current node in the graph.
  CUTS_BE_IDL_Node * current_node_;

  /// Type definition for a collection of files.
  typedef std::set <PICML::File> File_Set;

  /// Files that need to be parsed.
  File_Set pending_files_;

  /// The file that's currently being preprocessed.
  PICML::File active_file_;
};

#endif  // !defined _CUTS_BE_IDL_GRAPH_BUILDER_H_
