// -*- C# -*-

//=============================================================================
/**
 * @file        Database.cs
 *
 * $Id$
 *
 * @author      James H. Hill <j dot hill at vanderbilt dot edu>
 */
//=============================================================================

using System;
using System.Data;
using System.Data.SQLite;
using System.Security.Cryptography;

namespace CUTS.BMW
{
  public class Database
  {
    public Database ()
    {

    }

    public void Open (string database)
    {
      string connstr = String.Format ("Data Source={0}", database);
      this.conn_.ConnectionString = connstr;
      this.conn_.Open ();
    }

    ~Database ()
    {
      this.Close ();
    }

    public void Close ()
    {
      if (this.conn_.State == ConnectionState.Open)
        this.conn_.Close ();
    }

    public bool AuthenticateUser (string username, string password)
    {
      return true;
    }

    private SQLiteConnection conn_ = new SQLiteConnection ();
  }
}
