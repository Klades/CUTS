// -*- C++ -*-

#ifndef _CUTS_PROPERTY_PARSER_H_
#define _CUTS_PROPERTY_PARSER_H_

#include "ace/RW_Thread_Mutex.h"

template <typename MUTEX> class CUTS_Property_Map_T;

/**
 * @class CUTS_Property_Parser
 */
class CUTS_Property_Parser
{
public:
  /// Defualt constructor.
  CUTS_Property_Parser (CUTS_Property_Map_T <ACE_RW_Thread_Mutex> & map);

  /// Destructor
  ~CUTS_Property_Parser (void);

  bool parse (const char * begin, const char * end);

  bool parse (const char * str);

private:
  /// Reference to property map used during substitution
  CUTS_Property_Map_T <ACE_RW_Thread_Mutex> & prop_map_;
};

#endif  // !defined _CUTS_PROPERTY_PARSER_H_
