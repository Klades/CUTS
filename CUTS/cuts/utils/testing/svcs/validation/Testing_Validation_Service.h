// -*- C++ -*-

//=============================================================================
/**
 * @file          Testing_Validation_Service.h
 *
 * $Id $
 *
 * @author       Pooja Varshneya
 */
//=============================================================================

#ifndef _CUTS_TESTING_VALIDATION_SERVICE_H_
#define _CUTS_TESTING_VALIDATION_SERVICE_H_

#include "Testing_Validation_Service_export.h"
#include "cuts/utils/testing/Testing_Service.h"
#include "ace/SString.h"

/**
 * @class CUTS_Testing_Validation_Service
 *
 * Implementation of the validation service for the test manager.
 */

class CUTS_Testing_Validation_Service : public CUTS_Testing_Service
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]         parent        Parent testing application.
   */
  CUTS_Testing_Validation_Service (void);

  /// Destructor.
  virtual ~CUTS_Testing_Validation_Service (void);
	
	/**
	 * Initialize the service.
	 *
	 * @param[in]       argc          Number of command-ling arguments
	 * @param[in]       argv          Command-line arguments
	 */
	virtual int init (int argc, char * argv []);

	/**
	 * Handle the shutdown of a test.
	 *
	 * @param[in]     app         Parent testing application
	 */
	virtual int handle_shutdown (const ACE_Time_Value & tv);
	
private:

  /**
   * Parse the command-line arguments.
   */
  int parse_args (int argc, char * argv []);
	
	/**
   * Validate the test after parsing datagraph and condition file
   */
	int validate_test (void);
	
	/// Print help message
	void print_help (void);
	
  /// Path of the datagraph file.
  ACE_CString datagraph_;
	
	/// Path of condition file
	ACE_CString validation_config_;
};

CUTS_TESTING_SERVICE_DECL (CUTS_TESTING_VALIDATION_SERVICE_Export,   
                           _make_CUTS_Testing_Validation_Service);

#endif  // !defined _CUTS_TESTING_VALIDATION_SERVICE_H_
