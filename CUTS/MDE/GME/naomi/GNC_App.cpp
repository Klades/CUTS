// $Id$

#include "GNC_App.h"
#include "attribute_simple.h"
#include "interface.h"

#include "gme/GME.h"
#include "gme/XML.h"
#include "ace/ACE.h"
#include "ace/Get_Opt.h"
#include "ace/OS_NS_unistd.h"
#include "ace/OS_NS_string.h"
#include "ace/streams.h"

#include "boost/bind.hpp"

#include "XSCRT/utils/File_T.h"
#include "XSCRT/utils/XML_Schema_Resolver_T.h"

#include <sstream>
#include <algorithm>

// Helper macro for generating verbose messages.
#define VERBOSE_MESSAGE(msg) \
  if (this->opts_.verbose_) \
  { \
    ACE_DEBUG (msg); \
  }

static const char * usage = 
"USAGE: gnc [OPTIONS]\n\
Input/output NAOMI attributes for a GME model\n\
\n\
General Options\n\
  -p, --project=GMEFILE            absolute/relative path to GME project\n\
  -v, --verbose                    display progress\n\
  -h, --help                       display this help message\n\
\n\
Atttribute Options\n\
  -i, --input-attribute=ATTR       input the specified attribute\n\
  -o, --output-attribute=ATTR      output the specified attribute\n\
\n\
  -l, --list-attributes            list naomi attribute in project\n\
\n\
  -P, --attribute-path=PATH        path to naomi attributes on disk\n\
\n\
Interface Options\n\
  --interface-file-create=PATH     create an interface file for the\n\
                                   at the specified location\n\
  --interface-file-name=NAME       name stored in the <name> tag of\n\
                                   the interface file\n\
\n\
EXAMPLE:\n\
%> gnc -p ./models/traffic.xme -i scatter.traffic.deployment\n\
   -i rose.pedcontroller_period.msec -o picml.traffic.deployment\n\
   -P ./attributes\n\
\n\
REMARKS:\n\
The GME Connector for NAOMI is a generic connector that works with\n\
any GME project. The name of the input/output attributes must be tagged\n\
in the model for the connector to work properly. Also, the owner of\n\
the attribute must match the paradigm name of the target GME project.\n\
\n\
The GMEFILE can be either a .mga file or a .xme file. You do not have to\n\
provide a quantifier before the filename, such as \'MGA=', as required in\n\
previous versions.\n\
\n\
LIMITATIONS:\n\
The connector only supports simple types that can be expressed in\n\
the <value></value> tag of the attribute. It assumes it is a string\n\
and can be directly inputed into the model without any parsing.\n";

//
// CUTS_GNC_App
//
CUTS_GNC_App::CUTS_GNC_App (void)
: is_mga_file_ (false)
{

}

//
// CUTS_GNC_App
//
CUTS_GNC_App::~CUTS_GNC_App (void)
{

}

