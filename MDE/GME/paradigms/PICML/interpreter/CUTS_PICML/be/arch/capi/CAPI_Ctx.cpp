// $Id$

#include "CAPI_Ctx.h"

namespace CUTS_BE_Capi
{
//
// Context
//
Context::Context (void)
{
  this->env_seen_.insert (std::make_pair ("init", false));
  this->env_seen_.insert (std::make_pair ("activate", false));
  this->env_seen_.insert (std::make_pair ("deactivate", false));
  this->env_seen_.insert (std::make_pair ("fini", false));
}

//
// reset
//
void Context::reset (void)
{
  // Reset the environment flags.
  Context::Env_Seen_Map::iterator
    iter = this->env_seen_.begin (), iter_end = this->env_seen_.end ();

  for ( ; iter != iter_end; iter ++)
    iter->second = false;

  // Reset the event ports.
  this->sinks_.clear ();
  this->sources_.clear ();

  // Reset the periodic event collection.
  this->periodics_.clear ();
}

//
// generate_required_method_impl
//
void Context::
generate_required_method_impl (const std::string & method)
{
  if (method == "init")
  {
    Context::Event_Port_Map::const_iterator
      iter = this->sources_.begin (), iter_end = this->sources_.end ();

    for ( ; iter != iter_end; ++ iter)
    {
      this->source_
        << "// creation of source: " << iter->first << std::endl
        << "this." << iter->first << "_ = new "
        << iter->first << "Source (this);"
        << "this.registerInfoSequence (this." << iter->first << "_);"
        << std::endl;
    }

    iter = this->sinks_.begin ();
    iter_end = this->sinks_.end ();

    for ( ; iter != iter_end; ++ iter)
    {
      this->source_
        << "// creation of sink: " << iter->first << std::endl
        << "this." << iter->first << "_ = new "
        << iter->first << "Sink (this);"
        << "this.registerInfoSequence (this." << iter->first << "_);"
        << std::endl;
    }
  }
  else if (method == "activate")
  {
    Context::Periodic_Map::const_iterator
      iter = this->periodics_.begin (), iter_end = this->periodics_.end ();
    std::string name;

    for ( ; iter != iter_end; ++ iter)
    {
      name = iter->second.name ();

      this->source_  << "this." << name << "_.setHertz ("
                      << iter->second.Hertz () << ");"
                      << "this." << name << "_.scheduleNextTimeout ();";
    }
  }
  else if (method == "deactivate")
  {
    Context::Periodic_Map::const_iterator
      iter = this->periodics_.begin (), iter_end = this->periodics_.end ();

    for ( ; iter != iter_end; ++ iter)
      this->source_ << "this." << iter->first << "_.cancel ();";
  }
}

//
// generate_throws_signature
//
void Context::generate_throws_signature (const std::string & method)
{

}
}
