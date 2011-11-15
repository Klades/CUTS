// -*- C# -*-

//=============================================================================
/**
 * @file        ConsoleMessage.cs
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

using System;

namespace CUTS.Web.UI
{
  [Serializable]
  public class ConsoleMessage
  {
    public string Message
    {
      get
      {
        return this.message_;
      }

      set
      {
        this.message_ = value;
      }
    }

    public MessageSeverity Severity
    {
      get
      {
        return this.severity_;
      }

      set
      {
        this.severity_ = value;
      }
    }

    private MessageSeverity severity_;

    private string message_;
  }
}
