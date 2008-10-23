// -*- C# -*-

//=============================================================================
/**
 * @file          UnitTestGroupResults.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System;
using System.Collections.Generic;
using System.Runtime.Serialization;

namespace CUTS.Data.UnitTesting
{
  /**
   * @class GroupResults
   *
   */
  [Serializable]
  public class GroupResults : Dictionary<string, object>
  {
    /**
     * Default constructor.
     */
    public GroupResults ()
    {

    }

    protected GroupResults (SerializationInfo info, StreamingContext context)
      : base (info, context)
    {
    }
  }
}

