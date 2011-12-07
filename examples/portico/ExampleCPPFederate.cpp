// $Id$

#include <string>
#include <iostream>

#include "RTI.hh"
#include "fedtime.hh"

#include "ExampleFedAmb.h"
#include "ExampleCPPFederate.h"

using namespace std;

ExampleCPPFederate::ExampleCPPFederate (void)
{
}

ExampleCPPFederate::~ExampleCPPFederate (void)
{
}

///////////////////////////////////////////////////////////////////////////
////////////////////////// Main Simulation Method /////////////////////////
///////////////////////////////////////////////////////////////////////////

//
// runFederate
//
void ExampleCPPFederate::runFederate (const std::string & federateName )
{
  /////////////////////////////////
  // 1. create the RTIambassador //
  /////////////////////////////////
  this->rtiamb_.reset (new RTI::RTIambassador());

  //////////////////////////////////////////
  // 2. create and join to the federation //
  //////////////////////////////////////////
  // create
  // NOTE: some other federate may have already created the federation,
  //       in that case, we'll just try and join it
  try
  {
    this->rtiamb_->createFederationExecution ("ExampleFederation", "testfom.fed");
    cout << "Created Federation" << endl;
  }
  catch (const RTI::FederationExecutionAlreadyExists & )
  {
    cout << "Didn't create federation, it already existed" << endl;
  }

  ////////////////////////////
  // 3. join the federation //
  ////////////////////////////
  // create the federate ambassador and join the federation
  this->fedamb_.reset (new ExampleFedAmb ());
  this->rtiamb_->joinFederationExecution (federateName.c_str (),
                                          "ExampleFederation",
                                          this->fedamb_.get ());

  cout << "Joined Federation as " << federateName << endl;

  // initialize the handles - have to wait until we are joined
  initializeHandles();

  ////////////////////////////////
  // 4. announce the sync point //
  ////////////////////////////////
  // announce a sync point to get everyone on the same page. if the point
  // has already been registered, we'll get a callback saying it failed,
  // but we don't care about that, as long as someone registered it
  this->rtiamb_->registerFederationSynchronizationPoint( READY_TO_RUN, "" );
  while( fedamb_->isAnnounced == false )
  {
    this->rtiamb_->tick();
  }

  // WAIT FOR USER TO KICK US OFF
  // So that there is time to add other federates, we will wait until the
  // user hits enter before proceeding. That was, you have time to start
  // other federates.
  waitForUser();

  ///////////////////////////////////////////////////////
  // 5. achieve the point and wait for synchronization //
  ///////////////////////////////////////////////////////
  // tell the RTI we are ready to move past the sync point and then wait
  // until the federation has synchronized on
  this->rtiamb_->synchronizationPointAchieved( READY_TO_RUN );
  cout << "Achieved sync point: " << READY_TO_RUN << ", waiting for federation..." << endl;
  while( fedamb_->isReadyToRun == false )
  {
    this->rtiamb_->tick();
  }

  /////////////////////////////
  // 6. enable time policies //
  /////////////////////////////
  // in this section we enable/disable all time policies
  // note that this step is optional!
  enableTimePolicy();
  cout << "Time Policy Enabled" << endl;

  //////////////////////////////
  // 7. publish and subscribe //
  //////////////////////////////
  // in this section we tell the RTI of all the data we are going to
  // produce, and all the data we want to know about
  publishAndSubscribe();
  cout << "Published and Subscribed" << endl;

  /////////////////////////////////////
  // 8. register an object to update //
  /////////////////////////////////////
  RTI::ObjectHandle objectHandle = registerObject();
  cout << "Registered Object, handle=" << objectHandle << endl;

  ////////////////////////////////////
  // 9. do the main simulation loop //
  ////////////////////////////////////
  // here is where we do the meat of our work. in each iteration, we will
  // update the attribute values of the object we registered, and will
  // send an interaction.
  int i;
  for( i = 0; i < 20; i++ )
  {
    // 9.1 update the attribute values of the instance //
    updateAttributeValues( objectHandle );

    // 9.2 send an interaction
    sendInteraction();

    // 9.3 request a time advance and wait until we get it
    advanceTime( 1.0 );
    cout << "Time Advanced to " << fedamb_->federateTime << endl;
  }

  //////////////////////////////////////
  // 10. delete the object we created //
  //////////////////////////////////////
  deleteObject( objectHandle );
  cout << "Deleted Object, handle=" << objectHandle << endl;

  ////////////////////////////////////
  // 11. resign from the federation //
  ////////////////////////////////////
  this->rtiamb_->resignFederationExecution( RTI::NO_ACTION );
  cout << "Resigned from Federation" << endl;

  ////////////////////////////////////////
  // 12. try and destroy the federation //
  ////////////////////////////////////////
  // NOTE: we won't die if we can't do this because other federates
  //       remain. in that case we'll leave it for them to clean up
  try
  {
    this->rtiamb_->destroyFederationExecution( "ExampleFederation" );
    cout << "Destroyed Federation" << endl;
  }
  catch( RTI::FederationExecutionDoesNotExist dne )
  {
    cout << "No need to destroy federation, it doesn't exist" << endl;
  }
  catch( RTI::FederatesCurrentlyJoined fcj )
  {
    cout << "Didn't destroy federation, federates still joined" << endl;
  }

  //////////////////
  // 13. clean up //
  //////////////////
  this->rtiamb_.reset ();
}

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Helper Methods ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*
* This method will get all the relevant handle information from the RTIambassador
*/
void ExampleCPPFederate::initializeHandles()
{
  this->aHandle  = this->rtiamb_->getObjectClassHandle( "ObjectRoot.A" );
  this->aaHandle = this->rtiamb_->getAttributeHandle( "aa", aHandle );
  this->abHandle = this->rtiamb_->getAttributeHandle( "ab", aHandle );
  this->acHandle = this->rtiamb_->getAttributeHandle( "ac", aHandle );

  this->xHandle  = this->rtiamb_->getInteractionClassHandle( "InteractionRoot.X" );
  this->xaHandle = this->rtiamb_->getParameterHandle( "xa", xHandle );
  this->xbHandle = this->rtiamb_->getParameterHandle( "xb", xHandle );
}

