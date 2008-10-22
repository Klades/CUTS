// -*- C# -*-

using System;
using System.Collections.Generic;

namespace CUTS.Web.UI.UnitTesting
{
  /**
   * @class UnitTests
   *
   * A collection of UnitTest objects.
   */
  [Serializable]
  public class UnitTests : List <UnitTest>
  {
    /**
     * Default constructor.
     */
    public UnitTests ()
    {

    }

    /**
     * Initializing constructor.
     */
    public UnitTests (UnitTest[] tests) : base (tests)
    {

    }
  }
}
