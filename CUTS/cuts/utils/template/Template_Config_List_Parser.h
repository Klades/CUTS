// -*- C++ -*-

//=============================================================================
/**
 * @file        Template_Config_List_Parser.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEMPLATE_CONFIG_LIST_PARSER_H_
#define _CUTS_TEMPLATE_CONFIG_LIST_PARSER_H_

#include "cuts/utils/Property_Parser.h"
#include "cuts/utils/Text_Processor.h"
#include "boost/spirit/core.hpp"
#include "boost/spirit/utility/confix.hpp"
#include "boost/spirit/actor/assign_actor.hpp"
#include "boost/spirit/iterator/file_iterator.hpp"
#include <fstream>
#include <sstream>
#include <string>

// Forward decl.
class CUTS_Property_Map;

/**
 * @class CUTS_Template_Config_List_Parser_Grammar
 */
class CUTS_Template_Config_List_Parser_Grammar :
  public boost::spirit::grammar <CUTS_Template_Config_List_Parser_Grammar>
{
public:
  CUTS_Template_Config_List_Parser_Grammar (const std::string & template_file,
                                            const std::string & output_dir,
                                            const CUTS_Property_Map & overrides);

  /// Destructor
  ~CUTS_Template_Config_List_Parser_Grammar (void);

  /**
   * Configure the grammar's behavior.
   */
  void configure (bool use_env, bool ignore_variables, bool ignore_commands);

  template <typename ScannerT>
  class definition
  {
  public:
    /**
      * Initializing constructor.
      *
      * @param[in]     self        The input grammar.
      */
    definition (CUTS_Template_Config_List_Parser_Grammar const & self)
    {
      using namespace boost::spirit;

      this->config_ =
        str_p ("config") >>
        confix_p ('(', (*anychar_p)[assign_a (this->filename_)] , ')') >>
        confix_p ('{', (*anychar_p)[parse_config (this->prop_map_, self.overrides_)], '}')[
          generate_file (self.template_file_,
                         self.output_dir_,
                         this->filename_,
                         this->prop_map_,
                         self.use_env_,
                         self.ignore_variables_,
                         self.ignore_commands_)];

      this->config_list_ = *this->config_;
    }

    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->config_list_;
    }

  private:
    struct parse_config
    {
      parse_config (CUTS_Property_Map & prop_map,
                    const CUTS_Property_Map & overrides)
        : prop_map_ (prop_map),
          overrides_ (overrides)
      {

      }

      template <typename IteratorT>
      void operator () (IteratorT begin, IteratorT end) const
      {
        // Empty the property map.
        if (!this->prop_map_.empty ())
          this->prop_map_.clear ();

        // Parse the configuration.
        CUTS_Property_Parser parser (this->prop_map_);
        if (!parser.parse (begin, end))
          ACE_ERROR ((LM_ERROR,
                      "%T (%t) - %M - failed to parse configuration "
                      "properties [%s]\n",
                      std::string (begin, end).c_str ()));

        // Insert the overrides into the property map.
        this->prop_map_.join (this->overrides_, true);
      }

    private:
      CUTS_Property_Map & prop_map_;

      const CUTS_Property_Map & overrides_;
    };

    struct generate_file
    {
      generate_file (const std::string & template_file,
                     const std::string & output_dir,
                     const std::string & filename,
                     const CUTS_Property_Map & prop_map,
                     const bool & use_env,
                     const bool & ignore_variables,
                     const bool & ignore_commands)
        : filename_ (filename),
          output_dir_ (output_dir),
          template_file_ (template_file),
          prop_map_ (prop_map),
          use_env_ (use_env),
          ignore_variables_ (ignore_variables),
          ignore_commands_ (ignore_commands)
      {
      }

      template <typename IteratorT>
      void operator () (IteratorT begin, IteratorT end) const
      {
        // Get filename extension of template file, if it exist.
        size_t pos = this->template_file_.find_last_of ('.');

        std::ostringstream ostr;
        ostr << this->output_dir_ << "/" << this->filename_;

        if (pos != std::string::npos)
          ostr << this->template_file_.substr (pos);

        // Now, generate the file using the template.
        std::ofstream outfile;
        outfile.open (ostr.str ().c_str ());

        // Open the template file for parsing.
        boost::spirit::
          file_iterator < > file_begin (this->template_file_.c_str ());

        if (file_begin)
        {
          // Locate the end of the template file.
          boost::spirit::file_iterator < > file_end = file_begin.make_end ();

          if (outfile.is_open ())
          {
            CUTS_Text_Processor processor (this->prop_map_);

            if (processor.evaluate (file_begin,
                                    file_end,
                                    outfile,
                                    this->use_env_,
                                    this->ignore_variables_,
                                    this->ignore_commands_) == 0)
            {
              ACE_DEBUG ((LM_DEBUG,
                          "%T (%t) - %M - successfully generated %s\n",
                          this->filename_.c_str ()));
            }
            else
            {
              ACE_ERROR ((LM_ERROR,
                          "%T (%t) - %M - failed to generate %s\n",
                          this->filename_.c_str ()));
            }

            outfile.close ();
          }
        }
      }

    private:
      const std::string & filename_;

      const std::string & output_dir_;

      const std::string & template_file_;

      const CUTS_Property_Map & prop_map_;

      const bool & use_env_;

      const bool & ignore_variables_;

      const bool & ignore_commands_;
    };

    std::string filename_;

    CUTS_Property_Map prop_map_;

    /// rule: config_;
    boost::spirit::rule <ScannerT> config_;

    boost::spirit::rule <ScannerT> config_list_;
  };

private:
  const std::string & template_file_;

  const std::string & output_dir_;

  const CUTS_Property_Map & overrides_;

  bool use_env_;

  bool ignore_variables_;

  bool ignore_commands_;
};

/**
 * @class CUTS_Template_Config_List_Parser
 */
class CUTS_Template_Config_List_Parser
{
public:
  /**
   * Initializing constructor
   *
   * @param[in]       overrides       Property overrides.
   */
  CUTS_Template_Config_List_Parser (const std::string & template_file,
                                    const std::string & output_dir,
                                    const CUTS_Property_Map & overrides);

  /// Destructor.
  ~CUTS_Template_Config_List_Parser (void);

  bool parse (const char * filename,
              bool use_env = false,
              bool ignore_variables = false,
              bool ignore_commands = false);
private:
  CUTS_Template_Config_List_Parser_Grammar grammar_;
};



#if defined (__CUTS_INLINE__)
#include "Template_Config_List_Parser.inl"
#endif

#endif  // !defined _CUTS_TEMPLATE_CONFIG_LIST_PARSER_H_
