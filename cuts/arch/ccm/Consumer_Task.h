#ifndef _CUTS_CONSUMER_TASK_H_
#define _CUTS_CONSUMER_TASK_H_

#include "ace/Task.h"
#include "ace/Synch.h"

template <typename T, typename SERVANT>
class Consumer_Task : public ACE_Task<ACE_MT_SYNCH>
{
public:
  typedef int (*upcall_method_type) (SERVANT *, T *);

  Consumer_Task (SERVANT * servant, upcall_method_type upcall);
  
  virtual ~Consumer_Task (void);

  int open (void * args = 0);
  int close (u_long flags = 0);
  int svc (void);
  int put (ACE_Message_Block * msg, ACE_Time_Value * time = 0);
  enum { MAX_THREADS = 4 };

private:
  SERVANT * servant_;

  upcall_method_type upcall_;
};

#include "Consumer_Task.cpp"
#endif