// -*- C++ -*-

//=============================================================================
/**
 * @file        Process_Options_List.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_PROCESS_OPTIONS_LIST_H_
#define _CUTS_PROCESS_OPTIONS_LIST_H_

#include "ace/Containers_T.h"
#include "cuts/Static_Node_T.h"
#include "Process_Options.h"
#include "Node_Daemon_Core_export.h"

/// Type definition of the CUTS_Process_Options_List node.
typedef CUTS_Static_Node_T <CUTS_Process_Options> CUTS_Process_Options_List_Node;

/// Type definition of the iterator.
typedef ACE_Double_Linked_List_Iterator <CUTS_Process_Options_List_Node> CUTS_Process_Options_List_Iterator;

/**
 * @class CUTS_Process_Options_List
 *
 * Collection of process options. The options are stored in sequential
 * order, which reflects their desired order of execution.
 */
class CUTS_NODE_DAEMON_CORE_Export CUTS_Process_Options_List :
  public ACE_Double_Linked_List <CUTS_Process_Options_List_Node>
{
public:
  /// Iterator for the collection.
  typedef CUTS_Process_Options_List_Iterator ITERATOR;

  /// Default constructor.
  CUTS_Process_Options_List (void);

  /// Destructor.
  ~CUTS_Process_Options_List (void);

  /**
   * Append options to the end of the listing.
   *
   * @param[in]     opts          Options to append to list.
   */
  int append (const CUTS_Process_Options & opts);

private:
  /// Type definition of the node type.
  typedef CUTS_Static_Node_T <CUTS_Process_Options> node_type;
};

#if defined (__CUTS_INLINE__)
#include "Process_Options_List.inl"
#endif

#endif  // !defined _CUTS_PROCESS_OPTIONS_LIST_H_
