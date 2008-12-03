// -*- C++ -*-

#ifndef _CUTS_EISA_PORT_MANAGER_T_H_
#define _CUTS_EISA_PORT_MANAGER_T_H_

#include <map>
#include "cuts/config.h"

template <typename PORTTYPE>
class CUTS_EISA_Port_Manager_T
{
public:
  CUTS_EISA_Port_Manager_T (void);

  ~CUTS_EISA_Port_Manager_T (void);

  bool insert (PORTTYPE & port);

  bool get_scoped_typename (const std::string & portname,
                            std::string & scoped_name);

  bool empty (void) const;

  size_t size (void) const;

  void clear (void);

private:
  bool insert_i (PORTTYPE & port, std::string & scoped_name);

  static void get_scoped_typename_i (PORTTYPE & port,
                                     std::string & dest);

  typedef std::map <std::string, std::string> Port_Map;

  Port_Map ports_;
};

#if defined (__CUTS_INLINE__)
#include "Port_Manager_T.inl"
#endif

#include "Port_Manager_T.cpp"

#endif  // !defined _CUTS_BE_EISA_PORT_MANAGER_T_H_
