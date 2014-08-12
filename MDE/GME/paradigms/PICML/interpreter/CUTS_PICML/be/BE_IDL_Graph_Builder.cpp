// $Id$

#include "BE_IDL_Graph_Builder.h"
#include "BE_IDL_Graph.h"

#include "boost/bind.hpp"
#include "Uml.h"

#include <algorithm>

//
// CUTS_BE_IDL_Graph_Builder
//
CUTS_BE_IDL_Graph_Builder::
CUTS_BE_IDL_Graph_Builder (CUTS_BE_IDL_Graph & graph)
: graph_ (graph)
{

}

//
// ~CUTS_BE_IDL_Graph_Builder
//
CUTS_BE_IDL_Graph_Builder::~CUTS_BE_IDL_Graph_Builder (void)
{

}

//
// Visit_RootFolder
//
void CUTS_BE_IDL_Graph_Builder::
Visit_RootFolder (const PICML::RootFolder & root)
{
  typedef std::set <PICML::InterfaceDefinitions> IDefs_Set;
  IDefs_Set defs = root.InterfaceDefinitions_kind_children ();

  for (auto def : defs)
    def.Accept (*this);
}

//
// Visit_InterfaceDefinitions
//
void CUTS_BE_IDL_Graph_Builder::
Visit_InterfaceDefinitions (const PICML::InterfaceDefinitions & folder)
{
  typedef std::set <PICML::File> File_Set;
  File_Set files = folder.File_kind_children ();

    for (auto file : files)
      file.Accept (*this);
}

//
// Visit_File
//
void CUTS_BE_IDL_Graph_Builder::
Visit_File (const PICML::File & file)
{
  // Find this node in the graph then visit the <file>.
  if (this->graph_.find (file.name (), this->current_node_) == -1)
    return;

  // We are trying to keep from parsing this file more than once.
  // So, if we are have already visited this file, then we do
  // not need to do it again!! Just a waste of time.
  if (!this->current_node_->flags_[CUTS_BE_IDL_Node::IDL_VISITED])
  {
    // Set the visit flag. See above for reason.
    this->current_node_->flags_[CUTS_BE_IDL_Node::IDL_VISITED] = true;
    this->current_node_->file_ = file;

    std::vector <PICML::FileRef> filerefs = file.FileRef_children ();
    for (auto fileref : filerefs)
      fileref.Accept (*this);

    // Save the active file and visit its contents.
    this->active_file_ = file;
    this->visit_file_and_package_contents (file);

    while (!this->pending_files_.empty ())
    {
      // Get the first file in the collection.
      File_Set::iterator iter = this->pending_files_.begin ();
      PICML::File file = *iter;

      // Remove the file from the collection and visit it.
      this->pending_files_.erase (iter);
      file.Accept (*this);
    }
  }
}

//
// Visit_FileRef
//
void CUTS_BE_IDL_Graph_Builder::
Visit_FileRef (const PICML::FileRef & f)
{
  // Find the node with the name of the parent.
  PICML::File file = f.ref ();

  CUTS_BE_IDL_Node * node = 0;
  this->graph_.find (file.name (), node);

  if (node != 0)
  {
    // Update this new's references.
    node->file_ = file;
    this->current_node_->references_.insert (node);

    // We still need to parse this file.
    this->pending_files_.insert (file);
  }
}

