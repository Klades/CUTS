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
using Actions;
using System.IO;
using System.Xml;
using System.Text;
using MySql.Data.MySqlClient;

namespace CUTS
{
  public partial class Unit_Test_Chart : System.Web.UI.Page
  {
    private MySqlConnection conn_ =
      new MySqlConnection (ConfigurationManager.AppSettings["MySQL"]);

    private CUTS.Data.UnitTestEvaluator evaluator_;

    protected void Page_Load (object sender, EventArgs e)
    {
      this.evaluator_ =
        new CUTS.Data.UnitTestEvaluator (this.conn_, new CUTS.Data.MySqlDataAdapterFactory ());

      if (this.IsPostBack)
        return;

      string id_string = Request.QueryString.Get ("utid");
      int id = Int32.Parse (id_string);
      string test_num_str = Request.QueryString.Get ("t");
      int test_num = Int32.Parse (test_num_str);

      string eval;

      DataTable table =
        this.evaluator_.evaluate (test_num, id, false, out eval);

      this.Chart (eval, table);

      string ChartObject = @"<object classid='clsid:D27CDB6E-AE6D-11cf-96B8-444553540000' codebase='http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0'" +
          @" width='900' height='500' id='charts'>" +
          @"<param name='movie' value='charts/charts.swf?library_path=charts/charts_library&xml_source=xml/auto_generated.xml' />" +
          @"<param name='quality' value='high' />" +
          @"<param name='bgcolor' value='#666666' />" +
          @"<param name='allowScriptAccess' value='sameDomain' />" +
          @"<embed src='charts/charts.swf?library_path=charts/charts_library&xml_source=xml/auto_generated.xml' " +
          @"quality='high' bgcolor='#666666' width='900' height='500' name='charts' allowscriptaccess='sameDomain' " +
          @"swliveconnect='true' type='application/x-shockwave-flash' pluginspage='http://www.macromedia.com/go/getflashplayer'>" +
          @"</embed></object>";

      LiteralControl chart = new LiteralControl (ChartObject);
      placeholder.Controls.Add (chart);
    }

    private void Chart (string evaluation, DataTable dt)
    {
      string xmlPath = Server.MapPath ("~/xml/auto_generated.xml");
      FileInfo XMLExists = new FileInfo (xmlPath);

      if (XMLExists.Exists)
        File.Delete (xmlPath);

      XmlTextWriter writer = new XmlTextWriter (xmlPath, Encoding.UTF8);

      writer.WriteStartDocument ();
      writer.WriteStartElement ("chart"); // <chart>
      writer.WriteStartElement ("chart_data"); // <chart_data>

      writer.WriteStartElement ("row");   // <row>
      writer.WriteRaw ("<null/>");        // <null/>
      for (int i = 0; i < dt.Rows.Count; i++)
        writer.WriteElementString ("string", i.ToString ());
      writer.WriteEndElement ();           // </row>

      writer.WriteStartElement ("row");   // <row>
      writer.WriteElementString ("string", evaluation);

      foreach (DataRow row in dt.Rows)
        writer.WriteElementString ("number", row["result"].ToString ());

      writer.WriteEndElement ();


      writer.WriteEndElement ();  // </chart_data>

      /* If you would like to add/set other charting attributes
       *   using the charting class below, do that here!!
       */
      ChartingAPI api = new ChartingAPI (writer);


      writer.WriteEndElement ();  // </chart>
      writer.WriteEndDocument ();
      writer.Flush ();
      writer.Close ();
    }

  }
}

public enum line_types { solid, dotted, dashed };
public enum chart_types { line, column, pie, donut, bar, area, scatter };
public enum data_point_label_positions { center, above, below, left, right, cursor, hide };
public enum legend_bullet_types { square, circle, line };

public class ChartingAPI
{
  private XmlTextWriter writer;

  /**
   * Constructor.
   *
   * @param[in]   writer    An XmlTextWriter that is initialized
   *                          and ready to be written to.
   */
  public ChartingAPI (XmlTextWriter writer)
  {
    this.writer = writer;
  }

  /**
   * Used to set the border properties for the entire charting rectangle.
   *
   * @param[in]    pixel_width    The width in pixels of the desired border.
   * @param[in]    hex_color      The hexadecimal color value to make the border.
   */
  public void set_border (int pixel_width, string hex_color)
  {
    writer.WriteStartElement ("chart_border");
    writer.WriteAttributeString ("top_thickness", pixel_width.ToString ());
    writer.WriteAttributeString ("bottom_thickness", pixel_width.ToString ());
    writer.WriteAttributeString ("left_thickness", pixel_width.ToString ());
    writer.WriteAttributeString ("right_thickness", pixel_width.ToString ());
    writer.WriteAttributeString ("color", hex_color);
    writer.WriteEndElement ();
  }

