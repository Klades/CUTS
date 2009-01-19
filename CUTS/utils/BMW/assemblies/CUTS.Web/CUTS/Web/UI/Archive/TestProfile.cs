// -*- C# -*-

//=============================================================================
/**
 * @file        Console.cs
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

using System;
using System.Drawing;
using System.ComponentModel;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace CUTS.Web.UI.Archive
{
  /**
   * @class TestProfile
   */
  public class TestProfile : CompositeControl, INamingContainer
  {
    public TestProfile ()
    {

    }

    public TestProfile (CUTS.TestProfile profile)
    {
      this.profile_ = profile;
    }

    public CUTS.TestProfile Data
    {
      get
      {
        return this.profile_;
      }

      set
      {
        this.profile_ = value;
      }
    }

    protected override void CreateChildControls ()
    {
      base.CreateChildControls ();

      Label label = new Label ();
      this.Controls.Add (label);

      label.Text = "Test Profile";
      label.Style[HtmlTextWriterStyle.TextDecoration] = "underline";

      // The test profile is displayed in a table.
      Table profile = new Table ();
      this.Controls.Add (profile);

      // Create the row for displaying the name.
      TableRow row = new TableRow ();
      profile.Rows.Add (row);

      //== cell for the name.
      TableCell cell = new TableCell ();
      row.Cells.Add (cell);
      cell.Text = "Name:";
      cell.CssClass = "form-title";

      //== cell for the name's value.
      cell = new TableCell ();
      row.Cells.Add (cell);
      cell.Text = this.profile_.name;

      // Create the row for displaying the uuid.
      row = new TableRow ();
      profile.Rows.Add (row);

      //== cell for the UUID.
      cell = new TableCell ();
      row.Cells.Add (cell);
      cell.Text = "UUID:";
      cell.CssClass = "form-title";

      //== cell for the UUID's value
      cell = new TableCell ();
      row.Cells.Add (cell);
      cell.Text = CUTS.Data.UUID.ToString (this.profile_.uuid);
    }

    protected override object SaveViewState ()
    {
      object [] state = new object[2];
      state[0] = base.SaveViewState ();
      state[1] = this.profile_;

      return state;
    }

    protected override void LoadViewState (object savedState)
    {
      object[] state = (object[])savedState;

      if (state[0] != null)
        base.LoadViewState (state[0]);

      if (state[1] != null)
        this.profile_ = (CUTS.TestProfile)state[1];
    }

    private CUTS.TestProfile profile_;
  }
}
