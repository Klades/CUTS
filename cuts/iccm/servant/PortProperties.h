#ifndef _PORT_PROPERTIES_H_
#define _PORT_PROPERTIES_H_

#include "cuts/iccm/configuration/Plugins/CPU_Mask.h"
#include <string>
#include <map>

class PortProperties
{
  public:
    friend class PortProperties_Builder;

    PortProperties (void);
    PortProperties (const PortProperties & props);
    PortProperties & operator= (const PortProperties & rhs);

    int max_threads (void);
    CPU_Mask mask (void);

  private:
    PortProperties (int threads, CPU_Mask cores);

    int max_threads_;
    CPU_Mask mask_;
};

/// Builder for PortProperties objects to ensure all PortProperties are in a valid state
class PortProperties_Builder
{
  public:
    typedef std::map<std::string, std::string> prop_map;
    PortProperties_Builder (prop_map & map);

    /// Create a PortProperties item based on the name of the port and a map of property strings
    PortProperties operator() (std::string & prefix);

  private:
    PortProperties default_props;
    prop_map & property_map;
};
#endif
