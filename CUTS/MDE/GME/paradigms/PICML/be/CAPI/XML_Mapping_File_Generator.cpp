// $Id$

#include "XML_Mapping_File_Generator.h"
#include "CAPI_Ctx.h"
#include "be/UDM_Position_Sort_T.h"
#include "CCF/CodeGenerationKit/IndentationXML.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"
#include "boost/bind.hpp"
#include "Utils.h"
#include <algorithm>

//
// XML_Mapping_File_Generator
//
XML_Mapping_File_Generator::
XML_Mapping_File_Generator (const std::string & outdir)
: outdir_ (outdir),
  dispatcher_ (*this)
{
  this->dispatcher_.insert <PICML::String> ();
  this->dispatcher_.insert <PICML::LongInteger> ();
  this->dispatcher_.insert <PICML::ShortInteger> ();
  this->dispatcher_.insert <PICML::Boolean> ();
  this->dispatcher_.insert <PICML::Byte> ();
  this->dispatcher_.insert <PICML::RealNumber> ();
}

//
// ~XML_Mapping_File_Generator
//
XML_Mapping_File_Generator::~XML_Mapping_File_Generator (void)
{
  if (this->outfile_.is_open ())
    this->outfile_.close ();
}

//
// Visit_Event
//
void XML_Mapping_File_Generator::
Visit_Event (const PICML::Event & event)
{
  // Gather required information about the event.
  std::string xmltag = event.SpecifyIdTag ();
  std::string fq_name = CUTS_BE_Capi::fq_name (event, '.');
  std::string classname = fq_name + '.' + CUTS_BE_Capi::classname (xmltag);

  // Save the package name for later.
  this->package_ = fq_name;

  // Construct the path for the filename. We need to make sure
  // this directory exist before trying to open the mapping file.
  std::ostringstream path;
  path
    << this->outdir_ << "\\"
    << CUTS_BE_Capi::fq_name (event, '\\');

  Utils::CreatePath (path.str (), '\\');
  std::string filename = path.str () + "\\mapping.xml";

  // Open the file for writing.
  this->outfile_.open (filename.c_str ());

  if (!this->outfile_.is_open ())
    return;

  // Set the indentation implanter for the output file.
  typedef Indentation::Implanter <
    Indentation::XML, char> formatter_type;

  formatter_type formatter (this->outfile_);

  // Write the XML preamble and opening tag.
  this->outfile_
    << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << std::endl
    << "<!DOCTYPE mapping PUBLIC \"-//EXOLAB/Castor Mapping DTD Version 1.0//EN\"" << std::endl
    << "                       \"http://castor.org/mapping.dtd\">" << std::endl
    << "<mapping>" << std::endl
    << std::endl
    << "<!-- event : " << fq_name << " -->" << std::endl
    << "<class name=\"" << classname << "\" auto-complete=\"false\">" << std::endl
    << "<map-to xml=\"" << xmltag << "\" />" << std::endl;

  typedef
    UDM_Position_Sort_T <PICML::Member, PS_Top_To_Bottom>
    _sort_function;

  // Visit all the members in this event.
  typedef std::set <PICML::Member, _sort_function> Member_Set;

  Member_Set members =
    event.Member_kind_children_sorted (_sort_function ());

  std::for_each (members.begin (),
                 members.end (),
                 boost::bind (&Member_Set::value_type::Accept,
                              _1,
                              boost::ref (*this)));

  // Close the class definition.
  this->outfile_
    << "</class>" << std::endl;

  // Process the extension classes.
  std::for_each (this->extensions_.begin (),
                 this->extensions_.end (),
                 boost::bind (&XML_Mapping_File_Generator::write_extension_mapping,
                              this,
                              _1));

  // Process the remaining complex types.
  PICML::Aggregate complex_type;

  while (!this->complex_types_.empty ())
  {
    complex_type = this->complex_types_.top ();
    this->complex_types_.pop ();

    // Visit this complex type.
    complex_type.Accept (*this);
  }

  // Writing the closing tag.
  this->outfile_
    << "</mapping>" << std::endl
    << std::endl;

    // Close the mapping file.
  this->outfile_.close ();
}

