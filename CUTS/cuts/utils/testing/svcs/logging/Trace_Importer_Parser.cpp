// $Id$

#include "Trace_Importer_Parser.h"

#if !defined (__CUTS_INLINE__)
#include "Trace_Importer_Parser.inl"
#endif

#include "Log_Message_Table.h"
#include "cuts/Auto_Functor_T.h"
#include "cuts/utils/db/DB_Query.h"
#include "cuts/utils/db/SQLite/Types.h"
#include "cuts/utils/testing/Test_Database.h"

#include "boost/spirit/core.hpp"
#include "boost/spirit/iterator/file_iterator.hpp"
#include "ace/streams.h"

static const char * __INSERT_STMT__ =
  "INSERT INTO cuts_logging (timeofday, severity, hostname, message) "
  "VALUES (DATETIME('NOW'), 1, ?, ?)";

namespace actors
{
  /**
   * @struct insert_message
   */
  class insert_message
  {
  public:
    insert_message (CUTS_DB_Query & query)
      : query_ (query)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      // Bind the message to its appropriate parameter.
      std::string message (begin, end);
      this->query_.parameters ()[1].bind (message.c_str (), message.length ());

      // Execute the query.
      this->query_.execute_no_record ();

      // Reset the query for the next message.
      this->query_.reset ();
    }

  private:
    CUTS_DB_Query & query_;
  };
}

/**
 * @struct CUTS_Trace_Importer_Parser_Grammar
 */
struct CUTS_Trace_Importer_Parser_Grammar :
  boost::spirit::grammar <CUTS_Trace_Importer_Parser_Grammar>
{
  /**
   * Initializing constructor
   */
  CUTS_Trace_Importer_Parser_Grammar (CUTS_DB_Query & query)
    : query_ (query)
  {

  }

  /**
   * @struct definition
   */
  template <typename ScannerT>
  struct definition
  {
    /**
     * Initializing constructor.
     *
     * @param[in]     self        The input grammar.
     */
    definition (CUTS_Trace_Importer_Parser_Grammar const & self)
    {
      using namespace boost::spirit;

      this->log_message_ =
        (*(anychar_p - eol_p))[::actors::insert_message (self.query_)] >> eol_p;

      this->execution_trace_ = *this->log_message_;
    }

    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->execution_trace_;
    }

  private:
    boost::spirit::rule <ScannerT> log_message_;

    boost::spirit::rule <ScannerT> execution_trace_;
  };

private:
  CUTS_DB_Query & query_;
};


//
// import_trace
//
bool CUTS_Trace_Importer_Parser::
import_trace (const ACE_CString & trace_file, const ACE_CString & hostname)
{
  // Verify the database is initialized with the log message table.
  CUTS_Log_Message_Table logmsg_table (this->test_db_);

  if (0 != logmsg_table.init ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to initialize database\n")),
                       false);

  using namespace boost::spirit;

  // Re-open the temp file using an iterator this time.
  file_iterator < > iter_begin (trace_file.c_str ());

  if (!iter_begin)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open trace [file=%s]\n"),
                       trace_file.c_str ()),
                       false);

  file_iterator < > iter_end = iter_begin.make_end ();

  // Parse the trace and insert messages into database.
  CUTS_DB_Query * query = this->test_db_.create_query ();
  CUTS_Auto_Functor_T <CUTS_DB_Query> auto_clean (query, &CUTS_DB_Query::destroy);

  // Prepare the query for inserting records.
  query->execute_no_record ("BEGIN TRANSACTION");
  query->prepare (__INSERT_STMT__);

  // Bind the hostname since it will never change.
  query->parameters ()[0].bind (hostname.c_str (), hostname.length ());

  CUTS_Trace_Importer_Parser_Grammar grammar (*query);

  parse_info < file_iterator < > > info =
    parse (iter_begin, iter_end, grammar);

  query->execute_no_record ("COMMIT");

  return true;
}