  /**
   * Used to configure the horizontal grid lines.
   *
   * @param[in]  thickness    The thickness in pixels to make the grid lines.
   * @param[in]  hex_color    The hexadecimal color to make the grid lines.
   * @param[in]  alpha        The alpha value to filter the color with. Should be
   *                            between 0 and 100.
   * @param[in]  type         A value from the line_types enum. Solid, dashed, dotted.
   */
  public void set_grid_horizontal (int thickness, string hex_color, int alpha, line_types type)
  {
    writer.WriteStartElement ("chart_grid_h");
    writer.WriteAttributeString ("thickness", thickness.ToString ());
    writer.WriteAttributeString ("color", hex_color);
    writer.WriteAttributeString ("alpha", alpha.ToString ());
    writer.WriteAttributeString ("type", type.ToString ());
    writer.WriteEndElement ();
  }

  /**
   * Used to configure the vertical grid lines.
   *
   * @param[in]  thickness    The thickness in pixels to make the grid lines.
   * @param[in]  hex_color    The hexadecimal color to make the grid lines.
   * @param[in]  alpha        The alpha value to filter the color with. Should be
   *                            between 0 and 100.
   * @param[in]  type         A value from the line_types enum. Solid, dashed, dotted.
   */
  public void set_grid_vertical (int thickness, string hex_color, int alpha, line_types type)
  {
    writer.WriteStartElement ("chart_grid_v");
    writer.WriteAttributeString ("thickness", thickness.ToString ());
    writer.WriteAttributeString ("color", hex_color);
    writer.WriteAttributeString ("alpha", alpha.ToString ());
    writer.WriteAttributeString ("type", type.ToString ());
    writer.WriteEndElement ();
  }

  /**
   * Used to configure the chart labels (the individual data point labels).
   *
   * @param[in]   prefix    Any prefix that should be universally added to the
   *                          data point labels. Ex: "$"
   * @param[in]   suffix    Any suffix that should be universally added to the
   *                          data point labels. Ex: " parts per million"
   * @param[in]   position  The appropriate label_position enum. Default is hide.
   */
  public void set_chart_labels (string prefix, string suffix, data_point_label_positions position)
  {
    writer.WriteStartElement ("chart_label");
    writer.WriteAttributeString ("prefix", prefix);
    writer.WriteAttributeString ("suffix", suffix);
    writer.WriteAttributeString ("position", position.ToString ());
    writer.WriteEndElement ();
  }

  /**
   * Used to set values for the rectabgle that encloses the charting area.
   *
   * @param[in]   width   The desired width in pixels.
   * @param[in]   height  The desired height in pixels.
   * @param[in]   positive_hex_color    The hexadecimal color desired for the
   *                                      above-zero-line part of the chart.
   * @param[in]   positive_alpha        The alpha overlay desired for the
   *                                      above-zero-line part of the chart.
   *                                      Valid between 0 and 100.
   * @param[in]   negative_hex_color    The hexadecimal color desired for the
   *                                      below-zero-line part of the chart.
   * @param[in]   negative_alpha        The alpha overlay desired for the
   *                                      below-zero-line part of the chart.
   *                                      Valid between 0 and 100.
   */
  public void set_chart_rect (string width, string height, string positive_hex_color,
    string positive_alpha, string negative_hex_color, string negative_alpha)
  {
    writer.WriteStartElement ("chart_rect");
    writer.WriteAttributeString ("width", width);
    writer.WriteAttributeString ("height", height);
    writer.WriteAttributeString ("positive_color", positive_hex_color);
    writer.WriteAttributeString ("positive_alpha", positive_alpha);
    writer.WriteAttributeString ("negative_color", negative_hex_color);
    writer.WriteAttributeString ("negative_aplha", negative_alpha);
    writer.WriteEndElement ();
  }

  /**
   * Used to explicetly set the chart type.
   *
   * @param[in]  type   The chart type desired (bar, line, etc).
   */
  public void set_chart_type (chart_types type)
  {
    writer.WriteStartElement ("chart_type");
    writer.WriteString (type.ToString ());
    writer.WriteEndElement ();
  }

