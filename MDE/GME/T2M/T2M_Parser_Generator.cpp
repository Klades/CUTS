// $Id$

#include "T2M_Parser_Generator.h"

#define BOOST_SPIRIT_DEBUG
#include "boost/spirit/core.hpp"
#include "boost/spirit/actor/assign_actor.hpp"
#include "boost/spirit/iterator/file_iterator.hpp"
#include "boost/spirit/utility/confix.hpp"
#include "boost/spirit/utility/lists.hpp"

// code generation headers
#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <set>

namespace actor
{
  // Actor that outputs a string to the specified stream.  The string is fixed
  // at the time of actor instantiation (i.e. when the grammar is declared).
  struct output
  {
    output (std::ostream & outstream)
      : out_ (outstream)
    {

    }

    template <typename iterator_t>
    void operator () (iterator_t const & first, iterator_t const & last) const
    {
      std::string str (first, last);
      out_ << str;
    }

  private:
    std::ostream & out_;
  };

  /**
   * @struct output_create_model
   *
   * Actor that outputs a string to the specified stream.  The string is
   * fixed at the time of actor instantiation (i.e. when the grammar
   * is declared).
   */
  struct output_create_model
  {
    output_create_model (std::ostream & outstream, const std::string & model_type)
      : out_ (outstream),
        model_type_ (model_type)
    {

    }

    template <typename iterator_t>
    void operator () (iterator_t const &, iterator_t const &) const
    {
      this->out_
        << "[T2M_actor::create_model (model_, self.parent_, \""
        << this->model_type_
        << "\")]";
    }

  private:
    std::ostream & out_;

    const std::string & model_type_;
  };

  /**
   * @struct append_rule_decl
   *
   * Actor that outputs a string to the specified stream.  The string is fixed
   * at the time of actor instantiation (i.e. when the grammar is declared).
   */
  struct append_rule_decl
  {
    append_rule_decl (std::string & rule_decl)
      : rule_decl_ (rule_decl)
    {

    }

    template <typename iterator_t>
    void operator () (iterator_t const & start, iterator_t const & end) const
    {
      std::string rule_name (start, end);

      std::ostringstream ostr;
      ostr
        << this->rule_decl_
        << "boost::spirit::rule <ScannerT> T2M_" << rule_name << "_;"
        << std::endl;

      this->rule_decl_ = ostr.str ();
    }

  private:
    std::string & rule_decl_;
  };

  /**
   * @struct output_rule_name
   *
   * Actor that outputs a string to the specified stream.  The string is fixed
   * at the time of actor instantiation (i.e. when the grammar is declared).
   */
  struct output_rule_name
  {
    output_rule_name (std::ostream & outstream)
      : out_ (outstream)
    {

    }

    template <typename iterator_t>
    void operator () (iterator_t const & first, iterator_t const & last) const
    {
      std::string str (first, last);
      out_ << "this->T2M_" << str << "_";
    }

  private:
    std::ostream & out_;
  };

  /**
   * @struct output_const
   *
   * Actor that outputs a string to the specified stream.  The string is fixed
   * at the time of actor instantiation (i.e. when the grammar is declared).
   */
  struct output_const
  {
    output_const (std::ostream & outstream, const std::string & output)
      : out_ (outstream), output_ (output)
    {

    }

    template <typename iterator_t>
    void operator () (iterator_t const & first, iterator_t const & last) const
    {
      out_ << output_;
    }

  private:
    std::ostream & out_;
    const std::string output_;
  };

  // Actor that outputs a string to the specified stream.  The string is held by
  // reference, so it can be a variable in the grammar.
  struct output_var
  {
    output_var (std::ostream & outstream, const std::string & output)
      : out_ (outstream), output_ (output)
    {

    }

    template <typename iterator_t>
    void operator () (iterator_t const & first, iterator_t const & last) const
    {
      out_ << output_;
    }

  private:
    std::ostream & out_;
    const std::string & output_;
  };

  // Actor that outputs a string to the specified stream.  The string is held by
  // reference, so it can be a variable in the grammar.
  struct output_start_rule
  {
    output_start_rule (std::ostream & outstream, const std::string & start)
      : out_ (outstream),
        start_ (start)
    {

    }

