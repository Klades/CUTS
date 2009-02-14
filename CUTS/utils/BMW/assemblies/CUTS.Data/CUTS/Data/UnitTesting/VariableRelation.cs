// -*- C# -*-

//=============================================================================
/**
 * @file          Relation.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

namespace CUTS.Data.UnitTesting
{
  public class VariableRelation
  {
    public VariableRelation ()
    {

    }

    public LogFormatVariable Left
    {
      get
      {
        return this.left_;
      }
    }

    public LogFormatVariable Right
    {
      get
      {
        return this.right_;
      }
    }

    private LogFormatVariable left_ = new LogFormatVariable ();

    private LogFormatVariable right_ = new LogFormatVariable ();
  }
}
