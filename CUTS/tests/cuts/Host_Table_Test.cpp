// $Id$

#include "boost/test/unit_test.hpp"
#include "Boost_JUnit_Formatter.h"
#include "Test_Log.h"

#include "cuts/Host_Table.h"
#include "cuts/Host_Table_Entry.h"

struct fixture
{
  fixture (void)
    : ipaddr_ ("127.0.0.1"),
      hostname_ ("localhost")
  {
    this->host_table_.bind (this->ipaddr_, this->hostname_);
  }

public:
  ACE_CString ipaddr_;
  ACE_CString hostname_;

  CUTS_Host_Table host_table_;
};

//=============================================================================
/*
 * Unit_Test: constructor
 */
//=============================================================================

void constructor (void)
{
  CUTS_Host_Table table;
  BOOST_CHECK (table.size () == 0);
}

//=============================================================================
/*
 * Unit_Test: host_table_bind
 */
//=============================================================================

void host_table_bind (void)
{
  const char * hostname = "localhost", * ipaddr = "127.0.0.1";

  CUTS_Host_Table table;
  const CUTS_Host_Table_Entry * entry = 0;

  BOOST_CHECK (table.bind (ipaddr, hostname, &entry) == 0);
  BOOST_CHECK (entry->hostname_ == hostname);
  BOOST_CHECK (entry->ipaddr_ == ipaddr);
  BOOST_CHECK (table.size () == 1);

  // Reset the entry and rebind to the same information.
  const CUTS_Host_Table_Entry * dup_entry = 0;
  BOOST_CHECK (table.bind (ipaddr, hostname, &dup_entry) == 1);
  BOOST_CHECK (dup_entry == entry);
  BOOST_CHECK (entry->hostname_ == hostname);
  BOOST_CHECK (entry->ipaddr_ == ipaddr);
}

//=============================================================================
/*
 * Unit_Test: find_by_ipaddr
 */
//=============================================================================

void find_by_ipaddr (void)
{
  fixture f;

  const CUTS_Host_Table_Entry * entry = 0;
  BOOST_CHECK (f.host_table_.find_by_ipaddr (f.ipaddr_, &entry) == 0);
  BOOST_CHECK (entry->hostname_ == f.hostname_);
}

//=============================================================================
/*
 * Unit_Test: find_by_name
 */
//=============================================================================

void find_by_name (void)
{
  fixture f;

  const CUTS_Host_Table_Entry * entry = 0;
  BOOST_CHECK (f.host_table_.find_by_name (f.hostname_, &entry) == 0);
  BOOST_CHECK (entry->ipaddr_ == f.ipaddr_);
}

//=============================================================================
/*
 * Unit_Test: reset
 */
//=============================================================================

void reset (void)
{
  fixture f;
  f.host_table_.clear ();

  BOOST_CHECK (f.host_table_.size () == 0);
}

//=============================================================================
/*
 * Unit_Test: unbind_by_name
 */
//=============================================================================

void unbind_by_name (void)
{
  fixture f;
  f.host_table_.unbind_by_name (f.hostname_);

  BOOST_CHECK (f.host_table_.find_by_name (f.hostname_) == -1);
  BOOST_CHECK (f.host_table_.find_by_ipaddr (f.ipaddr_) == -1);
}

//=============================================================================
/*
 * Unit_Test: unbind_by_ipaddr
 */
//=============================================================================

void unbind_by_ipaddr (void)
{
  fixture f;
  f.host_table_.unbind_by_ipaddr (f.ipaddr_);

  BOOST_CHECK (f.host_table_.find_by_ipaddr (f.ipaddr_) == -1);
  BOOST_CHECK (f.host_table_.find_by_name (f.hostname_) == -1);
}

//
// init_unit_test_suite
//
bool init_unit_test_suite (void)
{
  using namespace ::boost::unit_test;

  // Add the unit test to the master suite.
  framework::master_test_suite ().p_name.value = "CUTS_Host_Table";

  framework::master_test_suite ().add (
    make_test_case (&constructor,
    "CUTS_Host_Table (void)"));

  framework::master_test_suite ().add (
    make_test_case (&host_table_bind,
    "bind (const ACE_CString &, const ACE_CString &amp;, "
    "const CUTS_Host_Table_Entry **)"));

  framework::master_test_suite ().add (
    make_test_case (&reset, "reset (void)"));

  framework::master_test_suite ().add (
    make_test_case (&find_by_ipaddr,
    "find_by_ipaddr (const ACE_CString &amp;, "
    "const CUTS_Host_Table_Entry * &amp;)"));

  framework::master_test_suite ().add (
    make_test_case (&find_by_name,
    "find_by_name (const ACE_CString &amp;, "
    "const CUTS_Host_Table_Entry * &amp;)"));

  framework::master_test_suite ().add (
    make_test_case (&unbind_by_ipaddr,
    "unbind_by_ipaddr (const ACE_CString &amp;)"));

  framework::master_test_suite ().add (
    make_test_case (&unbind_by_name,
    "unbind_by_name (const ACE_CString &amp;)"));

  INSTALL_BOOST_LOG_FORMATTER (CUTS_Boost_JUnit_Formatter ("CUTS"),
                               false);

  return true;
}
