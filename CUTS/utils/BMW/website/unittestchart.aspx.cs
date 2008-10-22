using System;
using System.Data;
using System.Drawing;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using Actions;
using System.IO;
using System.Xml;
using System.Text;
using MySql.Data.MySqlClient;

using CUTS.Data;
using CUTS.Data.UnitTesting;
using CUTS.Drawing;

using WebChart;

namespace CUTS
{
  /**
   * @class Unit_Test_Chart
   */
  public partial class UnitTestChart : System.Web.UI.Page
  {
    private MySqlConnection conn_ =
      new MySqlConnection (ConfigurationManager.AppSettings["MySQL"]);

    private UnitTestEvaluator evaluator_;

    private CUTS.Master master_;

    public UnitTestChart ()
    {
      // Open the connection to the database.
      this.conn_.Open ();

      // Create an evaluator for this page.
      this.evaluator_ = new UnitTestEvaluator (new MySqlClientFactory (), Server.MapPath ("~/db"));
      this.evaluator_.ConnectionString = ConfigurationManager.AppSettings["MySQL"];
      this.evaluator_.Open ();
    }

    /**
     *
     */
    protected void Page_Load (object sender, EventArgs e)
    {
      // Get the master page for this page.
      this.master_ = (CUTS.Master)Master;

      if (this.IsPostBack)
        return;

      try
      {
        int id = Int32.Parse (Request.QueryString.Get ("utid"));
        int test_num = Int32.Parse (Request.QueryString.Get ("t"));

        UnitTestResult result =
          this.evaluator_.Evaluate (test_num, id, false);

        //this.generate_chart (eval, table, groups);
      }
      catch (Exception ex)
      {
        this.master_.show_error_message (ex.Message);
      }
    }

    /**
     *
     */
    private void generate_chart (string evaluation,
                                 DataTable dt,
                                 string [] group_names)
    {
      LineChart line_chart;
      float y_value;
      int i = 0, max_x = 0;

      ChartPointCollection points = new ChartPointCollection ();

      if (group_names.Length == 0)
      {
        // Write the data set for the single group.
        foreach (DataRow row in dt.Rows)
        {
          y_value = float.Parse (row["result"].ToString ());
          points.Add (new ChartPoint (i.ToString (), y_value));

          // Increment the x-value
          ++i;
        }

        // Insert the line chart into the chart control.
        line_chart = new LineChart (points);

        // Create a new color for the group.
        Color color = this.color_map_.Add ("unknown");
        line_chart.Fill.Color = color;
        line_chart.Line.Color = color;

        // Insert the line chart into the control.
        this.chart_.Charts.Add (line_chart);

        // We can hide the legend since we only have 1 line chart.
        this.chart_.HasChartLegend = false;

        max_x = i;
      }
      else
      {
        // Make sure we can see the legend for the chart since there is a
        // good chance more than one line graph will be produced.
        this.chart_.HasChartLegend = true;

        string current_group = String.Empty;

        foreach (DataRow grp_row in dt.Rows)
        {
          // First, construct the name of the group for this row in
          // the data table.
          ArrayList name_list = new ArrayList ();

          foreach (string name in group_names)
            name_list.Add (grp_row[name]);

          string grp_name = String.Join (".", (string[])name_list.ToArray (typeof (string)));

          if (grp_name != current_group)
          {
            if (current_group != String.Empty)
            {
              // End the current group's data by creating a new chart.
              line_chart = new LineChart (points);
              line_chart.Legend = current_group;

              // Create a new color for the group.
              Color color = this.color_map_.Add (current_group);
              line_chart.Fill.Color = color;
              line_chart.Line.Color = color;

              // Insert the chart into the control.
              this.chart_.Charts.Add (line_chart);

              // Reset the points.
              points.Clear ();
            }

            // Save the new group name.
            current_group = grp_name;

            // Reset the x-value.
            i = 0;
            max_x = Math.Max (i, max_x);
          }


          // Write the data for the group.
          y_value = float.Parse (grp_row["result"].ToString ());
          points.Add (new ChartPoint (i.ToString (), y_value));

          // Increment the x-value.
          ++i;
        }

        if (points.Count != 0)
        {
          // Make sure we add a line chart for the last group.
          line_chart = new LineChart (points);
          line_chart.Legend = current_group;

          // Create a new color for the group.
          Color color = this.color_map_.Add (current_group);
          line_chart.Fill.Color = color;
          line_chart.Line.Color = color;

          // Insert the line chart into the control.
          this.chart_.Charts.Add (line_chart);
          max_x = Math.Max (i, max_x);
        }

        this.chart_.XTicksInterval = (max_x / 20) + 1;
      }

      // Redraw the chart control.
      this.chart_.RedrawChart ();
    }

    private ColorMap color_map_ = new ColorMap ();
  }
}