//
// visit_file_and_package_contents
//
void CUTS_BE_IDL_Graph_Builder::
visit_file_and_package_contents (const Udm::Object & obj)
{
  // Visit all the events at this level.
  std::vector <PICML::Event> events =
    Udm::ChildrenAttr <PICML::Event> (obj.__impl (), Udm::NULLCHILDROLE);

    for (auto event : events)
      event.Accept (*this);

  // Visit all the objects at this level.
  std::vector <PICML::Object> objects =
    Udm::ChildrenAttr <PICML::Object> (obj.__impl (), Udm::NULLCHILDROLE);

    for (auto object : objects)
      object.Accept (*this);

  // Visit all the aggregates (i.e., structure) objects.
  std::vector <PICML::Aggregate> aggregates =
    Udm::ChildrenAttr <PICML::Aggregate> (obj.__impl (), Udm::NULLCHILDROLE);

    for (auto aggregate : aggregates)
      aggregate.Accept (*this);

  // Visit all the components at this level.
  std::vector <PICML::Component> components =
    Udm::ChildrenAttr <PICML::Component> (obj.__impl (), Udm::NULLCHILDROLE);

    for (auto component : components)
      component.Accept (*this);

  // Visit all the packages at this level.
  std::set <PICML::Package> packages =
    Udm::ChildrenAttr <PICML::Package> (obj.__impl (), Udm::NULLCHILDROLE);

    for (auto package : packages)
      package.Accept (*this);
}

//
// Visit_Package
//
void CUTS_BE_IDL_Graph_Builder::
Visit_Package (const PICML::Package & package)
{
  this->visit_file_and_package_contents (package);
}

//
// Visit_Component
//
void CUTS_BE_IDL_Graph_Builder::
Visit_Component (const PICML::Component & component)
{
  // Set the flag for this node.
  this->current_node_->has_components_ = true;

  // Determine if the component has output events.
  typedef std::vector <PICML::OutEventPort> OutEventPort_Set;
  OutEventPort_Set oep_set = component.OutEventPort_kind_children ();

    for (auto oep : oep_set)
      oep.Accept (*this);

  // Determine if the component has input events.
  typedef std::vector <PICML::InEventPort> InEventPort_Set;
  InEventPort_Set iep_set = component.InEventPort_kind_children ();

    for (auto iep : iep_set)
      iep.Accept (*this);

  // Determine if the component has any receptacles.
  typedef std::vector <PICML::RequiredRequestPort> Receptacle_Set;
  Receptacle_Set receptacles = component.RequiredRequestPort_kind_children ();

    for (auto receptacle : receptacles)
      receptacle.Accept (*this);

  // Determine if the component has any facets.
  typedef std::vector <PICML::ProvidedRequestPort> Facet_Set;
  Facet_Set facets = component.ProvidedRequestPort_kind_children ();

    for (auto facet : facets)
      facet.Accept (*this);

  // Determine the dependency for supported interfaces.
  typedef std::vector <PICML::Supports> Supports_Set;
  Supports_Set supports = component.Supports_children ();

    for (auto support : supports)
      support.Accept (*this);

  // Determine the dependency for attributes. We get the read-only
  // kind since it will return both read-only and read-write
  // attributes.
  typedef std::vector <PICML::ReadonlyAttribute> Readonly_Set;
  Readonly_Set attrs = component.ReadonlyAttribute_kind_children ();

    for (auto attr : attrs)
      attr.Accept (*this);

  // If this component is a <subtype> of another component, there is a
  // chance that it is located in another file. If this is the case
  // then we have to update its references.
  if (component.isSubtype ())
  {
    PICML::NamedType subtype = PICML::NamedType::Cast (component).Archetype ();
    this->Visit_NamedType (subtype);
  }
}

//
// Visit_OutEventPort
//
void CUTS_BE_IDL_Graph_Builder::
Visit_OutEventPort (const PICML::OutEventPort & port)
{
  PICML::EventType et = port.ref ();

  if (et.type () == PICML::Event::meta)
    PICML::Event::Cast (et).Accept (*this);
}

//
// Visit_InEventPort
//
void CUTS_BE_IDL_Graph_Builder::
Visit_InEventPort (const PICML::InEventPort & port)
{
  PICML::EventType et = port.ref ();

  if (et.type () == PICML::Event::meta)
    PICML::Event::Cast (et).Accept (*this);
}

//
// Visit_RequiredRequestPort
//
void CUTS_BE_IDL_Graph_Builder::
Visit_RequiredRequestPort (const PICML::RequiredRequestPort & port)
{
  PICML::Provideable provides = port.ref ();

  if (provides != Udm::null)
    this->Visit_Providable (provides);
}

