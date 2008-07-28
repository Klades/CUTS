using System;
using System.Collections;
using System.Configuration;
using System.ComponentModel;
using System.Data;
using System.Data.Odbc;
using System.Diagnostics;
using System.ServiceProcess;
using System.Drawing;
using System.Web;
using System.Web.SessionState;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;
using System.Text.RegularExpressions;

namespace CUTS
{
  /// <summary>
  /// Hamilton:
  ///
  /// Pleaes move the MessageSeverity enumeration its own file preferably
  /// in the App_Code folder.
  /// </summary>
  public enum MessageSeverity
  {
    /// <summary>
    /// Hamilton:
    ///
    /// Please place each item in the enumeration on its own line and add
    /// a comment above each one. Also, please manaully assign each one a
    /// value.
    ///
    /// Lastly, please make the enumerations all capital letters!!
    /// </summary>
    Error, Information, Success
  }

  /**
   * @class BMW_Master
   *
   * Master page for the Benchmark Manager Web (BMW) Utility application.
   * This class defines the common structure of the website, and variables
   * and methods that are accesible to other member pages.
   */
  public partial class BMW_Master : System.Web.UI.MasterPage
  {
    private bool InQuietMode_;

    /**
     * Initial event/fucntion called with the page is loaded.
     *
     * @param[in]           sender        Sender of the event
     * @param[in]           e             Arguments for the event.
     */
    private void Page_Load (object sender, System.EventArgs e)
    {

    }

    //protected override void OnPreRender (EventArgs e)
    //{
    //  ClearBlankMessages ();
    //  base.OnPreRender (e);
    //}

    public bool InQuietMode
    {
      get { return InQuietMode_; }
      set { InQuietMode_ = value; }
    }

    //private void ClearBlankMessages ()
    //{
    //  if (message_text_error.Text == String.Empty)
    //    message_error.Visible = false;
    //  if (message_text_info.Text == String.Empty)
    //    message_info.Visible = false;
    //  if (message_text_success.Text == String.Empty)
    //    message_success.Visible = false;
    //}

    //public void show_error_message (string message)
    //{
    //  AddNewMessage (message, MessageSeverity.Information);
    //}

    //public void show_error_message (string message)
    //{
    //  AddNewMessage (message, MessageSeverity.Error);
    //}

    //public void show_info_message (string message)
    //{
    //  AddNewMessage (message, MessageSeverity.Success);
    //}

    //public void AddNewMessage (string message, MessageSeverity severity)
    //{
    //  if (InQuietMode_)
    //    return;

    //  if (severity == MessageSeverity.Information)
    //  {
    //    if (message_text_info.Text.Contains (message))
    //      return;
    //    if (message_text_info.Text != String.Empty)
    //      message_text_info.Text += "<br />";
    //    message_text_info.Text += message;
    //    message_info.Visible = true;
    //  }
    //  else if (severity == MessageSeverity.Success)
    //  {
    //    if (message_text_success.Text.Contains (message))
    //      return;
    //    if (message_text_success.Text != String.Empty)
    //      message_text_success.Text += "<br />";
    //    message_text_success.Text += message;
    //    message_success.Visible = true;
    //  }
    //  else
    //  {
    //    if (message_text_error.Text.Contains (message))
    //      return;
    //    if (message_text_error.Text != String.Empty)
    //      message_text_error.Text += "<br />";
    //    message_text_error.Text += message;
    //    message_error.Visible = true;
    //  }
    //}

    /**
     * Show an error message to the user.
     *
     * @param[in]         msg             Message to display
     */
    public void show_error_message (String msg)
    {
      Label label = new Label ();
      label.CssClass = "msg_error";
      label.Text = "<div>" + msg + "</div>";

      this.insert_console_message (label);
    }

    /**
     * Show an info message to the user.
     *
     * @param[in]         msg             Message to display
     */
    public void show_info_message (String msg)
    {
      Label label = new Label ();
      label.CssClass = "msg_info";
      label.Text = "<div>" + msg + "</div>";

      this.insert_console_message (label);
    }

    /**
     * Show a warning message to the user.
     *
     * @param[in]         msg             Message to display
     */
    public void show_warning_message (String msg)
    {
      Label label = new Label ();
      label.CssClass = "msg_warning";
      label.Text = "<div>" + msg + "</div>";

      this.insert_console_message (label);
    }

    /**
     * Insert the actual message into the console. This will display the
     * console if it is not already visible to the user.
     *
     * @param[in]         msg_control     Control containing the message
     */
    private void insert_console_message (Control msg_control)
    {
      this.console_text_.Controls.Add (msg_control);

      // Make sure we can actually see the console.
      if (!this.console_.Visible)
        this.console_.Visible = true;
    }

    /**
     * Hamilton:
     *
     * Please update this function so that it works with a single panel
     * based on the comment in BMW_Master.aspx
     */
    //public void OnClick_Clear_Me (object sender, EventArgs e)
    //{
    //  Button btn = (Button)sender;
    //  Panel p = (Panel)btn.Parent;

    //  if (p == message_error)
    //  {
    //    message_error.Visible = false;
    //    message_text_error.Text = String.Empty;
    //  }
    //  else if (p == message_info)
    //  {
    //    message_info.Visible = false;
    //    message_text_info.Text = String.Empty;
    //  }
    //  else if (p == message_success)
    //  {
    //    message_success.Visible = false;
    //    message_text_success.Text = String.Empty;
    //  }
    //  else
    //  {
    //    /**
    //     * Hamilton:
    //     *
    //     * Please remove this error message an
    //     */
    //    AddNewMessage ("I could not figure out which messages you wanted to clear!" +
    //        "(Hint: Just switch pages to clear them all!)", MessageSeverity.Error);
    //  }
    //}
  }
}
