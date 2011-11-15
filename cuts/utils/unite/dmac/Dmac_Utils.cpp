#include "Dmac_Utils.h"


//
// tokenize
//
void CUTS_DMAC_UTILS::tokenize (const std::string & str,
                                CUTS_DMAC_UTILS::string_vector & tokens)
{
  std::string delimiters (" \n\t'\",<>-");
  // Skip delimiters at beginning.
  std::string::size_type lastPos = str.find_first_not_of (delimiters, 0);
  // Find first "non-delimiter".
  std::string::size_type pos = str.find_first_of (delimiters, lastPos);

  while (std::string::npos != pos || std::string::npos != lastPos)
  {
    std::string item = str.substr (lastPos, pos - lastPos);
    tokens.push_back (item);

    lastPos = str.find_first_not_of (delimiters, pos);
    // Find next "non-delimiter"
    pos = str.find_first_of (delimiters, lastPos);
  }
}