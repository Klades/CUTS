// $Id$

#include "XSD_File_Generator.h"
#include "CAPI_Ctx.h"
#include "Utils/Utils.h"
#include "../../UDM_Position_Sort_T.h"
#include "boost/bind.hpp"
#include "CCF/CodeGenerationKit/IndentationXML.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

//
// XSD_File_Generator
//
XSD_File_Generator::XSD_File_Generator (const std::string & outdir)
: outdir_ (outdir),
  dispatcher_ (this)
{
  // Initialize the Accept dispatcher for abstract base types.
  this->dispatcher_.insert <PICML::String> ();
  this->dispatcher_.insert <PICML::LongInteger> ();
  this->dispatcher_.insert <PICML::ShortInteger> ();
  this->dispatcher_.insert <PICML::Boolean> ();
  this->dispatcher_.insert <PICML::Byte> ();
  this->dispatcher_.insert <PICML::DoubleNumber> ();
  this->dispatcher_.insert <PICML::Aggregate> ();
  this->dispatcher_.insert <PICML::Enum> ();
}

//
// ~XSD_File_Generator
//
XSD_File_Generator::~XSD_File_Generator (void)
{
  if (this->fout_.is_open ())
    this->fout_.close ();
}

//
// Visit_Event
//
void XSD_File_Generator::Visit_Event (const PICML::Event & ev)
{
  // Gather required information about the ev.
  std::string xmltag = ev.SpecifyIdTag ();
  std::string fq_name = CUTS_BE_Java::fq_type (ev, ".", false);
  std::string classname = fq_name + '.' + CUTS_BE_Java::classname (xmltag);

  // Construct the path for the filename. We need to make sure
  // this directory exist before trying to open the mapping file.
  std::ostringstream path;
  path
    << this->outdir_ << CUTS_BE_Java::fq_type (ev, "\\", true);

  Utils::CreatePath (path.str (), '\\');
  std::string filename = path.str () + "\\" + fq_name + ".xsd";

  // Open the file for writing.
  this->fout_.open (filename.c_str ());

  if (!this->fout_.is_open ())
    return;

  // Set the indentation implanter for the output file.
  typedef Indentation::Implanter <
    Indentation::XML, char> formatter_type;

  formatter_type formatter (this->fout_);

  // Write the header for the file.
  this->fout_ << "<?xml version='1.0' encoding='UTF-8' standalone='no' ?>" << std::endl
              << "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
              << " elementFormDefault='unqualified' version='";

  // Set the version number for the schema based on the ev's
  // version number.
  std::string version = ev.VersionTag ();

  if (version.empty ())
  {
    version = "1.0";
    ev.VersionTag () = version;
  }

  this->fout_ << version << "'>" << std::endl;

  // Push the root element onto the stack then finish visiting
  // the ev element.

  std::string name = ev.SpecifyIdTag ();

  this->fout_ << "<xsd:element name='" << name << "'>" << std::endl;
  this->Visit_Event_i (ev, true);
  this->fout_ << "</xsd:element>" << std::endl;

  while (!this->complex_types_.empty ())
  {
    // Visit all the complex types that we located, but have not
    // generate code for.
    PICML::Aggregate aggr = this->complex_types_.top ();
    this->complex_types_.pop ();

    this->Visit_Aggregate_i (aggr);
  }

  std::for_each (this->enum_types_.begin (),
                 this->enum_types_.end (),
                 boost::bind (&XSD_File_Generator::Visit_Enum_i,
                              this,
                              _1));

  this->fout_ << "</xsd:schema>" << std::endl
              << std::endl;

  // Close the file.
  this->fout_.close ();
}

//
// Visit_Member
//
void XSD_File_Generator::Visit_Member (const PICML::Member & member)
{
  PICML::MemberType mt = member.ref ();

  if (mt != Udm::null)
  {
    // Create a xsd:complexType element for the ev.
    this->fout_ << "<xsd:element name='" << member.name () << "' ";
    this->dispatcher_.dispatch (mt);
    this->fout_ << " />" << std::endl;
  }
}

//
// Visit_String
//
void XSD_File_Generator::Visit_String (const PICML::String & )
{
  this->fout_ << "type='xsd:string'";
}

