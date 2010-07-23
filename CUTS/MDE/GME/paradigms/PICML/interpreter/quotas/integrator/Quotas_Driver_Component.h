// -*- C++ -*-

//=============================================================================
/**
 *  @file       Quotas_Driver_Component.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _QUOTAS_DRIVER_COMPONENT_H_
#define _QUOTAS_DRIVER_COMPONENT_H_

#include "game/Model.h"

/**
 * @class Quotas_Driver_Component_Generator
 *
 * Utility class that generates driver components.
 */
class Quotas_Driver_Component_Generator
{
public:
  /**
   * Initializing constructor
   *
   * @param[in]     folder        Target output folder for generation.
   */
  Quotas_Driver_Component_Generator (GAME::Folder & folder);

  /// Destructor.
  ~Quotas_Driver_Component_Generator (void);

  /**
   * Generate a driver component
   *
   * @param[in]     model         Source component.
   */
  bool generate (const GAME::Model & component, GAME::Model & driver);

private:
  struct fileinfo_t
  {
    /// The target file.
    GAME::Model file_;

    /// The associated package.
    std::vector <GAME::Model> package_;
  };

  void get_file_info (const GAME::Model & component, fileinfo_t & info);

  void duplicate_package_structure (const std::vector <GAME::Model> & packages,
                                    const GAME::Model & start, 
                                    GAME::Model & package);

  /// Target folder for the generation.
  GAME::Folder & folder_;
};

#endif  // !defined _QUOTAS_DRIVER_COMPONENT_H_
