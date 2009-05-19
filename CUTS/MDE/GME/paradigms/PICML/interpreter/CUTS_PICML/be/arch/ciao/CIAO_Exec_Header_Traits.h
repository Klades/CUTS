// -*- C++ -*-

//=============================================================================
/**
 * @file      CIAO_Exec_Header_Traits.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CIAO_EXEC_HEADER_TRAITS_H_
#define _CUTS_CIAO_EXEC_HEADER_TRAITS_H_

#include "CIAO_Header_Traits.h"
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"

/**
 * @class CUTS_CIAO_Exec_Header_Traits
 *
 * CIAO header file generator for the CUTS-PICML backend.
 */
class CUTS_CIAO_Exec_Header_Traits : public CUTS_CIAO_Header_Traits
{
public:
  /// Type definition of the super class.
  typedef CUTS_CIAO_Header_Traits _super;

  CUTS_CIAO_Exec_Header_Traits (void);

  virtual ~CUTS_CIAO_Exec_Header_Traits (void);

  virtual bool open_file (
    const PICML::ComponentImplementationContainer & container);

  virtual void write_prologue (
    const PICML::ComponentImplementationContainer & container);

  virtual void write_epilogue (
    const PICML::ComponentImplementationContainer & container);

  void write_impl_begin (
    const PICML::MonolithicImplementation & monoimpl,
    const PICML::Component & type);

  void write_impl_end (
    const PICML::MonolithicImplementation &,
    const PICML::Component & type);

  virtual void write_environment_method_begin (
    const PICML::MultiInputAction & action);

  virtual void write_variables_begin (
    const PICML::Component & component);

  virtual void write_variable (
    const PICML::Variable & variable);

  virtual void write_PeriodicEvent_variable (
    const PICML::PeriodicEvent & periodic);

  virtual void write_worker_variable (
    const PICML::WorkerType & type,
    const PICML::Worker & worker);

  virtual void write_ReadonlyAttribute_variable (
    const PICML::ReadonlyAttribute & readonly);

  virtual void write_InEventPort_begin (
    const PICML::InEventPort & sink,
    const std::vector <PICML::Property> & properties);

  virtual void write_InEventPort_end (
    const PICML::InEventPort & sink,
    const std::vector <PICML::Property> & properties);

  virtual void write_environment_end (
    const PICML::Component & component);

private:
  void write_event_handler_variable (
    const std::map <std::string, std::string>::value_type &);

  /// Type definition for pointer-to-methods to environment methods.
  typedef void (CUTS_CIAO_Exec_Header_Traits::
    *Environment_Method) (const PICML::Component &);

  /// Type definition for environment jump table.
  typedef std::map <std::string,
                    Environment_Method> Environment_Table;

  /// Global jump table for the environment writers.
  static Environment_Table env_table_;

  std::map <std::string, std::string> asynch_events_;

  bool has_activate_;
};

// Singleton definition.
#define CIAO_EXEC_HEADER_GENERATOR() \
  ACE_Singleton <CUTS_CIAO_Exec_Header_Traits, \
                 ACE_Null_Mutex>::instance ()

#endif  // !defined _CUTS_CIAO_EXEC_HEADER_TRAITS_H_
