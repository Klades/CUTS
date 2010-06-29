// $Id$

#include "StdAfx.h"
#include "UniteVisitor.h"

///////////////////////////////////////////////////////////////////////////////
// class UniteVisitor
///////////////////////////////////////////////////////////////////////////////

namespace CUTS
{
  //
  // UniteVisitor
  //
  UniteVisitor::UniteVisitor (std::string & outputPath)
  : dom_impl_(0), 
    doc_(0), 
    serializer_(0),
    target_(0),
    cur_node_(0), 
    logformats_node_(0), 
    outputPath_(outputPath)
  {
  }

  //
  // ~UniteVisitor
  //
  UniteVisitor::~UniteVisitor ()
  {
  }
	
	//
  // Visit_RootFolder
  //
  void UniteVisitor::Visit_RootFolder(const RootFolder &rf)
  {
		// Iterate over all Datagraphs folders
	  std::set<DataGraphs> datagraphs_set = rf.DataGraphs_kind_children ();
		
    for (std::set<DataGraphs>::iterator iter = datagraphs_set.begin ();
         iter != datagraphs_set.end ();
         ++iter)
    {
      DataGraphs datagraphs = *iter;
      datagraphs.Accept (*this);
    }
		
    // Iterate over all UnitTests folders
	  std::set<UnitTests> unittests_set = rf.UnitTests_kind_children ();
		
    for (std::set<UnitTests>::iterator iter = unittests_set.begin ();
         iter != unittests_set.end ();
         ++iter)
		{	
		  UnitTests unittests = *iter;
			unittests.Accept (*this);
		}
  }

	//
  // Visit_Datagraphs
  //
	void UniteVisitor::Visit_DataGraphs(const DataGraphs &datagraphs)
	{
		// Iterate over all DataGraph components
    std::set<DataGraph> datagraph_set = datagraphs.DataGraph_kind_children ();
		
	  for (std::set<DataGraph>::iterator iter = datagraph_set.begin ();
         iter != datagraph_set.end ();
         ++iter)
    {
      DataGraph datagraph = *iter;
      datagraph.Accept (*this);
    }
	}
	
	//
	// Visit_UnitTests
	//
	void UniteVisitor::Visit_UnitTests(const UnitTests &unittests)
	{
		// Iterate over all UnitTest components
		std::set<UnitTest> unittest_set = unittests.UnitTest_kind_children ();

		for (std::set<UnitTest>::iterator iter = unittest_set.begin ();
				 iter != unittest_set.end ();
				 ++iter)
		{
			UnitTest unittest = *iter;
			unittest.Accept (*this);
		}
	}

	
	//
  // Visit_Datagraph
  //
	void UniteVisitor::Visit_DataGraph(const DataGraph &datagraph)
	{
		// Create the output file path
		std::string filePath = outputPath_;
		filePath += "\\" + std::string(datagraph.name ()) + ".datagraph";
		
		// Initialize xerces
		this->initialize (filePath, "cuts:datagraph");
		
		// Add elements to the DOM tree
		this->addElement ("name", datagraph.name ());
		
		// Store the <logformats> element for adding <logformat> elements
		this->logformats_node_ = this->createElement ("logformats");    
		this->addElement (this->logformats_node_);
		
		// Iterate over all logformat components
		std::set <LogFormat> logformat_set = datagraph.LogFormat_kind_children();
		
		for (std::set<LogFormat>::iterator iter = logformat_set.begin();
				 iter != logformat_set.end();
				 ++iter)
		{
			LogFormat logformat = *iter;
			logformat.Accept (*this);
		}
		
		// Iterate over all causality connections
		std::set <Causality> causality_set = datagraph.Causality_kind_children ();
		
		for (std::set<Causality>::iterator iter = causality_set.begin();
				 iter != causality_set.end();
				 ++iter)
		{
			Causality causality = *iter;
			causality.Accept (*this);
		}
		
		// Write the xml document to physical file
		this->writeDocument ();
	}
	
