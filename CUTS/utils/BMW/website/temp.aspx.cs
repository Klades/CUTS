using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

namespace CUTS
{
    public partial class tempasdf : System.Web.UI.Page
    {
        private BMW_Master m;
        protected void Page_Load(object sender, EventArgs e)
        {
            m = (BMW_Master)Master;
            m.AddNewMessage("first error", MessageSeverity.Information);
        }

        protected void add(object sender, EventArgs e)
        {
            m.AddNewMessage("This is an info message",MessageSeverity.Information);
        }

        protected void add_err(object sender, EventArgs e)
        {
            m.AddNewMessage("This is an error message",MessageSeverity.Error);
        }

        protected void add_success(object sender, EventArgs e)
        {
            m.AddNewMessage("This is a success message", MessageSeverity.Success);
        }
    }
}