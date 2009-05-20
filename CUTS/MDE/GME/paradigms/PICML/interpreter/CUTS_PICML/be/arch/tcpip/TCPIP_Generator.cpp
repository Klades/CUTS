// $Id$

#include "TCPIP_Generator.h"
#include "Stub_Source_Generator.h"
#include "Stub_Header_Generator.h"
#include "Servant_Header_Generator.h"
#include "../../BE_Options.h"

//
// CUTS_BE_Finalize_T <CUTS_BE_TCPIP_Ctx>::generate
//
void CUTS_BE_Finalize_T <CUTS_BE_TCPIP_Ctx>::
generate (const PICML::RootFolder & root)
{
  PICML::RootFolder temp (root);
  std::string outdir = CUTS_BE_OPTIONS ()->output_directory_;

  // Genernate the stub source file(s).
  CUTS_BE_TCPIP_Stub_Source_Generator stub_source (outdir);
  temp.Accept (stub_source);

  // Generator the stub header file(s)
  CUTS_BE_TCPIP::Stub_Header_Generator stub_header (outdir);
  temp.Accept (stub_header);

  CUTS_BE_TCPIP::Servant_Header_Generator svnt_header (outdir);
  temp.Accept (svnt_header);
}
