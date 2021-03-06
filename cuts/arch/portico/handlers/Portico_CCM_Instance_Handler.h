// -*- C++ -*-

//=============================================================================
/**
 * @file          Portico_CCM_Instance_Handler.h
 *
 * $Id$
 *
 *  Code generated by iCCM skeleton project generator that is include
 *  in the CUTS (http://cuts.cs.iupui.edu) and developed by:
 *
 *      Software Engineering & Distributed System (SEDS) Group
 *      Indiana Univesity-Purdue University Indianapolis
 *      Indianapolis, IN 46202
 *      USA
 */
//=============================================================================

#ifndef _PORTICO_CCM_INSTANCE_HANDLER_H_
#define _PORTICO_CCM_INSTANCE_HANDLER_H_

#include "cuts/arch/ccm/CCM_Component_Instance_Handler_T.h"

#include "Portico_CCM_Container.h"
#include "Portico_CCM_Deployment_Handlers_export.h"

/**
 * @class Portico_CCM_Instance_Handler
 *
 * Portico implementation of the deployment handlers for component
 * instances. This instance handler creates its own RTIambassor object
 * for registering federates (i.e., components). In order for this
 * handler to function correctly, FEDFile and FEDExecution domain
 * properties must be defined. Otherwise, the handler does not know
 * what execution a federate is a member.
 */
class Portico_CCM_Instance_Handler :
  public CUTS_CCM_Component_Instance_Handler_T <Portico_CCM_Instance_Handler,
                                                Portico_CCM_Container>
{
public:
  struct FED
  {
    /// FED file.
    std::string file_;

    /// Target execution for the federate.
    std::string execution_;
  };

  /// Type definition of the base type.
  typedef CUTS_CCM_Component_Instance_Handler_T <Portico_CCM_Instance_Handler,
                                                 Portico_CCM_Container>
                                                 base_type;
  /// Default constructor.
  Portico_CCM_Instance_Handler (void);

  /// Destructor.
  virtual ~Portico_CCM_Instance_Handler (void);

  /**
   * Configure the instance handler. The deployment properties passed
   * into this function are the ones attached to the Node in the
   * deployment model.
   *
   * @param[in]           config          Configuration properties
   */
  virtual void configure (const Deployment::Properties & config);

  /// Close the instance handler.
  virtual void close (void);

  /// Get a pointer to the RTI ambassador.
  const FED & get_fedinfo (void) const;

private:
  /// RTI FED information.
  FED fedinfo_;
};

extern "C"
::DAnCE::InstanceDeploymentHandler_ptr
PORTICO_CCM_DEPLOYMENT_HANDLERS_Export
create_Portico_CCM_Component_Instance_Handler (void);

#if defined (__CUTS_INLINE__)
#include "Portico_CCM_Instance_Handler.inl"
#endif

#endif  // !defined _Portico_CCM_INSTANCE_HANDLER_H_
