// -*- C++ -*-

//=============================================================================
/**
 * @file        XML_Manager.h
 *
 * Defines the CUTS_BE_XML_Manager manager object
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_XML_MANAGER_H_
#define _CUTS_BE_XML_MANAGER_H_

#include "../BE_Manager_T.h"
#include "../BE_Workspace_Strategy.h"
#include "../BE_Project_Generator.h"
#include "XML_Generators.h"

typedef CUTS_BE_Manager_T <CUTS_BE_Xml>
                           CUTS_BE_XML_Manager;

#endif  // !defined _CUTS_BE_XML_MANAGER_H_
