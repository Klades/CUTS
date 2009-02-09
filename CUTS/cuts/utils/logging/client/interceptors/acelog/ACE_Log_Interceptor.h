// -*- C++ -*-

//=============================================================================
/**
 * @file      ACE_Log_Interceptor.h
 *
 * $Id$
 *
 * @author    Pooja Varshneya
 */
//=============================================================================


#ifndef _CUTS_ACE_LOG_INTERCEPTOR_H_
#define _CUTS_ACE_LOG_INTERCEPTOR_H_

#include "ace/Service_Object.h"
#include "ace/Auto_Ptr.h"
#include "ACE_Log_Interceptor_export.h"
#include "ACE_Log_Interceptor_App_Options.h"
#include "ACE_Log_Callback.h"

/**
 * @class CUTS_ACE_Log_Interceptor
 *
 * 
 */

class CUTS_ACE_Log_Interceptor_Export CUTS_ACE_Log_Interceptor : public ACE_Service_Object
{
	public:
		
		/**
		 *  Performs initialization for run-time service configuration
		 *
     * @param[in]         argc        Number of arguments
     * @param[in]         argv        Command-line arguments
     */
	  virtual int init (int argc, ACE_TCHAR *argv[]);
		
		
		/// Performs cleanup 
		virtual int fini (void);
		
		/**
		 *  Provides information about the service bing configured
		 *  
		 */
	  virtual int info (ACE_TCHAR **str, size_t len) const;
		
		//virtual int suspend ();
		//virtal int resume ();
		
	private:
	
		/**
		 * Parses the command-line arguments	
		 *
     * @param[in]         argc        Number of arguments
     * @param[in]         argv        Command-line arguments
		 *
		 * @param[out]        -1				  Represents faliure
		 *										 0					Represents success
     */
		int parse_args (int argc, char * argv []);
		
		/// Print the help for the application.
		int print_help (void);
		
		/// Makes the connection to test-manager based on command-line arguments
		int make_connection(void);

		/// callback_ is used for handling callbacks 
		ACE_Auto_Ptr<CUTS_ACE_Log_Callback> callback_;
		
    /// logger_ is used for to make connection with test_logger
		CUTS_Test_Logger logger_;
		
		/// app_options is used to save the parsed command-line options
		CUTS_ACE_Log_Interceptor_App_Options app_options_;
		
};

ACE_FACTORY_DEFINE(CUTS_ACE_Log_Interceptor, CUTS_ACE_Log_Interceptor)

#endif /* _CUTS_ACE_LOG_INTERCEPTOR_H_ */