//
// Visit_ProvidedRequestPort
//
void CUTS_BE_IDL_Graph_Builder::
Visit_ProvidedRequestPort (const PICML::ProvidedRequestPort & port)
{
  PICML::Provideable provides = port.ref ();

  if (provides != Udm::null)
    this->Visit_Providable (provides);
}

//
// Visit_Provideable
//
void CUTS_BE_IDL_Graph_Builder::
Visit_Providable (const PICML::Provideable & provides)
{
  this->Visit_NamedType (PICML::NamedType::Cast (provides));
}

//
// Visit_Object
//
void CUTS_BE_IDL_Graph_Builder::
Visit_Object (const PICML::Object & object)
{
  this->current_node_->has_interfaces_ = true;
  this->Visit_NamedType (object);
}

//
// Visit_Event
//
void CUTS_BE_IDL_Graph_Builder::
Visit_Event (const PICML::Event & evt)
{
  if (this->NamedType_parent (evt) == this->active_file_)
    this->current_node_->has_events_ = true;

  this->Visit_NamedType (evt);

  std::vector <PICML::Member> members = evt.Member_children ();
  for (auto member : members)
    member.Accept (*this);
}

//
// Visit_Aggregate
//
void CUTS_BE_IDL_Graph_Builder::
Visit_Aggregate (const PICML::Aggregate & a)
{
  // Visit the members in this aggregate.
  std::vector <PICML::Member> members = a.Member_children ();
  for (auto member : members)
    member.Accept (*this);

  PICML::Key key = a.Key_child ();

  if (this->NamedType_parent (a) == this->active_file_ && key != Udm::null)
    this->current_node_->has_dds_events_ = true;
}

//
// Visit_NamedType
//
void CUTS_BE_IDL_Graph_Builder::
Visit_NamedType (const PICML::NamedType & type)
{
  // Get the parent of the named type.
  PICML::File parent = this->NamedType_parent (type);

  // Determine the location of this named type. If this event is not
  // in the current file then, when we need to add it to the list of
  // depends.
  CUTS_BE_IDL_Node * node = 0;

  if (this->active_file_ != parent)
  {
    // Find the node with the name of the parent.
    this->graph_.find (parent.name (), node);

    if (node != 0)
      this->current_node_->references_.insert (node);

    // Ok, now we have to parse the <parent> before quiting.
    this->pending_files_.insert (parent);
  }
}

//
// Visit_Supports
//
void CUTS_BE_IDL_Graph_Builder::
Visit_Supports (const PICML::Supports & supports)
{
  PICML::Object object = PICML::Object::Cast (supports.ref ());

  if (object != Udm::null)
    object.Accept (*this);
}

//
// Visit_ReadonlyAttribute
//
void CUTS_BE_IDL_Graph_Builder::
Visit_ReadonlyAttribute (const PICML::ReadonlyAttribute & readonly)
{
  PICML::AttributeMember member = readonly.AttributeMember_child ();

  if (member != Udm::null)
  {
    // The model is valid since we have a child!!!!
    PICML::MemberType type = member.ref ();

    try
    {
      // Try and extact the named type so we can update our
      // dependencies.
      PICML::NamedType named_type = PICML::NamedType::Cast (type);
      this->Visit_NamedType (named_type);
    }
    catch (udm_exception)
    {
      /* bad cast: not a NamedType */
    }
  }
}

//
// NamedType_parent
//
PICML::File CUTS_BE_IDL_Graph_Builder::
NamedType_parent (const PICML::NamedType & type)
{
  PICML::MgaObject parent = type.parent ();

  while (parent.type () != PICML::File::meta)
    parent = PICML::MgaObject::Cast (parent.parent ());

  return PICML::File::Cast (parent);
}

//
// Visit_Member
//
void CUTS_BE_IDL_Graph_Builder::Visit_Member (const PICML::Member & m)
{
  PICML::MemberType mt = m.ref ();

  if (Udm::IsDerivedFrom (mt.type (), PICML::NamedType::meta))
    this->Visit_NamedType (PICML::NamedType::Cast (mt));
}
