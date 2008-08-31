/**
 * @file        DataBaseActions.cs
 *
 * Defines the Actions.DataBaseActions code.
 *
 * @author      Hamilton Turner
 */
using System;
using System.Data;
using System.Collections;
using MySql.Data.MySqlClient;


namespace Actions.DataBaseActions
{
  /**
   * @class DataBaseActions
   *
   * A general class for interacting with the database on a
   *   fundamental level - executing sql, retrieving data. This
   *   class needs updates!!!
   *
   * Updates needed: Move this from the Actions namespace and
   *   into the correct CUTS namespace.
   */
  public class DataBaseActions
  {
    private MySqlConnection conn_;

    /**
     * Constructor.
     *
     * @param[in] connection_string   The connection string used to initialize
     *                                  the database connection.
     */
    public DataBaseActions (string connection_string)
    {
      this.conn_ = new MySqlConnection (connection_string);
    }

    /**
     * Used to safely execute any block of SQL code that is
     *   not intended to return a value.
     *
     * @param[in]  sql  The sql code to be executed.
     */
    public void execute_mysql (string sql)
    {
      MySqlCommand comm = new MySqlCommand (sql, conn_);
      comm.ExecuteNonQuery ();
    }

    /**
     * Used to safely execute any block of SQL code that is
     *   not intended to return a value.
     *
     * @param[in]  comm   The MySqlCommand to be executed.
     */
    public void execute_mysql (MySqlCommand comm)
    {
      comm.ExecuteNonQuery ();
    }

    /**
     * Used to safely execute any block of SQL code that is
     *   intended to return a single value. Needs to be updated
     *   to return more than just integer values.
     *
     * @param[in]  sql  The sql to be executed.
     */
    public int execute_mysql_scalar (string sql)
    {
      MySqlCommand comm = new MySqlCommand (sql, conn_);
      object obj = comm.ExecuteScalar ();
      return (int)obj;
    }

    /**
     * Used to safely execute any block of SQL code that is
     *   intended to return a single value. Needs to be updated
     *   to return more than just integer values.
     *
     * @param[in]  comm   The MySqlCommand to be executed.
     */
    public int execute_mysql_scalar (MySqlCommand comm)
    {
      object obj = comm.ExecuteScalar ();
      return (int)obj;
    }

    /**
     * Used to facilitate creating a MySqlCommand from a
     *   section of sql code.
     *
     * @param[in]  sql  The sql to assign as the command text.
     */
    public MySqlCommand get_command (string sql)
    {
      MySqlCommand comm = conn_.CreateCommand ();
      comm.CommandText = sql;
      return comm;
    }

    /**
     * Used to evaluate sql and return the results in a
     *   DataTable.
     *
     * @param[in]  sql  The Sql code to be evaluated.
     */
    public DataTable execute_mysql_adapter (string sql)
    {
      MySqlDataAdapter da = new MySqlDataAdapter (sql, conn_);
      DataSet ds = new DataSet ();
      da.Fill (ds);
      return ds.Tables[0];
    }

    /**
     * Used to evaluate sql and return the results in a
     *   DataTable.
     *
     * @param[in]  command  The MySqlCommand to be evaluated.
     */
    public DataTable execute_mysql_adapter (MySqlCommand command)
    {
      MySqlDataAdapter da = new MySqlDataAdapter (command);
      DataSet ds = new DataSet ();
      da.Fill (ds);
      return ds.Tables[0];
    }

    /**
     * Used to return one column(stored in an array) from a sql query.
     *
     * @param[in]   sql           The sql to evaluate.
     * @param[in]   column_name   The name of the column desired.
     */
    public Array execute_mysql_reader (string sql, string column_name)
    {
      MySqlCommand comm = new MySqlCommand (sql, this.conn_);
      MySqlDataReader r = comm.ExecuteReader ();
      ArrayList al = new ArrayList ();
      while (r.Read ())
        al.Add (r.GetString (column_name));
      return al.ToArray ();
    }

    /**
     * Used to return the top one row from a MySqlCommand.
     *   Note that this could be improved internally by checking to
     *   see if the command contained limit or top.
     */
    public DataRow execute_mysql_row (MySqlCommand comm)
    {
      DataTable dt = this.execute_mysql_adapter (comm);
      return dt.Rows[0];
    }

  }

}

