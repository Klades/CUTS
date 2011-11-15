// -*- C++ -*-

//=============================================================================
/**
 * @file      CUTS_BE_IDL_Graph.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_IDL_GRAPH_H_
#define _CUTS_BE_IDL_GRAPH_H_

#include "BE_Depend_Graph_T.h"
#include "BE_IDL_Node.h"
#include "../../paradigms/CHAOS.h"

//=============================================================================
/**
 * @class CUTS_BE_IDL_Graph
 */
//=============================================================================

class CUTS_BE_IDL_Graph :
  public CUTS_BE_Depend_Graph_T <CUTS_BE_IDL_Node>,
  public CHAOS::Visitor
{
public:
  /// Default constructor.
  CUTS_BE_IDL_Graph (void);

  /// Destructor.
  virtual ~CUTS_BE_IDL_Graph (void);

protected:
  /// Visit the RootFolder of a CHAOS model.
  void Visit_RootFolder (const CHAOS::RootFolder &);

  /// Visit InterfaceDefinitions folder in a CHAOS model.
  void Visit_InterfaceDefinitions (const CHAOS::InterfaceDefinitions &);

  /// Visit a File in a CHAOS model.
  void Visit_File (const CHAOS::File &);

  /// Visit a Package in a CHAOS model.
  void Visit_Package (const CHAOS::Package &);

  /// Visit a Component in a CHAOS model.
  void Visit_Component (const CHAOS::Component &);

  /// Visit an Object in a CHAOS model.
  void Visit_Object (const CHAOS::Object &);

  /// Visit an InEventPort of a CHAOS model.
  void Visit_InEventPort (const CHAOS::InEventPort &);

  /// Visit an OutEventPort of a CHAOS model.
  void Visit_OutEventPort (const CHAOS::OutEventPort &);

  /// Visit an ProvidedRequestPort of a CHAOS model.
  void Visit_ProvidedRequestPort (const CHAOS::ProvidedRequestPort &);

  /// Visit an RequiredRequestPort of a CHAOS model.
  void Visit_RequiredRequestPort (const CHAOS::RequiredRequestPort &);

  /// Visit an Event in a CHAOS model.
  void Visit_Event (const CHAOS::Event &);

  /// Visit a Providable element in a CHAOS model.
  void Visit_Providable (const CHAOS::Provideable &);

  /// Visit a Supports element in a CHAOS model.
  void Visit_Supports (const CHAOS::Supports &);

  /// Visit a ReadonlyAttribute in a CHAOS model.
  void Visit_ReadonlyAttribute (const CHAOS::ReadonlyAttribute &);

  /// Visit a NameType element in a CHAOS model.
  void Visit_NamedType (const CHAOS::NamedType & type);

private:
  /**
   * Get the parent file of a named type.
   *
   * @param[in]     type      The source named type.
   * @return        The parent of the named type.
   */
  CHAOS::File NamedType_parent (const CHAOS::NamedType & type);

  /**
   * Visit the contents of a File/Package element in a CHAOS
   * model.
   *
   * @param[in]     object        The source object.
   */
  void visit_file_and_package_contents (const Udm::Object & object);

  /// The current node in the graph.
  CUTS_BE_IDL_Node * current_node_;

  /// Type definition for a collection of files.
  typedef std::set <CHAOS::File> File_Set;

  /// Files that need to be parsed.
  File_Set pending_files_;

  /// The file that's currently being preprocessed.
  CHAOS::File active_file_;
};

#endif  // !defined _CUTS_BE_IDL_GRAPH_H_
