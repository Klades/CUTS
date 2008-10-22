// -*- C# -*-

//=============================================================================
/**
 * @file          UnitTestSuite.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using CUTS.Data.UnitTesting;
using MySql.Data.MySqlClient;

namespace CUTS.Web.UI.UnitTesting
{
  /**
   * @class UnitTestSuite
   */
  [ ParseChildren(true),
    PersistChildren(false)]
  public class UnitTestSuite : CompositeControl, INamingContainer
  {
    public UnitTestSuite ()
    {

    }

    public UnitTestSuite (int test)
    {
      this.test_number_ = test;
    }

    /**
     *
     */
    public void Add (UnitTestPackage package)
    {
      // Inser the package into the control.
      PlaceHolder holder = this.UnitTestPackagePlaceHolder;
      holder.Controls.Add (package);

      // Increment the package count.
      ++this.packages_;
      this.EvaluateAllLinkButton.Visible = true;
    }

    /**
     * Clear all the test packages from the control. This is as simple
     * as deleting all the child controls.
     */
    public void Clear ()
    {
      PlaceHolder holder = this.UnitTestPackagePlaceHolder;
      holder.Controls.Clear ();

      this.packages_ = 0;
      this.EvaluateAllLinkButton.Visible = false;
    }

    /**
     *
     */
    protected override void CreateChildControls ()
    {
      PlaceHolder holder = new PlaceHolder ();
      this.Controls.Add (holder);

      for (int i = 0; i < this.packages_; ++i)
        holder.Controls.Add (new UnitTestPackage (this));

      this.Controls.Add (new LiteralControl ("<br clear='all' />"));

      LinkButton link = new LinkButton ();
      this.Controls.Add (link);

      link.Click += new System.EventHandler (this.onclick_evaluate_all_unit_tests);
      link.Text = "Evaluate all unit tests";
      link.Visible = false;
    }

    void onclick_evaluate_all_unit_tests (object sender, EventArgs e)
    {
      throw new Exception ("The method or operation is not implemented.");
    }

    /**
     * Load the view state of the control.
     *
     * @param[in]       savedState        Saved view state
     */
    protected override void LoadViewState(object savedState)
    {
      object[] state = (object[])savedState;

      if (state[0] != null)
        base.LoadViewState (state[0]);

      if (state[1] != null)
        this.test_number_ = (int)state[1];

      if (state[2] != null)
        this.packages_ = (int)state[2];
    }

    /**
     * Save the view state of the control.
     *
     * @return        The controls view state
     */
    protected override object SaveViewState ()
    {
      object[] state = new object[3];

      state[0] = base.SaveViewState ();
      state[1] = this.test_number_;
      state[2] = this.packages_;

      return state;
    }

    #region Factory Methods
    public UnitTestPackage NewUnitTestPackage ()
    {
      return new UnitTestPackage (this);
    }
    #endregion

    #region Attributes
    public int TestNumber
    {
      get
      {
        return this.test_number_;
      }

      set
      {
        this.test_number_ = value;
      }
    }

    /**
     *
     */
    [MergableProperty (false),
     PersistenceMode (PersistenceMode.InnerProperty)]
    public UnitTestPackages UnitTestPackages
    {
      get
      {
        // Make sure the child controls are in place.
        this.EnsureChildControls ();

        // Gather all the unit test packages.
        UnitTestPackages packages = new UnitTestPackages ();
        PlaceHolder holder = this.UnitTestPackagePlaceHolder;

        foreach (Control control in holder.Controls)
        {
          if (control is UnitTestPackage)
            packages.Add ((UnitTestPackage)control);
        }

        return packages;
      }
    }

    [MergableProperty (false),
     PersistenceMode (PersistenceMode.InnerProperty)]
    public UnitTestEvaluator Evaluator
    {
      get
      {
        return this.evaluator_;
      }
    }

    private PlaceHolder UnitTestPackagePlaceHolder
    {
      get
      {
        return (PlaceHolder)this.Controls[0];
      }
    }

    private LinkButton EvaluateAllLinkButton
    {
      get
      {
        return (LinkButton)this.Controls[2];
      }
    }
    #endregion

    #region Member Variables
    /**
     * Test number for the test suite.
     */
    private int test_number_ = -1;

    /**
     * Number of packages in the test suite.
     */
    private int packages_ = 0;

    /**
     * Unit test evaluator for the test suite.
     */
    private UnitTestEvaluator evaluator_ =
      new UnitTestEvaluator (new MySqlClientFactory ());
    #endregion
  }
}
