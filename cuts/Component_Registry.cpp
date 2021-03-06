// $Id$

#include "cuts/Component_Registry.h"

#if !defined (__CUTS_INLINE__)
#include "cuts/Component_Registry.inl"
#endif

#include "cuts/Component_Registry_Node.h"
#include "cuts/Component_Registry_Handler.h"
#include "cuts/Component_Type.h"
#include "ace/Guard_T.h"
#include "ace/Thread_Manager.h"

//
// CUTS_Component_Registry
//
CUTS_Component_Registry::CUTS_Component_Registry (void)
: open_ (0),
  grp_id_ (-1)
{

}

//
// ~CUTS_Component_Registry
//
CUTS_Component_Registry::~CUTS_Component_Registry (void)
{
  // Delete all the instances in the registry.
  CUTS_Component_Registry_Map::iterator reg_iter (this->registry_);

  for ( ; !reg_iter.done (); reg_iter.advance ())
    delete reg_iter->int_id_;

  // Delete all the types in the registry.
  CUTS_Component_Type_Map::CONST_ITERATOR type_iter (this->component_types_);

  for ( ; !type_iter.done (); type_iter ++)
    delete type_iter->item ();
}

//
// register_component
//
int CUTS_Component_Registry::
register_component (CUTS_Component_Registry_Node * info)
{
  // Re-insert the info into the component registry. Since we may get
  // back an old pointer, we are going to store that result in an
  // auto pointer. This way it will get deleted regardless of how we
  // leave this function.
  CUTS_Component_Registry_Node * old_info = 0;
  int retval = this->registry_.rebind (info->info_.inst_, info, old_info);
  ACE_Auto_Ptr <CUTS_Component_Registry_Node> auto_clean (old_info);

  if (retval == 0 || retval == 1)
  {
    if (retval == 1 && old_info != 0)
    {
      // Make sure we are updating a component that was already
      // passivated. Otherwise, we are changing the state of an active
      // component, which may pose some problems to the end-user.
      if (old_info->info_.state_ != CUTS_Component_Info::STATE_PASSIVATE)
      {
        ACE_ERROR ((LM_WARNING,
                    "*** warning (registry): `%s' was still an active "
                    "component\n",
                    old_info->info_.inst_.c_str ()));
      }
    }

    // Set the state of the component to *active* and signal all
    // the <handlers_> that we have a new component registered.
    info->info_.state_ = CUTS_Component_Info::STATE_ACTIVATE;
    info->delete_ = false;

    this->info_queue_.enqueue_tail (info);
  }
  else /* if (retval == -1) */
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (component registry): internal error during "
                "registration\n"));
  }

  return retval;
}

//
// unregister_component
//
void CUTS_Component_Registry::
unregister_component (const ACE_CString & instance)
{
  CUTS_Component_Registry_Node * node = 0;
  this->unregister_component (instance, node);
}

//
// unregister_component
//
void CUTS_Component_Registry::
unregister_component (const ACE_CString & instance, 
                      CUTS_Component_Registry_Node * & node)
{
  // Locate the registration information for <instance>.
  int retval = this->registry_.find (instance, node);

  if (retval == 0 && node != 0)
  {
    // Change its state to passivate and notify all the handlers
    // that are registered w/ the service.
    node->info_.state_ = CUTS_Component_Info::STATE_PASSIVATE;
    node->delete_ = false;

    this->info_queue_.enqueue_tail (node);
  }
}

//
// register_handler
//
int CUTS_Component_Registry::
register_handler (CUTS_Component_Registry_Handler * handler)
{
  ACE_WRITE_GUARD_RETURN (ACE_RW_Thread_Mutex, 
                          guard, 
                          this->handler_lock_, 
                          -1);

  if (this->handlers_.find (handler) == 0)
    return 1;

  return this->handlers_.insert (handler);
}

//
// unregister_handler
//
int CUTS_Component_Registry::
unregister_handler (CUTS_Component_Registry_Handler * handler)
{
  ACE_WRITE_GUARD_RETURN (ACE_RW_Thread_Mutex, 
                          guard, 
                          this->handler_lock_, 
                          -1);

  return this->handlers_.remove (handler);
}

//
// thr_svc
//
ACE_THR_FUNC_RETURN CUTS_Component_Registry::thr_svc (void * param)
{
  CUTS_Component_Registry * reg =
    reinterpret_cast <CUTS_Component_Registry *> (param);

  while (reg->is_open ())
  {
    // Get the next registry node from the <info_queue_>.
    CUTS_Component_Registry_Node * node = 0;
    int retval = reg->info_queue_.dequeue_head (node);

    if (retval != -1 && node != 0)
    {
      ACE_READ_GUARD_RETURN (ACE_RW_Thread_Mutex, 
                             guard, 
                             reg->handler_lock_, 
                             0);

      // Notify all loaded services to handle the component.
      CUTS_Handler_Set::ITERATOR iter (reg->handlers_);

      for ( ; !iter.done (); iter ++)
        (*iter)->handle_component (node->info_);
    }
  }

  return 0;
}

//
// open
//
int CUTS_Component_Registry::open (void)
{
  // We only all one thread open.
  if (this->is_open ())
    return 1;

  // We need to setup all workings for service thread.
  this->open_ = 1;
  this->info_queue_.activate ();

  // Spawn the service thread for the registry.
  this->grp_id_ =
    ACE_Thread_Manager::instance ()->
    spawn (&CUTS_Component_Registry::thr_svc,
           this);

  // Verify everything was created properly.
  if (this->grp_id_ == -1)
    this->open_ = 0;

  return this->open_ ? 0 : -1;
}

//
// close
//
int CUTS_Component_Registry::close (void)
{
  if (!this->is_open ())
    return 0;

  this->open_ = 0;
  this->info_queue_.deactivate ();

  ACE_Thread_Manager::instance ()->wait_grp (this->grp_id_);
  return 0;
}

//
// get_component_info
//
int CUTS_Component_Registry::
get_component_info (size_t uid, const CUTS_Component_Info ** info) const
{
  if (uid == CUTS_UNKNOWN_IMPL)
    return -1;

  /// @warning This only works as long as size_t is the size
  /// of a pointer.
  CUTS_Component_Registry_Node * node =
    reinterpret_cast <CUTS_Component_Registry_Node *> (uid);

  if (info != 0)
    *info = &node->info_;

  return 0;
}
