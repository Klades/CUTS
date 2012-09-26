// -*- C++ -*-
// $Id$

namespace iCCM
{
namespace TCPIP
{

//
// Push_Event_Visitor
//
CUTS_INLINE
Push_Event_Visitor::Push_Event_Visitor (std::ofstream & hfile,
                                        std::ofstream & sfile,
                                        const ACE_CString & servant)
: hfile_ (hfile),
  sfile_ (sfile),
  servant_ (servant)
{

}

//
// ~Push_Event_Visitor
//
CUTS_INLINE
Push_Event_Visitor::~Push_Event_Visitor (void)
{

}

} // namespace iCCM
} // namespace TCPIP