    template <typename iterator_t>
    void operator () (iterator_t const & , iterator_t const &) const
    {
      this->out_
        << "}"
        << "const boost::spirit::rule <ScannerT> & start (void) const"
        << "{"
        << "return this->T2M_" << this->start_ << "_;"
        << "}";
    }

  private:
    std::ostream & out_;

    const std::string & start_;
  };

  /**
   * @struct output_rule_assign
   */
  struct output_rule_assign
  {
    output_rule_assign (std::ostream & outstream)
      : out_ (outstream)
    {

    }

    template <typename iterator_t>
    void operator () (iterator_t const & start, iterator_t const & end) const
    {
      output_rule_name rule_name (this->out_);
      rule_name (start, end);

      this->out_ << " = " << std::endl;
    }

  private:
    std::ostream & out_;
  };

  struct output_rule_def
  {
    output_rule_def (std::ostream & outstream, const std::string & rule_def)
      : out_ (outstream),
        rule_def_ (rule_def)
    {

    }

    template <typename iterator_t>
    void operator () (iterator_t const & , iterator_t const & ) const
    {
      this->out_ << this->rule_def_ << ";" << std::endl;
    }

  private:
    std::ostream & out_;

    const std::string & rule_def_;
  };

  /**
   * @struct wrap
   *
   * Replaces the contents of a string, adding prefix to the front and
   * suffix to the end of the original string.
   */
  struct wrap
  {
    wrap (std::string & str,
          const std::string & prefix,
          const std::string & suffix)
      : str_ (str),
        prefix_ (prefix),
        suffix_ (suffix)
    {

    }

    template <typename iterator_t>
    void operator () (iterator_t const & first, iterator_t const & last) const
    {
      std::ostringstream ostr;
      ostr << this->prefix_ << this->str_ << this->suffix_;

      this->str_ = ostr.str ();
    }

  private:
    /// Target string to wrap.
    std::string & str_;

    /// Prefix for the target string.
    const std::string prefix_;

    /// Suffix for the target string.
    const std::string suffix_;
  };

  // Appends the contents of one string to another, with an optional spacer.  Both strings are held
  // by reference so they can be variables in the grammar.
  struct append
  {
    append (std::string & str,
            const std::string & to_append,
            const std::string & spacer = "")
      : str_ (str),
        to_append_ (to_append),
        spacer_ (spacer)
    {

    }

    template <typename iterator_t>
    void operator () (iterator_t const & first, iterator_t const & last) const
    {
      str_ += spacer_ + to_append_;
    }

  private:
    std::string & str_;

    const std::string & to_append_;

    std::string spacer_;
  };

  /**
   * @sturct prepend_a
   *
   * Inserts a string, or character, at the front of a string.
   */
  struct prepend_a
  {
    //
    // prepend_a
    //
    prepend_a (std::string & str)
      : str_ (str)
    {

    }

    //
    // operator ()
    //
    template <typename iterator_t>
    void operator () (iterator_t const & first, iterator_t const & last) const
    {
      std::string to_prepend  (first, last);

      std::ostringstream ostr;
      ostr << to_prepend  << this->str_;

      this->str_ = ostr.str ();
    }

  private:
    std::string & str_;
  };

  // Pushes the string onto the stack;
  // both are held by reference so they can be variables in the grammar.
  struct push
  {
    push (std::stack <std::string> & s, std::string const & var)
      : s_ (s), var_ (var)
    {

    }

    template <typename iterator_t>
    void operator () (iterator_t const & first, iterator_t const & last) const
    {
      s_.push (var_);
    }

  private:
    std::stack <std::string> & s_;

    std::string const & var_;
  };

  // Pops the top of the stack into the string;
  // both are held by reference so they can be variables in the grammar.
  struct pop
  {
    pop (std::stack <std::string> & s, std::string & var)
      : s_ (s), var_ (var)
    {

    }

    template <typename iterator_t>
    void operator () (iterator_t const & first, iterator_t const & last) const
    {
      var_ = s_.top();
      s_.pop();
    }

  private:
    std::stack <std::string> & s_;

    std::string & var_;
  };
}

/**
 * @struct T2M_Parser_Grammar
 *
 * Boost grammar used by the text-2-model parser generator.
 */
