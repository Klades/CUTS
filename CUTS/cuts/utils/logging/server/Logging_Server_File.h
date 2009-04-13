// -*- C++ -*-

#ifndef _CUTS_LOGGING_SERVER_FILE_H_
#define _CUTS_LOGGING_SERVER_FILE_H_

#include "cuts/config.h"
#include "logging.h"
#include "XSCRT/utils/File_Reader_T.h"
#include "XSC/utils/XML_Schema_Resolver.h"

/**
 * @class CUTS_Logging_Server_File
 */
class CUTS_Logging_Server_File :
  public XSCRT::utils::File_Reader_T <CUTS::loggingClients>
{
public:
  /// Type definition of the reader type
  typedef XSCRT::utils::File_Reader_T <CUTS::loggingClients> reader_type;

  CUTS_Logging_Server_File (void);

  virtual ~CUTS_Logging_Server_File (void);

private:
  /// Set the default configuration for the file.
  void configure (void);

  XSC::XML::Basic_Resolver < > br_;

  XSC::XML::XML_Schema_Resolver <XSC::XML::Basic_Resolver < > > resolver_;
};

#if defined (__CUTS_INLINE__)
#include "Logging_Server_File.inl"
#endif

#endif  // !defined _CUTS_LOGGING_SERVER_FILE_H_
