// $Id$

#include "TCPIP_Generator.h"
#include "Stub_Source_Generator.h"
#include "Stub_Header_Generator.h"
#include "../../BE_Options.h"

//
// CUTS_BE_Finalize_T <CUTS_BE_TCPIP_Ctx>::generate
//
void CUTS_BE_Finalize_T <CUTS_BE_TCPIP_Ctx>::
generate (const PICML::RootFolder & root)
{
  PICML::RootFolder temp (root);

  // Genernate the stub source file(s).
  CUTS_BE_TCPIP_Stub_Source_Generator ssg (CUTS_BE_OPTIONS ()->output_directory_);
  temp.Accept (ssg);

  // Generator the stub header file(s)
  CUTS_BE_TCPIP::Stub_Header_Generator shg (CUTS_BE_OPTIONS ()->output_directory_);
  temp.Accept (shg);
}
