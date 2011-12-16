// -*- C++ -*-

#ifndef _Portico_CCM_SERVANT_T_H_
#define _Portico_CCM_SERVANT_T_H_

#include "cuts/arch/ccm/CCM_Servant_T.h"
#include "Portico_CCM_Servant.h"

/**
 * @class Portico_CCM_Servant_T
 *
 * Base class for all Portico servants. This servant is also a
 * RTI FederateAmbassador, and is responsible for dispatching
 * object events to their correct ports (i.e., event upcalls).
 */
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
class Portico_CCM_Servant_T :
  public CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, Portico_CCM_Servant>
{
public:
  /// Type definition of the base type.
  typedef CUTS_CCM_Servant_T <T,
                              CONTEXT,
                              EXECUTOR,
                              POA_EXEC,
                              Portico_CCM_Servant>
                              base_type;

  /**
   * Initializing constructor.
   *
   * @param[in]         name          Name of the servant.
   * @param[in]         poa           POA for the servant.
   * @param[in]         executor      Pointer to the implementation
   */
  Portico_CCM_Servant_T (T * _this,
                         const char * name,
                         ::PortableServer::POA_ptr poa,
                         typename EXECUTOR::_ptr_type executor);

  /// Destructor.
  virtual ~Portico_CCM_Servant_T (void);

  /// Configure the servant with RTI. This is when the servant
  /// initializes its ports.
  virtual int install (const std::string & fed, const std::string & exec);

  virtual void remove (void);

  void reflectAttributeValues (RTI::ObjectHandle theObject,
                               const RTI::AttributeHandleValuePairSet& theAttributes,
                               const char *theTag);

  void reflectAttributeValues (RTI::ObjectHandle theObject,
                               const RTI::AttributeHandleValuePairSet& theAttributes,
                               const RTI::FedTime& theTime,
                               const char *theTag,
                               RTI::EventRetractionHandle theHandle);

protected:
  typedef typename base_type::consumer_map_type consumer_map_type;

  typedef typename base_type::emits_map_type emits_map_type;

  typedef typename base_type::publishes_map_type publishes_map_type;
};

#if defined (__CUTS_INLINE__)
#include "Portico_CCM_Servant_T.inl"
#endif

#include "Portico_CCM_Servant_T.cpp"

#endif  // !defined _Portico_CCM_SERVANT_T_H_