//
// parse_args
//
int CUTS_GNC_App::parse_args (int argc, char * argv [])
{
  const char * opts = ACE_TEXT ("p:P:i:o:lvh");
  ACE_Get_Opt get_opt (argc, argv, opts, 0);

  get_opt.long_option ("project", 'p', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("attribute-path", 'P', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("input-attribute", 'i', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("output-attribute", 'o', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("list-attributes", 'l', ACE_Get_Opt::NO_ARG);

  get_opt.long_option ("interface-file-create", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("interface-file-name", ACE_Get_Opt::ARG_REQUIRED);

  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);

  int option;

  while ((option = get_opt ()) != EOF)
  {
    switch (option)
    {
    case 0:
      if (ACE_OS::strcmp (get_opt.long_option (), "project") == 0)
      {
        this->opts_.project_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "input-attribute") == 0)
      {
        this->opts_.input_attributes_.insert (get_opt.opt_arg ());
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "output-attribute") == 0)
      {
        this->opts_.output_attributes_.insert (get_opt.opt_arg ());
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "list-attributes") == 0)
      {
        this->opts_.list_attributes_ = true;
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "attribute-path") == 0)
      {
        this->opts_.attribute_path_.insert (get_opt.opt_arg ());
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "verbose") == 0)
      {
        this->opts_.verbose_ = true;
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "interface-file-create") == 0)
      {
        this->opts_.interface_file_pathname_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "interface-file-name") == 0)
      {
        this->opts_.interface_file_name_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "help") == 0)
      {
        std::cerr << usage << std::endl;
        ACE_OS::exit (0);
      }
      break;

    case 'h':
      std::cerr << usage << std::endl;
      ACE_OS::exit (0);
      break;

    case 'p':
      this->opts_.project_ = get_opt.opt_arg ();
      break;

    case 'i':
      this->opts_.input_attributes_.insert (get_opt.opt_arg ());
      break;

    case 'o':
      this->opts_.output_attributes_.insert (get_opt.opt_arg ());
      break;

    case 'l':
      this->opts_.list_attributes_ = true;
      break;

    case 'v':
      this->opts_.verbose_ = true;
      break;

    case 'P':
      this->opts_.attribute_path_.insert (get_opt.opt_arg ());
      break;

    case '?':
      // unknown option; do nothing
      break;

    case ':':
      ACE_ERROR_RETURN ((LM_ERROR,
                         "*** error: %c is missing an argument\n",
                         get_opt.opt_opt ()),
                         -1);
      break;

    default:
      /* do nothing */;
    }
  }

  return 0;
}

//
// run_main
//
int CUTS_GNC_App::run_main (void)
{
  try
  {
    // Initialize the GME project.
    if (this->gme_project_init () == 0)
    {
      // Begin a new transaction.
      this->project_->begin_transaction ();

      // List all the attributes, if necessary.
      if (this->opts_.list_attributes_)
        this->list_all_attributes ();

      // Create the interface file for the project.
      if (!this->opts_.interface_file_pathname_.empty ())
        this->create_interface_file ();

      // Input all the attributes.
      if (!this->opts_.input_attributes_.empty ())
        this->input_all_attributes ();

      // Output all the attributes.
      if (!this->opts_.output_attributes_.empty ())
        this->output_all_attributes ();

      // Commit the current transaction.
      this->project_->commit_transaction ();
    }
  }
  catch (GME::Failed_Result & ex)
  {
    this->project_->abort_transaction ();

    ACE_ERROR ((LM_ERROR,
                "*** error: GME operation failed [0x%X]\n",
                ex.value ()));
  }
  catch (...)
  {
    // Abort the current transaction.
    this->project_->abort_transaction ();

    ACE_ERROR ((LM_ERROR,
                "*** error: caught unknown exception\n"));
  }

  // Finalize the GME project.
  this->gme_project_fini ();
  return 0;
}

//
// gme_init_project
//
int CUTS_GNC_App::gme_project_init (void)
{
  if (this->opts_.project_.empty ())
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                        "*** error: please specify a GME project\n"),
                        -1);
  }

  try
  {
    VERBOSE_MESSAGE ((LM_INFO, 
                      "*** info: initializing GME\n"));

    GME::init ();

    this->project_.reset (new GME::Project ());

    VERBOSE_MESSAGE ((LM_INFO,
                      "*** info: opening GME model %s\n",
                      this->opts_.project_.c_str ()));

    // Determine if this file is a MGA file.
    this->is_mga_file_ = 
      this->opts_.project_.rfind (".mga") != std::string::npos;

    if (this->is_mga_file_)
    {
      std::ostringstream connstr;
      connstr << "MGA=" << this->opts_.project_;

      this->project_->open (connstr.str ());
    }
    else
    {
      // Get information about the XML file.
      GME::XML_Parser parser;
      GME::XML_Info info;

      parser.get_info (this->opts_.project_, info);

      ACE_TCHAR pathname[MAX_PATH];

      if (ACE::get_temp_dir (pathname, MAX_PATH - 20) != -1)
      {
        // Create a temporary filename for the project.
        ACE_OS::strcat (pathname, "picmlin-XXXXXX.mga");
        ACE_HANDLE fd = ACE_OS::mkstemp (pathname);

        if (fd == 0)
          return -1;

        // Delete the temporary file, which we aren't using.
        ACE_OS::close (fd);
        ACE_OS::unlink (pathname);

        // Create the full pathname.
        std::ostringstream connstr;
        connstr << "MGA=" << pathname;

        // Create a empty PICML project and import the XML file.
        this->project_->create (connstr.str (), info.paradigm_);
        parser.parse (this->opts_.project_, *this->project_);
      }
      else
      {
        return -1;
      }
    }

    return 0;
  }
  catch (const GME::Failed_Result & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error: GME operation failed [0x%X]\n",
                ex.value ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error: caught unknown exception\n"));
  }

  return -1;
}