	//
	// Visit_UnitTest
	//
	void UniteVisitor::Visit_UnitTest(const UnitTest & unittest)
	{
		// Create the output file path
		std::string filePath = outputPath_;
		filePath += "\\" + std::string(unittest.name ()) + ".unite";
		
		// Initialize xerces
		this->initialize (filePath, "cuts:test");
		
		// Add elements to the DOM tree
		this->addElement ("name", unittest.name ());
		this->addElement ("description", unittest.Description ());
		this->addElement ("evaluation", unittest.Evaluation ());
		this->addElement ("aggregation", unittest.Aggregation ());
		
		// Store the <services> element for adding <service> elements
		this->services_node_ = this->createElement ("services");    
		this->addElement (this->services_node_);
		
		// Iterate over all group components
		std::set <Group> group_set = unittest.Group_kind_children();
		
		for (std::set<Group>::iterator iter = group_set.begin();
				 iter != group_set.end();
				 ++iter)
		{
			Group group = *iter;
			group.Accept (*this);
		}
		
		// Iterate over all service components
		std::set <Service> service_set = unittest.Service_kind_children();
		
		for (std::set<Service>::iterator iter = service_set.begin();
				 iter != service_set.end();
				 ++iter)
		{
			Service service = *iter;
			service.Accept (*this);
		}		
		
		// Write the xml document to physical file
		this->writeDocument ();
	}
	
  //
  // Visit_LogFormat
  //
  void UniteVisitor::Visit_LogFormat (const LogFormat & logformat)
  {
    // Add <logformat> element under <logformats>
    xercesc::DOMElement * logformat_element = this->createElement ("logformat");
    this->addElementAttribute (logformat_element, "id", logformat.name ());
    this->addSubElement (this->logformats_node_, logformat_element);

    // Add <value> element under <logformat>
    xercesc::DOMElement * value_element = this->createElement ("value", logformat.Value ());
    this->addSubElement (logformat_element, value_element);

    // Add <relations> element under <logformat>
    xercesc::DOMElement* relations_element = this->createElement ("relations");
	  this->addSubElement (logformat_element, relations_element);   
  }

  //
  // Visit_Causality
  //
  void UniteVisitor::Visit_Causality(const Causality &causality_connect)
  {
    xercesc::DOMElement * target_log_node = 0;
    xercesc::DOMElement * target_relation_node = 0;

    // Store the source and destination keys for given connection
    Key key_src = causality_connect.srcCausality_end ();
    Key key_dest = causality_connect.dstCausality_end ();
    
     // Store the source and destination logformats for given connection
    LogFormat key_src_parent = key_src.LogFormat_parent();
    LogFormat key_dest_parent = key_dest.LogFormat_parent();

     // Store the source and destination logformats names for given connection
    Utils::XStr src_log_id_xstr(std::string(key_src_parent.name()));
    Utils::XStr dest_log_id_xstr(std::string(key_dest_parent.name()));

    // Get the list of all <logformat> nodes from the DOM tree document
    xercesc::DOMNodeList* target_log_list 
      = doc_->getElementsByTagName (Utils::XStr("logformat"));

    // Find the <logformat> element representing src for given connection
    for (size_t i = 0 ; i < target_log_list->getLength (); i++)
    {    
      xercesc::DOMElement* logformat_element = (xercesc::DOMElement*)target_log_list->item(i);

      // Get the <logformat id> attribute
      Utils::XStr target_log_id_xstr = logformat_element->getAttribute(Utils::XStr("id"));
      
      // If the <logformat id> matches the source logformat name, 
      // then stop searching further.
      if (src_log_id_xstr == target_log_id_xstr)
      {
        target_log_node = logformat_element;
        break;
      }
    }
    
    // Get the list of relation nodes from the source logformat node
    xercesc::DOMNodeList* relation_node_list 
      = target_log_node->getElementsByTagName(Utils::XStr("relation"));

    // Find the <relation> element representing destination for given connection
    for (size_t i = 0; i < relation_node_list->getLength (); i++)
    {
      xercesc::DOMElement* relation_element 
        = (xercesc::DOMElement*)relation_node_list->item(i);

      // Get the <relation effectref> attribute
      Utils::XStr target_effectref_xstr 
        = relation_element->getAttribute(Utils::XStr("effectref"));
      
      // If the <relation effectref> matches the destination logformat name, 
      // then stop searching further.
      if (target_effectref_xstr == dest_log_id_xstr)
      {
        target_relation_node = relation_element;
        break;
      }
    }

    // If <relation> element for destination logformat does not exists,
    // then create it
    if (!target_relation_node)
    {
      // Find the <relations> element under given logformat
      xercesc::DOMNodeList* target_relations_nodelist 
        = target_log_node->getElementsByTagName (Utils::XStr ("relations"));
      
      xercesc::DOMElement* target_relations_node 
        = (xercesc::DOMElement*) target_relations_nodelist->item (0);

      // Create new <relation> element
      target_relation_node = this->createElement ("relation");

      // Add effectref attribute to <relation>
      this->addElementAttribute (target_relation_node, 
                                 "effectref", 
                                 key_dest_parent.name ());

      // Add <relation> element under <relations> element
      this->addSubElement (target_relations_node, 
                           target_relation_node);
    }

    // Find value of cause attribute for <causality> element
    std::string cause_str = std::string(key_src_parent.name()) 
                            + "." 
                            + std::string(key_src.name());

    // Find value of effect attribute for <causality> element
    std::string effect_str = std::string(key_dest_parent.name())
                             + "."
                             + std::string(key_dest.name());

    // Create <causality> element
    xercesc::DOMElement* causality = this->createElement ("causality");

    // Add cause attribute to causality element
    this->addElementAttribute (causality, "cause", cause_str);

    // Add effect attribute to causality element
    this->addElementAttribute (causality, "effect", effect_str);

    // Add <causality> element under <relation>
    this->addSubElement (target_relation_node, causality);
  }

