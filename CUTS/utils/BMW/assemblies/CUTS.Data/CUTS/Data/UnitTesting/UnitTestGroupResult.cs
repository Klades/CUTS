// -*- C# -*-

//=============================================================================
/**
 * @file          UnitTestGroupResults.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System;
using System.Collections;

namespace CUTS.Data.UnitTesting
{
  /**
   * @class UnitTestGroupResult
   *
   * Result structure for a unit test that contains grouping.
   */
  [Serializable]
  public class UnitTestGroupResult : UnitTestResult
  {
    /**
     * Default constructor.
     */
    public UnitTestGroupResult ()
    {

    }

    /**
     * Get the results for the grouping. This will return an array
     * of unit test results, where each item in the array is the result
     * for a group.
     */
    public UnitTestResult[] Results
    {
      get
      {
        return (UnitTestResult []) this.results_.ToArray (typeof (UnitTestResult));
      }
    }

    /**
     * Add a new group's result to the set.
     *
     * @param[in]       result        Group's result.
     */
    public void Add (UnitTestResult result)
    {
      this.results_.Add (result);
    }

    /**
     * Clear all the results for the grouping.
     */
    public void Clear ()
    {
      this.results_.Clear ();
    }

    /**
     * Collection of results for the group.
     */
    private ArrayList results_ = new ArrayList ();
  }
}

