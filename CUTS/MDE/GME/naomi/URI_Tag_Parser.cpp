// $Id$

#include "URI_Tag_Parser.h"
#include "boost/spirit/core.hpp"
#include "boost/spirit/utility/confix.hpp"
#include "boost/spirit/iterator/file_iterator.hpp"
#include "boost/spirit/actor.hpp"

///////////////////////////////////////////////////////////////////////////////
// CUTS_URI_Tag_Grammar

struct CUTS_URI_Tag_Grammar : 
  public boost::spirit::grammar <CUTS_URI_Tag_Grammar>
{
  /**
   * Initializing constructor.
   *
   * @param[in]       project               Target project.
   * @param[in]       deployment_folder     Target deployment folder.
   * @param[in]       options               Application options.
   */
  CUTS_URI_Tag_Grammar (std::string & attribute_tag,
                        std::string & gme_attr)
    : naomi_attribute_ (attribute_tag),
      gme_attribute_ (gme_attr)
  {

  }

  template <typename ScannerT>
  struct definition
  {
    // naomi:\\attribute.name[@object.attribute]

    /**
     * Initializing constructor.
     *
     * @param[in]     self        The input grammar.
     */
    definition (CUTS_URI_Tag_Grammar const & self)
    {
      // Create the string for recognizing the NAOMI protocol.
      this->protocol_ = boost::spirit::str_p ("naomi:\\\\");

      // Determine if we are searching for a specific attribute,
      // or getting the name of the attribute.
      if (self.naomi_attribute_.empty ())
      {
        this->naomi_attribute_ =
          (*(boost::spirit::anychar_p - boost::spirit::ch_p ('@'))) [
            boost::spirit::assign_a (self.naomi_attribute_)];
      }
      else
      {
        this->naomi_attribute_ =
          boost::spirit::str_p (self.naomi_attribute_.begin (),
                                self.naomi_attribute_.end ());
      }

      // Create the expression for recognizing the GME attribute.
      this->gme_attribute_ = 
        boost::spirit::ch_p ('@') >> 
          (*boost::spirit::anychar_p)[
            boost::spirit::assign_a (self.gme_attribute_)];

      this->attribute_tag_ = boost::spirit::lexeme_d[
        this->protocol_ >> this->naomi_attribute_ >> !this->gme_attribute_];
    }

    /**
     * Start of the input grammar.
     *
     * @return        Starting expression for the grammar.
     */
    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->attribute_tag_;
    }

  private:   
    /// rule: protocol_
    boost::spirit::rule <ScannerT> protocol_;

    /// rule: naomi_attribute_
    boost::spirit::rule <ScannerT> naomi_attribute_;

    /// rule: gme_attribute_
    boost::spirit::rule <ScannerT> gme_attribute_;

    /// rule: deployment_member_
    boost::spirit::rule <ScannerT> attribute_tag_;

    definition (const definition &);
    const definition & operator = (const definition &);
  };

  /// The target GME project.
  std::string & naomi_attribute_;

  /// GME attribute that contains the NAOMI attribute.
  std::string & gme_attribute_;
};

///////////////////////////////////////////////////////////////////////////////
// CUTS_URI_Tag_Parser

//
// CUTS_URI_Tag_Parser
//
CUTS_URI_Tag_Parser::CUTS_URI_Tag_Parser (void)
{

}

//
// ~URI_Tag_Parser
//
CUTS_URI_Tag_Parser::~CUTS_URI_Tag_Parser (void)
{

}

//
// parse
//
bool CUTS_URI_Tag_Parser::parse (const std::string & uri, 
                                 std::string & attr, 
                                 std::string & gme_attr)
{
  // Create the grammer parser for the attribute.
  std::string temp_attr;
  CUTS_URI_Tag_Grammar grammar (attr, temp_attr);

  // Parse the specified string.
  boost::spirit::parse_info <
    std::string::const_iterator> result = 
    boost::spirit::parse (uri.begin (), uri.end (),  grammar);

  // Update the GME attribute.
  if (result.full)
    gme_attr = temp_attr;

  return result.full;
}
