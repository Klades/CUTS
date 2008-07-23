// $Id$

#include "T2M_Parser_Generator.h"
#include <string>

//
// main
//
int main (int argc, char * argv [])
{
  T2M_Parser_Generator generator;

  return generator.parse (std::string (argv[1]));
}