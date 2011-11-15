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

namespace CUTS.Web.UI
{
  /**
   * @class Console
   */
  [ParseChildren (true),
   PersistChildren (false)]
  public class Console : CompositeControl, INamingContainer
  {
    /**
     * Default constructor.
     */
    public Console ()
    {

    }

    [ReadOnly(true),
     MergableProperty (false),
     PersistenceMode (PersistenceMode.InnerProperty)]
    public ConsoleMessages Messages
    {
      get
      {
        return this.messages_;
      }
    }

    public void Add (MessageSeverity severity, string message)
    {
      ConsoleMessage msg = new ConsoleMessage ();
      msg.Severity = severity;
      msg.Message = message;

      this.Add (msg);
    }

    public void Add (Exception ex)
    {
      ConsoleMessage msg = new ConsoleMessage ();
      msg.Severity = MessageSeverity.Error;
      msg.Message = ex.Message + "<br />" + ex.StackTrace.Replace ("\n", "<br />");

      this.Add (msg);
    }

    public void Add (ConsoleMessage msg)
    {
      // Make sure the child controls are created.
      this.EnsureChildControls ();

      // Insert the new message.
      this.messages_.Add (msg);

      Panel console = this.get_console ();
      Console.insert_message (console, msg);

      // Bubble the event to any parents.
      if (this.AddMessage != null)
        this.AddMessage (this, new EventArgs ());
    }

    /**
     * Clear the console messages.
     */
    public void Clear ()
    {
      // Make sure the child controls are created.
      this.EnsureChildControls ();

      // Clear all the messages.
      this.messages_.Clear ();

      // Clear messages from the panel.
      Panel console = this.get_console ();
      console.Controls.Clear ();

      if (this.ClearMessages != null)
        this.ClearMessages (this, new EventArgs ());
    }

    protected override void CreateChildControls ()
    {
      base.CreateChildControls ();

      // Create the panel for displaying console messages
      Panel console = new Panel ();
      this.Controls.Add (console);

      console.ScrollBars = ScrollBars.Auto;

      // Write the horizontal line a the bottom of the control.
      this.Controls.Add (new LiteralControl ("<hr />"));

      LinkButton clear_link = new LinkButton ();
      this.Controls.Add (clear_link);

      clear_link.Text = "Clear all messages";
      clear_link.Click += new EventHandler(handle_clear_messages);

      // Write the console messages.
      foreach (ConsoleMessage msg in this.messages_)
        Console.insert_message (console, msg);
    }

    /**
     * Event handler for clearing the console messages
     *
     * @param[in]       object        Sender of the event
     * @param[in]       e             Event arguments
     */
    protected void handle_clear_messages (object sender, EventArgs e)
    {
      this.Clear ();
    }

    protected override void LoadViewState (object savedState)
    {
      object[] state = (object[])savedState;

      if (state[0] != null)
        base.LoadViewState (state[0]);

      if (state[1] != null)
        this.messages_ = (ConsoleMessages)state[1];
    }

    protected override object SaveViewState ()
    {
      object[] state = new object[2];

      state[0] = base.SaveViewState ();
      state[1] = this.messages_;

      return state;
    }

    public event EventHandler ClearMessages;
    public event EventHandler AddMessage;

    static private void insert_message (Panel panel, ConsoleMessage msg)
    {
      Literal literal = new Literal ();
      literal.Text = "<div> &middot; " + msg.Message + "</div>";

      panel.Controls.Add (literal);
    }

    private Panel get_console ()
    {
      return (Panel)this.Controls[0];
    }

    private ConsoleMessages messages_ = new ConsoleMessages ();
  }
}
