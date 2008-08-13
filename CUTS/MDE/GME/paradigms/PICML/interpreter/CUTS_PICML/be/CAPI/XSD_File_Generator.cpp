// $Id$

#include "XSD_File_Generator.h"
#include "CAPI_Ctx.h"
#include "../UDM_Position_Sort_T.h"
#include "Utils.h"
#include "XercesString.h"
#include "boost/bind.hpp"
#include "xercesc/util/PlatformUtils.hpp"

//
// XSD_File_Generator
//
XSD_File_Generator::XSD_File_Generator (const std::string & outdir)
: outdir_ (outdir),
  dispatcher_ (*this),
  impl_ (0),
  doc_ (0),
  serializer_ (0),
  target_ (0)
{
  // Initialize the Accept dispatcher for abstract base types.
  this->dispatcher_.insert <PICML::String> ();
  this->dispatcher_.insert <PICML::LongInteger> ();
  this->dispatcher_.insert <PICML::ShortInteger> ();
  this->dispatcher_.insert <PICML::Boolean> ();
  this->dispatcher_.insert <PICML::Byte> ();
  this->dispatcher_.insert <PICML::RealNumber> ();
  this->dispatcher_.insert <PICML::Aggregate> ();

  // Initialize Xerces-C
  using namespace xercesc;
  XMLPlatformUtils::Initialize();

  this->impl_ =
    DOMImplementationRegistry::getDOMImplementation (Utils::XStr ("LS"));

  this->serializer_ =
    ((DOMImplementationLS *)impl_)->createDOMWriter ();

  // Initialize all the features for the writer.
  if (this->serializer_->canSetFeature (XMLUni::fgDOMWRTDiscardDefaultContent, true))
    this->serializer_->setFeature (XMLUni::fgDOMWRTDiscardDefaultContent, true);

  if (this->serializer_->canSetFeature (XMLUni::fgDOMWRTFormatPrettyPrint, true))
    this->serializer_->setFeature (XMLUni::fgDOMWRTFormatPrettyPrint, true);

  if (this->serializer_->canSetFeature (XMLUni::fgDOMWRTBOM, false))
    this->serializer_->setFeature (XMLUni::fgDOMWRTBOM, false);

  if (this->serializer_->canSetFeature (XMLUni::fgDOMWRTWhitespaceInElementContent, false))
    this->serializer_->setFeature (XMLUni::fgDOMWRTWhitespaceInElementContent, false);
}

//
// ~XSD_File_Generator
//
XSD_File_Generator::~XSD_File_Generator (void)
{
  xercesc::XMLPlatformUtils::Terminate();

  if (this->outfile_.is_open ())
    this->outfile_.close ();
}

//
// Visit_Event
//
void XSD_File_Generator::Visit_Event (const PICML::Event & event)
{
  // Create the XML document.
  if (this->doc_ != 0)
    this->doc_->release();

  this->doc_ =
    this->impl_->createDocument (
      Utils::XStr ("http://www.w3.org/2001/XMLSchema"),
      Utils::XStr ("xsd:schema"),
      0);

  this->doc_->setEncoding (Utils::XStr("UTF-8"));
  this->doc_->setVersion (Utils::XStr("1.0"));

  xercesc::DOMElement * root = this->doc_->getDocumentElement ();
  this->root_.push (root);

  root->setAttributeNS (Utils::XStr ("http://www.w3.org/2000/xmlns/"),
                        Utils::XStr ("xmlns:xsd"),
                        Utils::XStr ("http://www.w3.org/2001/XMLSchema"));

  root->setAttribute (Utils::XStr ("elementFormDefault"),
                      Utils::XStr ("unqualified"));

  // Set the version number for the schema based on the event's
  // version number.
  std::string version = event.VersionTag ();

  if (version.empty ())
  {
    version = "1.0";
    event.VersionTag () = version;
  }

  root->setAttribute (Utils::XStr ("version"),
                      Utils::XStr (version));

  // Push the root element onto the stack then finish visiting
  // the event element.
  xercesc::DOMElement * element =
    this->doc_->createElement (Utils::XStr ("xsd:element"));

  // Set the name of the element.
  std::string name = event.SpecifyIdTag ();
  element->setAttribute (Utils::XStr ("name"),
                         Utils::XStr (name));
  root->appendChild (element);

  // Write the rest of the event as an anonymous type.
  this->root_.push (element);
  this->Visit_Event_i (event, true);
  this->root_.pop ();

  while (!this->complex_types_.empty ())
  {
    // Visit all the complex types that we located, but have not
    // generate code for.
    PICML::Aggregate aggr = this->complex_types_.top ();
    this->complex_types_.pop ();

    this->Visit_Aggregate_i (aggr);
  }

  // Gather required information about the event.
  std::string xmltag = event.SpecifyIdTag ();
  std::string fq_name = CUTS_BE_Capi::fq_name (event, '.');
  std::string classname = fq_name + '.' + CUTS_BE_Capi::classname (xmltag);

  // Construct the path for the filename. We need to make sure
  // this directory exist before trying to open the mapping file.
  std::ostringstream path;
  path
    << this->outdir_ << "\\"
    << CUTS_BE_Capi::fq_name (event, '\\');

  Utils::CreatePath (path.str (), '\\');
  std::string filename = path.str () + "\\" + fq_name + ".xsd";

  this->serialize_xsd_to_file (filename);
}