//
// gme_project_fini
//
int CUTS_GNC_App::gme_project_fini (void)
{
  if (this->project_.get ())
  {
    std::string tempfile;

    // Save the project file.
    this->project_->save ();

    if (!this->is_mga_file_)
    {
      VERBOSE_MESSAGE ((LM_INFO,
                        "*** info: exporting project as %s\n",
                        this->opts_.project_.c_str ()));

      // Export the project to the source XML file.
      GME::XML_Dumper dumper;
      dumper.write (this->opts_.project_, *this->project_);

      // Delete the temporary file.
      tempfile = this->project_->connstr ().substr (4);
    }

    // Close the project file.
    VERBOSE_MESSAGE ((LM_INFO,
                      "*** info: closing the PICML project\n"));

    this->project_->close ();
    this->project_.reset ();

    if (!tempfile.empty ())
      ACE_OS::unlink (tempfile.c_str ());
  }

  VERBOSE_MESSAGE ((LM_INFO,
                    "*** info: shutting down GME\n"));

  // Finalize GME backend.
  GME::fini ();

  return 0;
}

//
// locate_object_attribute
//
bool CUTS_GNC_App::
locate_object_attribute (const std::string & attr, 
                         attribute_tag & info)
{
  GME::Folder root = this->project_->root_folder ();
  return this->locate_object_attribute_i (attr, root, info);
}

//
// locate_object_attribute_i
//
bool CUTS_GNC_App::
locate_object_attribute_i (const std::string & attr,
                           const GME::Object & parent,
                           attribute_tag & info)
{
  // Get the registry nodes of this object.
  std::string path = parent.path (".", false).c_str ();

  VERBOSE_MESSAGE ((LM_DEBUG,
                    "*** debug: looking in <%s>...\n",
                    path.c_str ()));

  GME::Collection_T <GME::RegistryNode> registry;

  try
  {
    GME::FCO fco = GME::FCO::_narrow (parent);
    fco.registry (registry);
  }
  catch (...)
  {
    GME::Folder folder = GME::Folder::_narrow (parent);
    folder.registry (registry);
  }

  // Get all the top-level registry nodes for this object.
  GME::Collection_T <GME::RegistryNode>::iterator 
    reg_iter = registry.begin (), reg_iter_end = registry.end ();

  std::string temp = attr;

  for ( ; reg_iter != reg_iter_end; ++ reg_iter)
  {
    // Parse the name of this registry node. If the name parses
    // correctly, then we have found the correct model element.
    if (this->tag_parser_.parse (reg_iter->name (), temp, info.gme_attribute_))
    {
      info.object_    = parent;
      info.direction_ = reg_iter->child ("direction").value ();

      return true;
    }
  }  

  // We were not able to locate the attribute in this element. Get 
  // the child objects of this parent element.
  GME::Collection_T <GME::Object> children;

  if (parent.children (children) == 0)
    return false;

  GME::Collection_T <GME::Object>::iterator 
    iter = children.begin (), iter_end = children.end ();

  // Search all the children for the specified attribute.
  for ( ; iter != iter_end; ++ iter)
  {
    if (this->locate_object_attribute_i (attr, *iter, info))
      return true;
  }

  return false;
}

