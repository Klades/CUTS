// -*- C++ -*-

#ifndef _CUTS_BE_TCPIP_INPUT_EVENT_MEMBER_GENERATOR_H_
#define _CUTS_BE_TCPIP_INPUT_EVENT_MEMBER_GENERATOR_H_

#include "PICML/PICML.h"
#include <ostream>
#include "../../../UDM_Abstract_Type_Dispatcher_T.h"

namespace CUTS_BE_TCPIP
{
/**
 * @class Input_Stream_Event_Member_Generator
 */
class Input_Stream_Event_Member_Generator : public PICML::Visitor
{
public:
  Input_Stream_Event_Member_Generator (std::ostream & out);

  virtual ~Input_Stream_Event_Member_Generator (void);

  virtual void Visit_Member (const PICML::Member & member);

  virtual void Visit_Byte (const PICML::Byte & val);
  virtual void Visit_Boolean (const PICML::Boolean & val);
  virtual void Visit_Char (const PICML::Char & val);

  virtual void Visit_ShortInteger (const PICML::ShortInteger &);
  virtual void Visit_UnsignedShortInteger (const PICML::UnsignedShortInteger &);

  virtual void Visit_LongInteger (const PICML::LongInteger & val);
  virtual void Visit_LongLongInteger (const PICML::LongLongInteger & val);

  virtual void Visit_UnsignedLongInteger (const PICML::UnsignedLongInteger & val);
  virtual void Visit_UnsignedLongLongInteger (const PICML::UnsignedLongLongInteger & val);

  virtual void Visit_FloatNumber (const PICML::FloatNumber &);
  virtual void Visit_DoubleNumber (const PICML::DoubleNumber & val);
  virtual void Visit_LongDoubleNumber (const PICML::LongDoubleNumber &);

  virtual void Visit_String (const PICML::String & val);

private:
  std::ostream & out_;

  UDM_Abstract_Type_Dispatcher_T <Input_Stream_Event_Member_Generator> predefined_types_;
};

}

#endif  // !defined _CUTS_BE_TCPIP_INPUT_EVENT_MEMBER_GENERATOR_H_
