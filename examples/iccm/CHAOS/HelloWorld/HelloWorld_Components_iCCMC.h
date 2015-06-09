// -*- C++ -*-
// $Id$

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v2.1.8
 * TAO and the TAO IDL Compiler have been developed by:
 *       Center for Distributed Object Computing
 *       Washington University
 *       St. Louis, MO
 *       USA
 *       http://www.cs.wustl.edu/~schmidt/doc-center.html
 * and
 *       Distributed Object Computing Laboratory
 *       University of California at Irvine
 *       Irvine, CA
 *       USA
 * and
 *       Institute for Software Integrated Systems
 *       Vanderbilt University
 *       Nashville, TN
 *       USA
 *       http://www.isis.vanderbilt.edu/
 *
 * Information about TAO is available at:
 *     http://www.cs.wustl.edu/~schmidt/TAO.html
 **/

// TAO_IDL - Generated from
// c:\users\dfeiock.ads\documents\sem\middleware\tao\tao_idl\be\be_codegen.cpp:152

#ifndef _TAO_IDL_HELLOWORLD_COMPONENTS_ICCMC_Z9TAUU_H_
#define _TAO_IDL_HELLOWORLD_COMPONENTS_ICCMC_Z9TAUU_H_

#include /**/ "ace/pre.h"


#include /**/ "ace/config-all.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include /**/ "HelloWorld_Components_exec_export.h"
#include "tao/ORB.h"
#include "tao/SystemException.h"
#include "tao/Basic_Types.h"
#include "tao/ORB_Constants.h"
#include "tao/Object.h"
#include "tao/String_Manager_T.h"
#include "tao/Objref_VarOut_T.h"
#include "tao/Arg_Traits_T.h"
#include "tao/Basic_Arguments.h"
#include "tao/Special_Basic_Arguments.h"
#include "tao/Any_Insert_Policy_T.h"
#include "tao/Fixed_Size_Argument_T.h"
#include "tao/Var_Size_Argument_T.h"
#include "tao/Object_Argument_T.h"
#include /**/ "tao/Version.h"
#include /**/ "tao/Versioned_Namespace.h"

#include "HelloWorld_ComponentsEC.h"

#if TAO_MAJOR_VERSION != 2 || TAO_MINOR_VERSION != 1 || TAO_BETA_VERSION != 8
#error This file should be regenerated with TAO_IDL
#endif

#if defined (TAO_EXPORT_MACRO)
#undef TAO_EXPORT_MACRO
#endif
#define TAO_EXPORT_MACRO HELLOWORLD_COMPONENTS_EXEC_Export

// TAO_IDL - Generated from
// c:\users\dfeiock.ads\documents\sem\middleware\tao\tao_idl\be\be_visitor_root\root_ch.cpp:160
TAO_BEGIN_VERSIONED_NAMESPACE_DECL



namespace TAO
{
  template<typename T> class Narrow_Utils;
}
TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// c:\users\dfeiock.ads\documents\sem\middleware\tao\tao_idl\be\be_interface.cpp:750

#if !defined (_ICCM_HELLORECEIVER_CONTEXT__VAR_OUT_CH_)
#define _ICCM_HELLORECEIVER_CONTEXT__VAR_OUT_CH_

class iCCM_HelloReceiver_Context;
typedef iCCM_HelloReceiver_Context *iCCM_HelloReceiver_Context_ptr;

typedef
  TAO_Objref_Var_T<
      iCCM_HelloReceiver_Context
    >
  iCCM_HelloReceiver_Context_var;

typedef
  TAO_Objref_Out_T<
      iCCM_HelloReceiver_Context
    >
  iCCM_HelloReceiver_Context_out;

#endif /* end #if !defined */

// TAO_IDL - Generated from
// c:\users\dfeiock.ads\documents\sem\middleware\tao\tao_idl\be\be_visitor_interface\interface_ch.cpp:43

class HELLOWORLD_COMPONENTS_EXEC_Export iCCM_HelloReceiver_Context
  : public virtual ::CCM_HelloReceiver_Context

{
public:

  // TAO_IDL - Generated from
  // c:\users\dfeiock.ads\documents\sem\middleware\tao\tao_idl\be\be_type.cpp:307

  typedef iCCM_HelloReceiver_Context_ptr _ptr_type;
  typedef iCCM_HelloReceiver_Context_var _var_type;
  typedef iCCM_HelloReceiver_Context_out _out_type;

  // The static operations.
  static iCCM_HelloReceiver_Context_ptr _duplicate (iCCM_HelloReceiver_Context_ptr obj);

  static void _tao_release (iCCM_HelloReceiver_Context_ptr obj);

  static iCCM_HelloReceiver_Context_ptr _narrow (::CORBA::Object_ptr obj);
  static iCCM_HelloReceiver_Context_ptr _unchecked_narrow (::CORBA::Object_ptr obj);
  static iCCM_HelloReceiver_Context_ptr _nil (void);

  // TAO_IDL - Generated from
  // c:\users\dfeiock.ads\documents\sem\middleware\tao\tao_idl\be\be_visitor_interface\interface_ch.cpp:140

  virtual ::CORBA::Boolean _is_a (const char *type_id);
  virtual const char* _interface_repository_id (void) const;
  virtual ::CORBA::Boolean marshal (TAO_OutputCDR &cdr);

protected:
  // Abstract or local interface only.
  iCCM_HelloReceiver_Context (void);

  

  virtual ~iCCM_HelloReceiver_Context (void);

private:
  // Private and unimplemented for concrete interfaces.
  iCCM_HelloReceiver_Context (const iCCM_HelloReceiver_Context &);

  void operator= (const iCCM_HelloReceiver_Context &);
};