//
// list_all_attributes
//
void CUTS_GNC_App::list_all_attributes (void)
{
  GME::Folder root = this->project_->root_folder ();
  return this->list_all_attributes_i (root);
}

//
// list_all_attributes_i
//
void CUTS_GNC_App::list_all_attributes_i (const GME::Object & parent)
{
  // Get the registry nodes of this object.
  GME::Collection_T <GME::RegistryNode> registry;
  std::string path = parent.path (".", false).c_str ();

  try
  {
    GME::FCO fco = GME::FCO::_narrow (parent);
    fco.registry (registry);
  }
  catch (...)
  {
    GME::Folder folder = GME::Folder::_narrow (parent);
    folder.registry (registry);
  }

  // Get all the top-level registry nodes for this object.
  GME::Collection_T <GME::RegistryNode>::iterator 
    reg_iter = registry.begin (), reg_iter_end = registry.end ();

  std::string attr, gme_attr, value, direct;
  std::ostringstream ostr;

  for ( ; reg_iter != reg_iter_end; ++ reg_iter)
  {
    // Parse the name of this registry node. Since we are 
    // passing in an empty NAOMI attribute, the parser will
    // save the name of the attribute.
    if (this->tag_parser_.parse (reg_iter->name (), attr, gme_attr))
    {
      value = reg_iter->value ();

      GME::RegistryNode direction = reg_iter->child ("direction");
      direct = direction.value ();

      // Print information about the NAOMI attribute tag.
      ostr 
        << " . naomi attribute : " << attr << std::endl
        << "       gme element : " << parent.path (".", false) << std::endl;

      if (!gme_attr.empty ())
      {
        ostr 
          << "     gme attribute : " << gme_attr << std::endl;
      }

      ostr
        << "      complex type : " << (value.empty () ? "no" : "yes") 
        << std::endl
        << "         direction : " 
        << (!direct.empty () ? direction.value () : "<undefined>") 
        << std::endl;

      if (!value.empty () && !direct.empty ())
      {
        if (direct == "input")
          ostr << "            parser : " << value;
        else if (direct == "output")
          ostr << "         generator : " << value;
        else
          ostr << "*** error : invalid direction";

        ostr << std::endl;        
      }

      std::cout << ostr.str () << std::endl;
    }

    if (!attr.empty ())
    {
      // Clear the attribute for the next loop.
      attr.clear ();

      // Reset the string stream.
      ostr.clear ();
      ostr.str ("");
    }
  }  

  // We were not able to locate the attribute in this element. Get 
  // the child objects of this parent element.
  GME::Collection_T <GME::Object> children;

  if (parent.children (children) == 0)
    return;

  GME::Collection_T <GME::Object>::iterator 
    iter = children.begin (), iter_end = children.end ();

  // Search all the children for the specified attribute.
  for ( ; iter != iter_end; ++ iter)
    this->list_all_attributes_i (*iter);
}

