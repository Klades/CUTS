/// -*- C++ -*-

//=============================================================================
/**
 * @file          CIAO_Ctx.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_OPENSPLICE_GENERATORS_H_
#define _CUTS_OPENSPLICE_GENERATORS_H_

#include "String_Set.h"
#include "ccm/Component_Implementation.h"
#include "cpp/Behavior_Generator.h"
#include "Context.h"

/**
 * @class CUTS_BE_Finalize_T
 */
template < >
class CUTS_BE_Finalize_T <CUTS_CHAOS::Context> :
  public CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor> visitor_type;

  CUTS_BE_Finalize_T (CUTS_CHAOS::Context & context);

  virtual ~CUTS_BE_Finalize_T (void);

  void generate (const CHAOS::RootFolder & folder);
};

#endif  // !defined _CUTS_OPENSPLICE_GENERATORS_H_
