// $Id$

#include "TestArchiveBrowser_i.h"

#if !defined (__CUTS_INLINE__)
#include "TestArchiveBrowser_i.inl"
#endif

#include "adbc/Connection.h"
#include "adbc/Parameter_List.h"
#include "adbc/Parameter.h"
#include "adbc/Record.h"
#include "cuts/UUID.h"

//
// CUTS_TestArchiveBrowser_i
//
CUTS_TestArchiveBrowser_i::
CUTS_TestArchiveBrowser_i (ADBC::Connection & conn, ACE_UINT32 chunk_size)
: query_ (conn.create_query (), &ADBC::Query::destroy),
  chunk_size_ (chunk_size),
  index_ (0),
  is_done_ (false)
{
  // Prepare the SQL statement.
  const char * _SQL_STMT_ = "SELECT * FROM cuts.tests LIMIT ?, ?";
  this->query_->prepare (_SQL_STMT_);

  // Initialize the parameters.
  this->query_->parameters ()[0].bind (&this->index_);
  this->query_->parameters ()[1].bind (&this->chunk_size_);
}

//
// get_next
//
CORBA::Boolean CUTS_TestArchiveBrowser_i::
get_next (CUTS::TestProfiles_out profiles)
{
  try
  {
    // Execute the prepared query.
    ADBC::Record & record = this->query_->execute ();

    // Count the number of record returned.
    size_t count = 0;
    for (; !record.done (); record.advance ())
      ++ count;

    // Reset the cursor of the record.
    record.reset ();

    if (count)
    {
      // Allocate a new sequence for the profiles.
      ACE_NEW_THROW_EX (profiles,
                        CUTS::TestProfiles (count),
                        CORBA::NO_MEMORY ());

      profiles->length (count);

      char name[256];
      char uuid_str[37];
      ACE_Utils::UUID uuid;
      int index = 0;

      // Copy each of test profile to the sequence.
      for ( ; !record.done (); record.advance ())
      {
        record.get_data (2, name, sizeof (name));
        record.get_data (3, uuid_str, sizeof (uuid_str));

        // Conver the UUID from string format.
        uuid.from_string (uuid_str);

        // Save the profile in the collection.
        (*profiles)[index].uuid <<= uuid;
        (*profiles)[index].name = CORBA::string_dup (name);

        // Increment the index.
        ++ index;
      }

      // Increment the index count.
      this->index_ += count;
    }

    this->is_done_ = record.done ();
    return this->is_done_;
  }
  catch (const ADBC::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex.message ().c_str ()));

    throw CUTS::OperationFailed ();
  }
}

//
// reset
//
void CUTS_TestArchiveBrowser_i::reset (void)
{
  this->index_ = 0;
  this->is_done_ = false;
}
