// -*- C# -*-

//=============================================================================
/**
 * @file        PerformanceTimes.cs
 *
 * Defines the object for storing performance times.
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

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
  //===========================================================================
  /**
   * @class PerformanceTimes
   *
   * Data abstraction for storing performance metrucs.
   */
  //===========================================================================

  public class PerformanceTimes
  {
    /// Default constructor.
    public PerformanceTimes()
    {
      this.count_ = 0;
      this.avg_ = this.max_ = this.min_ = 0.0;
    }

    public PerformanceTimes(long min, double avg, long max)
    {
      this.min_ = min;
      this.avg_ = avg;
      this.max_ = max;
    }

    public long Count
    {
      set { this.count_ = value; }
      get { return this.count_; }
    }

    public double Minimum
    {
      set { this.min_ = value; }
      get { return this.min_; }
    }

    public double Average
    {
      set { this.avg_ = value; }
      get { return this.avg_; }
    }

    public double Maximum
    {
      set { this.max_ = value; }
      get { return this.max_; }
    }

    public void Set(long count, double min, double avg, double max)
    {
      this.count_ = count;

      this.min_ = min;
      this.avg_ = avg;
      this.max_ = max;
    }

    private double min_;

    private double avg_;

    private double max_;

    private long count_;
  }
}
