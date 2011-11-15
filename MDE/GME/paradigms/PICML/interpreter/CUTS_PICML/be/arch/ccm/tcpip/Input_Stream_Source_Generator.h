#ifndef _CUTS_BE_TCPIP_INPUT_STREAM_SOURCE_GENERATOR_H_
#define _CUTS_BE_TCPIP_INPUT_STREAM_SOURCE_GENERATOR_H_

#include "PICML/PICML.h"
#include "Uml.h"
#include <ostream>

namespace CUTS_BE_TCPIP
{
/**
 * @class Input_Stream_Source_Generator
 */
class Input_Stream_Source_Generator : public PICML::Visitor
{
public:
  Input_Stream_Source_Generator (std::ostream & out);

  virtual ~Input_Stream_Source_Generator (void);

  virtual void Visit_Event (const PICML::Event & ev);
  virtual void Visit_Aggregate (const PICML::Aggregate & aggr);
  virtual void Visit_Collection (const PICML::Collection & coll);

private:
  std::ostream & out_;

  std::map <Uml::Class, std::string> array_method_;
};
}

#endif  // !defined _CUTS_BE_TCPIP_OUTPUT_STREAM_SOURCE_GENERATOR_H_
