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

#include "Scatter_Deployment_Parser_export.h"
#include "GME/T2M/parsers/T2M_Parser.h"
#include "game/GME_fwd.h"
#include <map>

/**
 * @class Scatter_Deployment_Parser
 *
 * Text-2-Model parser for import Scatter input into a PICML deployment
 * model.
 */
class SCATTER_DEPLOYMENT_PARSER_Export Scatter_Deployment_Parser :
  public GME_T2M_Parser
{
public:
  /// Default constructor.
  Scatter_Deployment_Parser (void);

  /// Destructor.
  virtual ~Scatter_Deployment_Parser (void);

  bool parse (const std::string & filename,
              GME::Object & parent,
              const GME::Model & assembly,
              GME::Model & domain);

  // Parse the specified filename.
  virtual bool parse (const std::string & filename,
                      GME::Object & parent);

private:
  void clear_deployment (GME::Model & deployment);

  void insert_nodes_in_deployment (GME::Model & deployment,
                                   const std::map <std::string, GME::Model> & nodes,
                                   std::map <std::string, GME::Set> & groups);
};

GME_T2M_CREATE_PARSER_DECLARE (SCATTER_DEPLOYMENT_PARSER_Export);