//
// input_all_attributes
//
void CUTS_GNC_App::input_all_attributes (void)
{
  // Create the file reader for the configuration file.
  naomi::attributes::attributeType attr_info ("", "");

  XSCRT::utils::File_Reader_T <
    naomi::attributes::attributeType> 
    reader (&naomi::attributes::reader::attribute);

  // Discard comment nodes in the document.
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMComments, false))
    reader.parser ()->setFeature (xercesc::XMLUni::fgDOMComments, false);

  // Disable datatype normalization. The XML 1.0 attribute value
  // normalization always occurs though.
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMDatatypeNormalization, true))
    reader.parser ()->setFeature (xercesc::XMLUni::fgDOMDatatypeNormalization, true);

  // Do not create EntityReference nodes in the DOM tree. No
  // EntityReference nodes will be created, only the nodes
  // corresponding to their fully expanded substitution text will be
  // created.
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMEntities, false))
    reader.parser ()->setFeature (xercesc::XMLUni::fgDOMEntities, false);

  // Perform Namespace processing.
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMNamespaces, true))
    reader.parser ()->setFeature (xercesc::XMLUni::fgDOMNamespaces, true);

  // Do not include ignorable whitespace in the DOM tree.
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMWhitespaceInElementContent, false))
    reader.parser ()->setFeature (xercesc::XMLUni::fgDOMWhitespaceInElementContent, false);

  // Perform Validation
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMValidation, true))
    reader.parser ()->setFeature (xercesc::XMLUni::fgDOMValidation, true);

  // Enable the GetParser()'s schema support.
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgXercesSchema, true))
    reader.parser ()->setFeature (xercesc::XMLUni::fgXercesSchema, true);

  // Enable full schema constraint checking, including checking which
  // may be time-consuming or memory intensive. Currently, particle
  // unique attribution constraint checking and particle derivation
  // restriction checking are controlled by this option.
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgXercesSchemaFullChecking, true))
    reader.parser ()->setFeature (xercesc::XMLUni::fgXercesSchemaFullChecking, true);

  // The GetParser() will treat validation error as fatal and will exit.
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgXercesValidationErrorAsFatal, false))
    reader.parser ()->setFeature (xercesc::XMLUni::fgXercesValidationErrorAsFatal, false);

  // Locate each of the input attributes in the project.
  std::set <std::string>::const_iterator 
    iter = this->opts_.input_attributes_.begin (),
    iter_end = this->opts_.input_attributes_.end ();

  std::ostringstream pathname;
  attribute_tag info;

  for ( ; iter != iter_end; ++ iter)
  {
    VERBOSE_MESSAGE ((LM_INFO,
                      "*** info: searching for naomi attribute <%s>\n",
                      iter->c_str ()));

    // Search the current child element for the attribute.
    if (this->locate_object_attribute (*iter, info))
    {
      VERBOSE_MESSAGE ((LM_INFO,
                        "*** info: found naomi attribute in element <%s>\n",
                        info.object_.path (".", false).c_str ()));

      // Verfiy the attribute is an input attribute.
      if (info.direction_ != "input")
      {
        ACE_ERROR ((LM_ERROR,
                    "*** error: attribute <%s> is not an input attribute "
                    "for this model\n",
                    iter->c_str ()));

        continue;
      }

      // Locate the attribute on disk.
      std::set <std::string>::const_iterator
        path_iter = this->opts_.attribute_path_.begin (),
        path_iter_end = this->opts_.attribute_path_.end ();

      for ( ; path_iter != path_iter_end; ++ path_iter)
      {
        // Reset the pathname.
        pathname.clear ();
        pathname.str ("");

        // Construct the new pathname.
        pathname << *path_iter << "/" << *iter;

        // Attempt to open the attribute file.
        if (reader.open (pathname.str ().c_str ()) == 0)
          break;
      }

      if (!reader.is_open ())
      {
        ACE_ERROR ((LM_ERROR,
                    "*** error: could not locate attribute <%s> on disk; "
                    "please make sure path is correct\n",
                    iter->c_str ()));

        // Move to the next attribute.
        continue;
      }

      // Read the attribute information from the file.
      reader >> attr_info;

      if (info.gme_attribute_.empty ())
      {
        // The value is the name of the object.
        info.object_.name (attr_info.value ().c_str ());
      }
      else
      {
        // The value is an attribute of the object.
        GME::Attribute target_attr;

        try
        {
          GME::FCO fco = GME::FCO::_narrow (info.object_);
          target_attr = fco.attribute (info.gme_attribute_);
        }
        catch (...)
        {
          GME::Folder folder = GME::Folder::_narrow (info.object_);
        }

        // Set the value of the GME attribute.
        target_attr.string_value (attr_info.value ().c_str ());
      }

      // Close the XML file.
      reader.close ();
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "*** error: failed to locate attribute <%s>\n",
                  iter->c_str ()));
    }
  }
}