// TAO_IDL - Generated from
// c:\users\dfeiock.ads\documents\sem\middleware\tao\tao_idl\be\be_interface.cpp:750

#if !defined (_ICCM_HELLOSENDER_CONTEXT__VAR_OUT_CH_)
#define _ICCM_HELLOSENDER_CONTEXT__VAR_OUT_CH_

class iCCM_HelloSender_Context;
typedef iCCM_HelloSender_Context *iCCM_HelloSender_Context_ptr;

typedef
  TAO_Objref_Var_T<
      iCCM_HelloSender_Context
    >
  iCCM_HelloSender_Context_var;

typedef
  TAO_Objref_Out_T<
      iCCM_HelloSender_Context
    >
  iCCM_HelloSender_Context_out;

#endif /* end #if !defined */

// TAO_IDL - Generated from
// c:\users\dfeiock.ads\documents\sem\middleware\tao\tao_idl\be\be_visitor_interface\interface_ch.cpp:43

class HELLOWORLD_COMPONENTS_EXEC_Export iCCM_HelloSender_Context
  : public virtual ::CCM_HelloSender_Context

{
public:

  // TAO_IDL - Generated from
  // c:\users\dfeiock.ads\documents\sem\middleware\tao\tao_idl\be\be_type.cpp:307

  typedef iCCM_HelloSender_Context_ptr _ptr_type;
  typedef iCCM_HelloSender_Context_var _var_type;
  typedef iCCM_HelloSender_Context_out _out_type;

  // The static operations.
  static iCCM_HelloSender_Context_ptr _duplicate (iCCM_HelloSender_Context_ptr obj);

  static void _tao_release (iCCM_HelloSender_Context_ptr obj);

  static iCCM_HelloSender_Context_ptr _narrow (::CORBA::Object_ptr obj);
  static iCCM_HelloSender_Context_ptr _unchecked_narrow (::CORBA::Object_ptr obj);
  static iCCM_HelloSender_Context_ptr _nil (void);

  virtual ::MessageEvent * new_greeting_ospl_event (
    void) = 0;

  virtual ::MessageEvent * new_greeting_ndds_event (
    void) = 0;

  virtual ::MessageEvent * new_greeting_tcpip_event (
    void) = 0;

  // TAO_IDL - Generated from
  // c:\users\dfeiock.ads\documents\sem\middleware\tao\tao_idl\be\be_visitor_interface\interface_ch.cpp:140

  virtual ::CORBA::Boolean _is_a (const char *type_id);
  virtual const char* _interface_repository_id (void) const;
  virtual ::CORBA::Boolean marshal (TAO_OutputCDR &cdr);

protected:
  // Abstract or local interface only.
  iCCM_HelloSender_Context (void);

  

  virtual ~iCCM_HelloSender_Context (void);

private:
  // Private and unimplemented for concrete interfaces.
  iCCM_HelloSender_Context (const iCCM_HelloSender_Context &);

  void operator= (const iCCM_HelloSender_Context &);
};

// TAO_IDL - Generated from
// c:\users\dfeiock.ads\documents\sem\middleware\tao\tao_idl\be\be_visitor_arg_traits.cpp:68

TAO_BEGIN_VERSIONED_NAMESPACE_DECL


// Arg traits specializations.
namespace TAO
{
}

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// c:\users\dfeiock.ads\documents\sem\middleware\tao\tao_idl\be\be_visitor_traits.cpp:62

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

// Traits specializations.
namespace TAO
{

#if !defined (_ICCM_HELLORECEIVER_CONTEXT__TRAITS_)
#define _ICCM_HELLORECEIVER_CONTEXT__TRAITS_

  template<>
  struct HELLOWORLD_COMPONENTS_EXEC_Export Objref_Traits< ::iCCM_HelloReceiver_Context>
  {
    static ::iCCM_HelloReceiver_Context_ptr duplicate (
        ::iCCM_HelloReceiver_Context_ptr p);
    static void release (
        ::iCCM_HelloReceiver_Context_ptr p);
    static ::iCCM_HelloReceiver_Context_ptr nil (void);
    static ::CORBA::Boolean marshal (
        const ::iCCM_HelloReceiver_Context_ptr p,
        TAO_OutputCDR & cdr);
  };

#endif /* end #if !defined */

#if !defined (_ICCM_HELLOSENDER_CONTEXT__TRAITS_)
#define _ICCM_HELLOSENDER_CONTEXT__TRAITS_

  template<>
  struct HELLOWORLD_COMPONENTS_EXEC_Export Objref_Traits< ::iCCM_HelloSender_Context>
  {
    static ::iCCM_HelloSender_Context_ptr duplicate (
        ::iCCM_HelloSender_Context_ptr p);
    static void release (
        ::iCCM_HelloSender_Context_ptr p);
    static ::iCCM_HelloSender_Context_ptr nil (void);
    static ::CORBA::Boolean marshal (
        const ::iCCM_HelloSender_Context_ptr p,
        TAO_OutputCDR & cdr);
  };

#endif /* end #if !defined */
}
TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// c:\users\dfeiock.ads\documents\sem\middleware\tao\tao_idl\be\be_codegen.cpp:1703
#if defined (__ACE_INLINE__)
#include "HelloWorld_Components_iCCMC.inl"
#endif /* defined INLINE */

#include /**/ "ace/post.h"

#endif /* ifndef */

