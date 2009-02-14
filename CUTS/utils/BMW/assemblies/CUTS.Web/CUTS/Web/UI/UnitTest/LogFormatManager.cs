// -*- C# -*-

//=============================================================================
/**
 * @file          LogFormatManager.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using CUTS.Data.UnitTesting;

namespace CUTS.Web.UI.UnitTest
{
  public class LogFormatManager : CompositeControl, INamingContainer
  {
    public LogFormatManager ()
    {

    }

    public void Add (LogFormat f)
    {
      // Make sure the child controls exist.
      this.EnsureChildControls ();

      // Insert the log format into the selector.
      LogFormatSelector selector = (LogFormatSelector)this.Controls[0];
      selector.Add (f);
    }

    public void Clear ()
    {
      // Make sure the child controls exist.
      this.EnsureChildControls ();

      // Re-insert the selected formats into the listing.
      foreach (LogFormat format in this.selected_)
        this.selector_.Add (format);

      // Clear the selected log formats.
      this.selected_.Clear ();

      // Delete all the log format nodes.
      this.holder_.Controls.Clear ();
    }

    public LogFormat[] SelectedItems
    {
      get
      {
        return this.selected_.ToArray ();
      }
    }

    public LogFormatRelation [] SelectedRelations
    {
      get
      {
        // Make sure the child controls are created.
        this.EnsureChildControls ();

        LogFormatRelationCollection relations = new LogFormatRelationCollection ();

        // Iterate through each node in the manager. We need to append
        // the relations from each node to create a monolithic listing.
        foreach (Control control in this.holder_.Controls)
        {
          LogFormatNode node = (LogFormatNode)control;
          relations.AddRange (node.Relations);
        }

        return relations.ToArray ();
      }
    }

    protected override void CreateChildControls ()
    {
      // Pass control to the base class.
      base.CreateChildControls ();

      // Create the log format selector.
      this.selector_ = new LogFormatSelector ();
      this.Controls.Add (this.selector_);

      this.selector_.SelectLogFormat += new EventHandler (this.handle_select_log_format);

      // Placeholder for the LogFormatNode controls.
      this.holder_ = new PlaceHolder ();
      this.Controls.Add (this.holder_);

      for (int i = 0; i < this.selected_.Count; ++i)
        this.holder_.Controls.Add (new LogFormatNode ());
    }

    protected override object SaveViewState ()
    {
      object[] state = new object[2];

      state[0] = base.SaveViewState ();
      state[1] = this.selected_;

      return state;
    }

    protected override void LoadViewState (object savedState)
    {
      object[] state = (object[])savedState;

      if (state[0] != null)
        base.LoadViewState (state[0]);

      if (state[1] != null)
        this.selected_ = (LogFormatCollection)state[1];
    }

    private void handle_select_log_format (object sender, EventArgs e)
    {
      // Get the selected log format.
      LogFormatSelector selector = (LogFormatSelector)this.Controls[0];
      LogFormat lf = selector.SelectedLogFormat;

      // Create a new LogFormatNode for the selected LogFormat.
      LogFormatNode node = new LogFormatNode ();
      this.holder_.Controls.Add (node);

      // Set the value of the node.
      node.Value = lf;

      // Save selected log format and update candidate formats.
      this.selected_.Add (lf);

      foreach (Control c in this.holder_.Controls)
      {
        node = (LogFormatNode)c;
        node.CandidateChildren (this.selected_);
      }
    }

    private PlaceHolder holder_;

    private LogFormatCollection selected_ = new LogFormatCollection ();

    private LogFormatSelector selector_;
  }
}
