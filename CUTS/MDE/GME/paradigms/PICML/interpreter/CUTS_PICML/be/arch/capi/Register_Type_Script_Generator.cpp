// $Id$

#include "Register_Type_Script_Generator.h"
#include "CAPI_Ctx.h"
#include <sstream>

static const char * bat_header =
"@rem #########################################################################\n"
"@rem #\n"
"@rem # @file         register_mio_types.bat\n"
"@rem #\n"
"@rem # $Id$\n"
"@rem #\n"
"@rem # @author       James H. Hill (hillj@dre.vanerbilt.edu)\n"
"@rem #               CUTS Modeling Tools for CoSMIC\n"
"@rem #               http://www.dre.vanderbilt.edu/CUTS\n"
"@rem #\n"
"@rem #########################################################################\n";

static const char * sh_header =
"##############################################################################\n"
"#\n"
"# @file         register_mio_types.sh\n"
"#\n"
"# $Id$\n"
"#\n"
"# @author       James H. Hill\n"
"#               CUTS Modeling Tools for CoSMIC\n"
"#               http://www.dre.vanderbilt.edu/CUTS\n"
"#\n"
"##############################################################################\n";

//
// Register_Type_Script_Generator
//
Register_Type_Script_Generator::
Register_Type_Script_Generator (const std::string & basedir)
: basedir_ (basedir)
{

}

//
// ~Register_Type_Script_Generator
//
Register_Type_Script_Generator::~Register_Type_Script_Generator (void)
{

}

//
// generate
//
void Register_Type_Script_Generator::
generate (const std::set <PICML::Event> & events)
{
  this->generate_bat_script (events);
  this->generate_sh_script (events);
}

//
// generate_bat_script
//
void Register_Type_Script_Generator::
generate_bat_script (const std::set <PICML::Event> & events)
{
  std::ostringstream bat_filename;
  bat_filename << this->basedir_ << "/bin/" << "register_mio_types.bat";

  std::ofstream bat_file;
  bat_file.open (bat_filename.str ().c_str ());

  if (bat_file.is_open ())
  {
    bat_file
      << bat_header << std::endl;

    std::set <PICML::Event>::const_iterator
      iter = events.begin (), iter_end = events.end ();

    std::string fq_name;

    for (; iter != iter_end; ++ iter)
    {
      fq_name = CUTS_BE_Capi::fq_name (*iter, '.');

      bat_file
        << "%CUTS_ROOT%/bin/jbi/RegisterMioType.bat -mio-type "
        << fq_name << " %*" << std::endl;
    }

    // Close the output file.
    bat_file.close ();
  }
  else
  {

  }
}

//
// generate_bat_script
//
void Register_Type_Script_Generator::
generate_sh_script (const std::set <PICML::Event> & events)
{
  std::ostringstream sh_filename;
  sh_filename << this->basedir_ << "/bin/" << "register_mio_types.sh";

  std::ofstream sh_file;
  sh_file.open (sh_filename.str ().c_str ());

  if (sh_file.is_open ())
  {
    sh_file
      << "#!/bin/bash" << std::endl
      << std::endl
      << sh_header << std::endl;

    std::set <PICML::Event>::const_iterator
      iter = events.begin (), iter_end = events.end ();
    std::string fq_name;

    for (; iter != iter_end; ++ iter)
    {
      fq_name = CUTS_BE_Capi::fq_name (*iter, '.');

      sh_file
        << "${CUTS_ROOT}/bin/jbi/RegisterMioType.sh -mio-type "
        << fq_name << " \"$@\"" << std::endl;
    }

    // Close the output file.
    sh_file.close ();
  }
  else
  {

  }
}
