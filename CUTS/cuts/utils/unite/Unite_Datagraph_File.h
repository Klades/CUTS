// -*- C++ -*-

//=============================================================================
/**
 * @file        Unite_Datagraph_File.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_DATAGRAPH_FILE_H_
#define _CUTS_UNITE_DATAGRAPH_FILE_H_

#include "cuts-unite.h"
#include "XSC/utils/XML_Schema_Resolver.h"
#include "XSCRT/utils/File_Reader_T.h"

/**
 * @class CUTS_Unite_Datagraph_File
 *
 * Helper class for parsing XML documents that contain a unit test
 * data graph, i.e., its log formats and relations.
 */
class CUTS_UNITE_XML_Export CUTS_Unite_Datagraph_File :
  public XSCRT::utils::File_Reader_T <CUTS::datagraphType>
{
public:
  typedef XSCRT::utils::File_Reader_T <CUTS::datagraphType> reader_type;

  /// Default constructor.
  CUTS_Unite_Datagraph_File (void);

  /// Destructor.
  ~CUTS_Unite_Datagraph_File (void);

private:
  void configure (void);

  XSC::XML::Basic_Resolver < > br_;

  XSC::XML::XML_Schema_Resolver <XSC::XML::Basic_Resolver < > > resolver_;
};

#endif  // !defined _CUTS_UNITE_DATAGRAPH_FILE_H_
