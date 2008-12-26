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
using System.Configuration;
using System.Data;
using System.Data.Common;
using System.Reflection;
using System.Security.Cryptography;
using System.Runtime.Remoting;
using System.Text;

namespace CUTS.BMW
{
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
    public Database (string provider)
    {
      // Get the provider name.
      string[] items = provider.Split (",".ToCharArray ());

      // Dynamically instantiate provider factory for database.
      Assembly assembly = Assembly.LoadWithPartialName (items[1]);
      object obj = assembly.CreateInstance (items[0]);

      if (obj != null)
      {
        this.provider_ = (DbProviderFactory)obj;
        this.conn_ = this.provider_.CreateConnection ();
      }
    }

    /**
     * Default constructor
     */
    public Database (DbProviderFactory factory)
    {
      this.provider_ = factory;
      this.conn_ = this.provider_.CreateConnection ();
    }

    /**
     * Destructor
     */
    ~Database ()
    {
      if (this.conn_.State == ConnectionState.Open)
        this.conn_.Close ();
    }

    /**
     * Open a connection to the databse.
     *
     * @param[in]         filename          Location of the database.
     */
    public void Open ()
    {
      this.conn_.Open ();
    }

    /**
     * Get the state of the connection.
     */
    public ConnectionState State
    {
      get
      {
        return this.conn_.State;
      }
    }

    /**
     * Get/set the connection string for the connection.
     */
    public string ConnectionString
    {
      get
      {
        return this.conn_.ConnectionString;
      }

      set
      {
        this.conn_.ConnectionString = value;
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
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT password FROM users WHERE username=@username";

      // Initialize the parameters.
      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "@username";
      p1.DbType = DbType.String;
      p1.Value = username;

      command.Parameters.Add (p1);

      // Execute the command.
      object obj = command.ExecuteScalar ();

      if (obj == null)
        return false;

      byte [] passwd = (byte [])obj;

      // Compute the hash for the username/password.
      UTF8Encoding encoding = new UTF8Encoding ();
      SHA1CryptoServiceProvider crypt = new SHA1CryptoServiceProvider ();
      Byte[] hash = crypt.ComputeHash (encoding.GetBytes (username + password));

      // First, check the lengths of the arrays.
      if (passwd.Length != hash.Length)
        return false;

      // Next, compare each value in the array.
      for (int i = 0; i < passwd.Length; i++)
      {
        if (passwd[i] != hash[i])
          return false;
      }

      return true;
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
      SHA1CryptoServiceProvider crypt = new SHA1CryptoServiceProvider ();
      Byte[] hash = crypt.ComputeHash (encoding.GetBytes (profile.Username + profile.Password));

      // Create the SQL command.
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText =
        "INSERT INTO users (username, password, email) VALUES (@username, @password, @email)";

      // Prepare the SQL parameters.
      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "@username";
      p1.DbType = DbType.String;
      p1.Value = profile.Username;
      command.Parameters.Add (p1);

      DbParameter p2 = command.CreateParameter ();
      p2.ParameterName = "@password";
      p2.DbType = DbType.Binary;
      p2.Value = hash;
      command.Parameters.Add (p2);

      DbParameter p3 = command.CreateParameter ();
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
    private DbProviderFactory provider_;

    /**
     * Connection to the database.
     */
    private DbConnection conn_;
  }
}
