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
using System.Text;

namespace CUTS.BMW
{
  /**
   * @class NewUserProfile
   *
   * Profile for the new user. This must be completed in order to create
   * a new user in the database.
   */
  public class NewUserProfile
  {
    public string Username
    {
      set
      {
        this.username_ = value;
      }

      get
      {
        return this.username_;
      }
    }

    public string Password
    {
      get
      {
        return this.password_;
      }

      set
      {
        this.password_ = value;
      }
    }

    public string EmailAddress
    {
      get
      {
        return this.email_;
      }

      set
      {
        this.email_ = value;
      }
    }

    /**
     * Username of the new user
     */
    private string username_;

    /**
     * Password for the new user
     */
    private string password_;

    /**
     * Email address of the new user
     */
    private string email_;
  }

  /**
   * @class Database
   *
   * Helper class for managing/maintaining the BMW's database.
   */
  public class Database
  {
    /**
     * Default constructor
     */
    public Database ()
    {

    }

    /**
     * Open a connection to the databse.
     *
     * @param[in]         filename          Location of the database.
     */
    public void Open (string database)
    {
      this.Open (database, false);
    }

    /**
     * Open a connection to the databse.
     *
     * @param[in]         filename          Location of the database.
     */
    public void Open (string database, bool rdonly)
    {
      string connstr =
        String.Format ("Data Source={0}; Read Only={1}", database, rdonly);

      this.conn_.ConnectionString = connstr;
      this.conn_.Open ();
    }

    /**
     * Destructor
     */
    ~Database ()
    {
      if (this.conn_.State == ConnectionState.Open)
        this.conn_.Close ();
    }

    public ConnectionState State
    {
      get
      {
        return this.conn_.State;
      }
    }

    /**
     * Close the connection to the database.
     */
    public void Close ()
    {
      this.conn_.Close ();
    }

    /**
     * Autheticate username/password with the database.
     */
    public bool AuthenticateUser (string username, string password)
    {
      // Create a new SQL command.
      SQLiteCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT password FROM users WHERE username=@username";

      // Initialize the parameters.
      SQLiteParameter param = command.CreateParameter ();
      param.ParameterName = "@username";
      param.DbType = DbType.String;
      param.Value = username;

      command.Parameters.Add (param);

      // Execute the command.
      object obj = command.ExecuteScalar ();

      if (obj == null)
        return false;

      // Compute the hash for the username/password.
      UTF8Encoding encoding = new UTF8Encoding ();
      MD5CryptoServiceProvider crypt = new MD5CryptoServiceProvider ();
      Byte[] hash = crypt.ComputeHash (encoding.GetBytes (username + password));

      // Compare the compute hash with the selected password.
      string temp = (string)obj;
      return temp.Equals (encoding.GetString (hash));
    }

    /**
     * Create a new user profile in the database.
     *
     * @param[in]         username          Username for new user
     * @param[in]         password          Password for the new user
     */
    public void CreateNewUser (NewUserProfile profile)
    {
      // Compute the hash for the username/password.
      UTF8Encoding encoding = new UTF8Encoding ();
      MD5CryptoServiceProvider crypt = new MD5CryptoServiceProvider ();
      Byte[] hash =
        crypt.ComputeHash (encoding.GetBytes (profile.Username + profile.Password));

      // Create the SQL command.
      SQLiteCommand command = this.conn_.CreateCommand ();
      command.CommandText =
        "INSERT INTO users (username, password, email) VALUES (@username, @password, @email)";

      // Prepare the SQL parameters.
      SQLiteParameter p1 = command.CreateParameter ();
      p1.ParameterName = "@username";
      p1.DbType = DbType.String;
      p1.Value = profile.Username;
      command.Parameters.Add (p1);

      SQLiteParameter p2 = command.CreateParameter ();
      p2.ParameterName = "@password";
      p2.DbType = DbType.String;
      p2.Value = encoding.GetString (hash);
      command.Parameters.Add (p2);

      SQLiteParameter p3 = command.CreateParameter ();
      p3.ParameterName = "@email";
      p3.DbType = DbType.String;
      p3.Value = profile.EmailAddress;
      command.Parameters.Add (p3);

      // Execute the SQL query.
      command.ExecuteNonQuery ();
    }

    /**
     * Connection to the database.
     */
    private SQLiteConnection conn_ = new SQLiteConnection ();
  }
}
