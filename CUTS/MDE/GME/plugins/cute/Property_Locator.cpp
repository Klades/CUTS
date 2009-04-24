// $Id$

#include "stdafx.h"
#include "Property_Locator.h"

#if !defined (__CUTS_INLINE__)
#include "Property_Locator.inl"
#endif

#include "game/Attribute.h"
#include "game/MetaAttribute.h"
#include "game/Folder.h"
#include "game/Model.h"
#include "boost/bind.hpp"

//
// CUTS_CUTE_Property_Locator
//
CUTS_CUTE_Property_Locator::CUTS_CUTE_Property_Locator (void)
: evaluator_ (prop_map_, actor_),
  total_size_ (0)
{
  this->evaluator_.config ().open_tag_ = "<%";
  this->evaluator_.config ().close_tag_ = "%>";
}

//
// visit_Folder
//
void CUTS_CUTE_Property_Locator::visit_Folder (GME::Folder & folder)
{
  // First, visit all the folders in this folder.
  typedef GME::Collection_T <GME::Folder> folder_set;
  folder_set folders;

  folder.folders (folders);

  std::for_each (folders.begin (),
                 folders.end (),
                 boost::bind (&folder_set::type::accept,
                              _1,
                              boost::ref (*this)));

  // Then, visit all the FCOs in the folder.
  typedef GME::Collection_T <GME::FCO> fco_set;
  fco_set fcos;

  folder.fcos (fcos);

  std::for_each (fcos.begin (),
                 fcos.end (),
                 boost::bind (&fco_set::type::accept,
                              _1,
                              boost::ref (*this)));
}

//
// visit_FCO
//
void CUTS_CUTE_Property_Locator::visit_FCO (GME::FCO & fco)
{
  // Visit all the attributes in the FCO.
  typedef GME::Collection_T <GME::Attribute> attribute_set;
  attribute_set attributes;

  fco.attributes (attributes);

  std::for_each (attributes.begin (),
                 attributes.end (),
                 boost::bind (&CUTS_CUTE_Property_Locator::visit_Attribute,
                              this,
                              _1));

  // If the FCO is a model, we need to visit it as well.
  if (fco.type () == OBJTYPE_MODEL)
  {
    GME::Model model = GME::Model::_narrow (fco);
    model.accept (*this);
  }
}

//
// visit_Model
//
void CUTS_CUTE_Property_Locator::visit_Model (GME::Model & model)
{
  typedef GME::Collection_T <GME::FCO> collection_type;
  collection_type fcos;

  model.fcos (fcos);

  std::for_each (fcos.begin (),
                 fcos.end (),
                 boost::bind (&collection_type::type::accept,
                              _1,
                              boost::ref (*this)));
}

//
// visit_Attribute
//
void CUTS_CUTE_Property_Locator::visit_Attribute (GME::Attribute & attr)
{
  // Determine if attribute string has a template parameter. Right now,
  // we can only handle string value types.

  if (attr.meta ().type () != ATTVAL_STRING)
    return;

  // Reset the list for storing the properties.
  if (0 != this->actor_.list ().size ())
    this->actor_.clear ();

  if (this->evaluator_.evaluate (attr.string_value ().c_str ()) &&
      0 != this->actor_.list ().size ())
  {
    list_type::CONST_ITERATOR iter (this->actor_.list ());

    for ( ; !iter.done (); ++ iter)
    {
      if (0 != this->map_.bind (*iter, attr.owner ()))
        ++ this->total_size_;
    }
  }
}
