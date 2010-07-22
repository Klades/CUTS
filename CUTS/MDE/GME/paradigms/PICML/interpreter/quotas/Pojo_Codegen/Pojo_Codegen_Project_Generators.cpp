// $Id$

#include "stdafx.h"
#include "Pojo_Codegen_Project_Generators.h"

#if !defined (__CUTS_INLINE__)
#include "Pojo_Codegen_Project_Generators.inl"
#endif

#include "be/BE_Impl_Node.h"
#include "be/BE_Options.h"
#include "be/BE_Env_Variable_Parser_T.h"

#include "boost/bind.hpp"
#include <algorithm>
#include <sstream>

/**
 * @class ANT_Env_Variable
 */
class ANT_Env_Variable
{
public:
  ANT_Env_Variable (std::string & out)
    : out_ (out)
  {
  }

  template <typename IteratorT>
  void operator () (IteratorT begin, IteratorT end) const
  {
    std::string var (begin, end);
    this->out_ += "${env." + var + "}";
  }

private:
  std::string & out_;
};

//
// CUTS_BE_Project_File_Open_T
//
void CUTS_BE_Project_File_Open_T <
Quotas::Pojo::Codegen::Context, CUTS_BE_Impl_Node>::generate (const CUTS_BE_Impl_Node & node)
{
  std::ostringstream pathname;
  pathname
    << CUTS_BE_OPTIONS ()->output_directory_
    << "/" << node.name_ << ".build";

  this->ctx_.project_file_.open (pathname.str ().c_str ());

  if (!this->ctx_.project_file_.is_open ())
    return;

  // Create a formatter for the XML file.
  this->ctx_.project_formatter_.reset (
    new Quotas::Pojo::Codegen::Context::xml_formatter_type (
    this->ctx_.project_file_));
}

//
// CUTS_BE_Project_File_Begin_T
//
void CUTS_BE_Project_File_Begin_T <Quotas::Pojo::Codegen::Context, CUTS_BE_Impl_Node>::
generate (const CUTS_BE_Impl_Node & node)
{
  // Save the current implementation's node. This is bad, but it's
  // the way we are going to do it for now.
  this->ctx_.impl_node_ =
    const_cast <CUTS_BE_Impl_Node *> (&node);

  // Get the name of the container for later usage.
  std::string name = node.container_.name ();

  this->ctx_.project_file_
    << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << std::endl
    << "<project name=\"cuts.capi.client." << name << "\" basedir=\".\" "
    << "default=\"build.all\">" << std::endl
    << "<property environment=\"env\" />" << std::endl
    << std::endl
    << "<!-- import necessary external files -->" << std::endl
    << "<import file=\"${env.CUTS_ROOT}/etc/ANT/include/cuts.build\" />" << std::endl;

  // If we have any events in this implementation, then we need to
  // include the build file for using Castor within CUTS and ANT.
  if (!this->ctx_.impl_node_->maplist_["events"].empty ())
  {
    this->ctx_.project_file_
      << "<import file=\"${env.CUTS_ROOT}/etc/ANT/include/castor.build\" />" << std::endl
      << std::endl;
  }

  // Get all the monolithic implementations defined in this container.
  // We need to specify each one in the "build.all" target.
  typedef
    std::vector <PICML::MonolithicImplementation>
    MonolithicImplementation_Set;

  MonolithicImplementation_Set monoimpls =
    node.container_.MonolithicImplementation_kind_children ();

  this->ctx_.project_file_
    << std::endl
    << "<!-- build all the implementations -->" << std::endl
    << "<target name=\"build.all\" depends=\"";

  // Write the depends statement for the target, which is
  // all the monolithic task defined in this monolithic impl.
  if (!monoimpls.empty ())
  {
    MonolithicImplementation_Set::iterator
      iter = monoimpls.begin (), iter_end = monoimpls.end ();

    this->ctx_.project_file_
      << iter->name () << ".jar.build";

    for (++ iter; iter != iter_end; ++ iter)
    {
      this->ctx_.project_file_
        << " " << iter->name () << ".jar.build";
    }
  }

  this->ctx_.project_file_
    << "\" />" << std::endl;
}

//
// CUTS_BE_Project_Write_T
//
void CUTS_BE_Project_Write_T <Quotas::Pojo::Codegen::Context, CUTS_BE_Impl_Node>::
generate (const CUTS_BE_Impl_Node & node)
{
  // Get all the monolithic implementations defined in this container.
  // We need to specify each one in the "build.all" target.
  typedef
    std::vector <PICML::MonolithicImplementation>
    MonolithicImplementation_Set;

  MonolithicImplementation_Set monoimpls =
    node.container_.MonolithicImplementation_kind_children ();

  // Generate build scripts for each of the implemenations.
  std::for_each (monoimpls.begin (),
                 monoimpls.end (),
                 boost::bind (&CUTS_BE_Project_Write_T <Quotas::Pojo::Codegen::Context, CUTS_BE_Impl_Node>::generate_i,
                              this,
                              _1));
}

