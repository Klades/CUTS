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
#include "cuts/utils/Property_Expander.h"
#include "ace/SString.h"
#include "boost/spirit/core.hpp"
#include "boost/spirit/utility/confix.hpp"
#include "boost/spirit/actor/assign_actor.hpp"
#include "boost/spirit/iterator/file_iterator.hpp"
#include <fstream>

// Forward decl.
class CUTS_Property_Map;

// Forward decl.
class CUTS_Template_Config_List_Parser;

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
  CUTS_Template_Config_List_Parser (const ACE_CString & template_file,
                                    const CUTS_Property_Map & overrides);

  /// Destructor.
  ~CUTS_Template_Config_List_Parser (void);

  bool parse (const char * filename);

private:
  /// Template file to complete with configurations.
  ACE_CString template_file_;

  /// Reference to property overrides.
  const CUTS_Property_Map & overrides_;
};

/**
 * @class CUTS_Template_Config_List_Parser_Grammar
 */
class CUTS_Template_Config_List_Parser_Grammar :
  public boost::spirit::grammar <CUTS_Template_Config_List_Parser_Grammar>
{
public:
  CUTS_Template_Config_List_Parser_Grammar (const ACE_CString & template_file);

  ~CUTS_Template_Config_List_Parser_Grammar (void);

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
        confix_p ('{', (*anychar_p)[parse_config (this->prop_map_)], '}')[
          generate_file (self.template_file_, this->filename_, this->prop_map_)];

      this->config_list_ = *this->config_;
    }

    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->config_list_;
    }

  private:
    struct parse_config
    {
      parse_config (CUTS_Property_Map & prop_map)
        : prop_map_ (prop_map)
      {

      }

      template <typename IteratorT>
      void operator () (IteratorT begin, IteratorT end) const
      {
        if (!this->prop_map_.empty ())
          this->prop_map_.clear ();

        CUTS_Property_Parser parser (this->prop_map_);
        parser.parse (begin, end);
      }

    private:
      CUTS_Property_Map & prop_map_;
    };

    struct generate_file
    {
      generate_file (const ACE_CString & template_file,
                     const std::string & filename,
                     const CUTS_Property_Map & prop_map)
        : begin_ (template_file.c_str ()),
          filename_ (filename),
          prop_map_ (prop_map)
      {
        if (this->begin_)
          this->end_ = this->begin_.make_end ();
      }

      template <typename IteratorT>
      void operator () (IteratorT begin, IteratorT end) const
      {
        // Now, generate the file using the template.
        std::ofstream outfile;
        outfile.open (this->filename_.c_str ());

        if (outfile.is_open ())
        {
          CUTS_Property_Expander expander (this->prop_map_);

          if (expander.expand (this->begin_, this->end_, true, outfile))
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

    private:
      const std::string & filename_;

      boost::spirit::file_iterator < > begin_;

      boost::spirit::file_iterator < > end_;

      const CUTS_Property_Map & prop_map_;
    };

    std::string filename_;

    CUTS_Property_Map prop_map_;

    /// rule: config_;
    boost::spirit::rule <ScannerT> config_;

    boost::spirit::rule <ScannerT> config_list_;
  };

private:
  const ACE_CString & template_file_;
};

#if defined (__CUTS_INLINE__)
#include "Template_Config_List_Parser.inl"
#endif

#endif  // !defined _CUTS_TEMPLATE_CONFIG_LIST_PARSER_H_
