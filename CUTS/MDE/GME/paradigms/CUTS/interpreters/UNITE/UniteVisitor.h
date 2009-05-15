// -*- C++ -*-
//=============================================================================

/**
 *
 * $Id$
 *
 * @file      UniteVisitor.h
 *
 * @brief     This class implements the Visitor for CUTS.UNITE interpreter.
 *
 * @author    Pooja Varshneya
 */

//=============================================================================

#ifndef _CUTS_UNITEVISITOR_H_
#define _CUTS_UNITEVISITOR_H_

#include "paradigm/CUTS.h"
#include "paradigm/CUTS_export.h"

#include <xercesc/framework/localfileformattarget.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/util/XMLString.hpp>

#include "Utils/XercesString.h"
#include "Utils/Utils.h"

#include <string>

namespace CUTS {

  //===========================================================================
  /**
   * @class UniteVisitor
   *
   * Backend generator of UNITE configuration files from CUTS_DSML models.
   */
  //===========================================================================

  class UniteVisitor : public Visitor
  {
  public:

    /**
     * Constructor
     *
     * @param[in]     outputPath    Ouput path for the UNITE files.
     */
    UniteVisitor (std::string & outputPath);

    /// Destructor
    ~UniteVisitor ();
    
    /// Visit RootFolder element.
    virtual void Visit_RootFolder( const RootFolder&);
   
    /// Visit UniteTests folder.
    virtual void Visit_UnitTests (const UnitTests&);

    /// Visit UniteTest element.
	  virtual void Visit_UnitTest (const UnitTest&);

    /// Visit LogFormat element.
    virtual void Visit_LogFormat (const LogFormat&);

    /// Visit Causality connections.
	  virtual void Visit_Causality (const Causality&);

    /// Visit Key element.
	  virtual void Visit_Key (const Key&);  

  private:

    /// initializes xerces
    void initialize (std::string outputPath);

    /// writes the xerces DOM tree to physical file
    void writeDocument ();

    /// adds a new element to the xerces source tree
    void addElement (std::string element_name,
                     std::string element_val);

    /// adds a new element to the xerces source tree
    void addElement (std::string element_name);

    /// adds a new element to the xerces source tree
    void addElement (xercesc::DOMElement * element);

    /// creates a new DOM element 
    xercesc::DOMElement * createElement (std::string element_name);

    /// creates a new DOM element 
    xercesc::DOMElement * createElement (std::string element_name,
                                         std::string element_val);

    /// adds subelement to a given DOM element
    void addSubElement (xercesc::DOMElement * parent_element,
                        xercesc::DOMElement * child_element);

    /// adds an attribute value to a given DOM element
    void addElementAttribute (xercesc::DOMElement* element_name,
                              std::string attr_name,
                              std::string attr_val);


    /// stores xerces DOMImplementation handle
    xercesc::DOMImplementation* dom_impl_;

    /// stores DOM document
    xercesc::DOMDocument* doc_;

    /// stores xerces serializer
    xercesc::DOMLSSerializer* serializer_;

    /// stores xerces output file handle
    xercesc::XMLFormatTarget* target_;

    /// stores <cuts:unite> DOM element
    xercesc::DOMElement* cur_node_;

    /// stores <logformats> DOM element
    xercesc::DOMElement* logformats_node_;

    /// stores the output file path
    std::string outputPath_;
  };
}

#endif // _CUTS_UNITEVISITOR_H_