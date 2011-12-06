// $Id$

#include "ExampleCPPFederate.h"
#include <memory>

int main (int argc, char * argv [])
{
  // check to see if we have a federate name
  std::string federateName ("exampleFederate");

  if (argc > 1)
    federateName = argv[1];

  // create and run the federate
  std::auto_ptr <ExampleCPPFederate> federate (new ExampleCPPFederate ());
  federate->runFederate (federateName.c_str ());

  // clean up
  return 0;
}