//
// output_all_attributes
// 
void CUTS_GNC_App::output_all_attributes (void)
{
  // Create the file reader for the configuration file.
  naomi::attributes::attributeType attr_info ("", "");

  XSCRT::utils::File_Reader_T <
    naomi::attributes::attributeType>
    reader (&naomi::attributes::reader::attribute);

  // Discard comment nodes in the document.
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMComments, false))
    reader.parser ()->setFeature (xercesc::XMLUni::fgDOMComments, false);

  // Disable datatype normalization. The XML 1.0 attribute value
  // normalization always occurs though.
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMDatatypeNormalization, true))
    reader.parser ()->setFeature (xercesc::XMLUni::fgDOMDatatypeNormalization, true);

  // Do not create EntityReference nodes in the DOM tree. No
  // EntityReference nodes will be created, only the nodes
  // corresponding to their fully expanded substitution text will be
  // created.
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMEntities, false))
    reader.parser ()->setFeature (xercesc::XMLUni::fgDOMEntities, false);

  // Perform Namespace processing.
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMNamespaces, true))
    reader.parser ()->setFeature (xercesc::XMLUni::fgDOMNamespaces, true);

  // Do not include ignorable whitespace in the DOM tree.
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMWhitespaceInElementContent, false))
    reader.parser ()->setFeature (xercesc::XMLUni::fgDOMWhitespaceInElementContent, false);

  // Perform Validation
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMValidation, true))
    reader.parser ()->setFeature (xercesc::XMLUni::fgDOMValidation, true);

  // Enable the GetParser()'s schema support.
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgXercesSchema, true))
    reader.parser ()->setFeature (xercesc::XMLUni::fgXercesSchema, true);

  // Enable full schema constraint checking, including checking which
  // may be time-consuming or memory intensive. Currently, particle
  // unique attribution constraint checking and particle derivation
  // restriction checking are controlled by this option.
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgXercesSchemaFullChecking, true))
    reader.parser ()->setFeature (xercesc::XMLUni::fgXercesSchemaFullChecking, true);

  // The GetParser() will treat validation error as fatal and will exit.
  if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgXercesValidationErrorAsFatal, false))
    reader.parser ()->setFeature (xercesc::XMLUni::fgXercesValidationErrorAsFatal, false);

  XSCRT::utils::File_Writer_T <
    naomi::attributes::attributeType> 
    writer ("http://www.atl.lmco.com/naomi/attributes",
            "attribute", 
            &naomi::attributes::writer::attribute);

  if (writer.writer ()->canSetFeature (xercesc::XMLUni::fgDOMWRTDiscardDefaultContent, true))
    writer.writer ()->setFeature (xercesc::XMLUni::fgDOMWRTDiscardDefaultContent, true);
  
  if (writer.writer ()->canSetFeature (xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true))
    writer.writer ()->setFeature (xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true);

  // Locate each of the input attributes in the project.
  std::set <std::string>::const_iterator 
    iter = this->opts_.output_attributes_.begin (),
    iter_end = this->opts_.output_attributes_.end ();

  std::ostringstream pathname;
  attribute_tag info;

  for ( ; iter != iter_end; ++ iter)
  {
    VERBOSE_MESSAGE ((LM_INFO,
                      "*** info: searching for naomi attribute <%s>\n",
                      iter->c_str ()));

    // Search the current child element for the attribute.
    if (this->locate_object_attribute (*iter, info))
    {
      VERBOSE_MESSAGE ((LM_INFO,
                        "*** info: found naomi attribute in element <%s>\n",
                        info.object_.path (".", false).c_str ()));

      // Verfiy the attribute is an input attribute.
      if (info.direction_ != "output")
      {
        ACE_ERROR ((LM_ERROR,
                    "*** error: attribute <%s> is not an output attribute "
                    "for this model\n",
                    iter->c_str ()));

        continue;
      }

      // Locate the attribute on disk.
      std::set <std::string>::const_iterator
        path_iter = this->opts_.attribute_path_.begin (),
        path_iter_end = this->opts_.attribute_path_.end ();

      for ( ; path_iter != path_iter_end; ++ path_iter)
      {
        // Reset the pathname.
        pathname.clear ();
        pathname.str ("");

        // Construct the new pathname.
        pathname << *path_iter << "/" << *iter;

        // Attempt to open the attribute file.
        if (reader.open (pathname.str ().c_str ()) == 0)
          break;
      }

      // Get the paradigm for the project. This is the actual owner
      // of the attribute.
      GME::Project project = info.object_.project ();
      std::string owner = project.paradigm_name ();

      if (reader.is_open ())
      {
        // Read the attribute information from the file. This is to make
        // sure we preserve the current information.
        reader >> attr_info;
        reader.close ();

        // Validate the we actually own this attribute.
        if (attr_info.owner () != owner)
        {
          ACE_ERROR ((LM_ERROR,
                      "*** error: target model does not own attribute; "
                      "skipping...\n"));

          continue;
        }
      }
      else
      {
        // We are creating the attribute for the first time. We, therefore,
        // need to set the owner of the attribute.
        attr_info.owner (owner);
      }

      if (info.gme_attribute_.empty ())
      {
        // The value is the name of the object.
        attr_info.value (info.object_.name ());
      }
      else
      {
        // The value is an attribute of the object.
        GME::Attribute target_attr;

        try
        {
          GME::FCO fco = GME::FCO::_narrow (info.object_);
          target_attr = fco.attribute (info.gme_attribute_);
        }
        catch (...)
        {
          GME::Folder folder = GME::Folder::_narrow (info.object_);
        }

        // Set the attribute info using the GME attribute.
        attr_info.value (target_attr.string_value ());;
      }


      // Open the writer for usage.
      if (writer.open (pathname.str ().c_str ()) != 0)
      {
        ACE_ERROR ((LM_ERROR,
                    "*** error: failed to open %s for writing\n",
                    pathname.str ().c_str ()));
        continue;
      }

      // Set the attributes for the root element.
      xercesc::DOMElement * root = writer.document ()->getDocumentElement ();

      root->setAttribute (
        XSC::XStr ("xmlns:xsi"),
        XSC::XStr ("http://www.w3.org/2001/XMLSchema-instance"));

      root->setAttribute (
        XSC::XStr ("xsi:schemaLocation"),
        XSC::XStr ("http://www.atl.lmco.com/naomi/attributes attribute_simple.xsd"));
                          
      
      // Write the attribute to the file.
      writer << attr_info;
      writer.close ();
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "*** error: failed to locate attribute <%s>\n",
                  iter->c_str ()));
    }
  }
}

