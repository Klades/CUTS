// -*- C++ -*-

//=============================================================================
/**
 *  @file         Portico_Publisher_Table_T.h
 *
 *  $Id$
 *
 *  Code generated by iCCM skeleton project generator that is include
 *  in the CUTS (http://cuts.cs.iupui.edu) and developed by:
 *
 *      Software Engineering & Distributed System (SEDS) Group
 *      Indiana Univesity-Purdue University Indianapolis
 *      Indianapolis, IN 46202
 */
//=============================================================================

#ifndef _ICCM_PORTICO_PUBLISHER_TABLE_T_H_
#define _ICCM_PORTICO_PUBLISHER_TABLE_T_H_

#include "cuts/iccm/servant/Publisher_Table_T.h"

#include "Portico_Publisher_Table.h"
#include "Portico_Publisher_T.h"

namespace iCCM
{

/**
 * @class Portico_Publisher_Table_T
 */
template <typename EVENT>
class Portico_Publisher_Table_T :
  public Publisher_Table_T < Portico_Publisher_Table, Portico_Publisher_T <EVENT>, true >
{
public:
  /// Type definition of the base type.
  typedef Publisher_Table_T < Portico_Publisher_Table,
                              Portico_Publisher_T <EVENT>,
                              true > base_type;

  /// Default constructor.
  Portico_Publisher_Table_T (void);

  /// Destructor.
  virtual ~Portico_Publisher_Table_T (void);

  /**
   * Subscribe an event consumer.
   *
   * @param[in]       consumer          Event consumer object
   * @return          Cookie object
   */
  virtual ::Components::Cookie * subscribe (::Components::EventConsumerBase_ptr);

  /**
   * Unsubscribe an event consumer.
   *
   * @param[in]       consumer         Cookie object
   * @return          Event consumer object
   */
  virtual ::Components::EventConsumerBase_ptr unsubscribe (::Components::Cookie *);

  /// Send an event.
  void send_event (EVENT * ev);

  /// Allocate a new event.
  EVENT * allocate_event (void);

  /**
   * Initialize this publisher's handle.
   *
   * @param[in]           rtiamb            Pointer to the ambassador
   */
  void init (RTI::RTIambassador * rtiamb);

private:
  /// Type definition of the object class factory.
  typedef typename
    Portico_ObjectClass_Trait_T <EVENT>::objectclass_factory_type
    objectclass_factory_type;

  /// Pointer to the constructed object class.
  std::auto_ptr <objectclass_factory_type> factory_;
};

}

#include "Portico_Publisher_Table_T.cpp"

#endif  // !defined _ICCM_PORTICO_PUBLISHER_TABLE_T_H_