  /**
   * Used to configure the x axis.
   *
   * @param[in]   skip_amount    If you have a very full chart, the column
   *                               labels might overlap. In this case, use the
   *                               skip amount to skip some labes, and only
   *                               show every fifth (or second, etc) column label.
   * @param[in]   font_size      Explictly set the font size.
   * @param[in]   font_color     The hexadecimal font color desired.
   * @param[in]   font_alpha     The alpha overlay desired for the font. Valid
   *                               values are between 0 and 100.
   * @param[in]   font_orientation_angle  The angle to slant the font text to.
   *                                        This can become useful when you have
   *                                        many labels that do not fit well side
   *                                        to side, so need to be slanted to
   *                                        accomodate more.
   */
  public void set_x_axis (string skip_amount, string font_size, string font_color,
    string font_alpha, string font_orientation_angle)
  {
    writer.WriteStartElement ("axis_category");
    writer.WriteAttributeString ("skip", skip_amount);
    writer.WriteAttributeString ("size", font_size);
    writer.WriteAttributeString ("color", font_color);
    writer.WriteAttributeString ("alpha", font_alpha);
    writer.WriteAttributeString ("orientation", font_orientation_angle);
    writer.WriteEndElement ();
  }

  /**
   * Used to configure the y axis.
   *
   * @param[in]   min                     The minimum value to display on the y axis.
   * @param[in]   max                     The maximum value to display on the y axis.
   * @param[in]   steps                   If you have a very full chart, the value
   *                                        labels might overlap. In this case, use the
   *                                        step amount to skip some values, and only
   *                                        show every fifth (or second, etc) value label.
   * @param[in]   prefix                  Any prefix that should be applied to all y values.
   *                                        Ex: "$".
   * @param[in]   suffix                  Any suffix that should be applied to all y values.
   *                                        Ex. " packets".
   * @param[in]   font_size               Explictly set the font size.
   * @param[in]   font_color              The hexadecimal font color desired.
   * @param[in]   font_alpha              The alpha overlay desired for the font. Valid
   *                                        values are between 0 and 100.
   * @param[in]   font_orientation_angle  The angle to slant the font text to.
   *                                        This is more of a visual enhancer
   *                                        in this case, and not a critical funtion.
   *                                        Default is 0.
   */
  public void set_y_axis (string min, string max, string steps, string prefix,
    string suffix, string font_size, string font_color, string font_orientation_angle)
  {
    writer.WriteStartElement ("axis_value");
    writer.WriteAttributeString ("min", min);
    writer.WriteAttributeString ("max", max);
    writer.WriteAttributeString ("steps", steps);
    writer.WriteAttributeString ("prefix", prefix);
    writer.WriteAttributeString ("suffix", suffix);
    writer.WriteAttributeString ("size", font_size);
    writer.WriteAttributeString ("color", font_color);
    writer.WriteAttributeString ("orientation", font_orientation_angle);
    writer.WriteEndElement ();
  }

  /**
   * Used to configure the legend box.
   *
   * @param[in]   width           The desired width of the legend box.
   * @param[in]   height          The desired height of the legend box.
   * @param[in]   padding         The desired padding between the text in the
   *                                legend box and the box's border.
   * @param[in]   bullet_type     The shape of the bullet items in the legend.
   * @param[in]   font_size       The desired font size.
   * @param[in]   font_color      The hexadecimal color for the font.
   * @param[in]   font_alpha      The alpha filter to be applied to the font.
   *                                Valid values are between 0 and 100.
   * @param[in]   fill_color      The hexadecimal value for the legend box
   *                                background color.
   * @param[in]   fill_alpha      The alpha filter to be applied to the
   *                                legend box background.
   */
  public void set_legend (string width, string height, string padding, legend_bullet_types bullet_type, string font_size,
                          string font_color, string font_alpha, string fill_color, string fill_alpha)
  {
    writer.WriteStartElement ("legend");
    writer.WriteAttributeString ("width", width);
    writer.WriteAttributeString ("height", height);
    writer.WriteAttributeString ("margin", padding);
    writer.WriteAttributeString ("bullet", bullet_type.ToString ());
    writer.WriteAttributeString ("size", font_size);
    writer.WriteAttributeString ("color", font_color);
    writer.WriteAttributeString ("alpha", font_alpha);
    writer.WriteAttributeString ("fill_color", fill_color);
    writer.WriteAttributeString ("fill_alpha", fill_alpha);
    writer.WriteEndElement ();
  }

}