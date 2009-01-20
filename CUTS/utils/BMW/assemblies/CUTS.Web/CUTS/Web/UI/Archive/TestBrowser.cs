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

    public void DownloadTest (CUTS.TestProfile profile)
    {
      // Open the file to receieve the download on the server.
      string path = String.Format ("{0}/{1}.cdb",
                                   this.download_path_,
                                   CUTS.Data.UUID.ToString (profile.uuid));

      BinaryWriter writer = new BinaryWriter (File.Open (path, FileMode.OpenOrCreate));

      // Request a new download from the server.
      CUTS.DownloadRequest request = new DownloadRequest ();
      request.uuid = profile.uuid;
      request.chunk_size = 1024;

      CUTS.TestRetriever retriever = this.archive_.begin_download (request);

      try
      {
        // Download the data from the archive.
        byte[] data;

        while (retriever.recv_data (out data))
          writer.Write (data);
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
    }

    public void DataBind (CUTS.TestArchive archive)
    {
      this.archive_ = archive;
      this.DataBind ();
    }

    void handle_download_test (object sender, EventArgs e)
    {
      TestProfile test = (TestProfile)sender;
      this.DownloadTest (test.Profile);
    }

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
          TestProfile test = new TestProfile (profile);
          this.Controls.Add (test);

          test.DownloadTest += new EventHandler (handle_download_test);
        }

        // Update the number of profiles.
        this.profile_count_ += profiles.Length;
      }
    }

    protected override object SaveViewState ()
    {
      object[] state = new object[3];
      state[0] = base.SaveViewState ();
      state[1] = this.download_path_;
      state[2] = this.profile_count_;

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
    }

    protected override void CreateChildControls ()
    {
      base.CreateChildControls ();

      for (int i = 0; i < this.profile_count_; ++i)
      {
        // Make a new test profile.
        TestProfile test = new TestProfile ();
        this.Controls.Add (test);

        test.DownloadTest += new EventHandler (handle_download_test);
      }
    }
    #endregion

    private CUTS.TestArchive archive_;

    private string download_path_;

    private int profile_count_ = 0;
  }
}
