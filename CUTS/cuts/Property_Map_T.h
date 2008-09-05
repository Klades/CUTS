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
public:
  /// Type definition of the mutex type for the property list.
  typedef LOCK mutex_type;

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
   * Get the value of a key.
   *
   * @param[in]         key           Key of interest
   * @param[out]        value         Value of the key
   */
  int get (const ACE_CString & key, ACE_CString & value) const;

  /**
   * Set the value of a key.
   */
  int set (const ACE_CString & key, const ACE_CString & value);

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
