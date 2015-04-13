// $Id:

#include "Setaf_App.h"
#include "Setaf_Lang_Compiler.h"
#include "Setaf_Code_Generator.h"
#include "ace/Get_Opt.h"
#include "ace/CORBA_macros.h"
#include "ace/Log_Msg.h"


static const char * __HELP__ =
"Setaf - Generate code to adapt log formats for UNITE\n"
"\n"
"USAGE: cuts-setaf [OPTIONS]\n"
"\n"
"General options:\n"
"  -f, --file=FILE           input file containing the script\n"
"  -o, --output-dir=PATH     path of the directory to generate code\n"
"  -h, --help                print this help message\n";

//
// CUTS_Setaf_App
//
CUTS_Setaf_App::CUTS_Setaf_App (void)
{

}

//
// ~CUTS_Setaf_App
//
CUTS_Setaf_App::~CUTS_Setaf_App (void)
{

}

//
// run_main
//
int CUTS_Setaf_App::run_main (int argc, char * argv [])
{
  CUTS_SETAF_UTILS::Setaf_Entries entries;
  CUTS_SETAF_UTILS::Setaf_Relations relations;
  CUTS_SETAF_UTILS::string_vector var_decls;
  CUTS_SETAF_UTILS::Setaf_Code codes;
  std::string init_code ("");
  std::string reset_code ("");
  CUTS_Setaf_Lang_Compiler compiler;

  if (this->parse_args (argc, argv) == -1)
      return -1;

  // open the file

  std::ifstream file (this->input_file_.c_str ());
  std::ostringstream buf;
  buf << file.rdbuf ();
  std::string str = buf.str ();

  // Compile the file and populate the objects

  if(!compiler.compile (
    str.c_str (), entries, relations, var_decls, codes, init_code, reset_code))
    ACE_ERROR_RETURN ((LM_ERROR,
        ACE_TEXT ("%T (%t) - %M - Compilation failed error in the file %s\n"),
        this->input_file_.c_str ()),
        -1);

  // Generate the code by visiting the populated objects

  const char * adapter_name = this->extract_name ();

  CUTS_Setaf_Code_Generator code_generator
    (this->output_dir_.c_str (), adapter_name);

  code_generator.entries (entries);
  code_generator.relations (relations);
  code_generator.variable_decls (var_decls);
  code_generator.setaf_code (codes);
  code_generator.init_str (init_code);
  code_generator.reset_str (reset_code);
  code_generator.generate_workspace ();
  code_generator.generate_project ();
  code_generator.open_files ();
  code_generator.generate_header ();
  code_generator.generate_source ();
  code_generator.close_files ();

  return 1;

}

//
// print_help
//
void CUTS_Setaf_App::print_help (void)
{
  std::cerr << __HELP__ << std::endl;
  ACE_OS::exit (0);
}


//
// parse arguments
//

int CUTS_Setaf_App::parse_args (int argc, char * argv [])
{
  const char * optstr = "hf:o:";

  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("file", 'f', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("output-dir", 'o', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("help", 'h');

  int ch;

  while ((ch = get_opt ()) != EOF)
  {
    switch (ch)
    {
    case 0:
      if (ACE_OS::strcmp (get_opt.long_option (), "file") == 0)
      {
        this->input_file_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "output-dir") == 0)
      {
        this->output_dir_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "help") == 0)
      {
        this->print_help ();
      }
      break;

    case 'f':
      this->input_file_ = get_opt.opt_arg ();
      break;

    case 'o':
      this->output_dir_ = get_opt.opt_arg ();
      break;

    case 'h':
      this->print_help ();
    }
  }
  return 0;
}

//
// extract_name
//
const char * CUTS_Setaf_App::extract_name ()
{
  std::string text (this->input_file_.c_str ());

  // Generated code will get all the identifier names
  // from the adapter specification name. This method
  // extract the name form specifiaction file name

  const char * sep = "\\/";
  std::string::size_type found = text.find_last_of (sep);

  if (found)
  {
    std::string file_name = text.substr (found + 1);
    std::string::size_type pos = file_name.find (".");

    if (file_name.substr (pos + 1) == "uas")
    {
      char * cstr;
      std::string name = file_name.substr (0, pos);
      cstr = new char [file_name.size ()+1];
      ACE_OS::strcpy (cstr, name.c_str ());
      return cstr;
    }
    else
    {
      ACE_ERROR_RETURN ((LM_ERROR,
        ACE_TEXT ("%T (%t) - %M - Extension of the file wrong %s\n"),
        this->input_file_.c_str ()),
        0);
    }
  }
  else
  {
    return 0;
  }
}