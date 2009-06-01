// -*- C++ -*-

//=============================================================================
/**
 * @file        BE_Visitor_T.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_VISITOR_T_H_
#define _CUTS_BE_VISITOR_T_H_

#include "BE_export.h"
#include "BE_nil.h"

/**
 * @class CUTS_BE_Visitor_T
 *
 * Base class for all context-aware visitor
 */
template <typename CONTEXT, typename VISITOR>
class CUTS_BE_Visitor_T : public VISITOR
{
public:
  /// Type definition of the context.
  typedef CONTEXT context_type;

  /// Type definition of the visitor.
  typedef VISITOR visitor_type;

protected:
  CUTS_BE_Visitor_T (CONTEXT & ctx);

  virtual ~CUTS_BE_Visitor_T (void);

  /// The actual context for the generator.
  CONTEXT & ctx_;
};

/**
 * @class CUTS_BE_Visitor_T <CUTS_BE::NIL>
 */
template <typename VISITOR>
class CUTS_BE_Export CUTS_BE_Visitor_T <CUTS_BE::NIL, VISITOR> :
  public VISITOR
{
public:
  /// Type definition of the context.
  typedef CUTS_BE::NIL context_type;

  /// Type definition of the visitor type.
  typedef VISITOR visitor_type;

protected:
  /// Initializing constructor.
  CUTS_BE_Visitor_T (void) { }

  /// Destructor.
  virtual ~CUTS_BE_Visitor_T (void) { }
};

#if defined (__CUTS_INLINE__)
#include "BE_Visitor_T.inl"
#endif

#include "BE_Visitor_T.cpp"

#endif  // !defined _CUTS_BE_CONTEXT_T_H_
