// -*- C++ -*-

//=============================================================================
/**
 * @file        TestArchiveBrowser_i.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_ARCHIVE_BROWSER_H_
#define _CUTS_TEST_ARCHIVE_BROWSER_H_

#include "../archivingS.h"
#include "cuts/Auto_Functor_T.h"
#include "cuts/utils/db/DB_Query.h"

// Forward decl.
class CUTS_DB_Connection;

/**
 * @class CUTS_TestArchiveBrowser_i
 *
 * Implementation of the CUTS::TestArchiveBrowser interface.
 */
class CUTS_TestArchiveBrowser_i :
  public POA_CUTS::TestArchiveBrowser
{
public:
  /**
   * Initializing constructor
   *
   * @param[in]       conn        Connection to database.
   */
  CUTS_TestArchiveBrowser_i (CUTS_DB_Connection & conn,
                             ACE_UINT32 chunk_size);

  /// Destructor.
  virtual ~CUTS_TestArchiveBrowser_i (void);

  virtual CORBA::Boolean get_next (CUTS::TestProfiles_out profiles);

  virtual CORBA::Boolean done (void);

  virtual void reset (void);

private:
  /// The query from the database.
  CUTS_Auto_Functor_T <CUTS_DB_Query> query_;

  /// Number of records to request.
  ACE_UINT32 chunk_size_;

  ACE_UINT32 index_;

  bool is_done_;
};

#if defined (__CUTS_INLINE__)
#include "TestArchiveBrowser_i.inl"
#endif

#endif  // !defined _CUTS_TEST_ARCHIVE_BROWSER_H_
