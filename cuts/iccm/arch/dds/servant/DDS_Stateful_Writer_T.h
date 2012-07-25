// -*- C++ -*-

//==============================================================================
/**
 *  @file        DDS_Stateful_Writer_T.h
 *
 *  $Id$
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _DDS_STATEFUL_WRITER_T_H_
#define _DDS_STATEFUL_WRITER_T_H_

namespace iCCM
{

/**
 * @class DDS_Stateful_Writer_T
 *
 * Base class for stateful writers. There are two kinds of stateful writers
 * in DDS: unregistered event and registered event. This class also the
 * DDS_Publisher_T and DDS_Publiser_Table_T to use the State pattern and
 * optimize allocating and sending an event.
 */
template <typename T, typename EVENT>
class DDS_Stateful_Writer_T
{
public:
  /// Type definition of the event type.
  typedef EVENT event_type;

  /// Type definition of the event traits.
  typedef typename T::event_traits_type <EVENT>::result_type event_traits_type;

  /**
   * Initializing constructor.
   *
   * @param[in]         writer      Abstract writer object
   */
  DDS_Stateful_Writer_T (typename T::datawriter_ptr_type writer);

  /// Destructor.
  virtual ~DDS_Stateful_Writer_T (void);

  /// Send an event.
  virtual void send_event (EVENT * ev) = 0;

  /// Allocate a new event.
  virtual EVENT * allocate_event (void) = 0;

protected:
  /// Type specific writer for the publisher.
  typename event_traits_type::writer_var_type writer_;

private:
  // prevent the following operations
  DDS_Stateful_Writer_T (const DDS_Stateful_Writer_T &);
  const DDS_Stateful_Writer_T & operator = (const DDS_Stateful_Writer_T &);
};

/**
 * @class DDS_Unregistered_Instance_Writer_T
 *
 * Implementation of the DDS_Stateful_Writer_T for unregistered instances.
 */
template <typename T, typename EVENT>
class DDS_Unregistered_Instance_Writer_T : public DDS_Stateful_Writer_T <T, EVENT>
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]         writer      Abstract writer object
   */
  DDS_Unregistered_Instance_Writer_T (typename T::datawriter_ptr_type writer);

  /// Destructor.
  virtual ~DDS_Unregistered_Instance_Writer_T (void);

  /// Send an event.
  virtual void send_event (EVENT * ev);

  /// Allocate a new event.
  virtual EVENT * allocate_event (void);
};

/**
 * @class DDS_Registered_Instance_Writer_T
 *
 * Implementation of the DDS_Stateful_Writer_T for registered instances.
 */
template <typename T, typename EVENT>
class DDS_Registered_Instance_Writer_T : public DDS_Stateful_Writer_T <T, EVENT>
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]         writer      Abstract writer object
   */
  DDS_Registered_Instance_Writer_T (typename T::datawriter_ptr_type writer);

  /// Destructor.
  virtual ~DDS_Registered_Instance_Writer_T (void);

  /// Send an event.
  virtual void send_event (EVENT * ev);

  /// Allocate a new event.
  virtual EVENT * allocate_event (void);

private:
  /// The instance handle for the writer.
  typename T::instancehandle_type inst_;

  /// Event associated with the registered event.
  typename event_traits_type::downcall_event_type event_;
};

}

#if defined (__CUTS_INLINE__)
#include "DDS_Stateful_Writer_T.inl"
#endif  // !defined __CUTS_INLINE__

#include "DDS_Stateful_Writer_T.cpp"

#endif  // _DDS_STATEFUL_WRITER_T_H_
