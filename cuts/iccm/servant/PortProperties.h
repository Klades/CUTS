#ifndef _PORT_PROPERTIES_H_
#define _PORT_PROPERTIES_H_

#include "cuts/iccm/configuration/Plugins/CPU_Mask.h"
#include <string>
#include <map>

struct PortProperties
{
  int max_threads;
  CPU_Mask mask;
};

class PortProperties_Builder
{
  public:
    PortProperties_Builder (void);

    void set_defaults (PortProperties defaults);

    PortProperties operator() (std::string & prefix, std::map<std::string, std::string> & property_map);

  private:
    PortProperties default_props;
};
#endif