  //
  // Visit_Key
  //
  void UniteVisitor::Visit_Key (const Key &key)
  {
  }
	
	//
  // Visit_GroupItem
  //
	void UniteVisitor::Visit_GroupItem(const GroupItem &groupitem)
	{
	
    std::string groupitem_name;
    
    // Add <groupitem> element under <grouping>
    Log_Element groupitem_ref = groupitem.ref ();

    // Get the derived object from Log_Element
    if (Udm::IsDerivedFrom (groupitem_ref.type (), Key::meta) == true)
    {
      Key groupitem_key = Key::Cast (groupitem_ref);

      LogFormat key_parent = groupitem_key.LogFormat_parent ();

      groupitem_name =  std::string (key_parent.name ())
                         + "." 
                         + std::string (groupitem_key.name ());
    }
    else if (Udm::IsDerivedFrom (groupitem_ref.type (), Variable::meta)== true)
    {
      Variable groupitem_var = Variable::Cast (groupitem_ref);

      LogFormat var_parent = groupitem_var.LogFormat_parent ();

      groupitem_name =  std::string (var_parent.name ())
                        + "." 
                        + std::string (groupitem_var.name ());
    }

    xercesc::DOMElement * groupitem_element = 
      this->createElement ("groupitem", groupitem_name);
		
		this->addSubElement (this->grouping_node_, groupitem_element);			   
	}
	
	//
  // Visit_Service
  //
	void UniteVisitor::Visit_Service(const Service &service)
	{
	  // Add <service> element under <services>
    xercesc::DOMElement * service_element = this->createElement ("service");
    this->addElementAttribute (service_element, "id", service.name ());
	
		xercesc::DOMElement *location_element = 
      this->createElement ("location", service.Location ());
		this->addSubElement (service_element, location_element);
		
		xercesc::DOMElement *classname_element = 
      this->createElement ("classname", service.ClassName ());
		this->addSubElement (service_element, classname_element);
		
		xercesc::DOMElement *params_element = 
      this->createElement ("params", service.Params ());

		this->addSubElement (service_element, params_element);
   
		this->addSubElement (this->services_node_, service_element);
	}
	
	//
  // Visit_Group
  //
	void UniteVisitor::Visit_Group(const Group &group)
	{
		// Store the <grouping> element for adding <groupitem> elements
		this->grouping_node_ = this->createElement ("grouping");    
		this->addElement (this->grouping_node_);	
		
		// Iterate over all groupitem components
		std::set <GroupItem> groupitem_set = group.GroupItem_kind_children();
		
		for (std::set<GroupItem>::iterator iter = groupitem_set.begin();
				 iter != groupitem_set.end();
				 ++iter)
		{
			GroupItem groupitem = *iter;
			groupitem.Accept (*this);
		}		
	}
	
	//
  // Visit_Variable
  //
	void UniteVisitor::Visit_Variable(const Variable&)
	{
	
	}

