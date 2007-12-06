// -*- C# -*-

//=============================================================================
/**
 * @file        PortPerformance.ascx.cs
 *
 * User control for displaying performance metrics for input ports
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

namespace CUTS
{
  //===========================================================================
  /**
   * @class PortPerformance
   *
   * Partial class for the PortPerformance user control.
   */
  //===========================================================================

  public partial class PortPerformance : System.Web.UI.UserControl
  {
    protected void Page_Load(object sender, EventArgs e)
    {
    }

    public string PortName
    {
      set { this.portname_ = value; }
      get { return this.portname_; }
    }

    public long PortID
    {
      set { this.portid_ = value; }
      get { return this.portid_; }
    }

    public CUTS.PerformanceTimes QueuingTime
    {
      get { return this.queuing_time_; }
      set { this.queuing_time_ = value; }
    }

    public CUTS.PerformanceTimes QueuingTimeBaseline
    {
      get { return this.queuing_time_baseline_; }
      set { this.queuing_time_baseline_ = value; }
    }

    public CUTS.PerformanceTimes ServiceTime
    {
      get { return this.service_time_; }
      set { this.service_time_ = value; }
    }

    public CUTS.PerformanceTimes ServiceTimeBaseline
    {
      get { return this.service_time_baseline_; }
      set { this.service_time_baseline_ = value; }
    }

    public void InsertExitPoint (CUTS.ExitPoint ep)
    {
      if (!this.exittime_row_.Visible)
        this.exittime_row_.Visible = true;

      // Create a new row for the exit point.
      this.exittimes_.Add(ep);
      TableRow row = new TableRow();

      CUTS.PerformanceTimes percentage_error = ep.PercentageError();

      // Create the cell that contains the name.
      TableCell cell = new TableCell();
      cell.Text = ep.Name + ":";
      cell.CssClass = "performance-name";
      row.Cells.Add(cell);

      // Create cells for each of the performance metrics.
      cell = new TableCell();
      cell.Text = ep.Performance.Count.ToString();
      cell.CssClass = "performance-data-count";
      row.Cells.Add(cell);

      // Create new cell to contain the min performance metric.
      cell = new TableCell();
      cell.CssClass = "performance-data";
      cell.Text = ep.Performance.Minimum.ToString();

      if (percentage_error != null)
        cell.Text += " [" + Math.Round(percentage_error.Minimum, 2) + "%]";

      row.Cells.Add(cell);

      // Create new cell to contain the average performance metric.
      cell = new TableCell();
      cell.CssClass = "performance-data";
      cell.Text = Math.Round(ep.Performance.Average, 2).ToString();

      if (percentage_error != null)
        cell.Text += " [" + Math.Round(percentage_error.Average, 2) + "%]";

      row.Cells.Add(cell);

      // Create new cell to contain the maximum performance metric.
      cell = new TableCell();
      cell.CssClass = "performance-data";
      cell.Text = ep.Performance.Maximum.ToString();

      if (percentage_error != null)
        cell.Text += " [" + Math.Round(percentage_error.Maximum, 2) + "%]";

      row.Cells.Add(cell);

      // Add the new row to the table.
      this.portperf_table_.Rows.Add(row);
    }

    /// Number of events on this port.
    protected long event_count_;

    /// The name of the port.
    protected string portname_;

    /// The queuing time for the port.
    protected CUTS.PerformanceTimes queuing_time_;

    protected CUTS.PerformanceTimes queuing_time_baseline_;

    /// The process time for the port.
    protected CUTS.PerformanceTimes service_time_;

    protected CUTS.PerformanceTimes service_time_baseline_;

    /// Unique id for the port.
    private long portid_;

    /// Collection of exit times for the component
    private ArrayList exittimes_ = new ArrayList();
  }
}
