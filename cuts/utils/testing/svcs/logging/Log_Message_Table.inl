// -*- C++ -*-
// $Id$

//
// CUTS_Log_Message_Table
//
CUTS_INLINE
CUTS_Log_Message_Table::
CUTS_Log_Message_Table (CUTS_Test_Database & test_db)
: test_db_ (test_db),
  query_ (0)
{

}

//
// ~CUTS_Log_Message_Table
//
CUTS_INLINE
CUTS_Log_Message_Table::~CUTS_Log_Message_Table (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_Log_Message_Table_Insert_Stmt

//
// CUTS_Log_Message_Table_Insert_Stmt
//
CUTS_INLINE
CUTS_Log_Message_Table_Insert_Stmt::
CUTS_Log_Message_Table_Insert_Stmt (ADBC::Query & query)
: query_ (query)
{

}

//
// ~CUTS_Log_Message_Table_Insert_Stmt
//
CUTS_INLINE
CUTS_Log_Message_Table_Insert_Stmt::~CUTS_Log_Message_Table_Insert_Stmt (void)
{

}

//
// prepare
//
CUTS_INLINE
void CUTS_Log_Message_Table_Insert_Stmt::prepare (void)
{
  static const char * __INSERT_STMT__ =
    ACE_TEXT ("INSERT INTO cuts_logging (timeofday, severity, hostname, thread_id, message) ")
    ACE_TEXT ("VALUES (?, ?, ?, ?, ?)");

  this->query_.prepare (__INSERT_STMT__);
}

//
// reset
//
CUTS_INLINE
void CUTS_Log_Message_Table_Insert_Stmt::reset (void)
{
  this->query_.reset ();
}

//
// execute
//
CUTS_INLINE
void CUTS_Log_Message_Table_Insert_Stmt::execute (void)
{
  this->query_.execute_no_record ();
}

//
// bind_timeofday
//
CUTS_INLINE
void CUTS_Log_Message_Table_Insert_Stmt::
bind_timeofday (ADBC::SQLite::Date_Time & timeofday)
{
  this->query_.parameters ()[0].bind (&timeofday);
}

//
// bind_severity
//
CUTS_INLINE
void CUTS_Log_Message_Table_Insert_Stmt::
bind_severity (ACE_INT16 & severity)
{
  this->query_.parameters ()[1].bind (&severity);
}

//
// bind_hostname
//
CUTS_INLINE
void CUTS_Log_Message_Table_Insert_Stmt::
bind_hostname (const char * hostname)
{
  this->query_.parameters ()[2].bind (hostname, ACE_OS::strlen (hostname));
}
//
// bind_thread_id
//
CUTS_INLINE
void CUTS_Log_Message_Table_Insert_Stmt::
bind_thread_id (ACE_INT32 & thread_id)
{
  this->query_.parameters ()[3].bind (&thread_id);
}

//
// bind_message
//
CUTS_INLINE
void CUTS_Log_Message_Table_Insert_Stmt::
bind_message (const char * message, size_t length)
{
  this->query_.parameters ()[4].bind (message, length);
}