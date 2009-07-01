/* -*- C++ -*- */

//=============================================================================
/**
 * @file      Delay_Handler.h
 *
 * $Id $
 *
 * @author    Pooja Varshneya
 */
//=============================================================================

#ifndef _CUTS_DELAY_HANDLER_H_
#define _CUTS_DELAY_HANDLER_H_

#include "ace/Task.h"
#include "ace/Timer_Queue_Adapters.h"
#include "ace/Timer_Heap.h"
//#include "ace/Condition_T.h"

#include "ace/Barrier.h"

/**
 * @class CUTS_Delay_Handler
 *
 * @brief This class implements the delay functionality.
 *        Whenever cutsnode deamon needs to be blocked for <delay> seconds, 
 *        Delay_Handler schedules the timer queue and on receiving the 
 *        timeout event, lets the barrier synchronize the delay_handler thread
 *        with the main thread in Node_Daemon_i class.       
 */
 
 class CUTS_Delay_Handler : public ACE_Task_Base
	{
	public:
		/// Constructor
    CUTS_Delay_Handler (ACE_Barrier * delay_end_barrier);
		
    /// Destructor
		virtual~ CUTS_Delay_Handler (void);
		
    /// Activates this object
		int activate (void);
		
    /// Deactivates this object
		void deactivate (void);
		
		/// Callback routine for handling process termination.
		int handle_exit (ACE_Process * process);
		
		/// Callback routine for handling timeout.
		int handle_timeout (const ACE_Time_Value & tv, const void * act);
		
    /// Schedules the timer.
		long schedule (double delay);
		
	private:
    
    // Timer Queue used for setting timer
    ACE_Thread_Timer_Queue_Adapter <ACE_Timer_Heap> timer_queue_;

    // ACE_Barrier used to synchronize this thread with the main thread.
    ACE_Barrier * delay_end_barrier_;
    
    // Stores the activation status for this thread 
    bool active_;
	};

#endif  /* !defined _CUTS_DELAY_HANDLER_H_ */

