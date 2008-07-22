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
    public partial class BMW_Master : System.Web.UI.MasterPage
    {
        private void Page_Load(object sender, System.EventArgs e)
        {
            if (IsPostBack)
            {
                reCreateMessages();
                return;
            }

            // If we are on a new page, clear any old
            // messages
            ClearAllMessages();
        }
        private void reCreateMessages()
        {
            if (ViewState["messages"] == null)
                return;

            // Create the regex
            string messages = (string)ViewState["messages"];
            Regex reg = new Regex(@"~(?<message>.+?)\*(?<severity>.+?);");
            Match m = reg.Match(messages);

            // extract the variables
            while (m.Success)
            {
                string message = m.Groups["message"].ToString(),
                      severity = m.Groups["severity"].ToString();


                new_message_.Controls.Add(new BMW_Message(message, MessageSeverity.Information));

                m = m.NextMatch();
            }
 
        }

        public int Temp
        {
            get
            { return 1; }
        }

        public void ClearAllMessages()
        {
            new_message_.Controls.Clear();
        }

        public void AddNewMessage(string _message)
        {
            AddNewMessage (_message,MessageSeverity.Error);
        }

        public void AddNewMessage(string _message, MessageSeverity _severity)
        {
            new_message_.Controls.Add(new BMW_Message(_message,_severity));
            ViewState["messages"] += "~" + _message + "*" + _severity.ToString() + ";";
        }
    }
}
public enum MessageSeverity
{
    Error, Information, Success
}

public class BMW_Message : CompositeControl
{
    private string _message;
    private MessageSeverity _severity;

    public BMW_Message(string message, MessageSeverity severity)
    {
        this._message = message;
        this._severity = severity;
    }
    
    protected override void CreateChildControls()
    {
        Controls.Clear();
        CreateControlHierarchy();
        ClearChildViewState();
    }
    protected virtual void CreateControlHierarchy()
    {
        string div_style = String.Empty;
        Color button_BackColors = Color.Transparent;
        if (_severity == MessageSeverity.Information)
        {
            div_style = "border: solid 3px gold; background-color: yellow; padding-left: 10px;";
            button_BackColors = Color.Yellow;
        }

        LiteralControl div_start = new LiteralControl("<div style='" + div_style + "'>");
        
        Button Clear_Me = new Button();
        Clear_Me.Text = " X ";
        Clear_Me.BackColor = button_BackColors;        
        Clear_Me.Style.Add("float", "left");
        Clear_Me.Style.Add("position", "relative");
        Clear_Me.Style.Add("left", "-19px");
        Clear_Me.Style.Add("top", "-10px");

        Button Clear_All = new Button();
        Clear_All.Text = "Clear All";
        Clear_All.BackColor = button_BackColors;
        Clear_All.Style.Add("position", "relative");
        Clear_All.Style.Add("left", "-19px");
        Clear_All.Style.Add("top", "-10px");

        Label Message = new Label();
        Message.Text = _message;

        LiteralControl div_end = new LiteralControl("</div>");

        this.Controls.Add(div_start);
        this.Controls.Add(Clear_Me);
        this.Controls.Add(Clear_All);
        this.Controls.Add(Message);
        this.Controls.Add(div_end);
    }
}
