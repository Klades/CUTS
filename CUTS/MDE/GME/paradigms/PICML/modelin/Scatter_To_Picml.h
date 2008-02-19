// -*- C++ -*-

#include "gme/GME_fwd.h"
#include "Deployment_Map.h"

class CUTS_Scatter_To_Picml
{
public:
  CUTS_Scatter_To_Picml (void);

  ~CUTS_Scatter_To_Picml (void);

  bool run (const std::string & inputfile, CUTS_Deployment_Map & map);
};
