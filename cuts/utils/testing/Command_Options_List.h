// -*- C++ -*-

//=============================================================================
/**
 * @file        Command_Options_List.h
 *
 * $Id$
 *
 * @author      Manjula Peiris
 */
//=============================================================================

#ifndef _CUTS_COMMAND_OPTIONS_LIST_H_
#define _CUTS_COMMAND_OPTIONS_LIST_H_

#include "ace/Containers_T.h"
#include "cuts/Static_Node_T.h"
#include "Command_Options.h"
#include "Test_export.h"

/// Type definition of the CUTS_Command_Options_List node.
typedef CUTS_Static_Node_T <CUTS_Command_Options> CUTS_Command_Options_List_Node;

/// Type definition of the iterator.
typedef ACE_Double_Linked_List_Iterator <CUTS_Command_Options_List_Node> CUTS_Command_Options_List_Iterator;

/**
 * @class CUTS_Command_Options_List
 *
 * Collection of Command options. The options are stored in sequential
 * order, which reflects their desired order of execution.
 */
class CUTS_TEST_Export CUTS_Command_Options_List :
  public ACE_Double_Linked_List <CUTS_Command_Options_List_Node>
{
public:
  /// Iterator for the collection.
  typedef CUTS_Command_Options_List_Iterator ITERATOR;

  /// Default constructor.
  CUTS_Command_Options_List (void);

  /// Destructor.
  ~CUTS_Command_Options_List (void);

  /**
   * Append options to the end of the listing.
   *
   * @param[in]     opts          Options to append to list.
   */
  int append (const CUTS_Command_Options & opts);

private:
  /// Type definition of the node type.
  typedef CUTS_Static_Node_T <CUTS_Command_Options> node_type;
};

#if defined (__CUTS_INLINE__)
#include "Command_Options_List.inl"
#endif

#endif  // !defined _CUTS_COMMAND_OPTIONS_LIST_H_
