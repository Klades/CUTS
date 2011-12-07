#ifndef EXAMPLECPPFEDERATE_H_
// -*- C++ -*-

#define EXAMPLECPPFEDERATE_H_

#include "ExampleFedAmb.h"
#include "RTI.hh"
#include <memory>

#define READY_TO_RUN "ReadyToRun"

class ExampleCPPFederate
{
public:
  // public methods //
  ExampleCPPFederate (void);
  virtual ~ExampleCPPFederate (void);

  void runFederate( const std::string & federateName );

private:
  void initializeHandles();
  void waitForUser();
  void enableTimePolicy();
  void publishAndSubscribe();
  RTI::ObjectHandle registerObject();
  void updateAttributeValues( RTI::ObjectHandle objectHandle );
  void sendInteraction();
  void advanceTime( double timestep );
  void deleteObject( RTI::ObjectHandle objectHandle );

  std::auto_ptr <RTI::RTIambassador> rtiamb_;
  std::auto_ptr <ExampleFedAmb> fedamb_;

  // fom handles //
  RTI::ObjectClassHandle      aHandle;
  RTI::AttributeHandle        aaHandle;
  RTI::AttributeHandle        abHandle;
  RTI::AttributeHandle        acHandle;
  RTI::InteractionClassHandle xHandle;
  RTI::ParameterHandle        xaHandle;
  RTI::ParameterHandle        xbHandle;
};

#endif /*EXAMPLECPPFEDERATE_H_*/