  //
  // initialize
  //
  void UniteVisitor::initialize (std::string filePath, std::string doc_name)
  {
    // Initialize xerces

    xercesc::XMLPlatformUtils::Initialize( );
   
	  this->dom_impl_ = xercesc::DOMImplementationRegistry::getDOMImplementation (Utils::XStr("LS"));

    this->serializer_ = ((xercesc::DOMImplementationLS*)dom_impl_)->createLSSerializer ();

    // Set features if the serializer supports the feature/mode

    if (this->serializer_->getDomConfig ()->canSetParameter (xercesc::XMLUni::fgDOMWRTDiscardDefaultContent, 
                                                             true))
      this->serializer_->getDomConfig ()->setParameter (xercesc::XMLUni::fgDOMWRTDiscardDefaultContent,
                                                        true);

    if (this->serializer_->getDomConfig ()->canSetParameter (xercesc::XMLUni::fgDOMWRTFormatPrettyPrint,
                                                             true))
      this->serializer_->getDomConfig ()->setParameter (xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, 
                                                        true);

    if (this->serializer_->getDomConfig ()->canSetParameter (xercesc::XMLUni::fgDOMWRTBOM, 
                                                             false))
      this->serializer_->getDomConfig ()->setParameter (xercesc::XMLUni::fgDOMWRTBOM,
                                                        false);

    this->doc_ = this->dom_impl_->createDocument (Utils::XStr ("http://www.dre.vanderbilt.edu/CUTS"),
                                                  Utils::XStr (doc_name),
                                                  0);

    this->doc_->setXmlVersion (Utils::XStr ("1.0"));

    this->target_ = new xercesc::LocalFileFormatTarget (Utils::XStr (filePath));

    xercesc::DOMElement * root_node = doc_->getDocumentElement ();

    root_node->setAttribute (Utils::XStr ("xmlns"),
                             Utils::XStr ("http://www.dre.vanderbilt.edu/CUTS"));

    root_node->setAttribute (Utils::XStr ("xmlns:cuts"),
                             Utils::XStr ("http://www.dre.vanderbilt.edu/CUTS"));

    root_node->setAttribute (Utils::XStr ("xmlns:xsi"),
                             Utils::XStr ("http://www.w3.org/2001/XMLSchema-instance"));

    root_node->setAttribute (Utils::XStr ("xsi:schemaLocation"),
                             Utils::XStr ("http://www.dre.vanderbilt.edu/CUTS cuts-unite.xsd"));

    this->cur_node_ = root_node;
  }

  //
  // writeDocument
  //
  void UniteVisitor::writeDocument ()
  {
    xercesc::DOMLSOutput * output = ((xercesc::DOMImplementationLS*)
                                     this->dom_impl_)->createLSOutput ();

    output->setByteStream (this->target_);

    this->serializer_->write (this->doc_, output);

    output->release ();
    
    xercesc::XMLPlatformUtils::Terminate (); 
  }

  //
  // addElement
  //
  void UniteVisitor::addElement (std::string element_name, 
                                 std::string element_val)
  {
    xercesc::DOMElement* name = this->doc_->createElement (Utils::XStr (element_name));
    xercesc::DOMText* value = this->doc_->createTextNode (Utils::XStr (element_val));
    name->appendChild (value);
    this->cur_node_->appendChild (name);
  }

  //
  // addElement
  //
  void UniteVisitor::addElement (std::string element_name) 
  {
    xercesc::DOMElement* name = this->doc_->createElement (Utils::XStr (element_name));
    this->cur_node_->appendChild (name);
  }

  //
  // addElement
  //
  void UniteVisitor::addElement (xercesc::DOMElement * element) 
  {
    this->cur_node_->appendChild (element);
  }

  //
  // createElement
  //
  xercesc::DOMElement * UniteVisitor::createElement (std::string element_name) 
  {
    return this->doc_->createElement (Utils::XStr (element_name));
  }

  //
  // createElement
  //
  xercesc::DOMElement * UniteVisitor::createElement (std::string element_name,
                                                     std::string element_val) 
  {
    xercesc::DOMElement* element = this->doc_->createElement (Utils::XStr (element_name));
    xercesc::DOMText* value = this->doc_->createTextNode (Utils::XStr (element_val));
    element->appendChild (value);   
    return element;
  }

  //
  // addSubElement
  //
  void UniteVisitor::addSubElement (xercesc::DOMElement * parent_element,
                                    xercesc::DOMElement * child_element)
  {
    parent_element->appendChild (child_element);   
  }


  //
  // addElementAttribute
  //
  void UniteVisitor::addElementAttribute (xercesc::DOMElement * element_name,
                                          std::string attr_name,
                                          std::string attr_val)
  {
    element_name->setAttribute (Utils::XStr (attr_name), Utils::XStr (attr_val));
  }
	
}