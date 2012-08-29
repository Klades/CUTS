// -*- C++ -*-

//=============================================================================
/**
 * @file            CIAO_Traits.h
 *
 * $Id$
 *
 * @author          James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CCM_CIAO_TRAITS_H_
#define _CUTS_BE_CCM_CIAO_TRAITS_H_

#include "../Traits.h"
#include <set>

#include "BE_CIAO_export.h"

namespace CUTS_BE_CIAO
{

/**
 * @class Traits
 *
 * The CCM traits for OpenSplice.
 */
class CUTS_BE_CIAO_Export Traits :
  public CUTS_BE_CCM::Cpp::Traits
{
public:
  /// Destructor.
  virtual ~Traits (void);

  virtual bool generate_default_servant (void);

  virtual const char * stub_base_project (void);
  virtual const char * skel_base_project (void);
  virtual const char * svnt_base_project (void);

  virtual void write_top (std::ostream &, const CUTS_BE_IDL_Node & );

  virtual void write_stub_source_files (std::ostream &, const CUTS_BE_IDL_Node &);

  virtual void write_stub_after (std::ostream &, const CUTS_BE_IDL_Node &);
  virtual void write_exec_idl_files (std::ostream & proj, const CUTS_BE_IDL_Node & node);
  virtual void write_exec_source_files (std::ostream &, const CUTS_BE_IDL_Node &);

private:
  std::set <std::string> stub_after_;
};

}

#if defined (__CUTS_INLINE__)
#include "CIAO_Traits.inl"
#endif

#endif  // !defined _CUTS_BE_CCM_TRAITS_H_
