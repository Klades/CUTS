// $Id$

#include "Response_Time_Evaluator.h"

#if !defined (__CUTS_INLINE__)
#include "Response_Time_Evaluator.inl"
#endif

#include "Component_Assembly.h"
#include "Component_Instance.h"
#include "Deployment.h"
#include "Host.h"

//
// evaluate
//
void CUTS_Response_Time_Evaluator::
evaluate (const CUTS_Component_Assembly & assembly,
          const CUTS_Deployment & deployment)
{
  // Iterate over each host in the deployment.
  CUTS_Deployment::map_type::CONST_ITERATOR host_iter (deployment.items ());
  CUTS_Host * host;
  CUTS_Component_Instance * inst;

  for (; !host_iter.done (); ++ host_iter)
  {
    // Get the utilization of the host.
    host = host_iter->item ();
    double util = host->utilization ();

    // Iterate over each component on the current host.
    CUTS_Host::container_type::CONST_ITERATOR inst_iter (host->instances ());

    for ( ; !inst_iter.done (); ++ inst_iter)
    {
      inst = *inst_iter;
      inst->response_time (util);
    }
  }
}
