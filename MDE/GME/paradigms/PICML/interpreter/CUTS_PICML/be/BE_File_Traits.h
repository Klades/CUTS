// -*- C++ -*-

//=============================================================================
/**
 * @file        BE_File_Traits.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_FILE_TRAITS_H_
#define _CUTS_BE_FILE_TRAITS_H_

#include "BE_Traits.h"
#include <fstream>
#include <memory>

/**
 * @class CUTS_BE_File_Traits
 */
class CUTS_BE_Export CUTS_BE_File_Traits :
  public CUTS_BE_Traits
{
public:
  /// Default constructor.
  CUTS_BE_File_Traits (void);

  /// Destructor.
  virtual ~CUTS_BE_File_Traits (void);

  virtual void close_file (
    const PICML::ComponentImplementationContainer_in container);

protected:
  /// Pointer to the output file stream.
  std::ofstream out_;
};

#if defined (__CUTS_INLINE__)
#include "BE_File_Traits.inl"
#endif

#endif  // !defined _CUTS_BE_FILE_TRAITS_H_
