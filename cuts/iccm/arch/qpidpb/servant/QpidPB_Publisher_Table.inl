// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// QpidPB_Publisher_Table
//
CUTS_INLINE
QpidPB_Publisher_Table::QpidPB_Publisher_Table (void)
: host_ ("localhost"),
  port_ (5672),
  queue_ ("default")
{

}

//
// ~QpidPB_Publisher_Table
//
CUTS_INLINE
QpidPB_Publisher_Table::~QpidPB_Publisher_Table (void)
{

}

}
