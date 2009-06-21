// -*- C++ -*-

#ifndef _CUTS_ANYTEST_I_H_
#define _CUTS_ANYTEST_I_H_

#include "OverheadTestS.h"
#include "eisa/EINode_i.h"
#include "eisa/Software_Probe.h"
#include "eisa/Software_Probe_Factory_T.h"
#include "eisa/Software_Probe_Data_Packet.h"

class Simple_Probe : public EISA_Software_Probe
{
public:
  Simple_Probe (EISA::EINode_ptr parent)
    : EISA_Software_Probe (parent, "E860E6F7-0A10-4F94-846D-8E99F4B250B1", "heartbeat", " ")
  {
    EISA_Software_Probe_Data_Packet * packet = 0;

    ACE_NEW_THROW_EX (packet,
                      EISA_Software_Probe_Data_Packet (this->uuid_),
                      CORBA::NO_MEMORY ());

    this->packet_.reset (packet);
  }

  virtual ~Simple_Probe (void)
  {

  };

  void init (const char *)
  {

  }

  void fini (void)
  {

  }

  void handle_command (const char * command)
  {

  }

  void send_value (void)
  {
    this->packet_->reset (++ this->seqnum_, 0);
    this->einode_->send_data (this->packet_->stream ());
  }

private:
  ACE_Auto_Ptr <EISA_Software_Probe_Data_Packet> packet_;

  size_t seqnum_;
};

/**
 * @class OverheadTest_i
 */
class OverheadTest_i :
  public POA_PerformanceTests::OverheadTest
{
public:
  OverheadTest_i (void);

  virtual ~OverheadTest_i (void);

  void configure (const ACE_CString & config, ::CORBA::ORB_ptr orb);

  virtual void ping (void)
  {
    //if (0 == (++ this->event_ % 10))
      this->probe_.send_value ();
  }

  virtual void ping_oneway (void)
  {
    //if (0 == (++ this->event_ % 10))
      this->probe_.send_value ();
  }

private:
  EISA_EINode_i einode_;

  Simple_Probe probe_;

  size_t event_;
};

#endif  // !defined _CUTS_ANYTEST_I_H_
