// $Id$

#include "StdAfx.h"
#include "Generators.h"
#include "opensplice/Stub_Generator.h"
#include "rtidds/Stub_Generator.h"
#include "tcpip/Stub_Header_Generator.h"
#include "tcpip/Stub_Source_Generator.h"
#include "IDL_Generator.h"
#include "Servant_Generator.h"
#include "BE_Options.h"

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Finalize_T

CUTS_BE_Finalize_T <CUTS_CHAOS::Context>::
CUTS_BE_Finalize_T (CUTS_CHAOS::Context & context)
: visitor_type (context)
{

}

CUTS_BE_Finalize_T <CUTS_CHAOS::Context>::~CUTS_BE_Finalize_T (void)
{

}

//
// CUTS_BE_Finalize_T <CUTS_BE_TCPIP_Ctx>::generate
//
void CUTS_BE_Finalize_T <CUTS_CHAOS::Context>::
generate (const CHAOS::RootFolder & root)
{
  CHAOS::RootFolder non_const (root);
  std::string outdir = CUTS_BE_OPTIONS ()->output_directory_;

  // Genernate the stub files.
  CUTS_CHAOS::OpenSplice::Stub_Generator ospl_stub_generator (outdir);
  non_const.Accept (ospl_stub_generator);

  CUTS_CHAOS::RTIDDS::Stub_Generator rtidds_stub_generator (outdir);
  non_const.Accept (rtidds_stub_generator);

  CUTS_BE_TCPIP_Stub_Source_Generator tcpip_stub_source (outdir);
  non_const.Accept (tcpip_stub_source);

  CUTS_BE_TCPIP::Stub_Header_Generator tcpip_stub_header (outdir);
  non_const.Accept (tcpip_stub_header);

  // Generate the DDS IDL files.
  CUTS_CHAOS::IDL_Generator dds_idl_gen (outdir);
  non_const.Accept (dds_idl_gen);

  // Generate the servant files.
  CUTS_CHAOS::Servant_Generator svnt_gen (outdir);
  non_const.Accept (svnt_gen);
}