/*
* Blocks until the user hits enter
*/
void ExampleCPPFederate::waitForUser()
{
  cout << " >>>>>>>>>> Press Enter to Continue <<<<<<<<<<" << endl;
  string line;
  getline( cin, line );
}

/*
* This method will attempt to enable the various time related properties for
* the federate
*/
void ExampleCPPFederate::enableTimePolicy()
{
  ////////////////////////////
  // enable time regulation //
  ////////////////////////////
  RTIfedTime federateTime = fedamb_->federateTime;
  RTIfedTime lookahead = fedamb_->federateLookahead;
  this->rtiamb_->enableTimeRegulation( federateTime, lookahead );

  // tick until we get the callback
  while( fedamb_->isRegulating == false )
  {
    this->rtiamb_->tick();
  }

  /////////////////////////////
  // enable time constrained //
  /////////////////////////////
  this->rtiamb_->enableTimeConstrained();

  // tick until we get the callback
  while( fedamb_->isConstrained == false )
  {
    this->rtiamb_->tick();
  }
}

/*
* This method will inform the RTI about the types of data that the federate will
* be creating, and the types of data we are interested in hearing about as other
* federates produce it.
*/
void ExampleCPPFederate::publishAndSubscribe()
{
  ////////////////////////////////////////////
  // publish all attributes of ObjectRoot.A //
  ////////////////////////////////////////////
  // before we can register instance of the object class ObjectRoot.A and
  // update the values of the various attributes, we need to tell the RTI
  // that we intend to publish this information

  // package the information into a handle set
  RTI::AttributeHandleSet *attributes = RTI::AttributeHandleSetFactory::create( 3 );
  attributes->add( this->aaHandle );
  attributes->add( this->abHandle );
  attributes->add( this->acHandle );

  // do the actual publication
  this->rtiamb_->publishObjectClass( this->aHandle, *attributes );

  /////////////////////////////////////////////////
  // subscribe to all attributes of ObjectRoot.A //
  /////////////////////////////////////////////////
  // we also want to hear about the same sort of information as it is
  // created and altered in other federates, so we need to subscribe to it
  this->rtiamb_->subscribeObjectClassAttributes( this->aHandle, *attributes );

  /////////////////////////////////////////////////////
  // publish the interaction class InteractionRoot.X //
  /////////////////////////////////////////////////////
  // we want to send interactions of type InteractionRoot.X, so we need
  // to tell the RTI that we're publishing it first. We don't need to
  // inform it of the parameters, only the class, making it much simpler

  // do the publication
  this->rtiamb_->publishInteractionClass( this->xHandle );

  ////////////////////////////////////////////////////
  // subscribe to the InteractionRoot.X interaction //
  ////////////////////////////////////////////////////
  // we also want to receive other interaction of the same type that are
  // sent out by other federates, so we have to subscribe to it first
  this->rtiamb_->subscribeInteractionClass( this->xHandle );

  // clean up
  delete attributes;
}

