// -*- C# -*-

//=============================================================================
/**
 * @file          UnitTestPackages.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System;
using System.Collections.Generic;

namespace CUTS.Web.UI.UnitTest
{
  /**
   * @class UnitTestPackages
   */
  public class UnitTestPackages : List<UnitTestPackage>
  {
    public UnitTestPackages ()
    {

    }

    public UnitTestPackages (UnitTestPackage[] packages)
      : base (packages)
    {

    }
  }
}
