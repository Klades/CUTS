// -*- C++ -*-

//=============================================================================
/**
 * @file      BE_Manager_Factory_Repo.h
 *
 * Repository for managing CUTS_BE_Manager_Factory objects
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_MANAGER_FACTORY_REPO_H_
#define _CUTS_BE_MANAGER_FACTORY_REPO_H_

#include "BE_export.h"
#include <map>
#include <string>

// Forward decl.
class CUTS_BE_Manager_Factory;

/// Type definition that maps a name to a manager factory. The name is
/// the name of the module. The factory is the factory loaded from the
/// module specified by \a name.
typedef std::map <std::string,
                  CUTS_BE_Manager_Factory *> CUTS_BE_Manager_Factory_Set;

//=============================================================================
/**
 * @class CUTS_BE_Manager_Factory_Repo
 */
//=============================================================================

class CUTS_BE_Export CUTS_BE_Manager_Factory_Repo
{
public:
  /// Default constructor.
  CUTS_BE_Manager_Factory_Repo (void);

  /// Destructor.
  ~CUTS_BE_Manager_Factory_Repo (void);

  /**
   * Load a module into the repo.
   *
   * @param[in]     id              Id of the backend.
   * @param[in]     module          Pathname of the module.
   * @retval        true            Successfully loaded module.
   * @retval        false           Failed to load module.
   */
  bool load (const std::string & id,
             const std::string & module);

  /**
   * Load a module into the repo.
   *
   * @param[in]     id              Id of the backend.
   * @param[in]     module          Pathname of the module.
   * @retval        true            Successfully loaded module.
   * @retval        false           Failed to load module.
   */
  bool load (const std::string & id,
             const std::string & module,
             CUTS_BE_Manager_Factory * & factory);

  /**
   * Unload a factory module by its name.
   *
   * @param[in]     name            Name of the module.
   */
  void unload (const char * name);

  /// Unload all the backend generators.
  void unload_all (void);

  /**
   * Get the collection of factories loaded into the repo. This
   * is a read-only collection to prevent clients from maliciously
   * removing factories.
   *
   * @return        Collection of loaded factory modules.
   */
  const CUTS_BE_Manager_Factory_Set & factories (void) const;

  /**
   * Find a backend generator by its name.
   *
   * @param[in]     name          Name of the backend generator.
   * @param[in]     factory       The factory for the generator.
   */
  bool find (const char * name, CUTS_BE_Manager_Factory * &factory);

private:
  std::map <std::string, std::string> path_map_;

  /// Collection of loaded factories.
  CUTS_BE_Manager_Factory_Set factories_;
};

#if defined (__CUTS_INLINE__)
#include "BE_Manager_Factory_Repo.inl"
#endif

#endif  // !defined _CUTS_BE_MANAGER_FACTORY_REPO_H_