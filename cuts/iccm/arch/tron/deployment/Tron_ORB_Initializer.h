//  $Id$

#ifndef _TRON_ORB_INITIALIZER_H_
#define _TRON_ORB_INITIALIZER_H_

#include "ace/Task.h"
#include "cuts/Servant_Manager_T.h"

/**
 * Class to help initalize tron
 */
class Tron_ORB_Initializer : public ACE_Task_Base
{
public:
  // Initalizing ctor
  Tron_ORB_Initializer (::CORBA::ORB_ptr orb);

  // dtor
  virtual ~Tron_ORB_Initializer (void);

  // Service handler routine
  virtual int svc (void);

  // Deactivate the task
  void deactivate (void);

private:
  // The orb to work with
  ::CORBA::ORB_var orb_;

  // Flag for completion
  bool is_done_;
};

#endif  // !defined _TRON_ORB_INITIALIZER_H_