//
// Visit_LongInteger
//
void XSD_File_Generator::Visit_LongInteger (const PICML::LongInteger & )
{
  this->fout_ << "type='xsd:long'";
}

//
// Visit_Byte
//
void XSD_File_Generator::Visit_Byte (const PICML::Byte &)
{
  this->fout_ << "type='xsd:byte'";
}

//
// Visit_ShortInteger
//
void XSD_File_Generator::Visit_ShortInteger (const PICML::ShortInteger &)
{
  this->fout_ << "type='xsd:short'";
}

//
// Visit_Aggregate
//
void XSD_File_Generator::Visit_Aggregate (const PICML::Aggregate & aggr)
{
  std::string name = aggr.name ();

  // First, set the type for the current element.
  this->fout_ << "type='" << name << "'";

  if (this->seen_complex_types_.find (aggr) ==
      this->seen_complex_types_.end ())
  {
    // Save the aggregate for later.
    this->seen_complex_types_.insert (aggr);
    this->complex_types_.push (aggr);
  }
}

//
// Visit_Enum
//
void XSD_File_Generator::Visit_Enum (const PICML::Enum & e)
{
  this->fout_ << "type='" << e.name () << "'";
  this->enum_types_.insert (e);
}

//
// Visit_Enum
//
void XSD_File_Generator::Visit_Enum_i (const PICML::Enum & e)
{
  // The Enum is actually a *simpleType* in XSD.
  this->fout_ << "<xsd:simpleType name='" << e.name () << "'>" << std::endl
              << "<xsd:restriction base='xsd:string'>" << std::endl;

  // Visit each of the enum values.
  std::vector <PICML::EnumValue> values = e.EnumValue_children ();

  std::for_each (values.begin (),
                 values.end (),
                 boost::bind (&PICML::EnumValue::Accept,
                              _1,
                              boost::ref (*this)));

  this->fout_ << "</xsd:restriction>" << std::endl
              << "</xsd:simpleType>" << std::endl;
}

//
// Visit_EnumValue
//
void XSD_File_Generator::Visit_EnumValue (const PICML::EnumValue & val)
{
  this->fout_ << "<xsd:enumeration value='" << val.name ()
              << "' />" << std::endl;
}

//
// Visit_Aggregate_i
//
void XSD_File_Generator::Visit_Aggregate_i (const PICML::Aggregate & aggr)
{
  // Note that we have seen this aggregate type.
  this->seen_complex_types_.insert (aggr);

  this->fout_ << "<xsd:complexType name='" << aggr.name () << "'>" << std::endl
              << "<xsd:sequence>" << std::endl;

  // Visit all the members in this ev. We sort the members from top
  // to bottom on the page.
  typedef
    UDM_Position_Sort_T <PICML::Member, PS_Top_To_Bottom>
    _sort_function;

  typedef std::set <PICML::Member, _sort_function> Member_Set;

  Member_Set members =
    aggr.Member_kind_children_sorted (_sort_function ());

  std::for_each (members.begin (),
                 members.end (),
                 boost::bind (&Member_Set::value_type::Accept,
                              _1,
                              boost::ref (*this)));

  this->fout_ << "</xsd:sequence>" << std::endl
              << "</xsd:complexType>" << std::endl;
}

//
// Visit_Event_i
//
void XSD_File_Generator::
Visit_Event_i (const PICML::Event & ev, bool anonymous)
{
  this->fout_ << "<xsd:complexType";

  if (!anonymous)
    this->fout_ << " name='" << ev.SpecifyIdTag () << "'";

  this->fout_ << ">" << std::endl;

  // Create the xsd:sequence element for the ev's members.
  this->fout_ << "<xsd:sequence>" << std::endl;

  // Visit all the members in this ev. We sort the members from
  // top to bottom on the page, just like a file.
  typedef
    UDM_Position_Sort_T <PICML::Member, PS_Top_To_Bottom>
    _sort_function;

  typedef std::set <PICML::Member, _sort_function> Member_Set;

  Member_Set members =
    ev.Member_kind_children_sorted (_sort_function ());

  std::for_each (members.begin (),
                 members.end (),
                 boost::bind (&Member_Set::value_type::Accept,
                              _1,
                              boost::ref (*this)));

  this->fout_ << "</xsd:sequence>" << std::endl
              << "</xsd:complexType>" << std::endl;
}
