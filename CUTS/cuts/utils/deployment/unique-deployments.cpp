// $Id$

#include <algorithm>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>
#include "ace/Get_Opt.h"
#include "ace/OS_NS_stdlib.h"
#include "ace/OS_NS_time.h"
#include "boost/bind.hpp"
#include "Host_T.h"
#include "Unique_Deployment_T.h"

struct options_t
{
  options_t (void)
    : random_select_ (0)
  {

  }

  size_t random_select_;
};

//
// main
//
int main (int argc, char * argv [])
{
  typedef CUTS_Host_T <std::string> host_type;
  CUTS_Unique_Deployment_T <host_type> unique_deployments;

  // Initalize the domain.
  CUTS_Domain_T <host_type> domain;
  domain.insert (host_type ("Host1"));
  domain.insert (host_type ("Host2"));
  domain.insert (host_type ("Host3"));

  // Initialize the unique deployment generator.
  unique_deployments.init (domain);

  unique_deployments.calculate ("inst1");
  unique_deployments.calculate ("inst2");
  unique_deployments.calculate ("inst3");
  unique_deployments.calculate ("inst4");
  unique_deployments.calculate ("inst5");
  unique_deployments.calculate ("inst6");
  unique_deployments.calculate ("inst7");

  std::cerr << "Number of unique deployments : "
            << unique_deployments.size () << std::endl;

  //// Seed the random number generator
  //ACE_OS::srand (ACE_OS::time ());

  //std::set <size_t> selection;

  //while (selection.size () < 20)
  //{
  //  int index = ACE_OS::rand () % unique_deployments.size ();
  //  selection.insert (index);
  //}

  //for (std::set <size_t>::iterator iter = selection.begin ();
  //     iter != selection.end ();
  //     ++ iter)
  //{
  //  print <std::string> (std::cerr, *iter, unique_deployments[*iter]);
  //}

  return 0;
}
