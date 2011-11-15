// -*- C++ -*-

//=============================================================================
/**
 * @file        T2M_Parser_Generator.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _T2M_PARSER_GENERATOR_H_
#define _T2M_PARSER_GENERATOR_H_

#include <string>
#include <fstream>

/**
 * @class T2M_Parser_Generator
 */
class T2M_Parser_Generator
{
public:
  int parse (std::string filename);

private:
  std::string basename_;

  std::ofstream cpp_file_, h_file_, mpc_file_;
};

#endif  // !defined _T2M_PARSER_GENERATOR_H_