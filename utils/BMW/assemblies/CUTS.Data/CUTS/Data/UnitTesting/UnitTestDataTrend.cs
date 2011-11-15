// $Id$

//=============================================================================
/**
 * @file            UnitTestDataTrend.cs
 *
 * $Id$
 *
 * @author          James H. Hill
 */
//=============================================================================

using System;
using System.Collections;
using System.Collections.Generic;

namespace CUTS.Data.UnitTesting
{
  public class DataTrend : List <object>
  {
    public DataTrend ()
    {

    }
  }

  public class GroupDataTrend : Dictionary <string, DataTrend>
  {
    public GroupDataTrend ()
    {

    }
  }

  public class UnitTestDataTrend
  {
    public UnitTestDataTrend ()
    {

    }

    public DataTrend Data
    {
      get
      {
        return this.data_;
      }
    }

    public GroupDataTrend GroupData
    {
      get
      {
        return this.groups_;
      }
    }

    private DataTrend data_ = new DataTrend ();

    private GroupDataTrend groups_ = new GroupDataTrend ();
  }
}
