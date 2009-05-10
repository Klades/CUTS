#include "StdAfx.h"
#include "UniteVisitor.h"

namespace CUTS
{
  UniteVisitor::UniteVisitor (std::string & outputPath)
  : dom_impl_(0), doc_(0), serializer_(0)
  {
    this->initialize (outputPath);
  }

  UniteVisitor::~UniteVisitor ()
  {
  }

  void UniteVisitor::initialize(const std::string & outputPath)
  {
    this->dom_impl_ = xercesc::DOMImplementationRegistry::getDOMImplementation(Utils::XStr("LS"));

    this->serializer_ = ((xercesc::DOMImplementationLS*)dom_impl_)->createLSSerializer();

    // Set features if the serializer supports the feature/mode

    if (this->serializer_->getDomConfig ()->canSetParameter (xercesc::XMLUni::fgDOMWRTDiscardDefaultContent, true))
      this->serializer_->getDomConfig ()->setParameter (xercesc::XMLUni::fgDOMWRTDiscardDefaultContent, true);

    if (this->serializer_->getDomConfig ()->canSetParameter (xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true))
      this->serializer_->getDomConfig ()->setParameter (xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true);

    if (this->serializer_->getDomConfig ()->canSetParameter (xercesc::XMLUni::fgDOMWRTBOM, false))
      this->serializer_->getDomConfig ()->setParameter (xercesc::XMLUni::fgDOMWRTBOM, false);

    this->doc_ = this->dom_impl_->createDocument(Utils::XStr ("http://www.dre.vanderbilt.edu/CUTS"),
                                                 Utils::XStr ("cuts:unite"),
                                                 0);

    this->doc_->setXmlVersion (Utils::XStr ("1.0"));
    //this-->doc_->setEncoding (Utils::XStr ("UTF-8"));

    xercesc::DOMElement * root_node = doc_->getDocumentElement ();

    root_node->setAttribute (Utils::XStr ("xmlns"),
                             Utils::XStr("http://www.dre.vanderbilt.edu/CUTS"));

    root_node->setAttribute (Utils::XStr ("xmlns:cuts"),
                             Utils::XStr("http://www.dre.vanderbilt.edu/CUTS"));

    root_node->setAttribute (Utils::XStr ("xmlns:xsi"),
                             Utils::XStr ("http://www.w3.org/2001/XMLSchema-instance"));

    root_node->setAttribute (Utils::XStr ("xsi:schemaLocation"),
                             Utils::XStr("http://www.dre.vanderbilt.edu/CUTS cuts-unite.xsd"));

    this->target_ = new xercesc::LocalFileFormatTarget (outputPath.c_str());

    this->cur_node_ = root_node;
  }

  void UniteVisitor::Visit_Causality (const Causality &)
  {
  }

  void UniteVisitor::Visit_UNITE (const UnitTest & unite)
  {
    xercesc::DOMElement* name = this->doc_->createElement (Utils::XStr ("name"));
    xercesc::DOMText* name_pValue = this->doc_->createTextNode (Utils::XStr (unite.name().operator std::string()));
    name->appendChild (name_pValue);
    this->cur_node_->appendChild (name);

    xercesc::DOMElement* description = this->doc_->createElement (Utils::XStr ("description"));
    xercesc::DOMText* desc_pValue = this->doc_->createTextNode (Utils::XStr (unite.Description().operator std::string()));
    description->appendChild (desc_pValue);
    this->cur_node_->appendChild (description);

    xercesc::DOMElement* eval = this->doc_->createElement (Utils::XStr ("evaluation"));
    xercesc::DOMText* eval_pValue = this->doc_->createTextNode (Utils::XStr (unite.Evaluation ().operator std::string()));
    eval->appendChild (eval_pValue);
    this->cur_node_->appendChild (eval);

    xercesc::DOMElement* aggr = this->doc_->createElement (Utils::XStr ("aggregation"));
    xercesc::DOMText* aggr_pValue = this->doc_->createTextNode (Utils::XStr (unite.Aggregation ().operator std::string()));
    aggr->appendChild (aggr_pValue);
    this->cur_node_->appendChild (aggr);

    //CUTS::LogFormats logformats = unite.LogFormats_child ();
    //logformats.Accept (*this);

  }

  void UniteVisitor::Visit_LogFormat (const LogFormat & logformat)
  {
    xercesc::DOMElement* log_format = this->doc_->createElement (Utils::XStr ("logformat"));
    log_format->setAttribute (Utils::XStr ("id"), Utils::XStr (logformat.name ().operator std::string()));

    xercesc::DOMElement* log_format_value = this->doc_->createElement (Utils::XStr ("value"));
    xercesc::DOMText* log_format_value_content = this->doc_->createTextNode (Utils::XStr (std::string (logformat.Value ())));
    log_format_value->appendChild (log_format_value_content);

    xercesc::DOMElement* log_format_relations = this->doc_->createElement (Utils::XStr ("relations"));
    xercesc::DOMElement* log_format_relation = this->doc_->createElement (Utils::XStr ("relation"));
    //xercesc::DOMText* log_format_value_content = this->doc_->createTextNode (XStr (logformat.value ()));
    //log_format_value->appendChild (log_format_value_content);

    this->logformats_node_->appendChild (log_format);
  }

  //void UniteVisitor::Visit_LogFormats(const LogFormats & logformats)
  //{
  //  logformats_node_ = this->doc_->createElement (Utils::XStr ("logformats"));

  //  std::set <LogFormat> logformat_set = logformats.LogFormat_kind_children();

  //  for (std::set<LogFormat>::iterator iter = logformat_set.begin();
  //       iter != logformat_set.end();
  //       ++iter)
  //  {
  //    LogFormat logformat = *iter;
  //    logformat.Accept (*this);
  //  }

  //  this->cur_node_->appendChild (logformats_node_);
  //}

  void UniteVisitor::Visit_RootFolder (const RootFolder &rf)
  {
    //std::set<UnitTest> unite_set = rf.UNITE_kind_children();

    //for (std::set<UnitTest>::iterator iter = unite_set.begin();
    //     iter != unite_set.end();
    //     ++iter)
    //{
    //  UnitTest unite_obj = *iter;
    //  unite_obj.Accept (*this);
    //}
    writeDocument ();
  }

  void UniteVisitor::Visit_Object (const Udm::Object &)
  {
  }

  void UniteVisitor::writeDocument()
  {
    xercesc::DOMLSOutput * output = ((xercesc::DOMImplementationLS*)
                                     this->dom_impl_)->createLSOutput ();

    output->setByteStream (this->target_);

    this->serializer_->write (this->doc_, output);

    output->release ();

  }
}