//
// create_interface_file
//
void CUTS_GNC_App::create_interface_file (void)
{
  std::list <std::string> input, output;

  // Get the root folder for the project.
  GME::Folder root = this->project_->root_folder ();

  // Gather all the attributes in the model.
  this->gather_all_attributes (root, input, output);

  // Create the interface object.
  std::string type = this->project_->paradigm_name ();
  std::string name = this->opts_.interface_file_name_;

  if (name.empty ())
  {
    std::string::size_type pos =
      this->opts_.interface_file_pathname_.find_last_of ("\\/");

    if (pos == std::string::npos)
      name = this->opts_.interface_file_pathname_;
    else
      name = this->opts_.interface_file_pathname_.substr (pos + 1);
  }

  naomi::interfaces::interface_Type interface_type (name, type);

  // Add all the input attributes to the XML document.
  std::list <std::string>::const_iterator 
    iter = input.begin (), iter_end = input.end ();

  naomi::interfaces::interface_Type::inputType input_type;

  for ( ; iter != iter_end; ++ iter)
  {
    input_type.assign (*iter);
    interface_type.add_input (input_type);
  }

  // Add all the output attributes to the XML document.
  iter = output.begin (), iter_end = output.end ();

  naomi::interfaces::interface_Type::outputType output_type;

  for ( ; iter != iter_end; ++ iter)
  {
    output_type.assign (*iter);
    interface_type.add_output (output_type);
  }

  // Create the interface file for NAOMI.
  XSCRT::utils::File_Writer_T <
    naomi::interfaces::interface_Type> 
    writer ("http://www.atl.lmco.com/naomi/interfaces",
            "interface", 
            &naomi::interfaces::writer::interface_);

  if (writer.open (this->opts_.interface_file_pathname_.c_str ()) == 0)
  {
    if (writer.writer ()->canSetFeature (xercesc::XMLUni::fgDOMWRTDiscardDefaultContent, true))
      writer.writer ()->setFeature (xercesc::XMLUni::fgDOMWRTDiscardDefaultContent, true);
    
    if (writer.writer ()->canSetFeature (xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true))
      writer.writer ()->setFeature (xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true);

    // Set the attributes for the root element.
    xercesc::DOMElement * doc_root = writer.document ()->getDocumentElement ();

    doc_root->setAttribute (
      XSC::XStr ("xmlns:xsi"),
      XSC::XStr ("http://www.w3.org/2001/XMLSchema-instance"));

    doc_root->setAttribute (
      XSC::XStr ("xsi:schemaLocation"),
      XSC::XStr ("http://www.atl.lmco.com/naomi/interfaces interface.xsd"));

    writer << interface_type;
    writer.close ();

    VERBOSE_MESSAGE ((LM_INFO,
                      "*** info: successfully write interface file "
                      " to %s\n",
                      this->opts_.interface_file_pathname_.c_str ()));
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "*** error: failed to open %s for writing\n",
                this->opts_.interface_file_pathname_.c_str ()));
  }
}

