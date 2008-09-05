// $Id$

//=============================================================================
/**
 * @file        Property_Map_T.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_PROPERTY_MAP_H_
#define _CUTS_PROPERTY_MAP_H_

#include "cuts/config.h"
#include "ace/Hash_Map_Manager_T.h"

/**
 * @class CUTS_Property_Map_T
 */
template <typename MUTEX>
class CUTS_Property_Map_T
{
  /// Type definition of the internal hash map.
  typedef
    ACE_Hash_Map_Manager <ACE_CString, ACE_CString, MUTEX> map_type;

public:
  /// Type definition of the mutex type for the property list.
  typedef MUTEX mutex_type;

  /// Type definition of the iterator type.
  typedef typename map_type::iterator iterator;

  /// Type definition of the const iterator type.
  typedef typename map_type::const_iterator const_iterator;

  /// Default constructor
  CUTS_Property_Map_T (void);

  /// Destructor.
  ~CUTS_Property_Map_T (void);

  /**
   * Get the value of a key. If the key is not found, then it is
   * inserted into the map with an empty string value.
   *
   * @param[in]        key            Key of interest
   */
  ACE_CString & operator [] (const ACE_CString & key);

  /**
   * Get the value of a key. If the key exists in the property map, then
   * \a value will contain the value of \a key. If the key does not exist,
   * then nothing will happen.
   *
   * @param[in]         key           Key of interest
   * @param[out]        value         Value of the key
   * @retval            0             Key was found
   * @retval            -1            Key was not found.
   */
  int get (const ACE_CString & key, ACE_CString & value) const;

  /**
   * Set the value of a key. If the key does not exist, then it will
   * be inserted into the property map. If the key already exists, then
   * its value will be overwritten.
   *
   * @param[in]         key           Key of interest
   * @param[in]         value         New value of the key.
   * @retval            0             Successfully set the key's value
   * @retval            -1            Failed to set the key's value
   */
  int set (const ACE_CString & key, const ACE_CString & value);

  /**
   * Get the size of the property map.
   */
  size_t size (void) const;

  /**
   * Determine if the property map contains the specified key.
   *
   * @retval            true          The map contains the key.
   * @retval
   */
  bool contains (const ACE_CString & name) const;

  iterator begin (void);
  const_iterator begin (void) const;

  iterator end (void);
  const_iterator end (void) const;

private:
  /// Type definition of the internal hash map.
  typedef
    ACE_Hash_Map_Manager <ACE_CString, ACE_CString, MUTEX> map_type;

  /// Internal hash map of the property list.
  map_type map_;
};

#if defined (__CUTS_INLINE__)
#include "Property_Map_T.inl"
#endif

#include "Property_Map_T.cpp"

#endif  // !defined _CUTS_PROPERTY_MAP_H_
