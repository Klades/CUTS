// -*- C++ -*-

#ifndef _CUTS_BE_TCPIP_INPUT_EVENT_MEMBER_GENERATOR_H_
#define _CUTS_BE_TCPIP_INPUT_EVENT_MEMBER_GENERATOR_H_

#include "../../../paradigms/CHAOS.h"
#include <ostream>
#include "../UDM_Abstract_Type_Dispatcher_T.h"

namespace CUTS_BE_TCPIP
{
/**
 * @class Input_Stream_Event_Member_Generator
 */
class Input_Stream_Event_Member_Generator : public CHAOS::Visitor
{
public:
  Input_Stream_Event_Member_Generator (std::ostream & out);

  virtual ~Input_Stream_Event_Member_Generator (void);

  virtual void Visit_Member (const CHAOS::Member & member);

  virtual void Visit_Boolean (const CHAOS::Boolean & val);

  virtual void Visit_Byte (const CHAOS::Byte & val);

  virtual void Visit_LongInteger (const CHAOS::LongInteger & val);

  virtual void Visit_RealNumber (const CHAOS::RealNumber & val);

  virtual void Visit_ShortInteger (const CHAOS::ShortInteger & val);

  virtual void Visit_String (const CHAOS::String & val);

private:
  std::ostream & out_;

  UDM_Abstract_Type_Dispatcher_T <Input_Stream_Event_Member_Generator> predefined_types_;
};

}

#endif  // !defined _CUTS_BE_TCPIP_INPUT_EVENT_MEMBER_GENERATOR_H_
