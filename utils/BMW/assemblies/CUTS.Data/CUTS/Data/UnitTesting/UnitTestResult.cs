// -*- C# -*-

//=============================================================================
/**
 * @file        UnitTestResults.cs
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

using System;
using System.ComponentModel;
using System.Web.UI;

namespace CUTS.Data.UnitTesting
{
  [Serializable]
  public class UnitTestResult
  {
    /**
     * Default constructor.
     */
    public UnitTestResult ()
    {

    }

    /**
     * Initializing constructor.
     */
    public UnitTestResult (object value)
    {
      this.value_ = value;
    }

    #region Attributes
    /**
     * Setter/getter attribute for the unit test's result.
     */
    public object Value
    {
      set
      {
        this.value_ = value;
      }

      get
      {
        return this.value_;
      }
    }

    [MergableProperty (false),
     PersistenceMode (PersistenceMode.InnerProperty)]
    public GroupResult GroupResult
    {
      get
      {
        return this.groups_;
      }
    }

    public string EvaluationString
    {
      get
      {
        return this.eval_;
      }

      set
      {
        this.eval_ = value;
      }
    }
    #endregion

    /**
     * Result of the unit test.
     */
    private object value_;

    private string eval_;

    /**
     * Group result set for the unit test.
     */
    private GroupResult groups_ = new GroupResult ();
  }
}
