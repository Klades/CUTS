// -*- C++ -*-

//=============================================================================
/**
 * @file        OpenSplice_Domain_File.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_OPENSPLICE_DOMAIN_FILE_H_
#define _CUTS_OPENSPLICE_DOMAIN_FILE_H_

#include "dds.h"
#include "XSC/utils/XML_Schema_Resolver.h"
#include "XSCRT/utils/File_Reader_T.h"

/**
 * @ingroup UNITE_XML
 *
 * @class CUTS_Unite_Datagraph_File
 *
 * Helper class for parsing XML documents that contain a unit test
 * data graph, i.e., its log formats and relations.
 */
class CUTS_OpenSplice_Domain_File :
  public XSCRT::utils::File_Reader_T < iccm::dds::DomainParticipantFactoryQos >
{
public:
  /// Type definition of the XML reader type.
  typedef XSCRT::utils::File_Reader_T < iccm::dds::DomainParticipantFactoryQos > reader_type;

  /// Default constructor.
  CUTS_OpenSplice_Domain_File (void);

  /// Destructor.
  ~CUTS_OpenSplice_Domain_File (void);

private:
  /// Method for configuring the file reader.
  void configure (void);

  XSC::XML::Basic_Resolver < > br_;

  XSC::XML::XML_Schema_Resolver < ::XSC::XML::Basic_Resolver < > > resolver_;
};

#endif  // !defined _CUTS_UNITE_DATAGRAPH_FILE_H_