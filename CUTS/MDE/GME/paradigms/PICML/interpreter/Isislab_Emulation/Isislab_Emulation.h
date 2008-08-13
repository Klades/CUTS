// -*- C++ -*-

//=============================================================================
/**
 * @file            Isislab_Emulation.h
 *
 * $Id$
 *
 * @author          James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ISISLAB_EMULATION_H_
#define _CUTS_ISISLAB_EMULATION_H_

#include "PICML/PICML.h"
#include <fstream>

/**
 * @class CUTS_Isislab_Emulation
 *
 * Visitor that generates the NS script for running a CUTS emulation
 * in ISISLab.
 */
class CUTS_Isislab_Emulation : public PICML::Visitor
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]         outdir      Output directory
   */
  CUTS_Isislab_Emulation (const std::string & outdir);

  /// Destructor.
  virtual ~CUTS_Isislab_Emulation (void);

  virtual void Visit_RootFolder (const PICML::RootFolder & root);

  virtual void Visit_Targets (const PICML::Targets & targets);

  virtual void Visit_Domain (const PICML::Domain & domain);

  virtual void Visit_Node (const PICML::Node &);

private:
  /// Target directory for generation.
  const std::string & outdir_;

  /// Output file for NS script.
  std::ofstream outfile_;

  /// Name of the project.
  std::string project_name_;
};

#endif  // !defined _CUTS_ISISLAB_EMULATION_H_
