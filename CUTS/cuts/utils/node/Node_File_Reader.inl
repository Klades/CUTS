// -*- C++ -*-
// $Id$

#include "ace/Env_Value_T.h"

//
// ~CUTS_Node_File_Reader
//
CUTS_INLINE
CUTS_Node_File_Reader::~CUTS_Node_File_Reader (void)
{

}

//
// config
//
CUTS_INLINE
const CUTS::nodeConfig & CUTS_Node_File_Reader::config (void) const
{
  return this->config_;
}

//
// config
//
CUTS_INLINE
CUTS::nodeConfig & CUTS_Node_File_Reader::config (void)
{
  return this->config_;
}