//
// CUTS_BE_Project_Write_T::generate_i
//
void CUTS_BE_Project_Write_T <Quotas::Pojo::Codegen::Context, CUTS_BE_Impl_Node>::
generate_i (const PICML::MonolithicImplementation & monoimpl)
{
  std::string name = monoimpl.name ();

  const CUTS_String_Set & eventset = this->ctx_.impl_node_->maplist_["events"];
  const CUTS_String_Set & classpath = this->ctx_.impl_node_->maplist_["classpath"];

  this->ctx_.project_file_
    << std::endl
    << "<target name=\"" << name << ".build\">" << std::endl
    << "<javac srcdir=\".\" classpathref=\"cuts.quotas.pojo.classpath\" "
    << "debug=\"true\" debuglevel=\"source,lines\">" << std::endl;

  if (!classpath.empty ())
  {
    std::string output;
    CUTS_BE_Env_Variable_Parser_T <ANT_Env_Variable> env_parser (output);

    this->ctx_.project_file_
      << "<classpath>" << std::endl;

    for (CUTS_String_Set::const_iterator
         iter = classpath.begin (), iter_end = classpath.end ();
         iter != iter_end; ++ iter)
    {
      if (!output.empty ())
        output.clear ();

      // Convert any environment variables defined in the JAR file.
      boost::spirit::parse (iter->c_str (), env_parser);

      this->ctx_.project_file_
        << "<pathelement location=\"" << output << "\" />" << std::endl;
    }

    this->ctx_.project_file_
      << "</classpath>" << std::endl;
  }

  this->ctx_.project_file_
    << std::endl
    << "<!-- main class file (contains child classes) -->" << std::endl
    << "<include name=\"" << name << ".java\" />" << std::endl
    << "</javac>" << std::endl
    << "</target>" << std::endl
    << std::endl
    << "<target name=\"" << name << ".jar.build\" "
    << "depends=\"" << name << ".build\">" << std::endl
    << "<!-- create the library directory -->" << std::endl
    << "<mkdir dir=\"./lib\" />" << std::endl
    << std::endl
    << "<!-- create the final jar file -->" << std::endl
    << "<jar destfile=\"./lib/" << name << ".jar\" basedir=\".\">" << std::endl
    << std::endl
    << "<!-- main class -->" << std::endl
    << "<include name=\"" << name << ".class\" />" << std::endl
    << std::endl
    << "<!-- private child classes -->" << std::endl
    << "<include name=\"" << name << "$*.class\" />" << std::endl
    << "</jar>" << std::endl
    << "</target>" << std::endl;
}

//
// CUTS_BE_Project_Write_T::generate_target_events_srcgen
//
void CUTS_BE_Project_Write_T <Quotas::Pojo::Codegen::Context, CUTS_BE_Impl_Node>::
generate_target_events_srcgen (void)
{
  this->ctx_.project_file_
    << std::endl
    << "<target name=\"events.srcgen\">";

  const CUTS_String_Set & eventset =
    this->ctx_.impl_node_->maplist_["events"];

  std::string path;

  CUTS_String_Set::const_iterator
    iter = eventset.begin (), iter_end = eventset.end ();

  for ( ; iter != iter_end; ++ iter)
  {
    path = *iter;
    std::replace (path.begin (), path.end (), '.', '/');

    this->ctx_.project_file_
      << std::endl
      << "<!-- eventtype : " << *iter << ".xsd -->" << std::endl
      << "<delete includeemptydirs=\"true\" verbose=\"true\">" << std::endl
      << "<fileset dir=\".\">" << std::endl
      << "<include name=\"" << path << "/*.java\" />" << std::endl
      << "<include name=\"" << path << "/*.class\" />" << std::endl
      << "</fileset>" << std::endl
      << "</delete>" << std::endl
      << std::endl
      << "<java" << std::endl
      << "classname=\"org.exolab.castor.builder.SourceGeneratorMain\"" << std::endl
      << "classpathref=\"castor.srcgen.classpath\"" << std::endl
      << "failonerror=\"true\">" << std::endl
      << "<arg line=\"-i ${jbi.schemas.dir}/" << path
      << "/" << *iter << ".xsd\" />" << std::endl
      << "<arg line=\"-package " << *iter << "\" />" << std::endl
      << "<arg line=\"-f -nodesc -nomarshall\" />" << std::endl
      << "</java>" << std::endl;
  }

  this->ctx_.project_file_
    << "</target>" << std::endl;
}

//
// CUTS_BE_Project_File_End_T
//
void CUTS_BE_Project_File_End_T <Quotas::Pojo::Codegen::Context, CUTS_BE_Impl_Node>::
generate (const CUTS_BE_Impl_Node & node)
{
  std::string name = node.container_.name ();

  this->ctx_.project_file_
    << "</project>" << std::endl
    << std::endl
    << "<!-- end of auto-generated file -->" << std::endl;
}

//
// CUTS_BE_Project_File_Close_T
//
void CUTS_BE_Project_File_Close_T <Quotas::Pojo::Codegen::Context, CUTS_BE_Impl_Node>::
generate (void)
{
  this->ctx_.project_formatter_.reset ();
  this->ctx_.project_file_.close ();
}
