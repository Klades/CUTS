// $Id$

#include "Set_Classpath_Script_Generator.h"
#include "CAPI_Preprocessor.h"
#include "../BE_Env_Variable_Parser_T.h"
#include "boost/bind.hpp"
#include "ace/OS_NS_sys_stat.h"
#include <algorithm>
#include <fstream>

static const char * bat_header =
"@rem #########################################################################\n"
"@rem #\n"
"@rem # @file         set_classpath.bat\n"
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
"# @file         set_classpath.sh\n"
"#\n"
"# $Id$\n"
"#\n"
"# @author       James H. Hill\n"
"#               CUTS Modeling Tools for CoSMIC\n"
"#               http://www.dre.vanderbilt.edu/CUTS\n"
"#\n"
"##############################################################################\n";

/**
 * @struct ANT_Env_Variable
 */
struct Sh_Env_Variable
{
public:
  Sh_Env_Variable (std::string & out)
    : out_ (out)
  {
  }

  template <typename IteratorT>
  void operator () (IteratorT begin, IteratorT end) const
  {
    std::string var (begin, end);
    this->out_ += "${" + var + "}";
  }

private:
  std::string & out_;
};


/**
 * @struct ANT_Env_Variable
 */
struct Bat_Env_Variable
{
public:
  Bat_Env_Variable (std::string & out)
    : out_ (out)
  {
  }

  template <typename IteratorT>
  void operator () (IteratorT begin, IteratorT end) const
  {
    std::string var (begin, end);
    this->out_ += "%" + var + "%";
  }

private:
  std::string & out_;
};

//
// Set_Classpath_Script_Generator
//
Set_Classpath_Script_Generator::
Set_Classpath_Script_Generator (const std::string & basedir)
: basedir_ (basedir)
{

}

//
// Set_Classpath_Script_Generator
//
Set_Classpath_Script_Generator::~Set_Classpath_Script_Generator (void)
{

}

//
// Visit_RootFolder
//
void Set_Classpath_Script_Generator::
Visit_RootFolder (const PICML::RootFolder & folder)
{
  typedef std::vector <PICML::ComponentImplementations> Folder_Set;
  Folder_Set folders = folder.ComponentImplementations_children ();

  std::for_each (folders.begin (),
                 folders.end (),
                 boost::bind (&Folder_Set::value_type::Accept,
                              _1,
                              boost::ref (*this)));

  if (!this->impls_.empty ())
  {
    // Make sure the ./bin directory exist.
    std::string bindir = this->basedir_ + "/bin";
    ACE_OS::mkdir (bindir.c_str ());

    // Now, generate the scripts in the bin directory
    this->generate_sh_script (bindir);
    this->generate_bat_script (bindir);
  }
}

//
// Visit_ComponentImplementations
//
void Set_Classpath_Script_Generator::
Visit_ComponentImplementations (const PICML::ComponentImplementations & folder)
{
  typedef std::vector <PICML::ComponentImplementationContainer> Container_Set;
  Container_Set containers = folder.ComponentImplementationContainer_children ();

  std::for_each (containers.begin (),
                 containers.end (),
                 boost::bind (&Container_Set::value_type::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_ComponentImplementationContainer
//
void Set_Classpath_Script_Generator::
Visit_ComponentImplementationContainer (const PICML::ComponentImplementationContainer & container)
{
  typedef std::vector <PICML::MonolithicImplementation> Mono_Set;
  Mono_Set monos = container.MonolithicImplementation_kind_children ();

  const CUTS_BE_Impl_Node * impl = 0;

  if (CUTS_BE_CAPI_PREPROCESSOR->impls ().find (container.name (), impl))
  {
    CUTS_BE_Impl_Node::Map_List::
      const_iterator location =  impl->maplist_.find ("classpath");

    if (location != impl->maplist_.end ())
    {
      CUTS_String_Set::const_iterator
        iter = location->second.begin (), iter_end = location->second.end ();

      for ( ; iter != iter_end; ++ iter)
        this->lit_jars_.insert (*iter);
    }
  }

  std::for_each (monos.begin (),
                 monos.end (),
                 boost::bind (&Mono_Set::value_type::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_MonolithicImplementation
//
void Set_Classpath_Script_Generator::
Visit_MonolithicImplementation (const PICML::MonolithicImplementation & mono)
{
  this->impls_.insert (mono.name ());
}

//
// generate_batch_file
//
void Set_Classpath_Script_Generator::
generate_bat_script (const std::string & bindir)
{
  std::string bat_filename = bindir + "\\set_classpath.bat";

  std::ofstream bat_file;
  bat_file.open (bat_filename.c_str ());

  if (bat_file.is_open ())
  {
    bat_file
      << bat_header << std::endl
      << "@set CLASSPATH=";

    std::set <std::string>::const_iterator
      iter = this->impls_.begin (), iter_end = this->impls_.end ();

    for ( ; iter != iter_end; ++ iter)
    {
      bat_file
        << "%~dp0..\\lib\\" << *iter << ".jar;";
    }

    // We need to prepend te jarfiles that were used to build the application
    // level components. This usually includes the worker libraries.
    std::string output;
    CUTS_BE_Env_Variable_Parser_T <Bat_Env_Variable> env_parser (output);

    iter = this->lit_jars_.begin ();
    iter_end = this->lit_jars_.end ();

    for ( ; iter != iter_end; ++ iter)
    {
      // Convert any environment variables defined in the JAR file.
      if (boost::spirit::parse (iter->c_str (), env_parser).full)
        bat_file << output << ";";
      else
        bat_file << *iter << ";";
    }

    // Prepend the current classpath to the variable.
    bat_file
      << "%~dp0..\\lib\\jbi.eventtypes.jar;%CLASSPATH%" << std::endl;

    // Close the file
    bat_file.close ();
  }
  else
  {
    // print an error
  }
}

//
// generate_shell_script
//
void Set_Classpath_Script_Generator::
generate_sh_script (const std::string & bindir)
{
  std::string sh_filename = bindir + "/set_classpath.sh";

  std::ofstream sh_file;
  sh_file.open (sh_filename.c_str ());

  if (sh_file.is_open ())
  {
    sh_file
      << "#!/bin/bash" << std::endl
      << std::endl
      << sh_header << std::endl
      << "BIN_DIR=`dirname $0`" << std::endl
      << "LIB_DIR=${BIN_DIR}/../lib" << std::endl
      << std::endl
      << "export CLASSPATH=";

    std::set <std::string>::const_iterator
      iter = this->impls_.begin (), iter_end = this->impls_.end ();

    for ( ; iter != iter_end; ++ iter)
    {
      sh_file
        << "${LIB_DIR}/" << *iter << ".jar:";
    }

    // We need to prepend te jarfiles that were used to build the application
    // level components. This usually includes the worker libraries.
    std::string output;
    CUTS_BE_Env_Variable_Parser_T <Sh_Env_Variable> env_parser (output);

    iter = this->lit_jars_.begin ();
    iter_end = this->lit_jars_.end ();

    for ( ; iter != iter_end; ++ iter)
    {
      // Convert any environment variables defined in the JAR file.
      if (boost::spirit::parse (iter->c_str (), env_parser).full)
        sh_file << output << ":";
      else
        sh_file << *iter << ":";
    }

    // Prepend the current classpath to the variable.
    sh_file
      << "${LIB_DIR}/jbi.eventtypes.jar:${CLASSPATH}" << std::endl;

    // Close the file
    sh_file.close ();
  }
  else
  {
    // print an error
  }
}
