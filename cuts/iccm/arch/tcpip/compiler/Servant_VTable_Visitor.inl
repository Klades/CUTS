// -*- C++ -*-
// $Id$

namespace iCCM
{
namespace TCPIP
{

//
// Servant_VTable_Visitor
//
CUTS_INLINE
Servant_VTable_Visitor::Servant_VTable_Visitor (std::ofstream & sfile)
: sfile_ (sfile),
  port_counter_ (0)
{

}

//
// ~Servant_VTable_Visitor
//
CUTS_INLINE
Servant_VTable_Visitor::~Servant_VTable_Visitor (void)
{

}

} // namespace iCCM
} // namespace TCPIP
