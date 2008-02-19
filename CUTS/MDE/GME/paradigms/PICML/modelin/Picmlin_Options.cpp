// $Id$

#include "Picmlin_Options.h"
#include "ace/SString.h"
#include "ace/Log_Msg.h"
#include <utility>

//
// Picmlin_Options
//
Picmlin_Options::Picmlin_Options (void)
: verbose_ (false),
  instance_name_separator_ (0)
{

}

//
// insert_param
//
int Picmlin_Options::insert_param (char * param)
{
  int errors = 0;

  // Construct a tokenizer for the name-value arguments. The
  // parameters take the form: name=value;name=value;
  ACE_Tokenizer nv_tokenizer (param);
  nv_tokenizer.delimiter_replace (';', 0);

  // Iterate over all the parameters. The parameters
  char * nv_token;
  while (nv_token = nv_tokenizer.next ())
  {
    ACE_Tokenizer nv_separator (nv_token);
    nv_separator.delimiter_replace ('=', 0);

    // Get the <value> of the <name> parameter. We only can
    // store it if we have a value name value pair.
    char * name = nv_separator.next ();
    char * value = nv_separator.next ();

    if (name != 0 && value != 0)
    {
      this->params_.push_back (std::make_pair (name, value));
    }
    else
    {
      if (name == 0)
        ACE_ERROR ((LM_ERROR, ""));

      if (value == 0)
        ACE_ERROR ((LM_ERROR, ""));

      ++ errors;
    }
  }

  return errors == 0 ? 0 : -1;
}
