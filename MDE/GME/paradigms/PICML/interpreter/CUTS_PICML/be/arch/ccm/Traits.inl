// -*- C++ - *-
// $Id$

namespace CUTS_BE_CCM
{
namespace Cpp
{

//
// ~Traits
//
CUTS_INLINE
Traits::~Traits (void)
{

}

//
// generate_default_servant
//
CUTS_INLINE
bool Traits::generate_default_servant (void)
{
  return true;
}

//
// stub_base_project
//
CUTS_INLINE
const char * Traits::stub_base_project (void)
{
  return "";
}

//
// svnt_base_project
//
CUTS_INLINE
const char * Traits::svnt_base_project (void)
{
  return "";
}

//
// skel_base_project
//
CUTS_INLINE
const char * Traits::skel_base_project (void)
{
  return "";
}

//
// write_top
//
CUTS_INLINE
void Traits::write_top (std::ostream &, const CUTS_BE_IDL_Node &)
{

}


//
// write_stub_source_files
//
CUTS_INLINE
void Traits::
write_stub_source_files (std::ostream &, const CUTS_BE_IDL_Node &)
{

}

//
// write_stub_after
//
CUTS_INLINE
void Traits::
write_stub_after (std::ostream &, const CUTS_BE_IDL_Node &)
{

}

//
// write_stub_custom
//
CUTS_INLINE
void Traits::write_stub_custom (std::ostream &, const CUTS_BE_IDL_Node &)
{

}

//
// write_idl_gen_files
//
CUTS_INLINE
void Traits::
write_idl_gen_files (std::ostream &, const CUTS_BE_IDL_Node &)
{

}

//
// write_exec_idl_files
//
CUTS_INLINE
void Traits::
write_exec_idl_files (std::ostream &, const CUTS_BE_IDL_Node &)
{

}

//
// write_exec_source_files
//
CUTS_INLINE
void Traits::
write_exec_source_files (std::ostream &, const CUTS_BE_IDL_Node &)
{

}

//
// ccm_context_template_type
//
CUTS_INLINE
const char * Traits::custom_stub_prefix (void)
{
  return "";
}

//
// ccm_context_template_type
//
CUTS_INLINE
const char * Traits::ccm_context_template_type (void)
{
  return "CUTS_CCM_Context_T";
}

//
// ccm_context_template_type_header
//
CUTS_INLINE
const char * Traits::ccm_context_template_type_header (void)
{
  return "cuts/arch/ccm/CCM_Context_T";
}

//
// ccm_servant_template_type
//
CUTS_INLINE
const char * Traits::ccm_servant_template_type (void)
{
  return "CUTS_CCM_Servant_T";
}

//
// ccm_servant_template_type_header
//
CUTS_INLINE
const char * Traits::ccm_servant_template_type_header (void)
{
  return "cuts/arch/ccm/CCM_Servant_T.h";
}

//
// ccm_eventconsumer_template_type
//
CUTS_INLINE
const char * Traits::ccm_eventconsumer_template_type (void)
{
  return "CUTS_CCM_EventConsumer_T";
}

//
// ccm_eventconsumer_template_type_header
//
CUTS_INLINE
const char * Traits::ccm_eventconsumer_template_type_header (void)
{
  return "cuts/arch/ccm/CUTS_CCM_EventConsumer_T.h";
}

//
// ccm_publisher_template_type
//
CUTS_INLINE
const char * Traits::ccm_publisher_template_type (void)
{
  return "CUTS_CCM_Publisher_T";
}

//
// ccm_publisher_template_type_header
//
CUTS_INLINE
const char * Traits::ccm_publisher_template_type_header (void)
{
  return "cuts/arch/ccm/CCM_Publisher_T.h";
}

//
// ccm_publisher_table_template_type
//
CUTS_INLINE
const char * Traits::ccm_publisher_table_template_type (void)
{
  return "CUTS_CCM_Publisher_Table_T";
}

//
// ccm_publisher_table_template_type_header
//
CUTS_INLINE
const char * Traits::ccm_publisher_table_template_type_header (void)
{
  return "cuts/arch/ccm/CCM_Publisher_Table_T.h";
}

//
// emulates_async
//
CUTS_INLINE
bool Traits::emulates_async (void)
{
  return false;
}


}
}
