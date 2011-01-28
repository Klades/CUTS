// $Id$

#include "Generators.h"
#include "Stub_Generator.h"
#include "Servant_Generator.h"
#include "../../../BE_Options.h"

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Finalize_T

CUTS_BE_Finalize_T <CUTS_BE_OpenSplice::Context>::
CUTS_BE_Finalize_T (CUTS_BE_OpenSplice::Context & context)
: visitor_type (context)
{

}

CUTS_BE_Finalize_T <CUTS_BE_OpenSplice::Context>::~CUTS_BE_Finalize_T (void)
{

}

//
// CUTS_BE_Finalize_T <CUTS_BE_TCPIP_Ctx>::generate
//
void CUTS_BE_Finalize_T <CUTS_BE_OpenSplice::Context>::
generate (const PICML::RootFolder & root)
{
  PICML::RootFolder non_const (root);
  const std::string outdir = CUTS_BE_OPTIONS ()->output_directory_;

  // Genernate the stub files.
  CUTS_BE_OpenSplice::Stub_Generator stub_generator (outdir);
  non_const.Accept (stub_generator);

  CUTS_BE_OpenSplice::Servant_Generator svnt_gen (outdir);
  non_const.Accept (svnt_gen);
}
