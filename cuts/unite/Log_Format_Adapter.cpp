#include "Log_Format_Adapter.h"
#include "ace/CORBA_macros.h"
#include "cuts/unite/Variable.h"

//
// Destructor
//
CUTS_Log_Format_Adapter::~CUTS_Log_Format_Adapter (void)
{

}

//
// add_variable
//
void CUTS_Log_Format_Adapter::add_variable (CUTS_Log_Format * lfmt,
                                           char * Id,
                                           char * type)
{
    CUTS_Log_Format_Variable *variable = 0;
    std::string var_type (type);

    size_t index = lfmt->variables ().current_size ();

    /// Check the type of the variable specified in the spec
    /// and then crrate the appropriate variable

    if (var_type == "string")
    {
      ACE_NEW_THROW_EX (variable,
                        CUTS_String_Log_Format_Variable (index),
                        ACE_bad_alloc ());
    }
    else if (var_type == "int")
    {
      ACE_NEW_THROW_EX (variable,
                        CUTS_Basic_Log_Format_Variable_T <ACE_INT32> (index),
                        ACE_bad_alloc ());
    }
    else if (var_type == "long")
    {
      ACE_NEW_THROW_EX (variable,
                        CUTS_Basic_Log_Format_Variable_T <ACE_INT32> (index),
                        ACE_bad_alloc ());
    }

    else if (var_type == "short")
    {
      ACE_NEW_THROW_EX (variable,
                        CUTS_Basic_Log_Format_Variable_T <ACE_INT16> (index),
                        ACE_bad_alloc ());
    }
    else if (var_type == "float")
    {
      ACE_NEW_THROW_EX (variable,
                        CUTS_Basic_Log_Format_Variable_T <double> (index),
                        ACE_bad_alloc ());
    }

    // Store the variable in the map
    lfmt->variables ().bind (Id, variable);

    int * captures = 0;

    size_t captures_size = (lfmt->variables ().current_size ()  + 1) * 3;
    lfmt->captures_size (captures_size);
    ACE_NEW_THROW_EX (captures,  int[captures_size],  ACE_bad_alloc ());
    lfmt->captures ().reset (captures);
}

//
// add_relation
//

void CUTS_Log_Format_Adapter::add_relation (CUTS_Log_Format * lfmt,
                                 char * effect,
                                 char * cause_var,
                                 char * effect_var)
{
  // Get the relation count first

  ACE_CString effect_rel (effect);
  size_t relation_count = lfmt->relations ().size ();
  for (size_t i = 0; i < relation_count; ++i)
  {
    // Create a causality for each relation useing the provided values
    // in the spec, and then add each causality to the relations vector

    CUTS_Log_Format_Relation & rel = lfmt->relations ()[i];
    if(rel.effect ()->name () == effect_rel)
    {
      CUTS_Relation_Causality rc (cause_var, effect_var);
      rel.causality ().push_back (rc);
    }
  }
}