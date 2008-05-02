// $Id$

//=============================================================================
/**
 * @file      GNC_App.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_GNC_APP_H_
#define _CUTS_GNC_APP_H_

#include <string>
#include <set>
#include <list>
#include "gme/Project.h"
#include "URI_Tag_Parser.h"

//=============================================================================
/**
 * @struct CUTS_GNC_App_Options
 *
 * Configuration options for the application.
 */
//=============================================================================

struct CUTS_GNC_App_Options
{
  CUTS_GNC_App_Options (void)
    : list_attributes_ (false),
      update_attributes_ (false),
      verbose_ (false)      
  {

  }

  /// The target GME project.
  std::string project_;

  /// The location of the attributes.
  std::set <std::string> attribute_path_;

  /// List the attributes in the model.
  bool list_attributes_;

  /// Update all the attributes.
  bool update_attributes_;

  /// The verbosity state of the application.
  bool verbose_;

  /// Pathname of the interface file.
  std::string interface_file_pathname_;

  /// Name to store in the interface file.
  std::string interface_file_name_;
};

//=============================================================================
/**
 * @class CUTS_GNC_App
 *
 * Application object for the GME NAOMI connector.
 */
//=============================================================================

class CUTS_GNC_App
{
public:
  /// Default constructor.
  CUTS_GNC_App (void);

  /// Destructor.
  ~CUTS_GNC_App (void);

  /// Parse the command-line arguments.
  int parse_args (int argc, char * argv []);

  /// Run the main application.
  int run_main (void);

private:
  struct attribute_tag
  {
    GME::Object object_;
    
    std::string gme_attribute_;

    std::string direction_;

    std::string complex_;
  };

  void create_interface_file (void);

  void gather_all_attributes (const GME::Object & parent,
                              std::list <std::string> & input,
                              std::list <std::string> & output);

  /// Type definition of the callback method for iteration.
  typedef 
    void (CUTS_GNC_App::*attribute_callback)(const std::string & attr,
                                             attribute_tag & info);

  /// Iterate over all the attributes in the model.
  void iterate_all_attributes (attribute_callback callback);

  void iterate_all_attributes_i (const GME::Object & parent,
                                 attribute_callback callback);

  /// List all attributes in the model.
  void list_all_attributes (void);

  /// Callback method for listing the attribute.
  void list_attribute_callback (const std::string & attr, 
                                attribute_tag & info);

  bool locate_object_attribute (const std::string & attr, 
                                attribute_tag & info);

  bool locate_object_attribute_i (const std::string & attr,
                                  const GME::Object & parent,
                                  attribute_tag & info);

  void update_attributes (void);

  void update_attribute_callback (const std::string & attr,
                                  attribute_tag & info);

  void update_attribute_input (const std::string & attr,
                              attribute_tag & info);

  void update_attribute_output (const std::string & attr,
                                attribute_tag & info);

  int gme_project_init (void);

  int gme_project_fini (void);

  /// Configuration options for the application.
  CUTS_GNC_App_Options opts_;

  /// The target GME project.
  std::auto_ptr <GME::Project> project_;

  /// Flag that containse the project type.
  bool is_mga_file_;

  /// The parser for the tagged attributes.
  CUTS_URI_Tag_Parser tag_parser_;

  std::string update_phase_;
};

#endif  // !defined _CUTS_GNC_APP_H_
