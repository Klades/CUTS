// -*- C# -*-

//=============================================================================
/**
 * @file        Console.cs
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

using System;

namespace CUTS.Data
{
  /**
   * @class UUID
   *
   * Helper class for managing UUID
   */
  public class UUID
  {
    public static string ToString (CUTS.UUID uuid)
    {
      return String.Format ("{0:X8}-{1:X4}-{2:X4}-{3:X2}{4:X2}-{5:X2}{6:X2}{7:X2}{8:X2}{9:X2}{10:X2}",
                            uuid.data1,
                            uuid.data2,
                            uuid.data3,
                            uuid.data4[0],
                            uuid.data4[1],
                            uuid.data4[2],
                            uuid.data4[3],
                            uuid.data4[4],
                            uuid.data4[5],
                            uuid.data4[6],
                            uuid.data4[7]);
    }

    public static CUTS.UUID FromString (string uuidstr)
    {
      return new CUTS.UUID ();
    }
  }
}
