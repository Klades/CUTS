// -*- C++ -*-

//=============================================================================
/**
 * @file        CUTS_Unite_Validation_File.h
 *
 * $Id $
 *
 * @author      Pooja Varshneya
 */
//=============================================================================

#ifndef _CUTS_UNITE_VALIDATION_FILE_H_
#define _CUTS_UNITE_VALIDATION_FILE_H_

#include "cuts-unite.h"
#include "XSC/utils/XML_Schema_Resolver.h"
#include "XSCRT/utils/File_Reader_T.h"

/**
 * @ingroup UNITE_XML
 *
 * @class CUTS_Unite_Validation_File
 *
 * Helper class for parsing XML documents that contain validation
 * conditions for a given datagraph.
 */
class CUTS_UNITE_XML_Export CUTS_Unite_Validation_File :
  public XSCRT::utils::File_Reader_T < ::CUTS::XML::validationType >
{
public:
  /// Type definition of the XML reader type.
  typedef XSCRT::utils::File_Reader_T < ::CUTS::XML::validationType > reader_type;

  /// Default constructor.
  CUTS_Unite_Validation_File (void);

  /// Destructor.
  ~CUTS_Unite_Validation_File (void);

private:
  void configure (void);

  XSC::XML::Basic_Resolver < > br_;

  XSC::XML::XML_Schema_Resolver < ::XSC::XML::Basic_Resolver < > > resolver_;
};

#if defined (__CUTS_INLINE__)
#include "Unite_Validation_File.inl"
#endif

#endif  // !defined _CUTS_UNITE_VALIDATION_FILE_H_