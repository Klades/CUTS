#include "cuts/utils/Command_Substitution.h"
#include <iostream>

int main (int argc, char * argv [])
{
  std::cout << "Testing Command Substition:" << std::endl;
  ACE_CString in = "before `echo` after";
  ACE_CString out;
  std::cout << "  input = " << in.c_str () << std::endl;
  CUTS_Command_Substitution cs;
  std::cout << "  retval: " << cs.evaluate (in.c_str (), out) << std::endl;
  std::cout << "  output = " << out.c_str () << std::endl;
  return 0;
}