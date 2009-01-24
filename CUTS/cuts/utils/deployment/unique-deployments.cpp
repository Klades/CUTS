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

int parse_args (int argc, char * argv [], options_t & opts)
{
  const char * optstr = "n:";
  ACE_Get_Opt get_opt (argc, argv, optstr);

  char ch;

  while ((ch = get_opt ()) != EOF)
  {
    switch (ch)
    {
    case 'n':
      opts.random_select_ = ACE_OS::atoi (get_opt.opt_arg ());
      break;
    }
  }

  return 0;
}

struct print_host
{
  typedef void result_type;

  typedef CUTS_Host_T <std::string> host_type;

  print_host (std::ostream & out)
    : out_ (out)
  {
  }

  void operator () (const host_type & host)
  {
    host_type::const_iterator iter;

    for (iter = host.begin (); iter != host.end (); ++ iter)
      this->out_ << "  host." << *iter << "=" << host.name () << std::endl;
  }

private:
  std::ostream & out_;
};

struct print
{
  typedef CUTS_Host_T <std::string> host_type;

  typedef CUTS_Unique_Deployment_T <host_type> unique_deployment;

  typedef unique_deployment::deployment_type deployment_type;

  typedef void result_type;

  print (std::ostream & out, const unique_deployment & unique)
    : out_ (out),
      unique_ (unique)
  {

  }

  void operator () (size_t index)
  {
    // Get the unique deployment.
    deployment_type deployment = this->unique_[index];

    // Generate the deployment.
    this->out_ << "config (UniqueDeployment" << index << ".cdp) {"
               << std::endl;

    std::for_each (deployment.begin (),
                   deployment.end (),
                   boost::bind (print_host (this->out_), _1));

    this->out_ << "}" << std::endl
               << std::endl;
  }

private:
  std::ostream & out_;

  const unique_deployment & unique_;
};

//
// main
//
int main (int argc, char * argv [])
{
  options_t opts;

  // Parse the command-line options.
  if (::parse_args (argc, argv, opts) != 0)
    return 1;

  typedef CUTS_Host_T <std::string> host_type;
  CUTS_Unique_Deployment_T <host_type> unique_deployments;

  // Initalize the domain.
  CUTS_Domain_T <host_type> domain;
  domain.insert (host_type ("node-1"));
  domain.insert (host_type ("node-2"));
  domain.insert (host_type ("node-3"));

  // Initialize the unique deployment generator.
  unique_deployments.init (domain);

  unique_deployments.calculate ("inst1");
  unique_deployments.calculate ("inst2");
  unique_deployments.calculate ("inst3");
  unique_deployments.calculate ("inst4");
  unique_deployments.calculate ("inst5");

  std::cerr << "Number of unique deployments : "
            << unique_deployments.size () << std::endl;

  // Seed the random number generator
  ACE_OS::srand (ACE_OS::time ());

  std::set <size_t> selection;

  while (selection.size () < opts.random_select_)
  {
    int index = ACE_OS::rand () % unique_deployments.size ();
    selection.insert (index);
  }

  std::for_each (selection.begin (),
                 selection.end (),
                 boost::bind (print (std::cout, unique_deployments), _1));

  return 0;
}