//
// gather_all_attributes
//
void CUTS_GNC_App::
gather_all_attributes (const GME::Object & parent,
                       std::list <std::string> & input,
                       std::list <std::string> & output)
{
  // Get the registry nodes of this object.
  GME::Collection_T <GME::RegistryNode> registry;
  std::string path = parent.path (".", false).c_str ();

  try
  {
    GME::FCO fco = GME::FCO::_narrow (parent);
    fco.registry (registry);
  }
  catch (...)
  {
    GME::Folder folder = GME::Folder::_narrow (parent);
    folder.registry (registry);
  }

  // Get all the top-level registry nodes for this object.
  GME::Collection_T <GME::RegistryNode>::iterator 
    reg_iter = registry.begin (), reg_iter_end = registry.end ();

  std::string attr, gme_attr, value, direct;
  std::ostringstream ostr;

  for ( ; reg_iter != reg_iter_end; ++ reg_iter)
  {
    // Parse the name of this registry node. Since we are 
    // passing in an empty NAOMI attribute, the parser will
    // save the name of the attribute.
    if (this->tag_parser_.parse (reg_iter->name (), attr, gme_attr))
    {
      value = reg_iter->value ();

      GME::RegistryNode direction = reg_iter->child ("direction");
      direct = direction.value ();

      if (direct == "input")
      {
        input.push_back (attr);
      }
      else if (direct == "output")
      {
        output.push_back (attr);
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "*** warning: attribute <%s> tagged at <%s> has "
                    "no direction; skipping...\n",
                    attr.c_str (),
                    path.c_str ()));
      }

      // Reset the attribute for the next iteration.
      attr.clear ();
    }  
  }

  // We were not able to locate the attribute in this element. Get 
  // the child objects of this parent element.
  GME::Collection_T <GME::Object> children;

  if (parent.children (children) == 0)
    return;

  GME::Collection_T <GME::Object>::iterator 
    iter = children.begin (), iter_end = children.end ();

  // Search all the children for the specified attribute.
  for ( ; iter != iter_end; ++ iter)
    this->gather_all_attributes (*iter, input, output);
}