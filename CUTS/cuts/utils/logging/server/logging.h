#ifndef LOGGING_H
#define LOGGING_H

// Forward declarations.
//
namespace CUTS
{
  class loggingClients;
}

#include <memory>
#include <list>
#include "XMLSchema/Types.hpp"

namespace CUTS
{
  class loggingClients : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // client
    // 
    public:
    typedef ::std::list< ::XMLSchema::string< char > >::iterator client_iterator;
    typedef ::std::list< ::XMLSchema::string< char > >::const_iterator client_const_iterator;
    client_iterator begin_client ();
    client_iterator end_client ();
    client_const_iterator begin_client () const;
    client_const_iterator end_client () const;
    void add_client (::XMLSchema::string< char > const& );
    size_t count_client (void) const;

    protected:
    ::std::list< ::XMLSchema::string< char > > client_;

    public:
    loggingClients ();

    loggingClients (::XSCRT::XML::Element< char > const&);
    loggingClients (loggingClients const& s);

    loggingClients&
    operator= (loggingClients const& s);

    private:
    char regulator__;
  };
}

namespace CUTS
{
  namespace reader
  {
    ::CUTS::loggingClients
    logging (xercesc::DOMDocument const*);
  }
}

#include "logging.inl"

#endif // LOGGING_H
