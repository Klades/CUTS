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

#ifndef _CUTS_BE_CCM_CCP_TRAITS_H_
#define _CUTS_BE_CCM_CCP_TRAITS_H_

#include "CCM_export.h"
#include <iosfwd>

// Forward decl.
struct CUTS_BE_IDL_Node;

namespace CUTS_BE_CCM
{
namespace Cpp
{

/**
 * @class Traits
 *
 * Backend traits for integrating different distributed architectures
 * into CCM.
 */
class CUTS_BE_CCM_Export Traits
{
public:
  virtual ~Traits (void);

  virtual bool generate_default_servant (void);

  virtual const char * stub_base_project (void);

  virtual const char * svnt_base_project (void);

  virtual void write_top (std::ostream &, const CUTS_BE_IDL_Node & );

  virtual void write_stub_source_files (std::ostream &, const CUTS_BE_IDL_Node &);

  virtual void write_stub_after (std::ostream &, const CUTS_BE_IDL_Node &);

  virtual void write_idl_gen_files (std::ostream &, const CUTS_BE_IDL_Node &);
};

}
}

#if defined (__CUTS_INLINE__)
#include "Traits.inl"
#endif

#endif  // !defined _CUTS_BE_CCM_TRAITS_H_
