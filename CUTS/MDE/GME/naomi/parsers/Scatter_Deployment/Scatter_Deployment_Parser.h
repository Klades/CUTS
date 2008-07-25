// -*- C++ -*-

//=============================================================================
/**
 * @file        Scatter_Deployment_Parser.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _NAOMI_SCATTER_DEPLOYMENT_PARSER_H_
#define _NAOMI_SCATTER_DEPLOYMENT_PARSER_H_

#include "../../Naomi_Parser.h"
#include "Scatter_Deployment_Parser_export.h"

/**
 * @class NAOMI_Scatter_Deployment_Parser
 *
 * Adapter for allowing the Scatter_Deployment_Paser to work with the NAOMI
 * connector for GME.
 */
class NAOMI_Scatter_Deployment_Parser : public GME_Naomi_Parser
{
public:
  /// Default constructor.
  NAOMI_Scatter_Deployment_Parser (void);

  /// Destructor.
  virtual ~NAOMI_Scatter_Deployment_Parser (void);

  // Handle a attribute resource.
  virtual int handle_resource (const std::string & name,
                               const std::string & uri);

  // Run the parser.
  virtual int run (GME::Object & target, const std::string & attr_path);

private:
  /// Name of file to parse.
  std::string filename_;
};

GME_NAOMI_CREATE_PARSER_DECLARE (NAOMI_SCATTER_DEPLOYMENT_PARSER_Export);

#endif  // !defined _NAOMI_SCATTER_DEPLOYMENT_PARSER_H_
