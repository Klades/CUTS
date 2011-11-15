// -*- C# -*-

//=============================================================================
/**
 * @file          LogFormatSelector.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using CUTS.Data.UnitTesting;

namespace CUTS.Web.UI.UnitTest
{
  /**
   * @class LogFormatSelector
   */
  public class LogFormatSelector : CompositeControl, INamingContainer
  {
    public LogFormatSelector ()
    {

    }

    public void Add (LogFormat f)
    {
      // Make sure the child controls exist.
      this.EnsureChildControls ();

      // Insert a new item into the listing.
      this.listing_.Items.Add (new ListItem (f.Text, f.ID.ToString ()));

      // Save the log format.
      this.formats_.Add (f);
    }

    public LogFormat SelectedLogFormat
    {
      get
      {
        return this.selected_;
      }
    }

    protected override void CreateChildControls ()
    {
      // Pass control to the base class
      base.CreateChildControls ();

      this.listing_ = new DropDownList ();
      this.Controls.Add (this.listing_);

      this.insert_ = new LinkButton ();
      this.Controls.Add (this.insert_);

      this.ID = "include_";
      this.insert_.Text = "Include log format into table";
      this.insert_.Click += new EventHandler (this.handle_insert_log_format);
    }

    private void handle_insert_log_format (object sender, EventArgs e)
    {
      // Find the selected log format.
      this.selected_ = this.formats_.Find (int.Parse (this.listing_.SelectedValue));

      // Remove the log format from the selector.
      this.listing_.Items.Remove (this.listing_.SelectedItem);

      // Single all the listeners.
      if (this.SelectLogFormat != null)
        this.SelectLogFormat (this, e);
    }

    public event EventHandler SelectLogFormat;

    protected override void LoadViewState (object savedState)
    {
      object [] state = (object [])savedState;

      if (state[0] != null)
        base.LoadViewState(state[0]);

      if (state[1] != null)
        this.formats_ = (LogFormatCollection)state[1];

      if (state[2] != null)
        this.selected_ = (LogFormat)state[2];
    }

    protected override object SaveViewState ()
    {
      object [] state = new object [3];
      state[0] = base.SaveViewState ();
      state[1] = this.formats_;
      state[2] = this.selected_;

      return state;
    }

    protected override void Render (HtmlTextWriter writer)
    {
      this.listing_.RenderControl (writer);
      writer.WriteBreak ();

      if (this.listing_.Items.Count > 0)
        this.insert_.RenderControl (writer);
    }

    private LogFormatCollection formats_ = new LogFormatCollection ();

    private LogFormat selected_;

    private DropDownList listing_;

    private LinkButton insert_;
  }
}
