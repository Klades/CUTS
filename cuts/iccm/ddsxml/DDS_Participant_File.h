// -*- C++ -*-

//=============================================================================
/**
 *  @file         DDS_Participant_File.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ICCM_DDS_XML_PARTICIPANT_FILE_H_
#define _CUTS_ICCM_DDS_XML_PARTICIPANT_FILE_H_

#include "XSC/utils/XML_Schema_Resolver.h"
#include "XSCRT/utils/File_Reader_T.h"

#include "dds.h"

#include "cuts/config.h"

namespace iCCM
{

/**
 * @class DDS_Participant_File
 */
class ICCM_DDS_XML_Export DDS_Participant_File :
  public ::XSCRT::utils::File_Reader_T < ::iccm::DomainParticipantQos >
{
public:
  /// Type definition of the XML reader type.
  typedef XSCRT::utils::File_Reader_T < ::iccm::DomainParticipantQos > reader_type;

  /// Default constructor.
  DDS_Participant_File (void);

  /// Destructor.
  ~DDS_Participant_File (void);

private:
  void configure (void);

  XSC::XML::Basic_Resolver < > br_;

  XSC::XML::XML_Schema_Resolver < ::XSC::XML::Basic_Resolver < > > resolver_;
};

}

#if defined (__CUTS_INLINE__)
#include "DDS_Participant_File.inl"
#endif

#endif  // !defined _CUTS_ICCM_DDS_XML_PARTICIPANT_FILE_H_
