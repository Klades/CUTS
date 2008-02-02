/* -*- C++ -*- */

//=============================================================================
/**
 * @file          Statistics_T.h
 *
 * INSERT FILE DESCRIPTION HERE
 *
 * $Id$
 *
 * @author        James H. Hill <hillj@isis.vanderbilt.edu>
 */
//=============================================================================

#ifndef _CUTS_STATISTICS_T_H_
#define _CUTS_STATISTICS_T_H_

#include "ace/If_Then_Else.h"
#include "cuts/Traits.h"

template <typename T, bool is_builtin>
struct zero_t;

template <typename T>
struct zero_t <T, true>
{
  static inline T value (void)
  {
    return static_cast <T> (0);
  }
};

template <typename T>
struct zero_t <T, false>
{
  static inline T value (void)
  {
    return T::zero;
  }
};

//=============================================================================
/**
 * @struct CUTS_zero
 *
 * Get the zero value (i.e., 0) of type T.
 */
//=============================================================================

template <typename T>
struct CUTS_zero
{
public:
  static inline T value (void)
  {
    return zero_t <T, CUTS::builtin_type <T>::result_type>::value ();
  }
};

//=============================================================================
/**
 * @class CUTS_Statistics_T
 *
 * Generalized running statistic object. It calculates the minimum, average,
 * and maximum value handled during its lifetime. This object, however, does
 * not keep track of each value used to derive the statistics.
 *
 * If T is not a builtin type, it must define a zero trait, i.e., T::zero.
 */
//=============================================================================

template <typename T>
class CUTS_Statistics_T
{
public:
  /// The value type of the statistics.
  typedef T value_type;

  /// Default constructor.
  CUTS_Statistics_T (void);

  /**
   * Copy constructor.
   *
   * @param[in]         stat        Source statistic's object.
   */
  CUTS_Statistics_T (const CUTS_Statistics_T <T> & stat);

  /// Destructor.
  ~CUTS_Statistics_T (void);

  /// Reset the data.
  void reset (void);

  /// Get the number of items processed.
  size_t count (void) const;

  /**
   * Get the sum of all the data.
   *
   * @return      The summation of the data.
   */
  const T & summation (void) const;

  /**
   * Get the max value of the data.
   *
   * @return      The max value.
   */
  const T & max_value (void) const;

  /**
   * Get the min value of the data.
   *
   * @return      The min value.
   */
  const T & min_value (void) const;

  /**
   * Calculate the average value of the data.
   *
   * @param[in]       avg       Output of the average value.
   */
  template <typename T1>
  void avg_value (T1 & avg) const;

  /**
   * Assignment operator.
   *
   * @param[in]       rhs       Right-hand side of the operator.
   * @return          Reference to self.
   */
  const CUTS_Statistics_T & operator = (const CUTS_Statistics_T & rhs);

  /**
   * Addition assignment operator.
   *
   * @param[in]       rhs       Right-hand side of the operator.
   * @return          Reference to self.
   */
  const CUTS_Statistics_T & operator += (const CUTS_Statistics_T & rhs);

  /**
   * Addition assignment operator.
   *
   * @param[in]       rhs       Right-hand side of the operator.
   * @return          Reference to self.
   */
  const CUTS_Statistics_T & operator += (const T & rhs);

private:
  /// Number of data elements.
  size_t count_;

  /// The summation of the data elements.
  T sum_;

  /// The minimum value of the data elements.
  T min_;

  /// The maximum value of the data elements.
  T max_;
};

#if defined (__CUTS_INLINE__)
#include "Statistics_T.inl"
#endif  /* defined __CUTS_INLINE__ */

#include "Statistics_T.cpp"

#endif  /* !defined _CUTS_STATISTICS_T_H_ */
