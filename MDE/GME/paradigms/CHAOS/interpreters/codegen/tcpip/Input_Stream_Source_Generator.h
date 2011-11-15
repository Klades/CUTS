#ifndef _CUTS_BE_TCPIP_INPUT_STREAM_SOURCE_GENERATOR_H_
#define _CUTS_BE_TCPIP_INPUT_STREAM_SOURCE_GENERATOR_H_

#include "../../../paradigms/CHAOS.h"
#include <ostream>

namespace CUTS_BE_TCPIP
{
  /**
   * @class Input_Stream_Source_Generator
   */
  class Input_Stream_Source_Generator : public CHAOS::Visitor
  {
  public:
    Input_Stream_Source_Generator (std::ostream & out);

    virtual ~Input_Stream_Source_Generator (void);

    virtual void Visit_Event (const CHAOS::Event & ev);

    virtual void Visit_Aggregate (const CHAOS::Aggregate & aggr);

    virtual void Visit_Collection (const CHAOS::Collection & coll);

  private:
    std::ostream & out_;
  };
}

#endif  // !defined _CUTS_BE_TCPIP_OUTPUT_STREAM_SOURCE_GENERATOR_H_
