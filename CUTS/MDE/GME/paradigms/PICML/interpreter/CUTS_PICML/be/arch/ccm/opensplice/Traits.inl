// -*- C++ - *-
// $Id$

namespace CUTS_BE_OpenSplice
{

//
// Traits
//
CUTS_INLINE
Traits::Traits (void)
{

}

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
  return false;
}

//
// stub_base_project
//
CUTS_INLINE
const char * Traits::stub_base_project (void)
{
  return "cuts_opensplice_ccm_stub";
}

//
// svnt_base_project
//
CUTS_INLINE
const char * Traits::svnt_base_project (void)
{
  return "cuts_opensplice_ccm";
}

//
// custom_stub_prefix
//
CUTS_INLINE
const char * Traits::custom_stub_prefix (void)
{
  return "OpenSplice_";
}

//
// ccm_servant_template_type
//
CUTS_INLINE
const char * Traits::ccm_servant_template_type (void)
{
  return "CUTS_OpenSplice_CCM_Servant_T";
}

//
// ccm_servant_template_type_header
//
CUTS_INLINE
const char * Traits::ccm_servant_template_type_header (void)
{
  return "cuts/arch/opensplice/ccm/OpenSplice_CCM_Servant_T";
}

//
// ccm_eventconsumer_template_type
//
CUTS_INLINE
const char * Traits::ccm_eventconsumer_template_type (void)
{
  return "CUTS_OpenSplice_CCM_EventConsumer_T";
}

//
// ccm_eventconsumer_template_type_header
//
CUTS_INLINE
const char * Traits::ccm_eventconsumer_template_type_header (void)
{
  return "cuts/arch/opensplice/ccm/OpenSplice_EventConsumer_T";
}

//
// ccm_publisher_template_type
//
CUTS_INLINE
const char * Traits::ccm_publisher_template_type (void)
{
  return "CUTS_OpenSplice_CCM_Publisher_T";
}

//
// ccm_publisher_template_type_header
//
CUTS_INLINE
const char * Traits::ccm_publisher_template_type_header (void)
{
  return "cuts/arch/opensplice/ccm/OpenSplice_Publisher_T";
}

//
// ccm_publisher_table_template_type
//
CUTS_INLINE
const char * Traits::ccm_publisher_table_template_type (void)
{
  return "CUTS_OpenSplice_CCM_Publisher_Table_T";
}

//
// ccm_publisher_table_template_type_header
//
CUTS_INLINE
const char * Traits::ccm_publisher_table_template_type_header (void)
{
  return "cuts/arch/opensplice/ccm/OpenSplice_Publisher_Table_T";
}

}
