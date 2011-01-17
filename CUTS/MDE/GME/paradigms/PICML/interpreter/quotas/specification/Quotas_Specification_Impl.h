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
  int initialize (GAME::Project project);

  // Handle the InvokeEx callback.
  int invoke_ex (GAME::Project project,
                 GAME::FCO_in fco,
                 std::vector <GAME::FCO> & selected,
                 long flags);

private:
  // Visti an InterfaceDefinitions folder.
  void visit_interface_definitions (const GAME::Folder_in folder);

  // Visit a File model.
  void visit_file (const GAME::Model_in file);

  // Visit a Package model.
  void visit_package (const GAME::Model_in package);

  void visit_file_package (const GAME::Model_in file);

  void visit_object (const GAME::Model_in object);

  void visit_attribute_kind (const GAME::Model_in attr);

  void visit_attribute_member (const GAME::Reference_in member);

  static const std::string Quotas_InterfaceDefinitions;

  GAME::Folder quotas_idl_folder_;

  GAME::Model active_model_;

  std::stack <GAME::Model> stack_;

  std::set <GAME::Model> components_;

  CComPtr <IConfigurator> configurator_;
};

#endif  // !defined _QUOTAS_SPECIFICATION_IMPL_H_
