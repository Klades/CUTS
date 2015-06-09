// $Id$

#if !defined (__CUTS_INLINE__)
#include "CHAOS_EventConsumer_T.inl"
#endif

namespace iCCM
{

//
// allocate
//
template <typename SERVANT, typename EVENT>
void
CHAOS_EventConsumer_T <SERVANT, EVENT>::allocate (ptrdiff_t & symbol)
{
    typedef typename iCCM::EventConsumer * (*EventConsumerFactoryMethod) (SERVANT *, CALLBACK_METHOD);
    EventConsumerFactoryMethod factory_method = reinterpret_cast <EventConsumerFactoryMethod> (symbol);

    iCCM::EventConsumer * impl = (*factory_method) (this->servant_, this->callback_);
    this->impl (impl);
}

}
