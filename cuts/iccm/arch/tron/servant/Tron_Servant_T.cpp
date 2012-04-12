// $Id$

#if !defined (__CUTS_INLINE__)
#include "Tron_Servant_T.inl"
#endif

#include "boost/bind.hpp"

namespace iCCM
{

//
// init
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void Tron_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
init (Reporter * reporter, tron_consumer_map_type & consumer_map)
{
  // Register input channels with the consumers
  std::for_each (this->consumers_.begin (),
                 this->consumers_.end (),
                 boost::bind (&Tron_EventConsumer::register_channel,
                              boost::bind (&consumer_map_type::ENTRY::int_id_, _1),
                              reporter,
                              boost::bind (&consumer_map_type::ENTRY::ext_id_, _1),
                              boost::ref (consumer_map)));

  // Register output channels with the publisher tables
  std::for_each (this->publishes_.begin (),
                 this->publishes_.end (),
                 boost::bind (&Tron_Publisher_Table::register_channel,
                              boost::bind (&publishes_map_type::ENTRY::int_id_, _1),
                              reporter,
                              boost::bind (&publishes_map_type::ENTRY::ext_id_, _1)));

  // Register output channels with the publishers
  std::for_each (this->emits_.begin (),
                 this->emits_.end (),
                 boost::bind (&Tron_Publisher::register_channel,
                              boost::bind (&emits_map_type::ENTRY::int_id_, _1),
                              reporter,
                              boost::bind (&emits_map_type::ENTRY::ext_id_, _1)));
}


}
