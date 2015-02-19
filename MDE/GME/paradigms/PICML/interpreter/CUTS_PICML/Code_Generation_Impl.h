// -*- C++ -*-

//=============================================================================
/**
 * @file        Code_Generation_Impl.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CODE_GENERATION_IMPL_H_
#define _CODE_GENERATION_IMPL_H_

#include "game/mga/component/Interpreter_Impl_Base.h"
#include "game/mga/Project.h"

// Forward decl.
class CUTS_BE_Manager;

/**
 * @class Code_Generation_Impl
 */
class Code_Generation_Impl : public GAME::Mga::Interpreter_Impl_Base
{
public:
  /// Default constructor.
  Code_Generation_Impl (void);

  /// Destructor.
  virtual ~Code_Generation_Impl (void);

  int initialize (GAME::Mga::Project proj);

  // Handle the InvokeEx callback.
  int invoke_ex (GAME::Mga::Project project,
                 GAME::Mga::FCO fco,
                 GAME::Mga::Collection_T <GAME::Mga::FCO> & selected,
                 long flags);

  int set_parameter (const std::string & name, const std::string & value);

private:
  struct backend_t
  {
    typedef CUTS_BE_Manager * (* FACTORY_METHOD) (void);

    backend_t (const std::string & type, const std::string & name, FACTORY_METHOD factory)
      : type_ (type),
        name_ (name),
        factory_ (factory)
    {

    }

    std::string type_;
    std::string name_;
    FACTORY_METHOD factory_;
  };

  std::string output_;

  int selected_backend_;

  std::vector <backend_t> backends_;
};

#endif
