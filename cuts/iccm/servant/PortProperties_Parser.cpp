#include "PortProperties_Parser.h"

#include <sstream>

PortProperties_Parser::PortProperties_Parser (void)
{
}

std::pair<std::string, std::string> split (std::string & line, char delimit)
{
  size_t index = line.find (delimit);

  return std::make_pair(line.substr(0, index), line.substr(index+1, line.length()));
}
bool PortProperties_Parser::parse (std::ifstream & file)
{
  string_map * temp = process_file (file);
  process_map (*temp);  
  return true;
}

bool PortProperties_Parser::parse (const char * filename)
{
  std::ifstream file (filename);
  return parse (file);
}

PortProperties_Parser::property_map & PortProperties_Parser::get_map (void)
{
  return map_;
}

PortProperties_Parser::string_map * PortProperties_Parser::process_file (std::ifstream & file)
{
  std::string line;
  string_map * temp_map = new string_map;

  while (std::getline (file, line))
  {
    std::pair<std::string, std::string> split_line = split (line, '=');
    (*temp_map)[split_line.first] = split_line.second;
  }

  return temp_map;
}

void PortProperties_Parser::process_map (string_map & temp_map)
{
  std::stringstream converter_stream;

  // Find the defaults
  PortProperties default_props;  
  
  // Process the rest
}
