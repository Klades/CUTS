#ifndef MODELGEN_H
#define MODELGEN_H

// Forward declarations.
//
namespace CUTS
{
  class Generator_Description;
  class Configuration;
  class Generators;
}

#include <memory>
#include <string>
#include <list>
#include "XMLSchema/Types.hpp"
#include "XMLSchema/id_map.hpp"
#include "ace/Refcounted_Auto_Ptr.h"
#include "ace/Null_Mutex.h"
#include "ace/TSS_T.h"
#include "ace/ace_wchar.h"
#include "ace/Singleton.h"

namespace CUTS
{
  class Generator_Description : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < Generator_Description, ACE_Null_Mutex > _ptr;

    // location
    // 
    public:
    ::XMLSchema::string< char > const& location () const;
    void location (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > location_;

    // id
    // 
    public:
    ::XMLSchema::ID< char > const& id () const;
    ::XMLSchema::ID< char >& id ();
    void id (::XMLSchema::ID< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::ID< char > > id_;

    public:
    Generator_Description (::XMLSchema::string< char > const& location__,
                           ::XMLSchema::ID< char > const& id__);

    Generator_Description (::XSCRT::XML::Element< char > const&);
    Generator_Description (Generator_Description const& s);

    Generator_Description&
    operator= (Generator_Description const& s);

    private:
    char regulator__;
  };


  class Configuration : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < Configuration, ACE_Null_Mutex > _ptr;

    // backend
    // 
    public:
    bool backend_p () const;
    ::CUTS::Generators const& backend () const;
    void backend (::CUTS::Generators const& );

    protected:
    ::std::auto_ptr< ::CUTS::Generators > backend_;

    public:
    Configuration ();

    Configuration (::XSCRT::XML::Element< char > const&);
    Configuration (Configuration const& s);

    Configuration&
    operator= (Configuration const& s);

    private:
    char regulator__;
  };


  class Generators : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < Generators, ACE_Null_Mutex > _ptr;

    // generator
    // 
    public:
    typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::Generator_Description, ACE_Null_Mutex > >::iterator generator_iterator;
    typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::Generator_Description, ACE_Null_Mutex > >::const_iterator generator_const_iterator;
    generator_iterator begin_generator ();
    generator_iterator end_generator ();
    generator_const_iterator begin_generator () const;
    generator_const_iterator end_generator () const;
    void add_generator ( ACE_Refcounted_Auto_Ptr < ::CUTS::Generator_Description, ACE_Null_Mutex > const& );
    XSCRT::Type* get_generator_ptr ( std::basic_string<char> idref );
    void set_generator_ptr (std::basic_string<char> idref );
    size_t count_generator (void) const;

    protected:
    ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::Generator_Description, ACE_Null_Mutex > > generator_;

    public:
    Generators ();

    Generators (::XSCRT::XML::Element< char > const&);
    Generators (Generators const& s);

    Generators&
    operator= (Generators const& s);

    private:
    char regulator__;
  };
}

namespace CUTS
{
  namespace reader
  {
    ::CUTS::Configuration
    modelgen (xercesc::DOMDocument const*);
  }
}

#include "modelgen.inl"

#endif // MODELGEN_H
