// -*- C++ -*-

//=============================================================================
/**
 * @file      Node_File_Reader.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_NODE_FILE_READER_H_
#define _CUTS_NODE_FILE_READER_H_

#include "XSC/utils/XML_Schema_Resolver.h"
#include "XSCRT/utils/File_Reader_T.h"
#include "cuts/config.h"
#include "cutsnode.h"

/**
 * @class CUTS_Node_File_Reader
 */
class CUTS_Node_File_Reader :
  public XSCRT::utils::File_Reader_T <CUTS::schemas::NodeConfig>
{
public:
  /// Type definition of the reader type.
  typedef XSCRT::utils::File_Reader_T <CUTS::schemas::NodeConfig> reader_type;

  /// Default constructor.
  CUTS_Node_File_Reader (void);

  /// Destructor.
  virtual ~CUTS_Node_File_Reader (void);

private:
  XSC::XML::Basic_Resolver < > br_;

  XSC::XML::XML_Schema_Resolver <XSC::XML::Basic_Resolver < > > resolver_;
};

#if defined (__CUTS_INLINE__)
#include "Node_File_Reader.inl"
#endif

#endif  // !defined _CUTS_NODE_FILE_READER_H_