//
// Visit_Member
//
void XML_Mapping_File_Generator::
Visit_Member (const PICML::Member & member)
{
  // Extract information about the member and its type.
  PICML::MemberType mt = member.ref ();
  Uml::Class meta = mt.type ();

  if (meta == PICML::Aggregate::meta)
  {
    PICML::Aggregate aggr = PICML::Aggregate::Cast (mt);

    if (this->seen_complex_types_.find (aggr) == 
        this->seen_complex_types_.end ())
    {
      // We have not seen this complex type, so we need to generate a
      // definition for it.
      this->complex_types_.push (aggr);
      this->seen_complex_types_.insert (aggr);
    }

    std::string xml_name = member.name ();
    std::string field_name = member.name ();
    field_name[0] = ::toupper (field_name[0]);
    
    std::string mt_name = mt.name ();

    // Write the mapping for this aggregate type.
    this->outfile_
      << std::endl
      << "<field name=\"" << field_name << "\" type=\"" 
      << this->package_ << "." << field_name << "\">" << std::endl
      << "<bind-xml name=\"" << xml_name 
      << "\" node=\"element\" />" << std::endl
      << "</field>" << std::endl;

    // Save the extension mapping for later.
    this->extensions_.insert (std::make_pair (xml_name, mt_name));
  }
  else
  {
    std::string xml_name = member.name ();
    std::string field_name = member.name ();
    field_name[0] = ::toupper (field_name[0]);

    this->outfile_
      << std::endl
      << "<field name=\"" << field_name << "\" type=\"";

    this->dispatcher_.dispatch (mt);

    this->outfile_
      << "\">" << std::endl
      << "<bind-xml name=\"" << xml_name << "\" />" << std::endl
      << "</field>" << std::endl;
  }
}

//
// Visit_String
//
void XML_Mapping_File_Generator::
Visit_String (const PICML::String & )
{
  this->outfile_ << "java.lang.String";
}

//
// Visit_LongInteger
//
void XML_Mapping_File_Generator::
Visit_LongInteger (const PICML::LongInteger & )
{
  this->outfile_ << "long";
}

//
// Visit_ShortInteger
//
void XML_Mapping_File_Generator::
Visit_ShortInteger (const PICML::ShortInteger & )
{
  this->outfile_ << "short";
}

//
// Visit_Byte
//
void XML_Mapping_File_Generator::
Visit_Byte (const PICML::Byte & )
{
  this->outfile_ << "java.lang.Byte";
}

//
// Visit_Aggregate
//
void XML_Mapping_File_Generator::
Visit_Aggregate (const PICML::Aggregate & aggr)
{
  std::string name = aggr.name ();
  std::string fq_name = CUTS_BE_Capi::fq_name (aggr, '.');
  std::string classname = this->package_ + '.' + CUTS_BE_Capi::classname (name);

  // Begin the complex type's definition.
  this->outfile_
    << std::endl
    << "<!-- aggregate  : " << fq_name << " -->" << std::endl
    << "<class name=\"" << classname << "\" auto-complete=\"false\">" << std::endl;

  // Visit all the members of the complex type.
  typedef std::set <PICML::Member> Member_Set;
  Member_Set members = aggr.Member_kind_children ();

  std::for_each (members.begin (),
                 members.end (),
                 boost::bind (&Member_Set::value_type::Accept,
                              _1,
                              boost::ref (*this)));

  // End the complex type's definition.
  this->outfile_
    << "</class>" << std::endl;
}

//
// write_extension_mapping
//
void XML_Mapping_File_Generator::
write_extension_mapping (const std::pair <std::string, std::string> & extension)
{
  std::string subclass = extension.first;
  subclass[0] = ::toupper (subclass[0]);

  std::string base_class = extension.second;
  base_class[0] = ::toupper (extension.second[0]);

  this->outfile_
    << std::endl
    << "<class name=\"" << this->package_ << '.' << subclass 
    << "\" auto-complete=\"false\"" << std::endl
    << "     extends=\"" << this->package_ << '.' << base_class << "\" />" 
    << std::endl;
}
