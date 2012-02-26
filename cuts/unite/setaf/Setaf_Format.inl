// $Id:

//
// CUTS_Setaf_Log_Format
//
CUTS_INLINE
CUTS_Setaf_Log_Format::CUTS_Setaf_Log_Format (std::string & type)
: type_ (type),
  id_(""),
  name_ ("")
{

}

//
// ~CUTS_Setaf_Log_Format
//
CUTS_INLINE
CUTS_Setaf_Log_Format::~CUTS_Setaf_Log_Format (void)
{

}

//
// name
//
CUTS_INLINE
std::string & CUTS_Setaf_Log_Format::name ()
{
  return this->name_;
}

//
// id
//
CUTS_INLINE
std::string & CUTS_Setaf_Log_Format::id ()
{
  return this->id_;
}

//
// type
//
CUTS_INLINE
std::string & CUTS_Setaf_Log_Format::type ()
{
  return this->type_;
}

//
// CUTS_Setaf_Log_Format_Relation
//
CUTS_INLINE
CUTS_Setaf_Log_Format_Relation::CUTS_Setaf_Log_Format_Relation ()
{

}

//
// ~CUTS_Setaf_Log_Format_Relation
//
CUTS_INLINE
CUTS_Setaf_Log_Format_Relation::~CUTS_Setaf_Log_Format_Relation (void)
{

}

//
// cause_lf
//
CUTS_INLINE
std::string & CUTS_Setaf_Log_Format_Relation::cause_lf ()
{
  return this->cause_lf_;
}

//
// cause_var
//
CUTS_INLINE
std::string & CUTS_Setaf_Log_Format_Relation::cause_var ()
{
  return this->cause_var_;
}

//
// effect_lf
//
CUTS_INLINE
std::string & CUTS_Setaf_Log_Format_Relation::effect_lf ()
{
  return this->effect_lf_;
}

//
// effect_var
//
CUTS_INLINE
std::string & CUTS_Setaf_Log_Format_Relation::effect_var ()
{
  return this->effect_var_;
}

//
// CUTS_Setaf_Log_Format_Code
//
CUTS_INLINE
CUTS_Setaf_Log_Format_Code::CUTS_Setaf_Log_Format_Code (std::string & code_id,
                                                        std::string & adaptation_code)
: code_id_ (code_id),
  adaptation_code_ (adaptation_code)
{

}

//
// code_id
//
CUTS_INLINE
std::string & CUTS_Setaf_Log_Format_Code::code_id ()
{
  return this->code_id_;
}

//
// adaptation_code
//
CUTS_INLINE
std::string & CUTS_Setaf_Log_Format_Code::adaptation_code ()
{
  return this->adaptation_code_;
}