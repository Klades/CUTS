// $Id$

#include "StdAfx.h"
#include "Isislab_Emulation.h"
#include "boost/bind.hpp"
#include "Utils/Utils.h"
#include <algorithm>
#include <sstream>
#include <iostream>

//
// CUTS_Isislab_Emulation
//
CUTS_Isislab_Emulation::
CUTS_Isislab_Emulation (const std::string & outdir)
: outdir_ (outdir)
{

}

//
// ~CUTS_Isislab_Emulation
//
CUTS_Isislab_Emulation::~CUTS_Isislab_Emulation (void)
{

}

//
// Visit_RootFolder
//
void CUTS_Isislab_Emulation::
Visit_RootFolder (const PICML::RootFolder & root)
{
  // Save the name of the root folder.
  this->project_name_ = root.name ();

  // Visit all the target folders in the project.
  typedef std::vector <PICML::Targets> Target_Set;
  Target_Set targets = root.Targets_children ();

  std::for_each (targets.begin (),
                 targets.end (),
                 boost::bind (&Target_Set::value_type::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_Targets
//
void CUTS_Isislab_Emulation::
Visit_Targets (const PICML::Targets & targets)
{
  typedef std::vector <PICML::Domain> Domain_Set;
  Domain_Set domains = targets.Domain_children ();

  std::for_each (domains.begin (),
                 domains.end (),
                 boost::bind (&Domain_Set::value_type::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_Domain
//
void CUTS_Isislab_Emulation::
Visit_Domain (const PICML::Domain & domain)
{
  std::string name = domain.name ();

  // Construct the name of the NS file
  std::ostringstream filename;
  filename << this->outdir_ << "\\" << name << ".ns";

  // Open a new output file for generating the NS script.
  this->outfile_.open (filename.str ().c_str ());

  if (this->outfile_.is_open ())
  {
    // Write the beginning of the script.
    this->outfile_
      << "# Auto-generate NS script" << std::endl
      << "set ns [new Simulator]" << std::endl
      << "source tb_compat.tcl" << std::endl
      << std::endl;

    // Create the UUID for the emulation.
    std::string uuid = Utils::CreateUuid ();

    this->outfile_
      << "set opt(TEST_UUID) \"" << uuid << "\"" << std::endl
      << std::endl;

    // Visit all the node in this domain.
    typedef std::vector <PICML::Node> Node_Set;
    Node_Set nodes = domain.Node_children ();

    std::for_each (nodes.begin (),
                  nodes.end (),
                  boost::bind (&Node_Set::value_type::Accept,
                                _1,
                                boost::ref (*this)));

    // Write the end of the script.
    this->outfile_
      << "# configure the control node" << std::endl
      << "set control [$ns node]" << std::endl
      << "tb-set-node-os $control FC6-STD" << std::endl
      << "tb-set-hardware $control pc8832" << std::endl
      << std::endl
      << "tb-set-node-startcmd $control /proj/GUTS/scripts/naomi-startup.sh" << std::endl
      << std::endl
      << "# set the sync server for the system" << std::endl
      << "tb-set-sync-server $control" << std::endl
      << std::endl
      << "# use static routing" << std::endl
      << "$ns rtproto Static" << std::endl
      << std::endl
      << "# start the experiment" << std::endl
      << "$ns run" << std::endl;

    // Close the output file if it is open.
    this->outfile_.close ();
  }
}

//
// Visit_Node
//
void CUTS_Isislab_Emulation::
Visit_Node (const PICML::Node & node)
{
  std::string name = node.name ();

  this->outfile_
    << "# set configuration for node " << name << std::endl
    << "set " << name << " [$ns node]" << std::endl
    << "tb-set-node-os $" << name << " FC6-STD" << std::endl
    << "tb-set-hardware $" << name << " pc8832" << std::endl
    << std::endl
    << "# set start command for node " << name << std::endl
    << "tb-set-node-startcmd $" << name
    << " \"/proj/GUTS/scripts/client-startup-autorun.sh "
    << this->project_name_ << "\"" << std::endl
    << std::endl;
}
