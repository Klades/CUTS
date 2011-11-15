// -*- C# -*-

//=============================================================================
/**
 * @file        ConsoleMessages.cs
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

using System;
using System.Collections.Generic;

namespace CUTS.Web.UI
{
  [Serializable]
  public class ConsoleMessages : List<ConsoleMessage>
  {
    public ConsoleMessages ()
    {

    }

    public void Add (MessageSeverity severity, string message)
    {
      ConsoleMessage msg = new ConsoleMessage ();
      msg.Severity = severity;
      msg.Message = message;

      this.Add (msg);
    }
  }
}