struct T2M_Parser_Grammar :
  public boost::spirit::grammar <T2M_Parser_Grammar>
{
  //
  // T2M_Parser_Grammar
  //
  T2M_Parser_Grammar (std::ofstream & outfile)
    : outfile_ (outfile)
  {

  }

  /**
   * @struct definition
   *
   * Actual definition of the parser's grammar.
   */
  template <typename ScannerT>
  struct definition
  {
    //
    // definition
    //
    definition (T2M_Parser_Grammar const & self)
    {
      // Top-level rule.  Semantic actions finish printing the grammar with the start state and rule declarations.
      this->t2m_ =
        this->preprocessor_ >> (*this->t2m_rule_)
          [actor::output_start_rule (self.outfile_, this->start_rule_)]
          [actor::output_var (self.outfile_, this->rule_declarations_)];

      // Matches start rule specifier, saves name of start rule to start_rule_.
      this->preprocessor_ =
          boost::spirit::str_p ("#pragma start (")
            >> (*boost::spirit::alnum_p)[boost::spirit::assign_a (this->start_rule_)]
            >> ")";

      // The various rule types.  Except for temp_rule_, each corresponds to a GME type.
      //this->t2m_rule_ =
      //  this->model_rule_ | this->connection_rule_ |  this->reference_rule_ | this->temp_rule_;

      this->t2m_rule_ =
        // declaration of the rule's type
        this->rule_type_
          [boost::spirit::assign_a (this->rule_typename_)] >>
        // name assigned to the rule
        this->ncname_
          [actor::output_rule_assign (self.outfile_)]
          [actor::append_rule_decl (this->rule_declarations_)] >>
        // start of the rule definition
        boost::spirit::str_p (":") >> this->rule_def_ >>
        // end of the rule
        boost::spirit::str_p (";")
          [actor::output_rule_def (self.outfile_, this->full_rule_)];

      this->rule_type_ =
        boost::spirit::str_p ("connection") | "model" | "temp" |
        "reference" | "atom" | "set";

      // Matches model rules
      //this->model_rule_ =
      //  "model" >> this->ncname_
      //  // These actions save the rule name and print the start of the rule definition.
      //    [boost::spirit::assign_a (this->rule_name_)]
      //    [actor::output_rule_assign (self.outfile_)]
      //    [actor::output_const (self.outfile_, "(")] >>
      //  ":" >> this->rule_
      //  // These actions output the rule and associated semantic action
      //  // and add the rule to the list of declarations for later.
      //    [actor::output_var (self.outfile_, this->full_rule_)]
      //    [actor::output_const (self.outfile_, ")")]
      //    [actor::output_create_model (self.outfile_, this->rule_name_)]
      //    [actor::output_const (self.outfile_, ";\n")]
      //    [actor::append_rule_decl (this->rule_declarations_, this->rule_name_)] >>
      //  boost::spirit::str_p (";");

      // Matches connection rules, comparable to model rule
      //this->connection_rule_ =
      //  "connection" >> this->ncname_
      //    [boost::spirit::assign_a (this->rule_name_)]
      //    [actor::output_rule_name (self.outfile_)]
      //    [actor::output_const (self.outfile_, " = (")]
      //  >> ":"
      //  >> this->rule_
      //    [actor::output_var (self.outfile_, this->full_rule_)]
      //    [actor::output_const (self.outfile_,
      //      ")[T2M_actor::create_connection (conn_, self.parent_, src_, dst_, \"")]
      //    [actor::output_var (self.outfile_, this->rule_name_)]
      //    [actor::output_const (self.outfile_, "\")]")]
      //    [actor::wrap (this->rule_name_,
      //      "boost::spirit::rule <ScannerT> T2M_", "_;\n")]
      //    [actor::append (this->rule_declarations_, this->rule_name_)]
      //  >> boost::spirit::str_p (";")
      //    [actor::output_const (self.outfile_, ";\n")];

      // Matches connection rules, comparable to model rule. The only difference
      // is the reference trys to find a model element with the specified name.
      //this->reference_rule_ =
      //  "reference" >> this->ncname_
      //    [boost::spirit::assign_a (this->rule_name_)]
      //    [actor::output_rule_name (self.outfile_)]
      //    [actor::output_const (self.outfile_, " = (")]
      //  >> ":" >> this->rule_
      //    //[actor::output_var <iterator_t> (self.outfile_, this->full_rule_)]
      //    //[actor::output_const <iterator_t> (self.outfile_,
      //    //  ")[T2M_actor::create_reference <iterator_t> (ref_, self.parent_, \"")]
      //    //[actor::output_var <iterator_t> (self.outfile_, this->rule_name_)]
      //    //[actor::output_const <iterator_t> (self.outfile_, "\")]")]
      //    //[actor::wrap <iterator_t> (this->rule_name_,
      //    //  "    boost::spirit::rule <ScannerT> T2M_", "_;\n")]
      //    //[actor::append <iterator_t> (this->rule_declarations_, this->rule_name_)]
      //  >> boost::spirit::str_p (";");
      //    //[actor::output_const <iterator_t> (self.outfile_, ";\n")];

      // The temporary rule is like the other rules, but it doesn't print a semantic action.
      //this->temp_rule_ =
      //  "temp" >> this->ncname_
      //    [boost::spirit::assign_a (this->rule_name_)]
      //    [actor::append_rule_decl (this->rule_declarations_, this->rule_name_)]
      //    [actor::output_rule_name (self.outfile_)]
      //    [actor::output_const (self.outfile_, " = ")]
      //  >> ':' >> this->rule_
      //    [actor::output_var (self.outfile_, this->full_rule_)]
      //    [actor::output_const (self.outfile_, ";\n")]
      //  >> ';';

      // The main part of a rule is a series of elements, either in sequence
      // or separated by '|' for or.
      this->rule_def_ =
        // start a new rule
        this->rule_element_[boost::spirit::assign_a (this->full_rule_, this->rule_elem_)] >>
        // append each rule_elem_ to the full rule.
        *(this->rule_element_[actor::append (this->full_rule_, this->rule_elem_, " >>\n")]);

      // Each rule definition is either a subrule in parentheses or a keyword,
      // text, or subrule. Either way, it can be followed by a series of grammar
      // symbols.

      this->rule_element_ =
        this->keyword_ | this->text_ | this->subrule_;

      this->subrule_ =
        // single subrule
        ((this->name_ >>
        !(this->symbol_[actor::prepend_a (this->rule_elem_)]))) |
        // group of subrules
        (boost::spirit::str_p ("(")
          [actor::push (this->rule_def_stack_, this->full_rule_)] >>
        this->name_[boost::spirit::assign_a (this->full_rule_, this->rule_elem_)] >>
            *("|" >> this->name_[actor::append (this->full_rule_, this->rule_elem_, " | ")]) >>
        // copy the group back into the rule_elem_
        boost::spirit::str_p (")")
          [actor::wrap (this->full_rule_, "(", ")")]
          [boost::spirit::assign_a (this->rule_elem_, this->full_rule_)] >>
          // apply any symbols to the grouping
          !(this->symbol_[actor::prepend_a (this->rule_elem_)]))
          // pop the saved set of rules
          [actor::pop (this->rule_def_stack_, this->full_rule_)];

      // Matches the various symbols that can follow a word or parentheses,
      // generates corresponding symbols in necessary position for a spirit parser,
      // and adds parens to make sure we keep the ordering
      this->symbol_ =
        boost::spirit::str_p ("!") | "*" | "+";

        //boost::spirit::confix_p ("[", boost::spirit::str_p ("src"), "]")
        //  [actor::wrap (this->rule_elem_,
        //    "(", ")[boost::spirit::assign_a (this->src_, this->model_)]")] |
        //boost::spirit::confix_p ("[", boost::spirit::str_p ("dst"), "]")
        //  [actor::wrap (this->rule_elem_,
        //    "(", ")[boost::spirit::assign_a (this->dst_, this->model_)]")];

      // A name should be the name of another rule,
      // so it should match anything that can be an identifier in C.
      this->ncname_ =
        boost::spirit::lexeme_d[
          ((boost::spirit::alpha_p | "_") >> *(boost::spirit::alnum_p | "_"))];

      this->name_ =
        this->ncname_[boost::spirit::assign_a (this->rule_elem_)]
                     [actor::wrap (this->rule_elem_, "this->T2M_", "_")];

      // Matches quoted text, generates parser to match the text
      this->strlit_ =
        boost::spirit::confix_p ('"', *(boost::spirit::anychar_p - '"'), '"');

      this->text_ = this->strlit_
        [boost::spirit::assign_a (this->rule_elem_)]
        [actor::wrap (this->rule_elem_, "boost::spirit::str_p (", ")")];

      // Matches keywords, generates parser for associated type.
      this->keyword_ =
        boost::spirit::str_p ("IDENT")
          [boost::spirit::assign_a (this->rule_elem_,
          "boost::spirit::lexeme_d[((boost::spirit::alpha_p | \"_\") >> *(boost::spirit::alnum_p | \"_\"))]")]
        | boost::spirit::str_p ("INT")
          [boost::spirit::assign_a (this->rule_elem_, "boost::spirit::int_p")]
        | boost::spirit::str_p ("FLOAT")
          [boost::spirit::assign_a (this->rule_elem_, "boost::spirit::real_p")]
        | boost::spirit::str_p ("STRING")
          [boost::spirit::assign_a (this->rule_elem_,
            "boost::spirit::confix_p (\"\\\"\", +boost::spirit::anychar_p, \"\\\"\")")];

      BOOST_SPIRIT_DEBUG_RULE (this->t2m_);
      BOOST_SPIRIT_DEBUG_RULE (this->preprocessor_);
      BOOST_SPIRIT_DEBUG_RULE (this->t2m_rule_);
      BOOST_SPIRIT_DEBUG_RULE (this->rule_def_);
      BOOST_SPIRIT_DEBUG_RULE (this->rule_type_);
      BOOST_SPIRIT_DEBUG_RULE (this->subrule_);
      BOOST_SPIRIT_DEBUG_RULE (this->symbol_);
      BOOST_SPIRIT_DEBUG_RULE (this->keyword_);
      BOOST_SPIRIT_DEBUG_RULE (this->name_);
      BOOST_SPIRIT_DEBUG_RULE (this->ncname_);
      BOOST_SPIRIT_DEBUG_RULE (this->strlit_);
      BOOST_SPIRIT_DEBUG_RULE (this->text_);
    }

    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->t2m_;
    }

  private:
    boost::spirit::rule <ScannerT> t2m_;

    boost::spirit::rule <ScannerT> preprocessor_;

    boost::spirit::rule <ScannerT> t2m_rule_;

    boost::spirit::rule <ScannerT> model_rule_;

    boost::spirit::rule <ScannerT> connection_rule_;

    boost::spirit::rule <ScannerT> reference_rule_;

    boost::spirit::rule <ScannerT> temp_rule_;

    boost::spirit::rule <ScannerT> rule_type_;

    boost::spirit::rule <ScannerT> rule_element_;

    boost::spirit::rule <ScannerT> rule_def_;

    boost::spirit::rule <ScannerT> subrule_;

    boost::spirit::rule <ScannerT> symbol_;

    boost::spirit::rule <ScannerT> name_;

    boost::spirit::rule <ScannerT> text_;

    boost::spirit::rule <ScannerT> keyword_;

    boost::spirit::rule <ScannerT> ncname_;

    boost::spirit::rule <ScannerT> strlit_;

    std::string rule_typename_;

    std::string start_rule_;

    std::string rule_elem_;

    std::string full_rule_;

    std::string rule_declarations_;

    std::string rule_name_;

    // Stores current rule_def_ while parsing one inside parentheses
    std::stack <std::string> rule_def_stack_;

    std::set <std::string> t2m_rules_;
  };

