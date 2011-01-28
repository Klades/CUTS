// -*- C++ -*-

//=============================================================================
/**
 * @file            Traits.h
 *
 * $Id$
 *
 * @author          James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CCM_RTIDDS_TRAITS_H_
#define _CUTS_BE_CCM_RTIDDS_TRAITS_H_

#include <string>
#include "../Traits.h"

#include "BE_RTIDDS_export.h"


namespace CUTS_BE_RTIDDS
{

/**
 * @class Traits
 *
 * The CCM traits for OpenSplice.
 */
class CUTS_BE_RTIDDS_Export Traits :
  public CUTS_BE_CCM::Cpp::Traits
{
public:
  Traits (void);

  /// Destructor.
  virtual ~Traits (void);

  virtual bool generate_default_servant (void);

  virtual const char * stub_base_project (void);

  virtual const char * svnt_base_project (void);

  virtual void write_top (std::ostream &, const CUTS_BE_IDL_Node & );

  virtual void write_stub_source_files (std::ostream &, const CUTS_BE_IDL_Node &);

  virtual void write_stub_after (std::ostream &, const CUTS_BE_IDL_Node &);
};

}

#if defined (__CUTS_INLINE__)
#include "Traits.inl"
#endif

#endif  // !defined _CUTS_BE_CCM_RTIDDS_TRAITS_H_
