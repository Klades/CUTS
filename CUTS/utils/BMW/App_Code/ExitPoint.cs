using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

namespace CUTS
{
  public class ExitPoint
  {
    public ExitPoint()
    {

    }

    public string Name
    {
      set { this.name_ = value; }
      get { return this.name_; }
    }

    public CUTS.PerformanceTimes Performance
    {
      get { return this.perf_time_; }
      set { this.perf_time_ = value; }
    }

    public CUTS.PerformanceTimes BaselinePerformance
    {
      get { return this.baseline_time_; }
      set { this.baseline_time_ = value; }
    }

    public CUTS.PerformanceTimes PercentageError()
    {
      if (this.baseline_time_ == null)
        return null;

      CUTS.PerformanceTimes perf = new PerformanceTimes();
      perf.Maximum =
        this.PercentageError_i(this.perf_time_.Maximum, this.baseline_time_.Maximum);

      perf.Minimum =
        this.PercentageError_i(this.perf_time_.Minimum, this.baseline_time_.Minimum);

      perf.Average =
        this.PercentageError_i(this.perf_time_.Average, this.baseline_time_.Average);

      return perf;
    }

    private double PercentageError_i(double measured, double actual)
    {
      return ((measured - actual) / actual) * 100.0;
    }

    /// Name of the exit point.
    private string name_;

    /// Performance times for the exit point.
    CUTS.PerformanceTimes perf_time_ = new CUTS.PerformanceTimes();

    CUTS.PerformanceTimes baseline_time_;
  }
}
