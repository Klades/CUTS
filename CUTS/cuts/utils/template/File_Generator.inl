// -*- C++ -*-
// $Id$

//
// CUTS_File_Generator
//
CUTS_INLINE
CUTS_File_Generator::
CUTS_File_Generator (const bool & use_env,
                     const bool & ignore_variables,
                     const bool & ignore_commands,
                     const std::string & templ,
                     const std::string & output)
: use_env_ (use_env),
  ignore_variables_ (ignore_variables),
  ignore_commands_ (ignore_commands),
  template_ (templ),
  output_ (output)
{

}

//
// CUTS_File_Generator
//
CUTS_INLINE
CUTS_File_Generator::~CUTS_File_Generator (void)
{

}