/*
* This method will register an instance of the class ObjectRoot.A and will
* return the federation-wide unique handle for that instance. Later in the
* simulation, we will update the attribute values for this instance
*/
RTI::ObjectHandle ExampleCPPFederate::registerObject()
{
  return this->rtiamb_->registerObjectInstance( this->rtiamb_->getObjectClassHandle("ObjectRoot.A") );
}

/*
* This method will update all the values of the given object instance. It will
* set each of the values to be a string which is equal to the name of the
* attribute plus the current time. eg "aa:10.0" if the time is 10.0.
* <p/>
* Note that we don't actually have to update all the attributes at once, we
* could update them individually, in groups or not at all!
*/
void ExampleCPPFederate::updateAttributeValues( RTI::ObjectHandle objectHandle )
{
  ///////////////////////////////////////////////
  // create the necessary container and values //
  ///////////////////////////////////////////////
  // create the collection to store the values in, as you can see
  // this is quite a lot of work
  std::auto_ptr <RTI::AttributeHandleValuePairSet>
    attributes (RTI::AttributeSetFactory::create( 3 ));

  // generate the new values
  // we use EncodingHelpers to make things nice friendly for both Java and C++
  char aaValue[16], abValue[16], acValue[16];
  sprintf( aaValue, "aa:%f", fedamb_->federateTime );
  sprintf( abValue, "ab:%f", fedamb_->federateTime );
  sprintf( acValue, "ac:%f", fedamb_->federateTime );
  attributes->add( aaHandle, aaValue, (RTI::ULong)strlen(aaValue)+1 );
  attributes->add( abHandle, abValue, (RTI::ULong)strlen(abValue)+1 );
  attributes->add( acHandle, acValue, (RTI::ULong)strlen(acValue)+1 );

  //////////////////////////
  // do the actual update //
  //////////////////////////
  this->rtiamb_->updateAttributeValues( objectHandle, *attributes, "hi!" );

  // note that if you want to associate a particular timestamp with the
  // update. here we send another update, this time with a timestamp:
  RTIfedTime time = fedamb_->federateTime + fedamb_->federateLookahead;
  this->rtiamb_->updateAttributeValues( objectHandle, *attributes, time, "hi!" );
}

/*
* This method will send out an interaction of the type InteractionRoot.X. Any
* federates which are subscribed to it will receive a notification the next time
* they tick(). Here we are passing only two of the three parameters we could be
* passing, but we don't actually have to pass any at all!
*/
void ExampleCPPFederate::sendInteraction()
{
  ///////////////////////////////////////////////
  // create the necessary container and values //
  ///////////////////////////////////////////////
  // create the collection to store the values in
  std::auto_ptr <RTI::ParameterHandleValuePairSet>
    parameters (RTI::ParameterSetFactory::create( 2 ));

  // generate the new values
  char xaValue[16], xbValue[16];
  sprintf( xaValue, "xa:%f", fedamb_->federateTime );
  sprintf( xbValue, "xb:%f", fedamb_->federateTime );
  parameters->add( xaHandle, xaValue, (RTI::ULong)strlen(xaValue)+1 );
  parameters->add( xbHandle, xbValue, (RTI::ULong)strlen(xbValue)+1 );

  //////////////////////////
  // send the interaction //
  //////////////////////////
  this->rtiamb_->sendInteraction( xHandle, *parameters, "hi!" );

  // if you want to associate a particular timestamp with the
  // interaction, you will have to supply it to the RTI. Here
  // we send another interaction, this time with a timestamp:
  RTIfedTime time = fedamb_->federateTime + fedamb_->federateLookahead;
  this->rtiamb_->sendInteraction( xHandle, *parameters, time, "hi!" );
}

/*
* This method will request a time advance to the current time, plus the given
* timestep. It will then wait until a notification of the time advance grant
* has been received.
*/
void ExampleCPPFederate::advanceTime( double timestep )
{
  // request the advance
  fedamb_->isAdvancing = true;
  RTIfedTime newTime = (fedamb_->federateTime + timestep);
  this->rtiamb_->timeAdvanceRequest( newTime );

  // wait for the time advance to be granted. ticking will tell the
  // LRC to start delivering callbacks to the federate
  while( fedamb_->isAdvancing )
  {
    this->rtiamb_->tick();
  }
}

/*
* This method will attempt to delete the object instance of the given
* handle. We can only delete objects we created, or for which we own the
* privilegeToDelete attribute.
*/
void ExampleCPPFederate::deleteObject( RTI::ObjectHandle objectHandle )
{
  this->rtiamb_->deleteObjectInstance( objectHandle, NULL );
}
