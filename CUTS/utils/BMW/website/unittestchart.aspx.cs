// $Id$

using System;
using System.Data;
using System.Drawing;
using System.Configuration;
using System.Collections;
using System.Collections.Generic;
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

        UnitTestDataTrend trend = this.evaluator_.GetDataTrend ("", id);

        this.generate_chart (trend);
      }
      catch (Exception ex)
      {
        this.master_.Console.Add (ex);
      }
    }

    /**
     *
     */
    private void generate_chart (UnitTestDataTrend trend)
    {
      LineChart line_chart;
      float y_value;
      int i = 0, max_x = 0;

      ChartPointCollection points;

      if (trend.GroupData.Count == 0)
      {
        points = new ChartPointCollection ();

        // Write the data set for the single group.
        foreach (object v in trend.Data)
        {
          y_value = float.Parse (v.ToString ());
          points.Add (new ChartPoint (i.ToString (), y_value));
        }

        // Insert the line chart into the chart control.
        line_chart = new LineChart (points);

        // Create a new color for the group.
        Color color = this.color_map_.Add ("unknown", Color.Red);
        line_chart.Fill.Color = Color.Red;
        line_chart.Line.Color = Color.Red;

        // Insert the line chart into the control.
        this.chart_.Charts.Add (line_chart);

        // We can hide the legend since we only have 1 line chart.
        this.chart_.HasChartLegend = false;
      }
      else
      {
        // Make sure we can see the legend for the chart since there is a
        // good chance more than one line graph will be produced.
        this.chart_.HasChartLegend = true;

        foreach (KeyValuePair <string, DataTrend> entry in trend.GroupData)
        {
          // Reset the x-axis counter.
          i = 0;
          points = new ChartPointCollection ();

          foreach (object v in entry.Value)
          {
            y_value = float.Parse (v.ToString ());
            points.Add (new ChartPoint (i.ToString (), y_value));

            ++i;
          }

          max_x = Math.Max (i, max_x);

          // End the current group's data by creating a new chart.
          line_chart = new LineChart (points);
          line_chart.Legend = entry.Key;

          // Create a new color for the group.
          Color color = this.color_map_.Add (entry.Key);
          line_chart.Fill.Color = color;
          line_chart.Line.Color = color;

          // Insert the chart into the control.
          this.chart_.Charts.Add (line_chart);
        }

        this.chart_.XTicksInterval = (max_x / 20) + 1;
      }

      // Redraw the chart control.
      this.chart_.RedrawChart ();
    }

    private ColorMap color_map_ = new ColorMap ();
  }
}
