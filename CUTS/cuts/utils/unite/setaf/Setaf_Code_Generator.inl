//
// adapter_name
//

CUTS_INLINE
std::string CUTS_Setaf_Code_Generator::adapter_name (void)
{
  return this->adapter_name_;
}
//
// output_dir
//

CUTS_INLINE
std::string CUTS_Setaf_Code_Generator::output_dir (void)
{
  return this->output_dir_;
}

//
// relations
//
CUTS_INLINE
CUTS_SETAF_UTILS::Setaf_Relations & CUTS_Setaf_Code_Generator::relations (void)
{
  return this->relations_;
}

//
// entries
//
CUTS_INLINE
CUTS_SETAF_UTILS::Setaf_Entries & CUTS_Setaf_Code_Generator::entries (void)
{
  return this->entries_;
}

//
// entries
//
CUTS_INLINE
void CUTS_Setaf_Code_Generator::entries (CUTS_SETAF_UTILS::Setaf_Entries & entries)
{
  this->entries_ = entries;
}

//
// relations
//
CUTS_INLINE
void CUTS_Setaf_Code_Generator::relations (CUTS_SETAF_UTILS::Setaf_Relations & relations)
{
  this->relations_ = relations;
}

//
// variable_decls
//
CUTS_INLINE
void CUTS_Setaf_Code_Generator::variable_decls (CUTS_SETAF_UTILS::string_vector & variable_decls)
{
  this->variable_decls_ = variable_decls;
}

//
// setaf_code
//
CUTS_INLINE
void CUTS_Setaf_Code_Generator::setaf_code (CUTS_SETAF_UTILS::Setaf_Code & setaf_code)
{
  this->setaf_code_ = setaf_code;
}

//
// init_str
//
CUTS_INLINE
void CUTS_Setaf_Code_Generator::init_str (std::string & init_str)
{
  this->init_str_ = init_str;
}

//
// reset_str
//
CUTS_INLINE
void CUTS_Setaf_Code_Generator::reset_str (std::string & reset_str)
{
  this->reset_str_ = reset_str;
}