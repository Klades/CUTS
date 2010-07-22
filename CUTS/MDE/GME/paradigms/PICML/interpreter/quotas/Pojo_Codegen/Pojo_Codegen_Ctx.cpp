// $Id$

#include "stdafx.h"
#include "Pojo_Codegen_Ctx.h"
#include <algorithm>

namespace Quotas
{
namespace Pojo
{
namespace Codegen
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

/**
 * @struct activate_periodic_t
 *
 * Functor for activating periodic tasks contained in a
 * component.
 *
 * @todo This functor/functionality should be pushed down into
 *       the base context to ensure all Java-based code generators
 *       use it.
 */
struct activate_periodic_t
{
  activate_periodic_t (std::ofstream & out)
    : out_ (out)
  {
  }

  void operator () (const Context::Periodic_Map::value_type & v) const
  {
    const std::string name (v.second.name ());

    this->out_ << "this." << name << "_.setHertz (" << v.second.Hertz () << ");"
               << "this." << name << "_.scheduleNextTimeout ();";
  }

private:
  /// Target output stream.
  std::ofstream & out_;
};

/**
 * @struct activate_periodic_t
 *
 * Functor for deactivating periodic tasks contained in a
 * component.
 *
 * @todo This functor/functionality should be pushed down into
 *       the base context to ensure all Java-based code generators
 *       use it.
 */
struct deactivate_periodic_t
{
  deactivate_periodic_t (std::ofstream & out)
    : out_ (out)
  {
  }

  void operator () (const Context::Periodic_Map::value_type & v) const
  {
    const std::string name (v.second.name ());
    this->out_ << "this." << name << "_.cancel ();";
  }

private:
  /// Target output stream.
  std::ofstream & out_;
};

//
// generate_required_method_impl
//
void Context::
generate_required_method_impl (const std::string & method)
{
  if (method == "init")
  {
    // do something here...
  }
  else if (method == "activate")
  {
    std::for_each (this->periodics_.begin (),
                   this->periodics_.end (),
                   activate_periodic_t (this->source_));
  }
  else if (method == "deactivate")
  {
    std::for_each (this->periodics_.begin (),
                   this->periodics_.end (),
                   deactivate_periodic_t (this->source_));
  }
}

//
// generate_throws_signature
//
void Context::generate_throws_signature (const std::string & method)
{

}


}
}
}
