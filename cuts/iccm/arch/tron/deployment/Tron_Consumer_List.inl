//  $Id$

//
// Tron_Consumer_List
//
CUTS_INLINE
Tron_Consumer_List::
Tron_Consumer_List (void)
{

}


//
// ~Tron_Consumer_List
//
CUTS_INLINE
Tron_Consumer_List::
~Tron_Consumer_List (void)
{

}

//
// add
//
CUTS_INLINE
void Tron_Consumer_List::
add (::iCCM::Tron_EventConsumer * consumer)
{
  this->consumers_.push_back (consumer);
}
