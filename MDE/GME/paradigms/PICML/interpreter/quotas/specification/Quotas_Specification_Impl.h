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

#include "game/mga/Folder.h"
#include "game/mga/Model.h"

#include "addons/PICMLManager/Configurator.h"
#include "game/mga/component/Interpreter_Impl_Base.h"

#include <stack>
#include <set>

/**
 * @class Quotas_Specification_Impl
 *
 * Implemenation of the Quotas specification interpreter.
 */
class Quotas_Specification_Impl :
  public GAME::Mga::Interpreter_Impl_Base
{
public:
  /// Default constructor.
  Quotas_Specification_Impl (void);

  /// Destructor.
  virtual ~Quotas_Specification_Impl (void);

  // Initialize the interpreter.
  int initialize (GAME::Mga::Project project);

  // Handle the InvokeEx callback.
  int invoke_ex (GAME::Mga::Project project,
                 GAME::Mga::FCO_in fco,
                 std::vector <GAME::Mga::FCO> & selected,
                 long flags);

private:
  // Visti an InterfaceDefinitions folder.
  void visit_interface_definitions (const GAME::Mga::Folder_in folder);

  // Visit a File model.
  void visit_file (const GAME::Mga::Model_in file);

  // Visit a Package model.
  void visit_package (const GAME::Mga::Model_in package);

  void visit_file_package (const GAME::Mga::Model_in file);

  void visit_object (const GAME::Mga::Model_in object);

  void visit_attribute_kind (const GAME::Mga::Model_in attr);

  void visit_attribute_member (const GAME::Mga::Reference_in member);

  static const std::string Quotas_InterfaceDefinitions;

  GAME::Mga::Folder quotas_idl_folder_;

  GAME::Mga::Model active_model_;

  std::stack <GAME::Mga::Model> stack_;

  std::set <GAME::Mga::Model> components_;

  CComPtr <IConfigurator> configurator_;
};

#endif  // !defined _QUOTAS_SPECIFICATION_IMPL_H_
