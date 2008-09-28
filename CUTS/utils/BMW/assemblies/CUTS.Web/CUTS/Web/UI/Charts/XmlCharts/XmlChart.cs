// -*- C# -*-

//=============================================================================
/**
 * @file          XmlChart.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System;
using System.Collections;
using System.Data;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace CUTS.Web.UI.Charts.XmlCharts
{
  /**
   * @class XmlChart
   *
   * Custom control for inserting an XMLChart on a page. This class
   * with generate the XML file that is needed by XMLChart, and embedded
   * the charting object on the page.
   *
   * For more information on XMLCharts, please see the following URL:
   *
   *   http://www.maani.us/xml_charts
   */
  public class XmlChart : CompositeControl, INamingContainer
  {
    public XmlChart ()
    {
    }
  }
}
