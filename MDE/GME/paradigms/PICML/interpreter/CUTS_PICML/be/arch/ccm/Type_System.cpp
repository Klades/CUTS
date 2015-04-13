// $Id$

#include "Type_System.h"

#if !defined (__CUTS_INLINE__)
#include "Type_System.inl"
#endif

namespace CUTS_BE_CCM
{
template <typename BASE>
struct derives_from
{
public:
template <typename T>
bool operator () (const T & derived) const
{
  try
  {
    BASE base = BASE::_narrow (derived);
    return true;
  }
  catch (GAME::Mga::Exception &)
  {
    return false;
  }
}
};

//
// Type_System
//
Type_System::Type_System (std::ostream & out)
: out_ (out)
{

}

//
// generate
//
void Type_System::generate (const PICML::MemberType_in mt)
{
  if (derives_from <PICML::PredefinedType> () (mt))
    mt->accept (this);
}

}
