// -*- C++ -*-

#ifndef _CUTS_BE_TCPIP_COMPONENT_IMPL_GENERATOR_H_
#define _CUTS_BE_TCPIP_COMPONENT_IMPL_GENERATOR_H_

#include "TCPIP_Ctx.h"
#include "../../BE_Generators_T.h"

template < >
struct CUTS_BE_File_Open_T <CUTS_BE_TCPIP_Ctx>
{
  static bool generate (const PICML::ComponentImplementationContainer &,
                        const PICML::MonolithicImplementation &);
};

template < >
struct CUTS_BE_File_Close_T <CUTS_BE_TCPIP_Ctx>
{
  static bool generate (const PICML::ComponentImplementationContainer &,
                        const PICML::MonolithicImplementation &);
};

template < >
struct CUTS_BE_Prologue_T <CUTS_BE_TCPIP_Ctx>
{
  static bool generate (const PICML::ComponentImplementationContainer &,
                        const PICML::MonolithicImplementation &);
};

template < >
struct CUTS_BE_Component_Impl_Begin_T <CUTS_BE_TCPIP_Ctx>
{
  static bool generate (const PICML::MonolithicImplementation & monoimpl,
                        const PICML::Component & component);
};

template < >
struct CUTS_BE_Component_Impl_End_T <CUTS_BE_TCPIP_Ctx>
{
  static bool generate (const PICML::MonolithicImplementation & monoimpl,
                        const PICML::Component & component);
};

/**
 *
 */
template < >
struct CUTS_BE_InEventPort_Begin_T <CUTS_BE_TCPIP_Ctx>
{
  static bool generate (const PICML::InEventPort & sink,
                        const std::vector <PICML::Property> & properties);
};

/**
 *
 */
template < >
struct CUTS_BE_InEventPort_End_T <CUTS_BE_TCPIP_Ctx>
{
  static bool generate (const PICML::InEventPort & sink,
                        const std::vector <PICML::Property> & properties);
};

/**
 *
 */
template < >
struct CUTS_BE_Environment_Method_Begin_T <CUTS_BE_TCPIP_Ctx>
{
  static bool generate (const PICML::MultiInputAction & action);
};

/**
 *
 */
template < >
struct CUTS_BE_Environment_Method_End_T <CUTS_BE_TCPIP_Ctx>
{
  static bool generate (const PICML::MultiInputAction & action);
};

/**
 *
 */
template < >
struct CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_TCPIP_Ctx>
{
  static bool generate (const PICML::ReadonlyAttribute & attr);
};

/**
 *
 */
template < >
struct CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_TCPIP_Ctx>
{
  static bool generate (const PICML::ReadonlyAttribute & attr);
};

/**
 *
 */
template < >
struct CUTS_BE_Attribute_Begin_T <CUTS_BE_TCPIP_Ctx>
{
  static bool generate (const PICML::Attribute & attr);
};

/**
 *
 */
template < >
struct CUTS_BE_Attribute_End_T <CUTS_BE_TCPIP_Ctx>
{
  static bool generate (const PICML::Attribute & attr);
};

#endif  // !defined _CUTS_BE_TCPIP_COMPONENT_SOURCE_IMPL_GENERATOR_H_
