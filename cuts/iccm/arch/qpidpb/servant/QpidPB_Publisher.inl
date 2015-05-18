// -*- C++ -*-
// $IdQpidPB_Publisher.inl 3086 2011-01-22 05:53:51Z hillj $

namespace iCCM
{

//
// QpidPB_Publisher
//
CUTS_INLINE
QpidPB_Publisher::QpidPB_Publisher (void)
: host_ ("localhost"),
  port_ (5672),
  queue_ ("default")
{

}

//
// ~QpidPB_Publisher
//
CUTS_INLINE
QpidPB_Publisher::~QpidPB_Publisher (void)
{

}

}
