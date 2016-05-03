#include "CHAOS_Servant_Configuration.h"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/foreach.hpp>


namespace iCCM
{
  namespace fusion = boost::fusion;
  namespace phoenix = boost::phoenix;
  namespace qi = boost::spirit::qi;
  namespace ascii = boost::spirit::ascii;
}

BOOST_FUSION_ADAPT_STRUCT (
    iCCM::Servant_Definition,
    (std::string, alias)
    (std::string, module)
    (std::string, symbol)
)

BOOST_FUSION_ADAPT_STRUCT (
    iCCM::Port_Definition,
    (std::string, type)
    (std::string, source)
    (std::string, servant)
    (std::string, destination)
)

BOOST_FUSION_ADAPT_STRUCT (
    iCCM::Servant_Configuration,
    (std::vector <iCCM::Servant_Definition>, servants)
    (std::vector <iCCM::Port_Definition>, ports)
)

namespace iCCM
{

template <typename IteratorT, typename SpaceT>
struct grammar_t :
  public boost::spirit::qi::grammar <IteratorT, Servant_Configuration (void), SpaceT>
{
  /// Type definition of the grammar's iterator type.
  typedef IteratorT iterator_type;

  /// Type definition of the grammar's space type.
  typedef SpaceT space_type;

  /// Default constructor.
  grammar_t (void)
    : grammar_t::base_type (config_)
    , config_ (std::string ("config"))
    , servants_ (std::string ("servants"))
    , servant_def_ (std::string ("servant-definition"))
    , ports_ (std::string ("ports"))
    , port_def_ (std::string ("port-definition"))
    , ident_ (std::string ("ident"))
  {
    namespace fusion = boost::fusion;
    namespace phoenix = boost::phoenix;
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    
    using namespace qi::labels;
    using qi::uint_;
    using qi::on_error;
    using qi::fail;
    using qi::debug;

    using phoenix::construct;
    using phoenix::val;

    this->config_ %= 
      this->servants_ >> this->ports_;

    this->servants_ %= 
      qi::lit ("servants:") >> +this->servant_def_;

    this->servant_def_ %=
      qi::lit ("servant") >> this->ident_ >> this->ident_ >> ":" >> this->ident_;

    this->ports_ %= 
      qi::lit ("ports:") >> +this->port_def_;

    this->port_def_ %= 
      qi::lit ("port") >> this->ident_ >> this->ident_ >> "=>" >> this->ident_ >> "." >> this->ident_;

    this->ident_ %=
      qi::lexeme[(qi::char_ ('_') | qi::alpha) >> *(qi::alnum | qi::char_ ('_'))];

    on_error <fail> (
      config_, std::cout
                    << val("Error! Expecting ")
                    << _4                               // what failed?
                    << val(" here: \"")
                    << construct<std::string>(_3, _2)   // iterators to error-pos, end
                    << val("\"")
                    << std::endl
            );
  }

private:
  boost::spirit::qi::rule <IteratorT, Servant_Configuration (void), SpaceT> config_;
  boost::spirit::qi::rule <IteratorT, std::vector <Servant_Definition> (void), SpaceT> servants_;
  boost::spirit::qi::rule <IteratorT, Servant_Definition (void), SpaceT> servant_def_;
 
  boost::spirit::qi::rule <IteratorT, std::vector <Port_Definition> (void), SpaceT> ports_;
  boost::spirit::qi::rule <IteratorT, Port_Definition (void), SpaceT> port_def_;

  boost::spirit::qi::rule <IteratorT, std::string (), SpaceT> ident_;
};

CHAOS_Servant_Configuration::
CHAOS_Servant_Configuration (const std::string & filename)
  : file_ (filename)
{

}

CHAOS_Servant_Configuration::~CHAOS_Servant_Configuration (void)
{

}

bool CHAOS_Servant_Configuration::operator >>= (Servant_Configuration & config)
{
  if (!this->file_.is_open ())
    return false;

  namespace spirit = boost::spirit;
  namespace qi = boost::spirit::qi;
  namespace phoenix = boost::phoenix;

  long flags = this->file_.flags ();

  if ((flags & std::ios::skipws) != 0)
    this->file_.unsetf (std::ios::skipws);

  // Initialize the stream iterators for the file.
  spirit::istream_iterator begin (this->file_);
  spirit::istream_iterator end;

  // Parse the contents for the file.
  grammar_t <spirit::istream_iterator, qi::ascii::space_type> grammar;

  bool retval =
    qi::phrase_parse (begin,
                      end,
                      grammar,
                      qi::ascii::space,
                      config);

  if ((flags & std::ios::skipws) != 0)
    this->file_.setf (std::ios::skipws);

  return retval;
}

}
