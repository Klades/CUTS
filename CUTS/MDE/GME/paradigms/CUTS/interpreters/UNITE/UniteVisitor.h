#ifndef UNITEXMLGENERATOR_CUTS_H
#define UNITEXMLGENERATOR_CUTS_H

#include "paradigm/CUTS.h"
#include "paradigm/CUTS_export.h"

#include <xercesc/framework/localfileformattarget.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>

#include "Utils/XercesString.h"
#include "Utils/Utils.h"

namespace CUTS {

  class CUTS_DSML_Export UniteVisitor : public Visitor
  {
  public:

       UniteVisitor (std::string & outputPath);
    
      ~UniteVisitor ();

		   virtual void Visit_Connection (const Connection &);

		   virtual void Visit_Unite (const Unite &);

		   virtual void Visit_LogFormat (const LogFormat &);

		   virtual void Visit_LogFormats(const LogFormats &);

		   virtual void Visit_RootFolder (const RootFolder &);

		   virtual void Visit_Object (const Udm::Object &);

  private:

      void initialize(const std::string & outputPath);
      void writeDocument();

      xercesc::DOMImplementation* dom_impl_;
      xercesc::DOMDocument* doc_;
      xercesc::DOMLSSerializer* serializer_;
      xercesc::XMLFormatTarget* target_;
      xercesc::DOMElement* cur_node_;
      xercesc::DOMElement* logformats_node_;

      std::string outputPath_; 
  };
}
#endif // UNITEXMLGENERATOR_CUTS_H