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
    public UnitTestResult (int utid, string name, object result)
    {
      this.id_ = utid;
      this.name_ = name;
      this.result_ = result;
    }

    /**
     * Setter/getter attribute for the unit test's name.
     */
    public string Name
    {
      set
      {
        this.name_ = value;
      }

      get
      {
        return this.name_;
      }
    }

    /**
     * Setter/getter attribute for the unit test's result.
     */
    public object Result
    {
      set
      {
        this.result_ = value;
      }

      get
      {
        return this.result_;
      }
    }

    /**
     * Setter/getter methods for the unit test's id.
     */
    public int ID
    {
      set
      {
        this.id_ = value;
      }

      get
      {
        return this.id_;
      }
    }

    /**
     * Name of the unit test.
     */
    private string name_;

    /**
     * ID associated with the unit test.
     */
    private int id_ = -1;

    /**
     * Result of the unit test.
     */
    private object result_;
  }
}
