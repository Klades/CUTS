// -*- C++ -*-

//=============================================================================
/**
 * @file            Servant_Implementation.h
 *
 * $Id$
 *
 * @author          James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CCM_SERVANT_IMPLEMENTATION_H_
#define _CUTS_BE_CCM_SERVANT_IMPLEMENTATION_H_

#include "CCM_export.h"
#include "PICML/PICML.h"
#include "PICML/Visitor.h"

namespace CUTS_BE_CCM
{
namespace Cpp
{

/**
 * @class Servant_Set_Attribute_Decl
 *
 * Utility class for generating the set_attributes () method
 * declaration for a component's servant.
 */
class CUTS_BE_CCM_Export Servant_Set_Attribute_Decl :
    public PICML::Visitor
{
public:
  Servant_Set_Attribute_Decl (std::ostream & out);

  /// Destructor
  virtual ~Servant_Set_Attribute_Decl (void);

  void visit_Component (PICML::Component_in c);

private:
  /// Reference to output stream.
  std::ostream & out_;
};

/**
 * @class Servant_Set_Attribute_Impl
 *
 * Utility class for generating the set_attribute () method
 implementation for a component's servant.
 */
class CUTS_BE_CCM_Export Servant_Set_Attribute_Impl :
    public PICML::Visitor
{
public:
  Servant_Set_Attribute_Impl (std::ostream & out);

  /// Destructor
  virtual ~Servant_Set_Attribute_Impl (void);

  void visit_Component (PICML::Component_in c);

  void visit_Attribute (PICML::Attribute_in a);

private:
  /// Reference to output stream.
  std::ostream & out_;
};


}

}

#endif  // !defined _CUTS_BE_CCM_SERVANT_IMPLEMENTATION_H_