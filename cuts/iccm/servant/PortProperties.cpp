#include "PortProperties.h"

#include <sstream>

PortProperties::PortProperties (void)
  : max_threads_ (1)
{
}

PortProperties::PortProperties (int threads, CPU_Mask cores)
  : max_threads_ (threads),
    mask_ (cores)
{
}

int PortProperties::max_threads (void)
{
  return max_threads_;
}

CPU_Mask PortProperties::mask (void)
{
  return mask_;
}

PortProperties_Builder::PortProperties_Builder (prop_map & map)
  : property_map (map)
{
  std::string def("@default");
  default_props = operator() (def);
}

PortProperties PortProperties_Builder::operator() (std::string & prefix)
{
  std::string thread_name = prefix + ".thread_count";
  std::string cores_name = prefix + ".cores";


  int threads = default_props.max_threads();
  CPU_Mask mask = default_props.mask();

  if (property_map.count (thread_name))
  {
    std::stringstream converter;
    converter << property_map[thread_name];
    converter >> threads;
  }  

  if (property_map.count (cores_name))
  {
    CPU_Mask temp(property_map[cores_name].c_str());
    mask = temp;
  }

  // Make sure the new properties are valid
  if (threads > 0) 
  {
    return PortProperties (threads, mask);
  }
  else
  {
    /// TODO: Need to throw an error here but for now...
    return default_props;
  }
}
