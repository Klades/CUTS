// -*- C++ -*-
// $IdQpidPB_CCM_EventConsumer.inl 2687 2009-06-02 21:20:04Z hillj $

namespace iCCM
{

//
// QpidPB_EventConsumer
//
CUTS_INLINE
QpidPB_EventConsumer::QpidPB_EventConsumer (void)
: host_ ("localhost"),
  port_ (5672),
  queue_ ("default")
{

}

//
// ~QpidPB_EventConsumer
//
CUTS_INLINE
QpidPB_EventConsumer::~QpidPB_EventConsumer (void)
{

}

//
// configure
//
CUTS_INLINE
void QpidPB_EventConsumer::
configure (const char * host, int port, const char * queue)
{
  this->host_ = host;
  this->port_ = port;
  this->queue_ = queue;
}

}
