// $Id$

#include "OverheadTest_i.h"

OverheadTest_i::OverheadTest_i (void)
: einode_ (true),
  probe_ (&einode_),
  event_ (0)
{

}

OverheadTest_i::~OverheadTest_i (void)
{

}

void OverheadTest_i::
configure (const ACE_CString & config, ::CORBA::ORB_ptr orb)
{
  this->einode_.activate (config, orb);
}
