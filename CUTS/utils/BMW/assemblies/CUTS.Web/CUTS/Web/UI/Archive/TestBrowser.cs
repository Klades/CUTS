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
using System.IO;
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

    public TestBrowser (CUTS.TestArchive archive)
    {
      this.archive_ = archive;
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

    public string DownloadPath
    {
      get
      {
        return this.download_path_;
      }

      set
      {
        this.download_path_ = HttpContext.Current.Server.MapPath (value);
      }
    }

    public CUTS.UUID ActiveTest
    {
      get
      {
        return this.active_test_;
      }
    }

    public void ActivateTest (CUTS.UUID uuid)
    {
      this.active_test_ = uuid;
    }

    public void DownloadTest (CUTS.UUID uuid)
    {
      // Open the file to receieve the download on the server.
      string path = this.get_filename (uuid);
      BinaryWriter writer = new BinaryWriter (File.Open (path, FileMode.Create));

      // Request a new download from the server.
      CUTS.DownloadRequest request = new DownloadRequest ();
      request.uuid = uuid;
      request.chunk_size = 1024;

      CUTS.TestRetriever retriever = this.archive_.begin_download (request);
      bool success = false;

      try
      {
        byte[] data;

        // Download the data from the archive.
        while (retriever.recv_data (out data))
          writer.Write (data);

        // Set the result of the download.
        success = true;
      }
      finally
      {
        try
        {
          if (retriever != null)
            this.archive_.download_complete (retriever);
        }
        finally
        {
          writer.Close ();
        }
      }

      if (success)
      {
        // Save the UUID of the test.
        this.active_test_ = uuid;

        // Notify controls of the download complete.
        if (this.DownloadComplete != null)
          this.DownloadComplete (this, new EventArgs ());
      }
    }

    public void CloseTest (CUTS.UUID uuid)
    {
      // Open the file to receieve the download on the server.
      string path = this.get_filename (uuid);

      if (File.Exists (path))
        File.Delete (path);
    }

    void handle_profile_command (object sender, CommandEventArgs e)
    {
      CUTS.UUID uuid = (CUTS.UUID)e.CommandArgument;

      switch (e.CommandName)
      {
        case "open":
          this.DownloadTest (uuid);
          break;

        case "close":
          this.CloseTest (uuid);
          break;
      }
    }

    #region Custom Events
    public event EventHandler DownloadComplete;
    #endregion

    #region Overriden Methods
    public override void DataBind ()
    {
      // Clear the existing child controls.
      this.Controls.Clear ();
      this.profile_count_ = 0;

      // Make sure the required controls are created.
      this.EnsureChildControls ();

      if (this.archive_ == null)
        return;

      CUTS.TestArchiveBrowser browser = this.archive_.create_broswer (20);
      CUTS.TestProfile[] profiles;

      while (!browser.done)
      {
        // Get the next set of profiles.
        browser.get_next (out profiles);

        foreach (CUTS.TestProfile profile in profiles)
        {
          // Determine if this profile is open.
          bool is_open = CUTS.Data.UUID.IsEqual (profile.uuid, this.active_test_);

          // Create a new control for the profile.
          TestProfile test = new TestProfile (profile, is_open);
          this.Controls.Add (test);

          // Initialize the control's properties.
          test.Command += new CommandEventHandler (handle_profile_command);
        }

        // Update the number of profiles.
        this.profile_count_ += profiles.Length;
      }
    }

    protected override object SaveViewState ()
    {
      object[] state = new object[4];

      state[0] = base.SaveViewState ();
      state[1] = this.download_path_;
      state[2] = this.profile_count_;
      state[3] = this.active_test_;

      return state;
    }

    protected override void LoadViewState (object savedState)
    {
      object[] state = (object[])savedState;

      if (state[0] != null)
        base.LoadViewState (state[0]);

      if (state[1] != null)
        this.download_path_ = (string)state[1];

      if (state[2] != null)
        this.profile_count_ = (int)state[2];

      if (state[3] != null)
        this.active_test_ = (CUTS.UUID)state[3];
    }

    protected override void CreateChildControls ()
    {
      base.CreateChildControls ();

      for (int i = 0; i < this.profile_count_; ++i)
      {
        // Make a new test profile.
        TestProfile test = new TestProfile ();
        this.Controls.Add (test);

        test.Command += new CommandEventHandler (handle_profile_command);
      }
    }
    #endregion

    private string get_filename (CUTS.UUID uuid)
    {
      return String.Format ("{0}/{1}.cdb",
                            this.download_path_,
                            CUTS.Data.UUID.ToString (uuid));
    }

    #region Member Variables
    private CUTS.TestArchive archive_;

    private string download_path_;

    private int profile_count_ = 0;

    private CUTS.UUID active_test_;
    #endregion
  }
}
