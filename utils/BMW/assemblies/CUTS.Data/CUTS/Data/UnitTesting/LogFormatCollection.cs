// -*- C# -*-

//=============================================================================
/**
 * @file          LogFormats.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System;
using System.Collections.Generic;

namespace CUTS.Data.UnitTesting
{
  /**
   * @class LogFormats
   *
   * Collection of log formats.
   */
  [Serializable]
  public class LogFormatCollection : List <LogFormat>
  {
    public LogFormatCollection ()
    {

    }

    public LogFormatCollection (LogFormat[] formats)
      : base (formats)
    {

    }

    /**
     * Remove a log format for the collection by its id.
     */
    public void Remove (int lfid)
    {
      int index = base.FindIndex (
        delegate (LogFormat format)
        {
          return format.ID == lfid;
        });

      if (index != -1)
        this.RemoveAt (index);
    }

    /**
     * Find a log format by its id.
     *
     * @return        Located log format, or null.
     */
    public LogFormat Find (int lfid)
    {
      int index = base.FindIndex (
        delegate (LogFormat format)
        {
          return format.ID == lfid;
        });

      return index != -1 ? base[index] : null;
    }
  }
}
