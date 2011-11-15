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

    public static bool IsEqual (CUTS.UUID u1, CUTS.UUID u2)
    {
      return u1.data1 == u2.data1 &&
             u1.data2 == u2.data2 &&
             u1.data3 == u2.data3 &&
             u1.data4[0] == u2.data4[0] &&
             u1.data4[1] == u2.data4[1] &&
             u1.data4[2] == u2.data4[2] &&
             u1.data4[3] == u2.data4[3] &&
             u1.data4[4] == u2.data4[4] &&
             u1.data4[5] == u2.data4[5] &&
             u1.data4[6] == u2.data4[6] &&
             u1.data4[7] == u2.data4[7];
    }

    public static bool IsNotEqual (CUTS.UUID u1, CUTS.UUID u2)
    {
      return !IsEqual (u1, u2);
    }
  }
}
