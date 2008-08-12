// $Id$

#include "Command_Substitution.h"
#include "ace/Env_Value_T.h"
#include "ace/Log_Msg.h"
#include "ace/OS_NS_fcntl.h"
#include "ace/OS_NS_unistd.h"
#include "ace/Process_Manager.h"
#include "ace/SString.h"
#include "ace/streams.h"
#include "boost/spirit/core.hpp"
#include "boost/spirit/utility/confix.hpp"
#include <sstream>

namespace actors
{
  /**
   * @class append
   *
   * Functor for appending the value of an environment variable to
   * a string.
   */
  class append
  {
  public:
    /**
     * Initializing contructor.
     *
     * @param[out]         str         Target string
     */
    append (std::ostringstream & ostr)
      : ostr_ (ostr)
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

      this->ostr_ << str;
    }

  private:
    // Target stream for appending.
    std::ostringstream & ostr_;
  };

  /**
   * @class substitute
   *
   * Functor for inserting a string to a stream.
   */
  class substitute
  {
  public:
    /**
     * Initializing constructor.
     *
     * @param[in]         ostr        Target string for output
     */
    substitute (std::ostringstream & ostr)
      : ostr_ (ostr)
    {
      // Get the CUTS_ROOT environment variable.
      ACE_TCHAR pathname[1024];

      if (ACE::get_temp_dir (pathname, 1024 - 21) == -1)
      {
        ACE_ERROR ((LM_WARNING,
                    "%T - %M - failed to resolve temporary directory\n"));
      }

      // Create a temporary filename for the project.
      ACE_OS::strcat (pathname, "cutsnode-XXXXXX");
      char * tempfile = ACE_OS::mktemp (pathname);

      if (tempfile != 0)
      {
        ACE_DEBUG ((LM_DEBUG,
                    "%T - %M - saving temporary filename [%s]\n",
                    tempfile));

        // Save the filename for later.
        this->tempfile_ = tempfile;
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "%T - %M - failed to create temporary file; using %s\n",
                    pathname));

        this->tempfile_ = pathname;
      }
    }

    /**
     * Copy constructor.
     */
    substitute (const substitute & copy)
      : ostr_ (copy.ostr_),
        tempfile_ (copy.tempfile_)
    {

    }

    /**
     * Assignment operator.
     */
    const substitute & operator = (const substitute & rhs)
    {
      this->tempfile_ = rhs.tempfile_;
      return *this;
    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string str (begin, end);

      ACE_DEBUG ((LM_DEBUG,
                  "%T - %M - substituting command: %s\n",
                  str.c_str ()));

      // Open the temporary file, and map it into memory.
      int flags = O_WRONLY | O_CREAT;
      ACE_HANDLE pipe = ACE_OS::open (this->tempfile_.c_str (), flags);

      if (pipe != ACE_INVALID_HANDLE)
      {
        // Configure the options for spawning the process.
        ACE_Process_Options options;
        options.command_line ("%s", str.c_str ());
        options.set_handles (ACE_INVALID_HANDLE, pipe, ACE_INVALID_HANDLE);

        // Spawn the new process.
        ACE_Process process;
        ACE_Process_Manager * proc_man = ACE_Process_Manager::instance ();
        pid_t pid = proc_man->spawn (&process, options);

        if (pid != ACE_INVALID_PID)
        {
          // Wait for the newly spawned process to exit.
          proc_man->wait (pid);

          // Close the file used to store the output.
          ACE_OS::close (pipe);

          // Open tie
          char substitution[BUFSIZ];
          std::ifstream infile;

          infile.open (this->tempfile_.c_str ());

          if (infile.is_open ())
          {
            // Get only the first line of the file.
            infile.getline (substitution, BUFSIZ);

            // Append the line to the stream.
            this->ostr_ << substitution;

            // Close the file.
            infile.close ();
          }

          // Delete the temporary file.
          ACE_OS::unlink (this->tempfile_.c_str ());
        }
        else
        {
          ACE_ERROR ((LM_ERROR,
                      "%T - %M - failed to spawn process [%s]\n",
                      str.c_str ()));

          // Insert the original command to the stream.
          this->ostr_ << str;
        }
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "%T - %M - %m\n"
                    "%T - %M - failed to open temporary file [%s]\n",
                    this->tempfile_.c_str ()));

        this->ostr_ << str;
      }

    }

  private:
    // Target stream for appending.
    std::ostringstream & ostr_;

    ACE_CString tempfile_;
  };
}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Command_Substitution_i

/**
 * @class CUTS_Command_Substitution_i
 *
 * Parser that actuaully performs the substitution of commands.
 */
class CUTS_Command_Substitution_i :
  public boost::spirit::grammar <CUTS_Command_Substitution_i>
{
public:
  /**
   * Initializing constructor.
   *
   * @param[out]         str         Expanded version of string
   */
  CUTS_Command_Substitution_i (std::ostringstream & ostr)
    : ostr_ (ostr)
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
    definition (CUTS_Command_Substitution_i const & self)
    {
      this->text_ =
        *(boost::spirit::print_p - '`');

      this->command_value_ =
        (*(boost::spirit::anychar_p - '\`'))[actors::substitute (self.ostr_)];

      this->command_ =
        boost::spirit::confix_p ('`', this->command_value_, '\`');

      this->content_ =
        this->text_ [actors::append (self.ostr_)] >>
        *(this->command_ >> this->text_ [actors::append (self.ostr_)]);
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
    /// rule: command_
    boost::spirit::rule <ScannerT> command_;

    /// rule: command_value_
    boost::spirit::rule <ScannerT> command_value_;

    /// rule: text_;
    boost::spirit::rule <ScannerT> text_;

    /// Content of the string.
    boost::spirit::rule <ScannerT> content_;
  };

private:
  /// Location to store the converted string.
  std::ostringstream & ostr_;
};

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Command_Substitution

//
// CUTS_Command_Substitution
//
CUTS_Command_Substitution::CUTS_Command_Substitution (void)
{

}

//
// ~CUTS_Command_Substitution
//
CUTS_Command_Substitution::~CUTS_Command_Substitution (void)
{

}

//
// evaluate
//
bool CUTS_Command_Substitution::
evaluate (const char * str, ACE_CString & result)
{
  std::ostringstream ostr;
  CUTS_Command_Substitution_i parser (ostr);

  boost::spirit::parse_info < > info = boost::spirit::parse (str, parser);

  if (info.full)
    result = ostr.str ().c_str ();

  return info.full;
}
