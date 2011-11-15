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
using System.Collections.Generic;
using System.Runtime.Serialization;

namespace CUTS.Data.UnitTesting
{
  /**
   * @class GroupResultItem
   *
   * Result for a single item in a group result. The item contains both
   * the name and value of the result.
   */
  [Serializable]
  public class GroupResultItem
  {
    #region Constructor
    /**
     * Default constructor.
     */
    public GroupResultItem ()
    {

    }

    /**
     * Initializing constructor.
     *
     * @param[in]       name          Name of the result
     * @param[in]       value         Value of the result
     */
    public GroupResultItem (string name, object value)
    {
      this.name_ = name;
      this.value_ = value;
    }
    #endregion

    #region Attributes
    /**
     * Attribute for setting/getting the name of the result
     */
    public string Name
    {
      get
      {
        return this.name_;
      }

      set
      {
        this.name_ = value;
      }
    }

    /**
     * Attribute for setting/getting the value of the result.
     */
    public object Value
    {
      get
      {
        return this.value_;
      }

      set
      {
        this.value_ = value;
      }
    }
    #endregion

    #region Member variables
    /**
     * Name of the result
     */
    private string name_;

    /**
     * Value of the result
     */
    private object value_;
    #endregion
  }

  /**
   * @class GroupResults
   *
   * Collection of results for different groups in a unit test. Whenever
   * a unit test specifies grouping, then this object is populated with
   * their results.
   */
  [Serializable]
  public class GroupResult : List <GroupResultItem>
  {
    /**
     * Default constructor.
     */
    public GroupResult ()
    {
    }
  }
}
