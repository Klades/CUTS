template <typename T, typename SERVANT>
Consumer_Task<T, SERVANT>::Consumer_Task (SERVANT * servant, upcall_method_type upcall)
: servant_ (servant),
  upcall_ (upcall)
{

}

template <typename T, typename SERVANT>
Consumer_Task<T, SERVANT>::~Consumer_Task (void)
{

}

template <typename T, typename SERVANT>
int Consumer_Task<T, SERVANT>::open (void * args = 0)
{
  return activate (THR_NEW_LWP, MAX_THREADS);
}

template <typename T, typename SERVANT>
int Consumer_Task<T, SERVANT>::close (u_long flags = 0)
{
  if (!thr_count ())
  {
    delete this;
  }
  return 0;
}

template <typename T, typename SERVANT>
int Consumer_Task<T, SERVANT>::svc (void)
{
  ACE_Message_Block * msg;
 
  while (getq (msg) != -1) {
    if (0 != this->servant)
    {
      T * ev = reinterpret_cast<T*>(msg->rd_ptr ());
      (*this->upcall_) (this->servant_, ev);
      msg->release ();
    }
  }
}

template <typename T, typename SERVANT>
int Consumer_Task<T, SERVANT>::put (ACE_Message_Block * msg, ACE_Time_Value * time = 0)
{
  return putq (msg, time);
}