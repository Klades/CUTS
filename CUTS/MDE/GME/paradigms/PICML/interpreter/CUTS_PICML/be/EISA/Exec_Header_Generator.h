// -*- C++ -*-

//=============================================================================
/**
 * @file      Exec_Header_Generator.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CIAO_EXEC_HEADER_TRAITS_H_
#define _CUTS_CIAO_EXEC_HEADER_TRAITS_H_

#include "Header_Generator.h"
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"

/**
 * @class CUTS_EISA_Exec_Header_Generator
 *
 * CIAO header file generator for the CUTS-PICML backend.
 */
class CUTS_EISA_Exec_Header_Generator :
  public CUTS_EISA_Header_Generator
{
public:
  /// Type definition of the super class.
  typedef CUTS_EISA_Header_Generator _super;

  CUTS_EISA_Exec_Header_Generator (void);

  virtual ~CUTS_EISA_Exec_Header_Generator (void);

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

  virtual void write_variable (
    const PICML::Variable & variable);

  virtual void write_PeriodicEvent_variable (
    const PICML::PeriodicEvent & periodic);

  virtual void write_worker_variable (
    const PICML::WorkerType & type,
    const PICML::Worker & worker);

  virtual void write_ReadonlyAttribute_variable (
    const PICML::ReadonlyAttribute & readonly);

  virtual void write_environment_begin (
    const PICML::Component & component);

  virtual void write_environment_end (
    const PICML::Component & component);

private:
  /// Type definition for pointer-to-methods to environment methods.
  typedef void (CUTS_EISA_Exec_Header_Generator::
    *Environment_Method) (const PICML::Component &);

  /// Type definition for environment jump table.
  typedef std::map <std::string,
                    Environment_Method> Environment_Table;

  /// Global jump table for the environment writers.
  static Environment_Table env_table_;

  bool has_postactivate_;
};

// Singleton definition.
#define EISA_EXEC_HEADER_GENERATOR() \
  ACE_Singleton <CUTS_EISA_Exec_Header_Generator, \
                 ACE_Null_Mutex>::instance ()

#endif  // !defined _CUTS_CIAO_EXEC_HEADER_TRAITS_H_
