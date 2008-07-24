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
      /**
       * Hamilton:
       *
       * Please make sure all your methods have a Doxygen comment describing
       * its purpose and parameters. Please see the following for help on
       * Doxygen:
       *
       *   http://www.doxygen.org
       *
       * Also, please make sure you follow the ACE coding guidelines:
       *
       *   http://www.dre.vanderbilt.edu/~schmidt/DOC_ROOT/ACE/docs/ACE-guidelines.html
       *
       * More specifically, please set your *tab width* to 2 *spaces*, convert
       * spaces to tabs, and place a *space* after a open parenthesis '('. You can
       * set this in Visual Studio 2005 at the following location:
       *
       *   Tools | Options | Text Editor | C# | Formatting
       *
       * Please make this one of the highest priority updates before you continue
       * adding any more functionality!!
       */
        private bool InQuietMode_;

        private void Page_Load(object sender, System.EventArgs e)
        {
            if (IsPostBack)
                return;
            InQuietMode = false;
        }

      /**
       * Initial event/fucntion called with the page is loaded.
       *
       * @param[in]           sender        Sender of the event
       * @param[in]           e             Arguments for the event.
       */
      private void Page_Load (object sender, System.EventArgs e)
      {
      }

        protected override void OnPreRender(EventArgs e)
        {
            ClearBlankMessages();
            base.OnPreRender(e);
        }

        public bool InQuietMode
        {
            get { return InQuietMode_; }
            set { InQuietMode_ = value; }
        }

        private void ClearBlankMessages()
        {
          /**
           * Hamilton:
           *
           * Please use the 'this.' qualifier when accessing any member of
           * the class.
           *
           * Also, place a '_' after any private variable, event if its the
           * id of a control defined in the .aspx page.
           */
            if (message_text_error.Text == String.Empty)
                message_error.Visible = false;
            if (message_text_info.Text == String.Empty)
                message_info.Visible = false;
            if (message_text_success.Text == String.Empty)
                message_success.Visible = false;
        }

        /**
         * Hamilton:
         *
         * Please do not place leading '_' on a variable.
         */
        public void AddNewMessage(string _message)
        public void AddNewMessage_Info(string _message)
        {
            AddNewMessage (_message,MessageSeverity.Information);
        }

        /**
         * Hamilton:
         *
         * Please do not place leading '_' on a variable.
         */
        public void AddNewMessage_Error(string _message)
        {
            AddNewMessage(_message, MessageSeverity.Error);
        }
        
        public void AddNewMessage_Success(string _message)
        {
            AddNewMessage(_message, MessageSeverity.Success);
        }        

        public void AddNewMessage(string _message, MessageSeverity _severity)
        {
            if (InQuietMode_)
                return;

            if (_severity == MessageSeverity.Information)
            {
                if (message_text_info.Text.Contains(_message))
                    return;
                if (message_text_info.Text != String.Empty)
                    message_text_info.Text += "<br />";
                message_text_info.Text += _message;
                message_info.Visible = true;
            }
            else if (_severity == MessageSeverity.Success)
            {
                if (message_text_success.Text.Contains(_message))
                    return;
                if (message_text_success.Text != String.Empty)
                    message_text_success.Text += "<br />";
                message_text_success.Text += _message;
                message_success.Visible = true;
            }
            else
            {
                if (message_text_error.Text.Contains(_message))
                    return;
                if (message_text_error.Text != String.Empty)
                    message_text_error.Text += "<br />";
                message_text_error.Text += _message;
                message_error.Visible = true;
            }
        }

        /**
         * Hamilton:
         *
         * Please update this function so that it works with a single panel
         * based on the comment in BMW_Master.aspx
         */
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
            {
              /**
               * Hamilton:
               *
               * Please remove this error message an
               */
              AddNewMessage("I could not figure out which messages you wanted to clear!" +
                  "(Hint: Just switch pages to clear them all!)", MessageSeverity.Error);
            }
        }
    }
}