private:
  std::ofstream & outfile_;
};

///////////////////////////////////////////////////////////////////////////////
// class T2M_Parser_Generator

//
// parse
//
int T2M_Parser_Generator::parse (std::string filename)
{
  // Get name from filename (everything up to last '.', if present)
  this->basename_ = filename.substr (0, filename.find_last_of ('.'));

  // Parameterized because it looks like a good idea
  typedef char char_t;
  typedef boost::spirit::file_iterator <char_t> iterator_t;

  // Set up file iterator for T2M input
  iterator_t first (filename);

  if (!first)
    return 1;

  iterator_t last = first.make_end();

  // Open output file streams
  this->cpp_file_.open ((this->basename_ + "_T2M.cpp").c_str ());

  this->h_file_.open ((this->basename_ + "_T2M.h").c_str ());
  this->mpc_file_.open ((this->basename_ + "_T2M.mpc").c_str ());

  // Generate MPC file
  mpc_file_
    << "// $Id$" << std::endl
    << std::endl
    << "project : boost_base, cuts_gme, cutslib {" << std::endl
    << "  sharedname = " << this->basename_ << "_T2M" << std::endl
    << std::endl
    << "  dllout = ./lib" << std::endl
    << "  libout = ./lib" << std::endl
    << std::endl
    // An "includes =" statement might be needed here to
    // add the header file with the actors to the include path.
    << "  prebuild += $(MPC_ROOT)/generate_export_header.pl "
    << basename_ << " " << basename_ << "_T2M_export.h" << std::endl
    << std::endl
    << "  Header_Files {" << std::endl
    << "    " << basename_ << "_T2M.h" << std::endl
    << "  }" << std::endl
    << std::endl
    << "  Source_Files {" << std::endl
    << "    " << basename_ << "_T2M.cpp" << std::endl
    << "  }" << std::endl
    << "}" << std::endl
    << std::endl;

  this->mpc_file_.close ();

  // Generate header file
  h_file_ << "#ifndef _T2M_" << basename_ << "_H_\n"
    << "#define _T2M_" << basename_ << "_H_\n\n"
    << "#include \"" << basename_ << "_T2M_export.h\"\n"
    << "#include \"gme/GME.h\"\n"
    << "#include <string>\n\n"
    << "class " << basename_ << "_T2M\n"
    << "{\npublic:\n"
    << "  bool parse (GME::Project & project, GME::Object & parent, const std::string & filename);\n"
    << "};\n\n"
    << "#endif" << std::endl;

  this->h_file_.close ();

  /// Indentation implanter.
  {
    typedef Indentation::Implanter <Indentation::Cxx, char> Formatter_Type;
    Formatter_Type formatter (this->cpp_file_);

    // Begin generating cpp file
    cpp_file_
      << "// $Id$" << std::endl
      << std::endl
      << "#include \"" << basename_ << "_T2M.h\"" << std::endl
      << "#include \"T2M_actors.h\"" << std::endl
      << std::endl
      << "#include \"gme/GME.h\"" << std::endl
      << std::endl
      << "#include \"boost/spirit/core.hpp\"" << std::endl
      << "#include \"boost/spirit/iterator/file_iterator.hpp\"" << std::endl
      << std::endl
      << "#include <string>" << std::endl
      << std::endl
      << "struct " << basename_ <<"_T2M_grammar :" << std::endl
      << "  public boost::spirit::grammar <" << basename_ << "_T2M_grammar>" << std::endl
      << "{" << basename_ << "_T2M_grammar (GME::Project & project, GME::Object & parent)" << std::endl
      << ": project_ (project), parent_ (parent)"
      << "{"
      << "}"

      << "template <typename ScannerT>" << std::endl
      << "struct definition {"
      << "definition (" << basename_ << "_T2M_grammar const & self) {"
      << "typedef typename ScannerT::iterator_t iterator_t;" << std::endl;

    // The parser will output the rule definitions, the start rule, and the rule declarations.
    T2M_Parser_Grammar parser_generator (cpp_file_);
    BOOST_SPIRIT_DEBUG_NODE (parser_generator);

    boost::spirit::parse_info <iterator_t> result =
      boost::spirit::parse (first, last,
                            parser_generator >> boost::spirit::end_p,
                            boost::spirit::space_p |
                              boost::spirit::comment_p ("//") |
                              boost::spirit::comment_p ("/*", "*/"));

    cpp_file_ << "private:" << std::endl
      << "GME::Model model_, src_, dst_;"
      << "GME::Connection conn_;"
      << "};"
      << "private:" << std::endl
      << "GME::Project & project_;"
      << "GME::Object & parent_;"
      << "};"
      << "// grammar " << result.full << std::endl
      << std::endl
      << "bool "
      << basename_
      << "_T2M::parse (GME::Project & project, GME::Object & parent, const std::string & filename)"
      << "{"
      << "typedef char char_t;"
      << "typedef boost::spirit::file_iterator <char_t> iterator_t;" << std::endl
      << "iterator_t first (filename);"
      << "if (!first)" << std::endl
      << "return false;" << std::endl
      << "iterator_t last = first.make_end();"
      << std::endl
      << "" << basename_ << "_T2M_grammar " << basename_ << "_parser (project, parent);" << std::endl
      << "boost::spirit::parse_info <iterator_t> result =" << std::endl
      << "boost::spirit::parse (first, last," << std::endl
      << "" << basename_ << "_parser >> boost::spirit::end_p," << std::endl
      << "boost::spirit::space_p);" << std::endl
      << "return result.full;"
      << "}";
  }

  this->cpp_file_.close ();

  return 0;
}
