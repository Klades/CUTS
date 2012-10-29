// -*- C++ -*-
// $Id$

namespace iCCM
{
namespace TAO
{

//
// Register_Value_Factories_Visitor
//
CUTS_INLINE
Register_Value_Factories_Visitor::
Register_Value_Factories_Visitor (std::ofstream & hfile,
                                  std::ofstream & sfile,
                                  const ACE_CString & servant)
: hfile_ (hfile),
  sfile_ (sfile),
  servant_ (servant)
{

}

//
// ~Register_Value_Factories_Visitor
//
CUTS_INLINE
Register_Value_Factories_Visitor::~Register_Value_Factories_Visitor (void)
{

}

} // namespace iCCM
} // namespace TAO
