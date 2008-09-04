// -*- C++ -*-

//=============================================================================
/**
 * @file          UUID.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UUID_H_
#define _CUTS_UUID_H_

#include "ace/UUID.h"
#include "cuts/UUIDC.h"

/**
 * Extract a ESIA::UUID from the CORBA structure and store it in an
 * ACE_Utils::UUID object.
 *
 * @param[in]         src           Source object
 * @param[in]         dst           Destination object
 * @retval            true          Successfully extracted data
 * @retval            false         Failed to extract data
 */
bool operator >>= (const CUTS::UUID & src, ACE_Utils::UUID & dst);

/**
 * Insert an ACE_Utils::UUID object into an EISA::UUID CORBA
 * structure.
 *
 * @param[in]         dst           Destination object
 * @param[in]         src           Source object
 * @retval            true          Successfully inserted data
 * @retval            false         Failed to insert data
 */
bool operator <<= (CUTS::UUID & dst, const ACE_Utils::UUID & src);

#endif  // !defined _EISA_UUID_H_
