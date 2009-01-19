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
using System.Drawing;
using System.ComponentModel;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Ch.Elca.Iiop.Idl;

namespace CUTS.Web.UI.Archive
{
  /**
   * @class TestBrowser
   */
  [ParseChildren (true), PersistChildren (false)]
  public class TestBrowser : CompositeControl, INamingContainer
  {
    public TestBrowser ()
    {

    }

    public CUTS.TestArchive TestArchive
    {
      get
      {
        return this.archive_;
      }

      set
      {
        this.archive_ = value;
      }
    }

    public void DataBind (CUTS.TestArchive archive)
    {
      this.archive_ = archive;
      this.EnsureChildControls ();
    }

    public override void DataBind ()
    {
      this.EnsureChildControls ();
    }

    protected override void CreateChildControls ()
    {
      base.CreateChildControls ();

      CUTS.TestArchiveBrowser browser = this.archive_.create_broswer (20);
      CUTS.TestProfile[] profiles;

      while (!browser.done)
      {
        // Get the next set of profiles.
        browser.get_next (out profiles);

        foreach (CUTS.TestProfile profile in profiles)
        {
          TestProfile test = new TestProfile (profile);
          this.Controls.Add (test);
        }
      }
    }

    private CUTS.TestArchive archive_;
  }
}
