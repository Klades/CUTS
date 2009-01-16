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

#include "game/Project.h"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graph_traits.hpp"
#include "URI_Tag_Parser.h"

namespace naomi
{
  namespace attributes
  {
    // Forward decl.
    class attributeType;
  }
}

// Forward decl.
class GME_Attribute_Tag;

/**
 * @struct CUTS_GNC_App_Options
 *
 * Configuration options for the application.
 */
struct CUTS_GNC_App_Options
{
  /// Default constructor. Sets the default values for the options.
  CUTS_GNC_App_Options (void)
    : list_attributes_ (false),
      update_attributes_ (false),
      enable_auto_addons_ (true)
  {

  }

  /// The target GME project.
  std::string project_;

  /// The location of the attributes.
  std::string attribute_path_;

  /// List the attributes in the model.
  bool list_attributes_;

  /// Update all the attributes.
  bool update_attributes_;

  bool enable_auto_addons_;

  /// Pathname of the interface file.
  std::string interface_file_pathname_;

  /// Name to store in the interface file.
  std::string interface_file_name_;

  /// Owner of the attributes.
  std::string owner_;
};

/**
 * @class CUTS_GNC_App
 *
 * Application object for the GME NAOMI connector.
 */
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
  /// Helper method to write the interface file for the model.
  void create_interface_file (void);

  void gather_all_attributes (const GME::Object & parent,
                              std::list <std::string> & input,
                              std::list <std::string> & output);

  /// Type definition of the callback method for iteration.
  typedef
    void (CUTS_GNC_App::*attribute_callback)(const std::string & attr,
                                             GME_Attribute_Tag & info);

  /// Iterate over all the attributes in the model.
  void iterate_all_attributes (attribute_callback callback);

  void iterate_all_attributes_i (const GME::Object & parent,
                                 attribute_callback callback);

  /// List all attributes in the model.
  void list_all_attributes (void);

  /// Callback method for listing the attribute.
  void list_attribute_callback (const std::string & attr,
                                GME_Attribute_Tag & info);

  bool locate_object_attribute (const std::string & attr,
                                GME_Attribute_Tag & info);

  bool locate_object_attribute_i (const std::string & attr,
                                  const GME::Object & parent,
                                  GME_Attribute_Tag & info);

  void update_attributes (void);

  void gather_input_attributes_callback (const std::string & attr,
                                         GME_Attribute_Tag & info);

  void gather_output_attributes_callback (const std::string & attr,
                                          GME_Attribute_Tag & info);

  /**
   * Insert the following attribute in the graph. This will create a
   * new vertex for this attribute, and create the necessay dependency
   * edges between this attribute and other.
   */
  void insert_into_attr_graph (const std::string & attr,
                               GME_Attribute_Tag & info);

  /**
   * Helper method to update the gathered input attributes. This will
   * first do a topological sort of the attribute graph, then update
   * each attribute in the model.
   *
   * @param[in]         attr          Name of the attribute
   * @param[in]         info          Information about the attribute
   */
  void update_input_attributes (void);

  /**
   * Helper method to update an input attribute.
   *
   * @param[in]         attr          Name of the attribute
   * @param[in]         info          Information about the attribute
   */
  void update_input_attribute (const std::string & attr,
                               GME_Attribute_Tag & info);

  /**
   * Implemenation of the update method for simple attributes. Simple
   * attributes are basic scalar values.
   *
   * @param[in]         attr          Actually NAOMI attribute
   * @param[in]         info          Information about the attribute
   */
  void update_input_attribute_simple (
    const naomi::attributes::attributeType & attr,
    GME_Attribute_Tag & info);

  /**
   * Implemenation of the update method for complex attributes. Complex
   * attributes are metadata that generates child models.
   *
   * @param[in]         attr          Actually NAOMI attribute
   * @param[in]         info          Information about the attribute
   */
  void update_input_attribute_complex (
    const std::string & attr,
    const naomi::attributes::attributeType & naomi_attr,
    GME_Attribute_Tag & info);

  /**
   * Helper method to update the gathered output attributes. This will
   * first do a topological sort of the attribute graph, then update
   * each attribute in the model.
   *
   * @param[in]         attr          Name of the attribute
   * @param[in]         info          Information about the attribute
   */
  void update_output_attributes (void);

  /**
   * Helper method to update an output attribute.
   *
   * @param[in]         attr          Name of the attribute
   * @param[in]         info          Information about the attribute
   */
  void update_output_attribute (const std::string & attr,
                                GME_Attribute_Tag & info);

  void update_output_attribute_simple (
    naomi::attributes::attributeType & attr,
    GME_Attribute_Tag & info);

  void update_output_attribute_complex (
    const std::string & attr,
    naomi::attributes::attributeType & attr_type,
    GME_Attribute_Tag & info);

  /**
   * Initailize the GME project.
   *
   * @todo Implement a new class for managing the GME project's
   *       lifecycle, and move this method to that class.
   */
  int gme_project_init (void);

  /**
   * Finalize the GME project.
   *
   * @todo Implement a new class for managing the GME project's
   *       lifecycle, and move this method to that class.
   */
  int gme_project_fini (void);

  /// Configuration options for the application.
  CUTS_GNC_App_Options opts_;

  /// The target GME project.
  GME::Project project_;

  /// Flag that containse the project type.
  bool is_mga_file_;

  /// The parser for the tagged attributes.
  CUTS_URI_Tag_Parser tag_parser_;

  /// Flag that determines if the model needs to be saved.
  bool save_model_;

  /// The boost adjacency list for the dependency graph.
  typedef
    boost::property <boost::vertex_name_t, std::string,
    boost::property <boost::vertex_color_t, GME_Attribute_Tag> >
    vertex_property_type;

  typedef
    boost::adjacency_list <boost::setS,
                           boost::vecS,
                           boost::directedS,
                           vertex_property_type> graph_type;

  /// Type definition of the vertex type.
  typedef
    boost::graph_traits <graph_type>::vertex_descriptor vertex_type;

  /// Type definition of the edge type.
  typedef
    std::pair <vertex_type, vertex_type> edge_type;

  typedef
    std::map <std::string, vertex_type> vertex_map_type;

  /// The dependency graph for the assemblies.
  graph_type attr_graph_;
};

#endif  // !defined _CUTS_GNC_APP_H_
