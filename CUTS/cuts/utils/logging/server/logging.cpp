#include "logging.h"

namespace CUTS
{
  // loggingClients
  //

  loggingClients::
  loggingClients (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == "client")
      {
        ::XMLSchema::string< char > t (e);
        add_client (t);
      }

      else 
      {
      }
    }
  }
}

namespace CUTS
{
  namespace reader
  {
    ::CUTS::loggingClients
    logging (xercesc::DOMDocument const* d)
    {
      ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
      if (e.name () == "logging")
      {
        ::CUTS::loggingClients r (e);
        return r;
      }

      else
      {
        throw 1;
      }
    }
  }
}

