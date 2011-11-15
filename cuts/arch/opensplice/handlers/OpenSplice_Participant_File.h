// -*- C++ -*-

//=============================================================================
/**
 * @file        OpenSplice_Participant_File.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_OPENSPLICE_PARTICIPANT_FILE_H_
#define _CUTS_OPENSPLICE_PARTICIPANT_FILE_H_

#include "dds.h"
#include "XSC/utils/XML_Schema_Resolver.h"
#include "XSCRT/utils/File_Reader_T.h"

/**
 * @class CUTS_OpenSplice_Participant_File
 */
class CUTS_OpenSplice_Participant_File :
  public XSCRT::utils::File_Reader_T < iccm::dds::DomainParticipantQos >
{
public:
  /// Type definition of the XML reader type.
  typedef XSCRT::utils::File_Reader_T < iccm::dds::DomainParticipantQos > reader_type;

  /// Default constructor.
  CUTS_OpenSplice_Participant_File (void);

  /// Destructor.
  ~CUTS_OpenSplice_Participant_File (void);

private:
  /// Method for configuring the file reader.
  void configure (void);

  XSC::XML::Basic_Resolver < > br_;

  XSC::XML::XML_Schema_Resolver < ::XSC::XML::Basic_Resolver < > > resolver_;
};

#endif  // !defined _CUTS_UNITE_DATAGRAPH_FILE_H_