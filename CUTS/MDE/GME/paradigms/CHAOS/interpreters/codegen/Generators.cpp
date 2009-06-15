// $Id$

#include "StdAfx.h"
#include "Generators.h"
#include "Stub_Generator.h"
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
  CUTS_CHAOS::OpenSplice_Stub_Generator stub_generator (outdir);
  non_const.Accept (stub_generator);

  // Genernate the stub files.
  CUTS_BE_TCPIP_Stub_Source_Generator stub_source (outdir);
  non_const.Accept (stub_source);

  CUTS_BE_TCPIP::Stub_Header_Generator stub_header (outdir);
  non_const.Accept (stub_header);

  // Generate the DDS IDL files.
  CUTS_CHAOS::IDL_Generator idlgen (outdir);
  non_const.Accept (idlgen);

  // Generate the servant files.
  CUTS_CHAOS::Servant_Generator svnt_gen (outdir);
  non_const.Accept (svnt_gen);
}
