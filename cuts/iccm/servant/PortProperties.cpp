#include "PortProperties.h"

#include <sstream>
#include <iostream>

PortProperties::PortProperties (void)
  : max_threads_ (1)
{
}

PortProperties::PortProperties (int threads, CPU_Mask cores)
  : max_threads_ (threads),
    mask_ (cores)
{
}

PortProperties & PortProperties::operator= (const PortProperties & rhs)
{
  this->max_threads_ = rhs.max_threads_;
  this->mask_ = rhs.mask_;

  return *this;
}

int PortProperties::max_threads (void)
{
  return max_threads_;
}

CPU_Mask PortProperties::mask (void)
{
  return mask_;
}

PortProperties_Builder::PortProperties_Builder (prop_map * map)
  : def_threads (1),
    def_mask (),
    property_map (map)
{
}

PortProperties * PortProperties_Builder::operator() (std::string & prefix)
{
  std::string thread_name = prefix + ".thread_count";
  std::string cores_name = prefix + ".cores";

  int threads = 1;
  CPU_Mask mask;

  if (property_map->count (thread_name))
  {
    std::stringstream converter;
    converter << (*property_map)[thread_name];
    converter >> threads;
  }  

  if (property_map->count (cores_name))
  {
    CPU_Mask temp((*property_map)[cores_name].c_str());
    mask = temp;
  }

  // Make sure the new properties are valid
  if (threads > 0) 
  {
    return new PortProperties (threads, mask);
  }
  else
  {
    /// TODO: Need to throw an error here but for now...
    return new PortProperties (def_threads, def_mask);
  }
}
