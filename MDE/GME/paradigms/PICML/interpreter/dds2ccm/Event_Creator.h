// -*- C++ -*-

//==============================================================================
/**
 *  @file        Event_Creator.h
 *
 *  $Id$
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _DDS2CCM_EVENT_CREATOR_H_
#define _DDS2CCM_EVENT_CREATOR_H_

#include "PICML/Visitor.h"
#include "PICML/PICML.h"

#include "cuts/config.h"

namespace dds2ccm
{

/**
 * @class Event_Creator
 *
 * INSERT CLASS DESCRIPTION HERE
 */
class Event_Creator : public PICML::Visitor
{
public:
  /// Default constructor.
  Event_Creator (void);

  /// Destructor.
  virtual ~Event_Creator (void);

  virtual void visit_RootFolder (GAME::Mga::RootFolder_in folder);
  virtual void visit_InterfaceDefinitions (PICML::InterfaceDefinitions_in item);
  virtual void visit_File (PICML::File_in item);
  virtual void visit_Package (PICML::Package_in item);
  virtual void visit_Aggregate (PICML::Aggregate_in item);
  virtual void visit_Member (PICML::Member_in item);

private:
  PICML::InterfaceDefinitions target_folder_;
  GAME::Mga::Model target_model_;

  PICML::Event target_event_;
};

} // namespace dds2ccm

#if defined (__CUTS_INLINE__)
#include "Event_Creator.inl"
#endif  // !defined __CUTS_INLINE__

#endif  // _DDS2CCM_EVENT_CREATOR_H_
