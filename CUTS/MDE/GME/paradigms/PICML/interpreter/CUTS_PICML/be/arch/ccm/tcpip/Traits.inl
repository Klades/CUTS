// -*- C++ - *-
// $Id$

//
// CUTS_BE_TCPIP_Traits
//
CUTS_INLINE
CUTS_BE_TCPIP_Traits::CUTS_BE_TCPIP_Traits (void)
: has_events_ (false)
{

}

//
// ~CUTS_BE_TCPIP_Traits
//
CUTS_INLINE
CUTS_BE_TCPIP_Traits::~CUTS_BE_TCPIP_Traits (void)
{

}

//
// generate_default_servant
//
CUTS_INLINE
bool CUTS_BE_TCPIP_Traits::generate_default_servant (void)
{
  return false;
}

//
// stub_base_project
//
CUTS_INLINE
const char * CUTS_BE_TCPIP_Traits::stub_base_project (void)
{
  return "cuts_tcpip_ccm_stub";
}

//
// svnt_base_project
//
CUTS_INLINE
const char * CUTS_BE_TCPIP_Traits::svnt_base_project (void)
{
  return "cuts_tcpip_ccm";
}

//
// custom_stub_prefix
//
CUTS_INLINE
const char * CUTS_BE_TCPIP_Traits::custom_stub_prefix (void)
{
  return "TCPIP_";
}

//
// ccm_servant_template_type
//
CUTS_INLINE
const char * CUTS_BE_TCPIP_Traits::ccm_servant_template_type (void)
{
  return "CUTS_TCPIP_CCM_Servant_T";
}

//
// ccm_servant_template_type_header
//
CUTS_INLINE
const char * CUTS_BE_TCPIP_Traits::ccm_servant_template_type_header (void)
{
  return "cuts/arch/tcpip/ccm/TCPIP_CCM_Servant_T";
}

//
// ccm_eventconsumer_template_type
//
CUTS_INLINE
const char * CUTS_BE_TCPIP_Traits::ccm_eventconsumer_template_type (void)
{
  return "CUTS_RTIDDS_CCM_EventConsumer_T";
}

//
// ccm_eventconsumer_template_type_header
//
CUTS_INLINE
const char * CUTS_BE_TCPIP_Traits::ccm_eventconsumer_template_type_header (void)
{
  return "cuts/arch/rtidds/ccm/RTIDDS_EventConsumer_T";
}

//
// ccm_publisher_template_type
//
CUTS_INLINE
const char * CUTS_BE_TCPIP_Traits::ccm_publisher_template_type (void)
{
  return "CUTS_RTIDDS_CCM_Publisher_T";
}

//
// ccm_publisher_template_type_header
//
CUTS_INLINE
const char * CUTS_BE_TCPIP_Traits::ccm_publisher_template_type_header (void)
{
  return "cuts/arch/rtidds/ccm/RTIDDS_Publisher_T";
}

//
// ccm_publisher_table_template_type
//
CUTS_INLINE
const char * CUTS_BE_TCPIP_Traits::ccm_publisher_table_template_type (void)
{
  return "CUTS_RTIDDS_CCM_Publisher_Table_T";
}

//
// ccm_publisher_table_template_type_header
//
CUTS_INLINE
const char * CUTS_BE_TCPIP_Traits::
ccm_publisher_table_template_type_header (void)
{
  return "cuts/arch/rtidds/ccm/RTIDDS_Publisher_Table_T";
}
