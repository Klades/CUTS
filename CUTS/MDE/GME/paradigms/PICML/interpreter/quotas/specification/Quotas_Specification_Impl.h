// -*- C++ -*-

//=============================================================================
/**
 * @file        Quotas_Specification_Impl.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _QUOTAS_SPECIFICATION_IMPL_H_
#define _QUOTAS_SPECIFICATION_IMPL_H_

#include "game/Folder.h"
#include "game/Model.h"

#include "addons/PICMLManager/Configurator.h"
#include "game/be/Interpreter_Impl_Base.h"

#include <stack>
#include <set>

namespace GAME
{
// Forward decl.
class Reference;
}

/**
 * @class Quotas_Specification_Impl
 *
 * Implemenation of the Quotas specification interpreter.
 */
class Quotas_Specification_Impl : 
  public GAME::Interpreter_Impl_Base 
{
public:
  /// Default constructor.
  Quotas_Specification_Impl (void);

  /// Destructor.
  virtual ~Quotas_Specification_Impl (void);

  // Initialize the interpreter.
  int initialize (GAME::Project & project);

  // Handle the InvokeEx callback.
  int invoke_ex (GAME::Project & project,
                 GAME::FCO & fco,
                 std::vector <GAME::FCO> & selected,
                 long flags);

private:
  // Visti an InterfaceDefinitions folder.
  void visit_interface_definitions (const GAME::Folder & folder);

  // Visit a File model.
  void visit_file (const GAME::Model & file);
  
  // Visit a Package model.
  void visit_package (const GAME::Model & package);

  void visit_file_package (const GAME::Model & file);

  void visit_object (const GAME::Model & object);

  void visit_attribute_kind (const GAME::Model & attr);

  void visit_attribute_member (const GAME::Reference & member);

  static const std::string Quotas_InterfaceDefinitions;

  GAME::Folder quotas_idl_folder_;

  GAME::Model active_model_;

  std::stack <GAME::Model> stack_;

  std::set <GAME::Model> components_;

  CComPtr <IConfigurator> configurator_;
};

#endif  // !defined _QUOTAS_SPECIFICATION_IMPL_H_
