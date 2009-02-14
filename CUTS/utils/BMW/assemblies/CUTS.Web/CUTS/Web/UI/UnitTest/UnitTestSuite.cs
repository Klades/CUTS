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

namespace CUTS.Web.UI.UnitTest
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

    /**
     *
     */
    public void Add (UnitTestPackage package)
    {
      // Make sure the child controls exist.
      this.EnsureChildControls ();

      // Inser the package into the control.
      PlaceHolder holder = this.get_package_placeholder ();
      holder.Controls.Add (package);

      package.EvaluateUnitTest += new CommandEventHandler (this.handle_evaluate_unit_test);

      // Increment the package count.
      this.packages_.Add (package);
      ++this.package_count_;
    }

    /// Clear all the test packages in the suite.
    public void Clear ()
    {
      // Make sure the child controls exist.
      this.EnsureChildControls ();

      // Clear the controls.
      PlaceHolder holder = this.get_package_placeholder ();
      holder.Controls.Clear ();

      // Reset the package count.
      this.package_count_ = 0;
    }

    /**
     *
     */
    protected override void CreateChildControls ()
    {
      base.CreateChildControls ();

      PlaceHolder holder = new PlaceHolder ();
      this.Controls.Add (holder);

      for (int i = 0; i < this.package_count_; ++i)
      {
        UnitTestPackage package = new UnitTestPackage ();
        holder.Controls.Add (package);

        package.EvaluateUnitTest += new CommandEventHandler (this.handle_evaluate_unit_test);
      }

      this.Controls.Add (new LiteralControl ("<br clear='all' />"));
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
        this.package_count_ = (int)state[1];
    }

    /**
     * Save the view state of the control.
     *
     * @return        The controls view state
     */
    protected override object SaveViewState ()
    {
      object[] state = new object[2];

      state[0] = base.SaveViewState ();
      state[1] = this.package_count_;

      return state;
    }

    #region Attributes
    /**
     *
     */
    [ MergableProperty (false),
      PersistenceMode (PersistenceMode.InnerProperty)]
    public UnitTestPackages UnitTestPackages
    {
      get
      {
        return this.packages_;
      }
    }
    #endregion

    private PlaceHolder get_package_placeholder ()
    {
      return (PlaceHolder)this.Controls[0];
    }

    public event CommandEventHandler EvaluateUnitTest;

    private void handle_evaluate_unit_test (object sender, CommandEventArgs e)
    {
      if (this.EvaluateUnitTest != null)
        this.EvaluateUnitTest (this, e);
    }

    #region Member Variables
    /// Number of packages in the test suite.
    private int package_count_;

    /// The actual packages in the test suite.
    private UnitTestPackages packages_ = new UnitTestPackages ();
    #endregion
  }
}
