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
  void Visit_RootFolder (const PICML::RootFolder &);

  /// Visit InterfaceDefinitions folder in a PICML model.
  void Visit_InterfaceDefinitions (const PICML::InterfaceDefinitions &);

  /// Visit a File in a PICML model.
  void Visit_File (const PICML::File &);

  /// Visit a FileRef in a PICML model.
  void Visit_FileRef (const PICML::FileRef & f);

  /// Visit a Package in a PICML model.
  void Visit_Package (const PICML::Package &);

  /// Visit a Component in a PICML model.
  void Visit_Component (const PICML::Component &);

  /// Visit an Object in a PICML model.
  void Visit_Object (const PICML::Object &);

  /// Visit an InEventPort of a PICML model.
  void Visit_InEventPort (const PICML::InEventPort &);

  /// Visit an OutEventPort of a PICML model.
  void Visit_OutEventPort (const PICML::OutEventPort &);

  /// Visit an ProvidedRequestPort of a PICML model.
  void Visit_ProvidedRequestPort (const PICML::ProvidedRequestPort &);

  /// Visit an RequiredRequestPort of a PICML model.
  void Visit_RequiredRequestPort (const PICML::RequiredRequestPort &);

  /// Visit an Event in a PICML model.
  void Visit_Event (const PICML::Event &);

  /// Visit a Providable element in a PICML model.
  void Visit_Providable (const PICML::Provideable &);

  /// Visit a Supports element in a PICML model.
  void Visit_Supports (const PICML::Supports &);

  /// Visit a ReadonlyAttribute in a PICML model.
  void Visit_ReadonlyAttribute (const PICML::ReadonlyAttribute &);

  /// Visit a Member in a PICML model.
  void Visit_Member (const PICML::Member & m);

  /// Visit a Aggregate in the PICML model
  void Visit_Aggregate (const PICML::Aggregate & m);

private:
  /// Visit a NameType element in a PICML model.
  void Visit_NamedType (const PICML::NamedType & type);

  /**
   * Get the parent file of a named type.
   *
   * @param[in]     type      The source named type.
   * @return        The parent of the named type.
   */
  PICML::File NamedType_parent (const PICML::NamedType & type);

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
