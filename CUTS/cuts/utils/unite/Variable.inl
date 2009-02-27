// $Id$

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Log_Format_Variable

//
// CUTS_Log_Format_Variable
//
CUTS_INLINE
CUTS_Log_Format_Variable::
CUTS_Log_Format_Variable (type_t type, size_t index)
: type_ (type),
  index_ (index)
{

}

//
// ~CUTS_Log_Format_Variable
//
CUTS_INLINE
CUTS_Log_Format_Variable::~CUTS_Log_Format_Variable (void)
{

}

//
// index
//
CUTS_INLINE
size_t CUTS_Log_Format_Variable::index (void) const
{
  return this->index_;
}

//
// index
//
CUTS_INLINE
CUTS_Log_Format_Variable::type_t CUTS_Log_Format_Variable::type (void) const
{
  return this->type_;
}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Integer_Log_Format_Variable

//
// CUTS_Integer_Log_Format_Variable
//
CUTS_INLINE
CUTS_Integer_Log_Format_Variable::
CUTS_Integer_Log_Format_Variable (size_t index)
: CUTS_Log_Format_Variable (CUTS_Log_Format_Variable::VT_INTEGER, index)
{

}

//
// CUTS_Integer_Log_Format_Variable
//
CUTS_INLINE
CUTS_Integer_Log_Format_Variable::~CUTS_Integer_Log_Format_Variable (void)
{

}

//
// bind
//
CUTS_INLINE
void CUTS_Integer_Log_Format_Variable::bind (CUTS_DB_SQLite_Parameter & param)
{
  param.bind (this->value_);
}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_String_Log_Format_Variable

//
// CUTS_String_Log_Format_Variable
//
CUTS_INLINE
CUTS_String_Log_Format_Variable::
CUTS_String_Log_Format_Variable (size_t index)
: CUTS_Log_Format_Variable (CUTS_Log_Format_Variable::VT_STRING, index)
{

}

//
// CUTS_String_Log_Format_Variable
//
CUTS_INLINE
CUTS_String_Log_Format_Variable::~CUTS_String_Log_Format_Variable (void)
{

}

//
// CUTS_String_Log_Format_Variable
//
CUTS_INLINE
void CUTS_String_Log_Format_Variable::
value (const char * begin, const char * end)
{
  this->value_.set (begin, end - begin, true);
}

//
// bind
//
CUTS_INLINE
void CUTS_String_Log_Format_Variable::bind (CUTS_DB_SQLite_Parameter & param)
{
  param.bind (this->value_.c_str (), this->value_.length ());
}
