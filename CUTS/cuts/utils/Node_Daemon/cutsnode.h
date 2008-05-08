#ifndef CUTSNODE_H
#define CUTSNODE_H

// Forward declarations.
//
namespace CUTS
{
  class taskDescription;
  class taskList;
  class nodeConfig;
}

#include <memory>
#include <list>
#include "XMLSchema/Types.hpp"

namespace CUTS
{
  class taskDescription : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

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

    // id
    // 
    public:
    ::XMLSchema::ID< char > const& id () const;
    ::XMLSchema::ID< char >& id ();
    void id (::XMLSchema::ID< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::ID< char > > id_;

    public:
    taskDescription (::XMLSchema::string< char > const& executable__,
                     ::XMLSchema::ID< char > const& id__);

    taskDescription (::XSCRT::XML::Element< char > const&);
    taskDescription (taskDescription const& s);

    taskDescription&
    operator= (taskDescription const& s);

    private:
    char regulator__;
  };


  class taskList : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // task
    // 
    public:
    typedef ::std::list< ::CUTS::taskDescription >::iterator task_iterator;
    typedef ::std::list< ::CUTS::taskDescription >::const_iterator task_const_iterator;
    task_iterator begin_task ();
    task_iterator end_task ();
    task_const_iterator begin_task () const;
    task_const_iterator end_task () const;
    void add_task (::CUTS::taskDescription const& );
    size_t count_task (void) const;

    protected:
    ::std::list< ::CUTS::taskDescription > task_;

    public:
    taskList ();

    taskList (::XSCRT::XML::Element< char > const&);
    taskList (taskList const& s);

    taskList&
    operator= (taskList const& s);

    private:
    char regulator__;
  };


  class nodeConfig : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    // tasklist
    // 
    public:
    bool tasklist_p () const;
    ::CUTS::taskList const& tasklist () const;
    void tasklist (::CUTS::taskList const& );

    protected:
    ::std::auto_ptr< ::CUTS::taskList > tasklist_;

    public:
    nodeConfig ();

    nodeConfig (::XSCRT::XML::Element< char > const&);
    nodeConfig (nodeConfig const& s);

    nodeConfig&
    operator= (nodeConfig const& s);

    private:
    char regulator__;
  };
}

namespace CUTS
{
  namespace reader
  {
    ::CUTS::nodeConfig
    node (xercesc::DOMDocument const*);
  }
}

#include "cutsnode.inl"

#endif // CUTSNODE_H
