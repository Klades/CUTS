#ifndef CUTSNODE_H
#define CUTSNODE_H

// Forward declarations.
//
namespace CUTS
{
  namespace schemas
  {
    class ProcessOptions;
    class ProcessList;
    class NodeConfig;
    class DependsItem;
    class DependsList;
    class EnvConfig;
    class Variable;
    class VariableList;
    class VariableImport;
    class FileType;
  }
}

#include <memory>
#include <list>
#include "XMLSchema/Types.hpp"

#include "ace/Refcounted_Auto_Ptr.h"
#include "ace/Null_Mutex.h"

namespace CUTS
{
  namespace schemas
  {
    class ProcessOptions : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < ProcessOptions, ACE_Null_Mutex > _ptr;

      // after
      // 
      public:
      bool after_p () const;
      ::CUTS::schemas::DependsList const& after () const;
      void after (::CUTS::schemas::DependsList const& );

      protected:
      ::std::auto_ptr< ::CUTS::schemas::DependsList > after_;

      // executable
      // 
      public:
      ::XMLSchema::string< char > const& executable () const;
      void executable (::XMLSchema::string< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::string< char > > executable_;

      // arguments
      // 
      public:
      bool arguments_p () const;
      ::XMLSchema::string< char > const& arguments () const;
      void arguments (::XMLSchema::string< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::string< char > > arguments_;

      // workingdirectory
      // 
      public:
      bool workingdirectory_p () const;
      ::XMLSchema::string< char > const& workingdirectory () const;
      void workingdirectory (::XMLSchema::string< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::string< char > > workingdirectory_;

      // output
      // 
      public:
      bool output_p () const;
      ::XMLSchema::string< char > const& output () const;
      void output (::XMLSchema::string< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::string< char > > output_;

      // error
      // 
      public:
      bool error_p () const;
      ::XMLSchema::string< char > const& error () const;
      void error (::XMLSchema::string< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::string< char > > error_;

      // id
      // 
      public:
      ::XMLSchema::ID< char > const& id () const;
      ::XMLSchema::ID< char >& id ();
      void id (::XMLSchema::ID< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::ID< char > > id_;

      // delay
      // 
      public:
      bool delay_p () const;
      ::XMLSchema::double_ const& delay () const;
      ::XMLSchema::double_& delay ();
      void delay (::XMLSchema::double_ const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::double_ > delay_;

      // waitforcompletion
      // 
      public:
      bool waitforcompletion_p () const;
      ::XMLSchema::boolean const& waitforcompletion () const;
      ::XMLSchema::boolean& waitforcompletion ();
      void waitforcompletion (::XMLSchema::boolean const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::boolean > waitforcompletion_;

      public:
      ProcessOptions (::XMLSchema::string< char > const& executable__,
                      ::XMLSchema::ID< char > const& id__);

      ProcessOptions (::XSCRT::XML::Element< char > const&);
      ProcessOptions (ProcessOptions const& s);

      ProcessOptions&
      operator= (ProcessOptions const& s);

      private:
      char regulator__;
    };


    class ProcessList : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < ProcessList, ACE_Null_Mutex > _ptr;

      // process
      // 
      public:
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::ProcessOptions, ACE_Null_Mutex > >::iterator process_iterator;
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::ProcessOptions, ACE_Null_Mutex > >::const_iterator process_const_iterator;
      process_iterator begin_process ();
      process_iterator end_process ();
      process_const_iterator begin_process () const;
      process_const_iterator end_process () const;
      void add_process ( ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::ProcessOptions, ACE_Null_Mutex > const& );
      size_t count_process (void) const;

      protected:
      ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::ProcessOptions, ACE_Null_Mutex > > process_;

      public:
      ProcessList ();

      ProcessList (::XSCRT::XML::Element< char > const&);
      ProcessList (ProcessList const& s);

      ProcessList&
      operator= (ProcessList const& s);

      private:
      char regulator__;
    };


    class NodeConfig : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < NodeConfig, ACE_Null_Mutex > _ptr;

      // environment
      // 
      public:
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::EnvConfig, ACE_Null_Mutex > >::iterator environment_iterator;
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::EnvConfig, ACE_Null_Mutex > >::const_iterator environment_const_iterator;
      environment_iterator begin_environment ();
      environment_iterator end_environment ();
      environment_const_iterator begin_environment () const;
      environment_const_iterator end_environment () const;
      void add_environment ( ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::EnvConfig, ACE_Null_Mutex > const& );
      size_t count_environment (void) const;

      protected:
      ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::EnvConfig, ACE_Null_Mutex > > environment_;

      public:
      NodeConfig ();

      NodeConfig (::XSCRT::XML::Element< char > const&);
      NodeConfig (NodeConfig const& s);

      NodeConfig&
      operator= (NodeConfig const& s);

      private:
      char regulator__;
    };


    class DependsItem : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < DependsItem, ACE_Null_Mutex > _ptr;

      // id
      // 
      public:
      ::XMLSchema::IDREF< char > const& id () const;
      ::XMLSchema::IDREF< char >& id ();
      void id (::XMLSchema::IDREF< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::IDREF< char > > id_;

      public:
      DependsItem (::XMLSchema::IDREF< char > const& id__);

      DependsItem (::XSCRT::XML::Element< char > const&);
      DependsItem (DependsItem const& s);

      DependsItem&
      operator= (DependsItem const& s);

      private:
      char regulator__;
    };


    class DependsList : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < DependsList, ACE_Null_Mutex > _ptr;

      // process
      // 
      public:
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::DependsItem, ACE_Null_Mutex > >::iterator process_iterator;
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::DependsItem, ACE_Null_Mutex > >::const_iterator process_const_iterator;
      process_iterator begin_process ();
      process_iterator end_process ();
      process_const_iterator begin_process () const;
      process_const_iterator end_process () const;
      void add_process ( ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::DependsItem, ACE_Null_Mutex > const& );
      size_t count_process (void) const;

      protected:
      ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::DependsItem, ACE_Null_Mutex > > process_;

      public:
      DependsList (::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::DependsItem, ACE_Null_Mutex > > const& process__);

      DependsList (::XSCRT::XML::Element< char > const&);
      DependsList (DependsList const& s);

      DependsList&
      operator= (DependsList const& s);

      private:
      char regulator__;
    };


    class EnvConfig : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < EnvConfig, ACE_Null_Mutex > _ptr;

      // variables
      // 
      public:
      bool variables_p () const;
      ::CUTS::schemas::VariableList const& variables () const;
      void variables (::CUTS::schemas::VariableList const& );

      protected:
      ::std::auto_ptr< ::CUTS::schemas::VariableList > variables_;

      // startup
      // 
      public:
      bool startup_p () const;
      ::CUTS::schemas::ProcessList const& startup () const;
      void startup (::CUTS::schemas::ProcessList const& );

      protected:
      ::std::auto_ptr< ::CUTS::schemas::ProcessList > startup_;

      // shutdown
      // 
      public:
      bool shutdown_p () const;
      ::CUTS::schemas::ProcessList const& shutdown () const;
      void shutdown (::CUTS::schemas::ProcessList const& );

      protected:
      ::std::auto_ptr< ::CUTS::schemas::ProcessList > shutdown_;

      // id
      // 
      public:
      ::XMLSchema::ID< char > const& id () const;
      ::XMLSchema::ID< char >& id ();
      void id (::XMLSchema::ID< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::ID< char > > id_;

      // inherit
      // 
      public:
      bool inherit_p () const;
      ::XMLSchema::boolean const& inherit () const;
      ::XMLSchema::boolean& inherit ();
      void inherit (::XMLSchema::boolean const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::boolean > inherit_;

      // active
      // 
      public:
      bool active_p () const;
      ::XMLSchema::boolean const& active () const;
      ::XMLSchema::boolean& active ();
      void active (::XMLSchema::boolean const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::boolean > active_;

      public:
      EnvConfig (::XMLSchema::ID< char > const& id__);

      EnvConfig (::XSCRT::XML::Element< char > const&);
      EnvConfig (EnvConfig const& s);

      EnvConfig&
      operator= (EnvConfig const& s);

      private:
      char regulator__;
    };


    class Variable : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < Variable, ACE_Null_Mutex > _ptr;

      // name
      // 
      public:
      ::XMLSchema::string< char > const& name () const;
      ::XMLSchema::string< char >& name ();
      void name (::XMLSchema::string< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::string< char > > name_;

      // value
      // 
      public:
      ::XMLSchema::string< char > const& value () const;
      ::XMLSchema::string< char >& value ();
      void value (::XMLSchema::string< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::string< char > > value_;

      public:
      Variable (::XMLSchema::string< char > const& name__,
                ::XMLSchema::string< char > const& value__);

      Variable (::XSCRT::XML::Element< char > const&);
      Variable (Variable const& s);

      Variable&
      operator= (Variable const& s);

      private:
      char regulator__;
    };


    class VariableList : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < VariableList, ACE_Null_Mutex > _ptr;

      // import
      // 
      public:
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::VariableImport, ACE_Null_Mutex > >::iterator import_iterator;
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::VariableImport, ACE_Null_Mutex > >::const_iterator import_const_iterator;
      import_iterator begin_import ();
      import_iterator end_import ();
      import_const_iterator begin_import () const;
      import_const_iterator end_import () const;
      void add_import ( ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::VariableImport, ACE_Null_Mutex > const& );
      size_t count_import (void) const;

      protected:
      ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::VariableImport, ACE_Null_Mutex > > import_;

      // variable
      // 
      public:
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::Variable, ACE_Null_Mutex > >::iterator variable_iterator;
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::Variable, ACE_Null_Mutex > >::const_iterator variable_const_iterator;
      variable_iterator begin_variable ();
      variable_iterator end_variable ();
      variable_const_iterator begin_variable () const;
      variable_const_iterator end_variable () const;
      void add_variable ( ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::Variable, ACE_Null_Mutex > const& );
      size_t count_variable (void) const;

      protected:
      ::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::Variable, ACE_Null_Mutex > > variable_;

      public:
      VariableList ();

      VariableList (::XSCRT::XML::Element< char > const&);
      VariableList (VariableList const& s);

      VariableList&
      operator= (VariableList const& s);

      private:
      char regulator__;
    };


    class VariableImport : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < VariableImport, ACE_Null_Mutex > _ptr;

      // location
      // 
      public:
      ::XMLSchema::anyURI< char > const& location () const;
      ::XMLSchema::anyURI< char >& location ();
      void location (::XMLSchema::anyURI< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::anyURI< char > > location_;

      // type
      // 
      public:
      ::CUTS::schemas::FileType const& type () const;
      ::CUTS::schemas::FileType& type ();
      void type (::CUTS::schemas::FileType const& );

      protected:
      ::std::auto_ptr< ::CUTS::schemas::FileType > type_;

      public:
      VariableImport (::XMLSchema::anyURI< char > const& location__,
                      ::CUTS::schemas::FileType const& type__);

      VariableImport (::XSCRT::XML::Element< char > const&);
      VariableImport (VariableImport const& s);

      VariableImport&
      operator= (VariableImport const& s);

      private:
      char regulator__;
    };


    class FileType : public ::XSCRT::Type
    {
      public:
      FileType (::XSCRT::XML::Element< char > const&);
      FileType (::XSCRT::XML::Attribute< char > const&);

      static FileType const text;
      static FileType const xml;

      enum Value
      {
        text_l, xml_l
      };


      Value
      integral () const;

      friend bool 
      operator== (FileType const& a, FileType const& b);

      friend bool 
      operator!= (FileType const& a, FileType const& b);

      private:
      FileType (Value v);

      Value v_;
    };

    bool operator== (FileType const &a, FileType const &b);

    bool operator!= (FileType const &a, FileType const &b);
  }
}

namespace CUTS
{
  namespace schemas
  {
    namespace reader
    {
      ::CUTS::schemas::NodeConfig
      node (xercesc::DOMDocument const*);
    }
  }
}

#include "cutsnode.inl"

#endif // CUTSNODE_H
