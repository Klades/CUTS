// $Id$

//
// UDM_Abstract_Type_Dispatcher_T
//
template <typename VISITOR>
UDM_Abstract_Type_Dispatcher_T <VISITOR>::
UDM_Abstract_Type_Dispatcher_T (VISITOR * visitor)
: visitor_ (visitor)
{

}

//
// ~UDM_Abstract_Type_Dispatcher_T
//
template <typename VISITOR>
UDM_Abstract_Type_Dispatcher_T <VISITOR>::
~UDM_Abstract_Type_Dispatcher_T (void)
{
  UDM_Acceptor_Map::iterator
    iter = this->acceptors_.begin (), iter_end = this->acceptors_.end ();

  for ( ; iter != iter_end; ++ iter)
    delete iter->second;
}

//
// insert
//
template <typename VISITOR>
template <typename T>
void UDM_Abstract_Type_Dispatcher_T <VISITOR>::insert (void)
{
  UDM_Abstract_Type_Acceptor_Base_T <VISITOR> * acceptor =
    new UDM_Abstract_Type_Acceptor_T <T, VISITOR> ();

  std::pair <UDM_Acceptor_Map::iterator, bool> result =
    this->acceptors_.insert (UDM_Acceptor_Map::value_type (T::meta, acceptor));

  if (!result.second)
    delete acceptor;
}

//
// dispatch
//
template <typename VISITOR>
void UDM_Abstract_Type_Dispatcher_T <VISITOR>::
dispatch (const Udm::Object & object) const
{
  // Locate the acceptor for the type.
  UDM_Acceptor_Map::const_iterator result =
    this->acceptors_.find (object.type ());

  // Tell the acceptor to accept the object.
  if (result != this->acceptors_.end ())
    result->second->accept (this->visitor_, object);
}