//
// Visit_Member
//
void XSD_File_Generator::Visit_Member (const PICML::Member & member)
{
  PICML::MemberType mt = member.ref ();

  if (mt != Udm::null)
  {
    xercesc::DOMElement * parent = this->root_.top ();

    // Create a xsd:complexType element for the event.
    xercesc::DOMElement * element =
      this->doc_->createElement (Utils::XStr ("xsd:element"));
    parent->appendChild (element);

    // Set the name of the element.
    element->setAttribute (Utils::XStr ("name"),
                           Utils::XStr (std::string (member.name ())));

    // Dispatch the member to get its type.
    this->root_.push (element);
    this->dispatcher_.dispatch (mt);
    this->root_.pop ();
  }
}

//
// Visit_String
//
void XSD_File_Generator::Visit_String (const PICML::String & )
{
  // Set the type for the element.
  xercesc::DOMElement * element = this->root_.top ();
  element->setAttribute (Utils::XStr ("type"),
                         Utils::XStr ("xsd:string"));

}

//
// Visit_LongInteger
//
void XSD_File_Generator::Visit_LongInteger (const PICML::LongInteger & )
{
  // Set the type for the element.
  xercesc::DOMElement * element = this->root_.top ();
  element->setAttribute (Utils::XStr ("type"),
                         Utils::XStr ("xsd:long"));
}

//
// Visit_Byte
//
void XSD_File_Generator::Visit_Byte (const PICML::Byte &)
{
  // Set the type for the element.
  xercesc::DOMElement * element = this->root_.top ();
  element->setAttribute (Utils::XStr ("type"),
                         Utils::XStr ("xsd:byte"));
}

//
// Visit_ShortInteger
//
void XSD_File_Generator::Visit_ShortInteger (const PICML::ShortInteger &)
{
  // Set the type for the element.
  xercesc::DOMElement * element = this->root_.top ();
  element->setAttribute (Utils::XStr ("type"),
                         Utils::XStr ("xsd:short"));
}

//
// Visit_Aggregate
//
void XSD_File_Generator::Visit_Aggregate (const PICML::Aggregate & aggr)
{
  std::string name = aggr.name ();

  // First, set the type for the current element.
  xercesc::DOMElement * element = this->root_.top ();
  element->setAttribute (Utils::XStr ("type"),
                         Utils::XStr (name));

  if (this->seen_complex_types_.find (aggr) ==
      this->seen_complex_types_.end ())
  {
    // Save the aggregate for later.
    this->seen_complex_types_.insert (aggr);
    this->complex_types_.push (aggr);
  }
}

//
// Visit_Aggregate_i
//
void XSD_File_Generator::Visit_Aggregate_i (const PICML::Aggregate & aggr)
{
  // Note that we have seen this aggregate type.
  this->seen_complex_types_.insert (aggr);

  // Get the current root element of the document.
  xercesc::DOMElement * root = this->root_.top ();

  // Create a xsd:complexType element for the aggregate.
  xercesc::DOMElement * complexType =
    this->doc_->createElement (Utils::XStr ("xsd:complexType"));
  root->appendChild (complexType);

  // Set the name of the aggregate type.
  std::string name = aggr.name ();
  complexType->setAttribute (Utils::XStr ("name"),
                             Utils::XStr (name));

  // Create the xsd:sequence element for the event's members.
  xercesc::DOMElement * sequence =
    this->doc_->createElement (Utils::XStr ("xsd:sequence"));
  complexType->appendChild (sequence);

  // Make the sequence the top most element in the stack.
  this->root_.push (sequence);

  // Visit all the members in this event. We sort the members from top
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
  this->root_.pop ();
}

//
// serialize_xsd_to_file
//
void XSD_File_Generator::
serialize_xsd_to_file (const std::string & filename)
{
  if (this->target_)
    delete this->target_;

  this->target_ =
    new xercesc::LocalFileFormatTarget (filename.c_str ());

  if (this->target_ != 0)
  {
    // Dump the XML document to the target file.
    this->serializer_->writeNode (this->target_, *this->doc_);

    // Close the target file.
    delete this->target_;
    this->target_ = 0;
  }

  // Release the XML document.
  if (this->doc_ != 0)
  {
    this->doc_->release ();
    this->doc_ = 0;
  }
}

//
// Visit_Event_i
//
void XSD_File_Generator::
Visit_Event_i (const PICML::Event & event, bool anonymous)
{
  xercesc::DOMElement * root = this->root_.top ();

  // Create a xsd:complexType element for the event.
  xercesc::DOMElement * complexType =
    this->doc_->createElement (Utils::XStr ("xsd:complexType"));
  root->appendChild (complexType);

  if (!anonymous)
  {
    // Set the name of the complexType.
    std::string name = event.SpecifyIdTag ();

    complexType->setAttribute (Utils::XStr ("name"),
                               Utils::XStr (name));
  }

  // Create the xsd:sequence element for the event's members.
  xercesc::DOMElement * sequence =
    this->doc_->createElement (Utils::XStr ("xsd:sequence"));
  complexType->appendChild (sequence);

  // Make the sequence the top most element in the stack.
  this->root_.push (sequence);

  // Visit all the members in this event. We sort the members from
  // top to bottom on the page, just like a file.
  typedef
    UDM_Position_Sort_T <PICML::Member, PS_Top_To_Bottom>
    _sort_function;

  typedef std::set <PICML::Member, _sort_function> Member_Set;

  Member_Set members =
    event.Member_kind_children_sorted (_sort_function ());

  std::for_each (members.begin (),
                 members.end (),
                 boost::bind (&Member_Set::value_type::Accept,
                              _1,
                              boost::ref (*this)));

  this->root_.pop ();
}
