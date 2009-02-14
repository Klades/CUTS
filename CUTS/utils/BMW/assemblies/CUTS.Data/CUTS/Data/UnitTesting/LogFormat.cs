// -*- C# -*-

//=============================================================================
/**
 * @file          LogFormat.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System;

namespace CUTS.Data.UnitTesting
{
  /**
   * @class LogFormat
   *
   * Simple abstraction for storing information about log formats. This
   * will store both the log format's id and its text value.
   */
  [Serializable]
  public class LogFormat
  {
    /**
     * Default constructor.
     */
    public LogFormat ()
    {

    }

    public LogFormat (int id, string text)
    {
      this.lfid_ = id;
      this.format_ = text;
    }

    /**
     * Setter/getter attribute for the log format's text
     */
    public string Text
    {
      get
      {
        return this.format_;
      }

      set
      {
        this.format_ = value;
      }
    }

    /**
     * Setter/getter attribute for the log format's id
     */
    public int ID
    {
      get
      {
        return this.lfid_;
      }

      set
      {
        this.lfid_ = value;
      }
    }

    /**
     * Test the equality of the log format. Two log formats are equal
     * if they have the same log formats.
     *
     * @retval        true          The objects are equal
     * @retval        false         The objects are not equal
     */
    public override bool Equals (object obj)
    {
      if (!(obj is LogFormat))
        return false;

      LogFormat format = (LogFormat)obj;
      return format.lfid_ == this.lfid_ ? true : false;
    }

    /**
     * Get the hashcode for the object.
     *
     * @return        Hashcode for the object.
     */
    public override int GetHashCode ()
    {
      return this.lfid_.GetHashCode ();
    }

    /// ID of the log format.
    private int lfid_;

    /// The text value of the log format.
    private string format_;
  }
}
