// -*- C++ -*-

//=============================================================================
/**
 * @file        Endpoint_Data.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ENDPOINT_DATA_H_
#define _CUTS_ENDPOINT_DATA_H_

#include "cuts/config.h"
#include "cuts/CUTS_export.h"
#include "ace/Time_Value.h"

//=============================================================================
/**
 * @class CUTS_Endpoint_Data
 */
//=============================================================================

class CUTS_Export CUTS_Endpoint_Data
{
public:
  static const CUTS_Endpoint_Data zero;

  /// Default constructor.
  CUTS_Endpoint_Data (void);

  /**
   * Initializing constructor.
   *
   * @param[in]     toc         Time of completion.
   * @param[in]     datasize    Data size of endpoint.
   */
  CUTS_Endpoint_Data (const ACE_Time_Value & toc, size_t datasize);

  /**
   * Copy constructor.
   *
   * @param[in]       src         The source object.
   */
  CUTS_Endpoint_Data (const CUTS_Endpoint_Data & src);

  /// Destructor.
  ~CUTS_Endpoint_Data (void);

  /// Size of the data sent at this endpoint.
  size_t data_size (void) const;

  /// Time of completion for the endpoint.
  const ACE_Time_Value & time_of_completion (void) const;

  /**
   * Set the endpoint's data.
   *
   * @param[in]       toc           Time of completion.
   * @param[in]       data_size     Data size of the endpoint.
   */
  void set (const ACE_Time_Value & toc, size_t data_size);

  /**
   * Assignment operator.
   *
   * @param[in]       rhs       Right-hand side of operator.
   * @return          Reference to this object.
   */
  const CUTS_Endpoint_Data & operator = (const CUTS_Endpoint_Data & rhs);

  /**
   * Increase the endpoint data by the right-hand side
   *
   * @param[in]       rhs           Right-hand side of the equation.
   * @return          Reference to self.
   */
  const CUTS_Endpoint_Data & operator += (const CUTS_Endpoint_Data & rhs);

  bool operator == (const CUTS_Endpoint_Data & rhs) const;

  bool operator <= (const CUTS_Endpoint_Data & rhs) const;
  bool operator < (const CUTS_Endpoint_Data & rhs) const;

  bool operator >= (const CUTS_Endpoint_Data & rhs) const;
  bool operator > (const CUTS_Endpoint_Data & rhs) const;

protected:
  /// Size of the data send at this endpoint.
  size_t data_size_;

  /// Time of completion for the endpoint.
  ACE_Time_Value toc_;
};

CUTS_Export
CUTS_Endpoint_Data operator / (const CUTS_Endpoint_Data & ed, double d);

#if defined (__CUTS_INLINE__)
#include "cuts/Endpoint_Data.inl"
#endif

#endif  // !defined _CUTS_ENDPOINT_DATA_H_
