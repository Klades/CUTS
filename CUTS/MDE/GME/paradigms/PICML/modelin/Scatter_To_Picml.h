// -*- C++ -*-

#include "gme/GME_fwd.h"
#include "Deployment_Map.h"

class Picmlin_Options;

class CUTS_Scatter_To_Picml
{
public:
  CUTS_Scatter_To_Picml (void);

  ~CUTS_Scatter_To_Picml (void);

  bool run (const std::string & inputfile, 
            GME::Project & project, 
            const Picmlin_Options & options);
};
