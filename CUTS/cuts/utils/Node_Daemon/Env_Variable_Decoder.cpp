// $Id$

#include "Env_Variable_Decoder.h"
#include "ace/Log_Msg.h"
#include "ace/OS_NS_stdlib.h"
#include "boost/spirit/core.hpp"
#include <sstream>

namespace actors
{
  /**
   * @class append_env
   *
   * Functor for appending the value of an environment variable to
   * a string.
   */
  class append_env
  {
  public:
    /**
     * Initializing contructor.
     *
     * @param[out]         str         Target string
     */
    append_env (std::ostringstream & ostr,
                const CUTS_Property_Map & prop_map)
      : ostr_ (ostr),
        prop_map_ (prop_map)
    {

    }

    /**
     * Functor operator
     *
     * @param[in]         begin         Beginning of string
     * @param[in]         end           End of string
     */
    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string str (begin, end);
      ACE_CString value;

      // First, search the property map for the variable.
      if (this->prop_map_.get (str.c_str (), value) == 0)
      {
        this->ostr_ << value;
      }
      else
      {
        // Search for the value in the environment variables.
        char * val = ACE_OS::getenv (str.c_str ());

        // If the environment variable was found, then we should append
        // that value. Otherwise, we need to append the original environment
        // variable.
        if (val != 0)
        {
          this->ostr_ << val;
        }
        else
        {
          ACE_ERROR ((LM_WARNING,
                      "%T - %M - environment variable %s is not defined\n",
                      str.c_str ()));

          this->ostr_ << "${" << str << "}";
        }
      }
    }
  private:
    // Target stream for appending.
    std::ostringstream & ostr_;

    /// Property map for the appender.
    const CUTS_Property_Map & prop_map_;
  };

  /**
   * @class append_str
   *
   * Functor for inserting a string to a stream.
   */
  class append_str
  {
  public:
    append_str (std::ostringstream & ostr)
      : ostr_ (ostr)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string str (begin, end);
      this->ostr_ << str;
    }

  private:
    // Target stream for appending.
    std::ostringstream & ostr_;
  };
}

/**
 * @class Env_Variable_Decoder
 *
 * Parser that is does the actual decoding/expanding of environment
 * variables in a string.
 */
class Env_Variable_Decoder :
  public boost::spirit::grammar <Env_Variable_Decoder>
{
public:
  /// Default constructor.
  Env_Variable_Decoder (std::ostringstream & ostr,
                        const CUTS_Property_Map & map)
    : ostr_ (ostr),
      prop_map_ (map)
  {

  }

  /**
   * @class definition
   *
   * Definition of the grammar.
   */
  template <typename ScannerT>
  class definition
  {
  public:
    /**
     * Initializing constructor.
     *
     * @param[in]     self        The input grammar.
     */
    definition (Env_Variable_Decoder const & self)
    {
      this->var_name_ =
        *(boost::spirit::print_p - '}');

      this->text_ =
        *(boost::spirit::print_p - '$');

      this->env_var_ =
        boost::spirit::lexeme_d [
          boost::spirit::str_p ("${") >>
            this->var_name_[actors::append_env (self.ostr_, self.prop_map_)] >> '}'];

      this->content_ =
        this->text_ [actors::append_str (self.ostr_)] >>
        *(this->env_var_ >> this->text_ [actors::append_str (self.ostr_)]);
    }

    /**
     * Start of the input grammar.
     *
     * @return        Starting expression for the grammar.
     */
    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->content_;
    }

  private:
    /// rule: var_name_;
    boost::spirit::rule <ScannerT> var_name_;

    /// rule: env_var_
    boost::spirit::rule <ScannerT> env_var_;

    /// rule: text_;
    boost::spirit::rule <ScannerT> text_;

    /// Content of the string.
    boost::spirit::rule <ScannerT> content_;
  };

private:
  /// Location to store the converted string.
  std::ostringstream & ostr_;

  /// Property map used by the decoder.
  const CUTS_Property_Map & prop_map_;
};

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Env_Variable_Decoder

//
// CUTS_Env_Variable_Decorder
//
CUTS_Env_Variable_Decorder::
CUTS_Env_Variable_Decorder (const CUTS_Property_Map & map)
: prop_map_ (map)
{

}

//
// ~CUTS_Env_Variable_Decorder
//
CUTS_Env_Variable_Decorder::~CUTS_Env_Variable_Decorder (void)
{

}

//
// expand
//
bool CUTS_Env_Variable_Decorder::
expand (const char * str, ACE_CString & value)
{
  // Create a new decoder for the string.
  std::ostringstream ostr;
  Env_Variable_Decoder decoder (ostr, this->prop_map_);

  // Parse the string using the decoder grammar.
  boost::spirit::parse_info < > info = boost::spirit::parse (str, decoder);

  // Set the value if the parsing succeeded.
  if (info.full)
    value = ostr.str ().c_str ();

  return info.full;
}
