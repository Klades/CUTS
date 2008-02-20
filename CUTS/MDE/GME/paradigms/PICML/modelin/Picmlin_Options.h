// -*- C++ -*-

//=============================================================================
/**
 * @file      G2P_Options.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _PICMLIN_OPTIONS_H_
#define _PICMLIN_OPTIONS_H_

#include <string>
#include <list>

//=============================================================================
/**
 * @struct Picmlin_Options
 */
//=============================================================================

struct Picmlin_Options
{
  /// Default constructor.
  Picmlin_Options (void);

  /// Verbose flag.
  bool verbose_;

  /// Location of the GME model.
  std::string gme_connstr_;

  /// The target folder for the converted model.
  std::string target_deployment_;

  /// The input file name of the Scatter model.
  std::string scatter_input_;

  char instance_name_separator_;

  std::string deployment_output_;
};

#endif  // !defined _PICMLIN_OPTIONS_H_
