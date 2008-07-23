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
    public enum MessageSeverity
    {
        Error, Information, Success
    }

    public partial class BMW_Master : System.Web.UI.MasterPage
    {
        private void Page_Load(object sender, System.EventArgs e)
        {
        }

        protected override void OnPreRender(EventArgs e)
        {
            ClearBlankMessages();
            base.OnPreRender(e);
        }     

        private void ClearBlankMessages()
        {
            if (message_text_error.Text == String.Empty)
                message_error.Visible = false;
            if (message_text_info.Text == String.Empty)
                message_info.Visible = false;
            if (message_text_success.Text == String.Empty)
                message_success.Visible = false;
        }

        public void AddNewMessage(string _message)
        {
            AddNewMessage (_message,MessageSeverity.Error);
        }

        public void AddNewMessage(string _message, MessageSeverity _severity)
        {
            if (_severity == MessageSeverity.Information)
            {
                if (message_text_info.Text != String.Empty)
                    message_text_info.Text += "<br />";
                message_text_info.Text += _message;
                message_info.Visible = true;
            }
            else if (_severity == MessageSeverity.Success)
            {
                if (message_text_success.Text != String.Empty)
                    message_text_success.Text += "<br />";
                message_text_success.Text += _message;
                message_success.Visible = true;
            }
            else
            {
                if (message_text_error.Text != String.Empty)
                    message_text_error.Text += "<br />";
                message_text_error.Text += _message;
                message_error.Visible = true;
            }
        }

        public void OnClick_Clear_Me(object sender, EventArgs e)
        {
            Button btn = (Button)sender;
            Panel p = (Panel)btn.Parent;

            if (p == message_error)
            {
                message_error.Visible = false;
                message_text_error.Text = String.Empty;
            }
            else if (p == message_info)
            {
                message_info.Visible = false;
                message_text_info.Text = String.Empty;
            }
            else if (p == message_success)
            {
                message_success.Visible = false;
                message_text_success.Text = String.Empty;
            }
            else
                AddNewMessage("I could not figure out which messages you wanted to clear!" +
                    "(Hint: Just switch pages to clear them all!)", MessageSeverity.Error);
        }
    }
}