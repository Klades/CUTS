// -*- C# -*-

//=============================================================================
/**
 * @file      TestDatabase.cs
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

using System;
using System.Data;
using System.Data.SQLite;
using System.Text.RegularExpressions;

namespace CUTS.Testing
{
  /**
   * @class TestDatabase
   */
  public class TestDatabase
  {
    /**
     * Default constructor
     */
    public TestDatabase ()
    {

    }

    /**
     * Initializing constructor
     *
     * @param[in]         datafile        Target database file
     */
    public TestDatabase (string datafile)
    {
      this.Open (datafile);
    }

    /**
     * Destructor
     */
    ~TestDatabase ()
    {
      if (this.conn_.State == ConnectionState.Open)
        this.conn_.Close ();
    }

    /**
     * Open connection to the database.
     */
    public void Open (string datafile)
    {
      string connstr = String.Format ("Data Source={0}", datafile);
      this.conn_.ConnectionString = connstr;

      this.Open ();
    }

    public void Open ()
    {
      this.conn_.Open ();
    }

    /**
     * Close the database connection.
     */
    public void Close ()
    {
      this.conn_.Close ();
    }

    /**
     * Get the UUID for this test.
     *
     * @return        UUID for the test
     */
    public string GetTestUUID ()
    {
      SQLiteCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT uuid FROM cuts_test WHERE tid = 1";

      return (string)command.ExecuteScalar ();
    }

    /**
     * Select a subset of the log messages that match the provided regular
     * expression.
     *
     * @param[in]     regex           SQL regular expression used as filter
     * @return        Data reader to filtered log messages.
     */
    public SQLiteDataReader FilterLogMessages (string regex)
    {
      SQLiteCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT hostname, timeofday, severity, message " +
                            "FROM cuts_logging WHERE message REGEXP @format " +
                            "ORDER BY hostname, timeofday ASC, lid DESC;";

      SQLiteParameter format = command.CreateParameter ();
      format.ParameterName = "@format";
      format.DbType = DbType.String;
      format.Value = regex;

      command.Parameters.Add (format);

      return command.ExecuteReader (CommandBehavior.SequentialAccess);
    }

    /**
     * Connection to the test database.
     */
    private SQLiteConnection conn_ = new SQLiteConnection ();
  }

  /**
   * @class SQLiteRegExp
   *
   * Implementation of the REXEXP function for SQLite. This function is
   * loaded at run-time and enables usage of the REGEXP SQL function, which
   * is not implemented by default in SQLite.
   */
  [SQLiteFunction(Name = "REGEXP",
                  Arguments = 2,
                  FuncType = FunctionType.Scalar)]
  class SQLiteRegExp : SQLiteFunction
  {
    public override object Invoke (object[] args)
    {
      return Regex.IsMatch (Convert.ToString (args[1]), Convert.ToString (args[0]));
    }
  }
}
