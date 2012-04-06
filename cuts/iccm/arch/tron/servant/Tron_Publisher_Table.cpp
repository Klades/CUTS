// $Id$

#include "Tron_Publisher_Table.h"

#if !defined (__CUTS_INLINE__)
#include "Tron_Publisher_Table.inl"
#endif

namespace iCCM
{

//
// register_channel
//
void Tron_Publisher_Table::
register_channel (Reporter * reporter, const ACE_CString & name)
{
  this->channel_ = reporter->getOutputEncoding (reporter, name.c_str ());
  this->reporter_ = reporter;
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Got reporter for Publisher_Table [%s, %d]\n"),
              name.c_str (),
              this->channel_));
}

}
