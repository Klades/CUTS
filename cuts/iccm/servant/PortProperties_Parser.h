#ifndef _PORT_PROPERTIES_PARSER_H_
#define _PORT_PROPERTIES_PARSER_H_

#include "PortProperties.h"

#include <fstream>
#include <map>

class PortProperties_Parser
{
  public:
    typedef std::map<std::string, PortProperties *> property_map;
    typedef std::map<std::string, std::string> string_map;

    PortProperties_Parser (void);
    ~PortProperties_Parser (void);

    bool parse (std::ifstream & file);
    bool parse (const char * filename);

    property_map & get_map (void);

  private:
    string_map * process_file (std::ifstream & file);
    void process_map (string_map * temp_map);

    property_map map_;
};

#endif
