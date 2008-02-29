// $Id$

#include "Scatter_To_Picml.h"
#include "boost/spirit/core.hpp"
#include "boost/spirit/utility/confix.hpp"
#include "boost/spirit/iterator/file_iterator.hpp"
#include "boost/spirit/actor.hpp"
#include "gme/GME.h"

namespace actions
{
//=============================================================================
/**
 * @struct deploy_instance
 */
//=============================================================================

struct deploy_instance
{
  deploy_instance (CUTS_Deployment_Map & deployment, 
                   const std::string & node, 
                   const std::string & instance)
    : deployment_ (deployment),
      node_ (node),
      instance_ (instance)
  {

  }

  void operator () (char) const
  {
    if (!this->node_.empty () && !this->instance_.empty ())
      this->deployment_[this->node_].insert (this->instance_);
  }

private:
  CUTS_Deployment_Map & deployment_;

  const std::string & node_;
  
  const std::string & instance_;
};
}

//=============================================================================
/**
 * @class CUTS_Scatter_To_Picml_Parser
 */
//=============================================================================

struct CUTS_Scatter_To_Picml_Parser :
  public boost::spirit::grammar <CUTS_Scatter_To_Picml_Parser>
{
  CUTS_Scatter_To_Picml_Parser (CUTS_Deployment_Map & deployment)
    : deployment_ (deployment)
  {

  }

  template <typename ScannerT>
  struct definition
  {
    /**
     * Initializing constructor.
     *
     * @param[in]     self        The input grammar.
     */
    definition (CUTS_Scatter_To_Picml_Parser const & self)
    {
      this->comment_ = 
        boost::spirit::comment_p ("/**", "**/");

      this->special_chars_ = 
        boost::spirit::ch_p (';') | ':';

      this->identifier_ =
        boost::spirit::lexeme_d [
          (boost::spirit::alpha_p | boost::spirit::ch_p ('_')) >>
            *(boost::spirit::anychar_p - (boost::spirit::ch_p (':') | ';'))];

      this->component_ =
        boost::spirit::lexeme_d [
          *(boost::spirit::anychar_p - boost::spirit::ch_p (':'))];

      this->host_ = 
        boost::spirit::lexeme_d [
          *(boost::spirit::anychar_p - boost::spirit::ch_p (';'))];

      this->deployment_ =
        this->component_[boost::spirit::assign_a (this->component_id_)] >>
        ':' >> this->host_[boost::spirit::assign_a (this->host_id_)] >>
        boost::spirit::ch_p (';')[actions::deploy_instance (self.deployment_,
                                                            this->host_id_,
                                                            this->component_id_)] ;

      this->deployment_list_ = *(this->deployment_);

      this->start_ = this->deployment_list_ /*| this->comment_*/;
    }

    /**
     * Start of the input grammar.
     *
     * @return        Starting expression for the grammar.
     */
    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->start_;
    }

  private:   
    std::string component_id_;

    std::string host_id_;

    /// rule: identifier_
    boost::spirit::rule <ScannerT> special_chars_;

    /// rule: identifier_
    boost::spirit::rule <ScannerT> identifier_;

    /// rule: comment_
    boost::spirit::rule <ScannerT> comment_;

    /// rule: component_
    boost::spirit::rule <ScannerT> component_;

    /// rule: host_
    boost::spirit::rule <ScannerT> host_;

    /// rule: deployment_
    boost::spirit::rule <ScannerT> deployment_;

    /// rule: deployment_list_
    boost::spirit::rule <ScannerT> deployment_list_;

    /// rule: start_
    boost::spirit::rule <ScannerT> start_;

  private:
    definition (const definition &);
    const definition & operator = (const definition &);
  };

  CUTS_Deployment_Map & deployment_;
};

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Scatter_To_Picml

//
// CUTS_Scatter_To_Picml
//
CUTS_Scatter_To_Picml::CUTS_Scatter_To_Picml (void)
{

}

//
// ~CUTS_Scatter_To_Picml
//
CUTS_Scatter_To_Picml::~CUTS_Scatter_To_Picml (void)
{

}

//
// run
//
bool CUTS_Scatter_To_Picml::
run (const std::string & filename, CUTS_Deployment_Map & deployment)
{
  // Get an iterator to the beginning of the file.
  boost::spirit::file_iterator < > first (filename);

  if (!first)
    return false;

  // Get an iterator to the end of the file.
  boost::spirit::file_iterator < > last = first.make_end ();
  
  // Parse the select file.
  CUTS_Scatter_To_Picml_Parser parser (deployment);

  boost::spirit::parse_info <
    boost::spirit::file_iterator < > > result =
    boost::spirit::parse (first, last, parser);

  return result.hit;
}
