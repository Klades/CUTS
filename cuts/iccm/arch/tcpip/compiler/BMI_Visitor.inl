// -*- C++ -*-
// $Id$

namespace iCCM
{
namespace TCPIP
{

//
// BMI_Visitor
//
CUTS_INLINE
BMI_Visitor::BMI_Visitor (std::ofstream & sfile)
: sfile_ (sfile),
  port_counter_ (0)
{

}

//
// ~BMI_Visitor
//
CUTS_INLINE
BMI_Visitor::~BMI_Visitor (void)
{

}

} // namespace iCCM
} // namespace TCPIP
