// $Id$

#include "stdafx.h"
#include "Property_Locator.h"

#if !defined (__CUTS_INLINE__)
#include "Property_Locator.inl"
#endif

#include "Model_Interpreter_Action.h"
#include "Model_Interpreter_Action_List.h"
#include "Property_Locator_Handler.h"

#include "game/Attribute.h"
#include "game/MetaAttribute.h"
#include "game/Folder.h"
#include "game/Model.h"
#include "boost/bind.hpp"
#include "ace/CORBA_macros.h"

//
// CUTS_CUTE_Property_Locator
//
CUTS_CUTE_Property_Locator::
CUTS_CUTE_Property_Locator (CUTS_CUTE_Property_Locator_Handler & handler)
: handler_ (handler),
  evaluator_ (prop_map_, actor_)
{
  this->evaluator_.config ().open_tag_ = "<%";
  this->evaluator_.config ().close_tag_ = "%>";
}

//
// visit_Folder
//
void CUTS_CUTE_Property_Locator::visit_Folder (GAME::Folder_in folder)
{
  // Test the name of this folder for template parameters.
  // Reset the list for storing the properties.
  if (0 != this->actor_.list ().size ())
    this->actor_.clear ();

  bool retval = this->evaluator_.evaluate (folder->name ().c_str ());

  if (retval && 0 != this->actor_.list ().size ())
    this->handler_.handle_name (folder, this->actor_.list ());

  // Now, visit all the folders in this folder.
  typedef std::vector <GAME::Folder> folder_set;
  folder_set folders;

  folder->children (folders);

  std::for_each (folders.begin (),
                 folders.end (),
                 boost::bind (&GAME::Folder::impl_type::accept,
                              boost::bind (&GAME::Folder::get, _1),
                              this));

  // Then, visit all the FCOs in the folder.
  typedef std::vector <GAME::FCO> fco_set;
  fco_set fcos;

  folder->children (fcos);

  std::for_each (fcos.begin (),
                 fcos.end (),
                 boost::bind (&CUTS_CUTE_Property_Locator::visit_FCO, this, _1));
}

//
// visit_FCO
//
void CUTS_CUTE_Property_Locator::visit_FCO (GAME::FCO_in fco)
{
  // Test the name of this FCO for template parameters.
  // Reset the list for storing the properties.
  if (0 != this->actor_.list ().size ())
    this->actor_.clear ();

  bool result = this->evaluator_.evaluate (fco->name ().c_str ());

  if (result && 0 != this->actor_.list ().size ())
    this->handler_.handle_name (fco, this->actor_.list ());

  // Visit all the attributes in the FCO.
  typedef std::vector <GAME::Attribute> attribute_set;
  attribute_set attributes;

  fco->attributes (attributes);

  std::for_each (attributes.begin (),
                 attributes.end (),
                 boost::bind (&CUTS_CUTE_Property_Locator::visit_Attribute,
                              this,
                              _1));

  // Let's visit this FCO as well.
  fco->accept (this);
}

//
// visit_Model
//
void CUTS_CUTE_Property_Locator::visit_Model (GAME::Model_in model)
{
  std::vector <GAME::FCO> fcos;
  model->children (fcos);

  std::for_each (fcos.begin (),
                 fcos.end (),
                 boost::bind (&CUTS_CUTE_Property_Locator::visit_FCO,
                              this,
                              _1));
}

//
// visit_Attribute
//
void CUTS_CUTE_Property_Locator::visit_Attribute (GAME::Attribute_in attr)
{
  // Determine if attribute string has a template parameter. Right now,
  // we can only handle string value types.
  if (attr->meta ()->type () != ATTVAL_STRING)
    return;

  // Reset the list for storing the properties.
  if (0 != this->actor_.list ().size ())
    this->actor_.clear ();

  bool retval = this->evaluator_.evaluate (attr->string_value ().c_str ());

  if (retval && 0 != this->actor_.list ().size ())
    this->handler_.handle_attribute (attr, this->actor_.list ());
}
