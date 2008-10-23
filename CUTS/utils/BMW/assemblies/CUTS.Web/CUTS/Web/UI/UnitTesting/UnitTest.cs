// -*- C# -*-

//=============================================================================
/**
 * @file          UnitTest.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using CUTS.Data.UnitTesting;

namespace CUTS.Web.UI.UnitTesting
{
  /**
   * @class UnitTest
   *
   * Control for evaluating a unit test within a test package.
   */
  [Serializable]
  public class UnitTest
  {
    /**
     * Default constructor.
     */
    public UnitTest ()
    {
      this.name_ = String.Empty;
      this.utid_ = -1;
    }

    /**
     * Initializing constructor.
     *
     * @param[in]         name          Name of the unit test
     * @param[in]         utid          Id of the unit test
     */
    public UnitTest (String name, int utid)
    {
      this.name_ = name;
      this.utid_ = utid;
    }

    public static readonly UnitTest Undefined = new UnitTest ();

    [NotifyParentProperty (true)]
    public int ID
    {
      get
      {
        return this.utid_;
      }

      set
      {
        this.utid_ = value;
      }
    }

    [ MergableProperty (false),
      PersistenceMode (PersistenceMode.InnerProperty),
      NotifyParentProperty (true)]
    public UnitTestResult Result
    {
      get
      {
        return this.results_;
      }

      set
      {
        this.results_ = value;
      }
    }

    [NotifyParentProperty (true)]
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
     * Name of the unit test.
     */
    private string name_;

    /**
     * Unique id of the unit test.
     */
    private int utid_;

    /**
     * Results for the unit test.
     */
    private UnitTestResult results_;
  }
}
