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

//
// configure_broker
//
CUTS_INLINE
void
QpidPB_Publisher_Table::configure_broker (const std::string & host, int port)
{
  this->host_ = host;
  this->port_ = port;
}

//
// queue
//
CUTS_INLINE
void
QpidPB_Publisher_Table::queue (const std::string & queue)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("\n\n%T (%t) - %M - setting queue [%s]\n"),
              queue.c_str ()));
  this->queue_ = queue;
}

}
