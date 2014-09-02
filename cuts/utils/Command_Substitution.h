// -*- C++ -*-

//=============================================================================
/**
 * @file          Command_Subtitution.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_COMMAND_SUBSTITUTION_H_
#define _CUTS_COMMAND_SUBSTITUTION_H_

#include "Utils_export.h"
#include "ace/Env_Value_T.h"
#include "ace/Log_Msg.h"
#include "ace/OS_NS_fcntl.h"
#include "ace/OS_NS_unistd.h"
#include "ace/Process_Manager.h"
#include "ace/SString.h"
#include "ace/streams.h"
#include "ace/Lib_Find.h"
#include "boost/config/warning_disable.hpp"
#include "boost/spirit/include/qi.hpp"
#include "boost/spirit/include/classic_core.hpp"
#include "boost/spirit/include/classic_confix.hpp"
#include "boost/spirit/include/phoenix_bind.hpp"
#include <boost/spirit/include/qi_lexeme.hpp>
#include <ostream>
#include <sstream>

namespace qi = boost::spirit::qi;
namespace phoenix = boost::phoenix;
namespace ascii = boost::spirit::ascii;

namespace actors
{

struct replace
{
  template <typename Context>
  void operator()(const std::string & cmd, Context ctx, qi::unused_type) const
  {
    // Execute the provided string and put its output into the _val (ctx.attributes[0])
    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - substituting command: %s\n",
                cmd.c_str ()));

    std::string & out = boost::fusion::at_c <0> (ctx.attributes);

    // Get a temporary file to store output
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
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - failed to create temporary file; using %s\n",
                  pathname));

      tempfile = pathname;
    }

    int flags = O_WRONLY | O_CREAT;
    ACE_HANDLE pipe = ACE_OS::open (tempfile, flags);

    // Configure the options for spawning the process.
    ACE_Process_Options options;
    options.command_line ("%s", cmd.c_str ());
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

      if (process.exit_code () == 0)
      {
        char substitution[BUFSIZ];
        std::ifstream infile;

        infile.open (tempfile);

        if (infile.is_open ())
        {
          // Get only the first line of the file.
          infile.getline (substitution, BUFSIZ);

          // Append the line to the stream.
          out += substitution;

          // Close the file.
          infile.close ();
        }
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "%T - %M - process had exit status of %d [%s]\n",
                    process.exit_code (),
                    cmd.c_str ()));

        out += '`';
        out += cmd;
        out += '`';
      }
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - failed to spawn process [%s]\n",
                  cmd.c_str ()));

      // Insert the original command to the stream.
      out += '`';
      out += cmd;
      out += '`';
    }

    // Delete the temporary file.
    ACE_OS::unlink (tempfile);
  }

};

};

/**
 * @class CUTS_Command_Substitution_i
 *
 * Parser that actuaully performs the substitution of commands.
 */
template <typename IteratorT>
class CUTS_Command_Substitution_Grammar :
    public boost::spirit::qi::grammar <IteratorT,
                                       std::string (void)>
{
public:
  /**
   * Initializing constructor.
   *
   * @param[out]         str         Expanded version of string
   */
  CUTS_Command_Substitution_Grammar (void)
    : CUTS_Command_Substitution_Grammar::base_type (this->spec_)
  {

    this->text_ %=
      *(qi::char_ - '`');

    this->command_ =
      '`' >> this->text_ [actors::replace ()] >> '`';

    this->content_ %=
      this->text_ >>
      *(this->command_ >> this->text_);

    this->spec_ %= this->content_;
  }

private:
  qi::rule <IteratorT,
            std::string (void)> spec_;

  /// Content of the string.
  qi::rule <IteratorT,
            std::string (void)> content_;

  /// rule: command_
  qi::rule <IteratorT,
            std::string (void)> command_;

  /// rule: text_;
  qi::rule <IteratorT,
            std::string (void)> text_;
};

/**
 * @class CUTS_Command_Substitution
 *
 * Substitutes a command in a string with the output generated by the
 * command. Commands are defined by characters enclosed by `', similar
 * to a shell script on Unix platforms.
 */
class CUTS_UTILS_Export CUTS_Command_Substitution
{
public:
  /// Default constructor.
  CUTS_Command_Substitution (void);

  /// Destructor.
  ~CUTS_Command_Substitution (void);

  /**
   * Evaluate a string. This will substitute all commands in \a str with
   * the output it generates.
   *
   * @param[in]         str           Source string
   * @param[out]        result        String with substituted values
   * @retval            true          Evaluation succeeded
   * @retval            false         Evaluation failed
   */
  bool evaluate (const char * str, ACE_CString & result);

  template <typename IteratorT>
  bool evaluate (IteratorT begin, IteratorT end, std::ostream & out)
  {
    std::string ostr;
    CUTS_Command_Substitution_Grammar <IteratorT> grammar;
    bool retval = qi::parse (begin, end, grammar, ostr);
    out << ostr.c_str ();
    return retval;
  }

};

#if defined (__CUTS_INLINE__)
#include "Command_Substitution.inl"
#endif

#endif  // !defined _CUTS_COMMAND_SUBSTITUTION_H_
