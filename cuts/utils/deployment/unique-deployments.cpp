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
#include "ace/OS_NS_unistd.h"
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

struct is_collocated
{
  is_collocated (std::set <std::string> & instances)
    : instances_ (instances),
      result_ (false)
  {

  }

  is_collocated (const is_collocated & src)
    : instances_ (src.instances_),
      result_ (src.result_)
  {

  }

  const is_collocated & operator = (const is_collocated & rhs)
  {
    this->instances_ = rhs.instances_;
    this->result_ = rhs.result_;

    return *this;
  }

  void operator () (const CUTS_Host_T <std::string> & host)
  {
    size_t count = 0;

    std::set <std::string>::const_iterator iter = this->instances_.begin ();

    for ( ; iter != this->instances_.end (); ++ iter)
    {
      if (host.contains (*iter))
        ++ count;
    }

    this->result_ |= count > 1 ? true : false;
  }

  bool result (void) const
  {
    return this->result_;
  }

private:
  std::set <std::string> & instances_;

  bool result_;
};

int parse_args (int argc, char * argv [], options_t & opts)
{
  const char * optstr = "n:";
  ACE_Get_Opt get_opt (argc, argv, optstr);

  int ch;

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
  unique_deployments.calculate ("inst6");
  unique_deployments.calculate ("inst7");
  unique_deployments.calculate ("inst8");
  unique_deployments.calculate ("inst9");
  unique_deployments.calculate ("inst10");
  unique_deployments.calculate ("inst11");
  unique_deployments.calculate ("inst12");

  // Seed the random number generator
  std::set <size_t> selection;

  std::set <std::string> collocation;
  collocation.insert ("inst10");
  collocation.insert ("inst11");
  collocation.insert ("inst12");

  while (selection.size () < opts.random_select_)
  {
    int index = ACE_OS::rand () % unique_deployments.size ();
    is_collocated collocation_test (collocation);

    if (!std::for_each (unique_deployments[index].begin (),
                        unique_deployments[index].end (),
                        collocation_test).result ())
    {
      selection.insert (index);
    }
  }

  std::for_each (selection.begin (),
                 selection.end (),
                 boost::bind (print (std::cout, unique_deployments), _1));

  return 0;
}
