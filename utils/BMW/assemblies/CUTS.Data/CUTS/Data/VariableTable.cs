// -*- C# -*-

//=============================================================================
/**
 * @file          VariableTable.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Data.Common;
using System.Data.SQLite;
using System.IO;
using System.Text;

namespace CUTS.Data
{
  /**
   * @class VariableTable
   *
   * Collection of variables in a table format. Each row in the variable
   * table represents a data set that can be used for evaluation.
   */
  public class VariableTable
  {
    /**
     * Initializing constructor.
     *
     * @param[in]     location          Location of the variable table.
     */
    public VariableTable ()
    {
    }

    ~VariableTable ()
    {
      if (this.connection_.State == ConnectionState.Open)
        this.connection_.Close ();
    }
    /**
     * Delete the variable table database.
     */
    public void Delete ()
    {
      if (File.Exists (this.pathname_))
        File.Delete (this.pathname_);
    }

    /**
     * Open the variable table.
     */
    public void Open (String pathname)
    {
      // Append the extension to the location.
      pathname += ".vt";

      // Make sure the file exists.
      if (!File.Exists (pathname))
        SQLiteConnection.CreateFile (pathname);

      // Update the connection string.
      String connstr = String.Format ("Data Source={0}", pathname);
      this.connection_.ConnectionString = connstr;
      this.connection_.Open ();

      // Save the location.
      this.pathname_ = pathname;
    }

    /**
     * Close the variable table.
     */
    public void Close ()
    {
      this.connection_.Close ();
    }

    /**
     * Begin a transaction on the variable table.
     *
     * @return        Transaction object.
     */
    public DbTransaction BeginTransaction ()
    {
      return this.connection_.BeginTransaction ();
    }

    /**
     * Create the variable table. This will instantiate a new table in
     * the database.
     */
    public void Create (Hashtable columns, bool drop_existing)
    {
      // Convert the columns into types supported by SQLite.
      ArrayList column_list = new ArrayList ();

      foreach (DictionaryEntry entry in columns)
      {
        switch (entry.Value.ToString ())
        {
          case "STRING":
            column_list.Add (String.Format ("{0} TEXT DEFAULT NULL", entry.Key));
            break;

          case "INT":
          case "BIGINT":
          case "SMALLINT":
            column_list.Add (String.Format ("{0} INTEGER DEFAULT NULL", entry.Key));
            break;

          default:
            throw new Exception ("Unknown data type");
        }
      }

      // Convert the list to a partial SQL statement for the columns.
      String column_stmt = String.Join (",", (string [])column_list.ToArray (typeof (string)));
      String schema = column_stmt.Replace ('.', '_');

      this.create_i (schema, drop_existing);
    }

    /**
     * Create a set of indices on the variable table.
     */
    public void CreateIndex (String name, string [] index)
    {
      ArrayList values = new ArrayList ();

      // Create the list of index values.
      foreach (String index_name in index)
        values.Add (this.normalize (index_name));

      String index_values =
        String.Join (", ", (String[])values.ToArray (typeof (String)));

      // Create the SQL statement for this index.
      String index_stmt =
        String.Format ("CREATE INDEX IF NOT EXISTS {0} ON vtable ({1})",
                       name,
                       index_values);

      SQLiteCommand command = this.connection_.CreateCommand ();
      command.CommandText = index_stmt;
      command.ExecuteNonQuery ();
    }

    /**
     * Attribute for getting the connection.
     */
    public SQLiteConnection Connection
    {
      get
      {
        return this.connection_;
      }
    }

    /**
     * Insert the variables and their values into the database. This will
     * append the values to the end of the variable table in the database.
     *
     * @param[in]         variables           Variables to add to database
     */
    public void Insert (Hashtable variables)
    {
      ArrayList column_list = new ArrayList ();
      ArrayList values_list = new ArrayList ();

      foreach (DictionaryEntry entry in variables)
      {
        column_list.Add (entry.Key);
        values_list.Add (String.Format ("'{0}'", entry.Value));
      }

      // Start the insert SQL statement.
      StringBuilder builder = new StringBuilder ("INSERT INTO vtable ");

      // Append the column list to the statement.
      String column_stmt = String.Join (",", (String[])column_list.ToArray (typeof (String)));
      builder.Append (String.Format ("({0}) ",
                                     this.normalize (column_stmt)));

      // Append the values list to the statement.
      String values_stmt = String.Join (",", (String[])values_list.ToArray (typeof (String)));
      builder.Append (String.Format (" VALUES ({0})", values_stmt));

      // Execute the SQL statement on the database.
      SQLiteCommand command = this.connection_.CreateCommand ();
      command.CommandText = builder.ToString ();
      command.ExecuteNonQuery ();
    }

    /**
     * Update the variable table with the new values.
     */
    public void Update (Hashtable variables, Relation relation, bool rhs_filter)
    {
      // Construct the list of columns to set in the table.
      ArrayList set_list = new ArrayList ();

      foreach (DictionaryEntry entry in variables)
        set_list.Add (String.Format ("{0} = '{1}'",
                                     this.normalize ((string)entry.Key),
                                     entry.Value));

      String set_stmt = String.Join (",", (String[])set_list.ToArray (typeof (String)));

      // Determine what side of the relation is the filter, and what
      // side is the target values for the filter.
      object[] filter_column_names =
        rhs_filter ? relation.RightValues : relation.LeftValues;

      object[] target_column_names =
        rhs_filter ? relation.LeftValues : relation.RightValues;

      // Now, construct the list of columns to filter on.
      ArrayList filter_list = new ArrayList ();

      for (int i = 0; i < filter_column_names.Length; ++i)
      {
        String target_column_name = (string)target_column_names[i];
        object target_value = variables[target_column_name];

        String filter_column_name = (string)filter_column_names[i];
        String filter = String.Format ("({0} = '{1}')",
                                       this.normalize (filter_column_name),
                                       target_value);

        filter_list.Add (filter);
      }

      // Finally, create the complete filter for the relation.
      String filter_stmt =
        String.Join (" AND ",
                     (String[])filter_list.ToArray (typeof (String)));

      // Construct the UPDATE command.
      String command_str = String.Format ("UPDATE vtable SET {0} WHERE {1}",
                                          set_stmt,
                                          filter_stmt);

      // Execute the statement on the database.
      SQLiteCommand command = new SQLiteCommand (this.connection_);
      command.CommandText = command_str;
      command.ExecuteNonQuery ();
    }

    /**
     * Evaluate the given statement and return the result in the table.
     *
     * @param[in]         statement         Statement to evaluate
     * @param[inout]      table             Table to store results
     */
    public void Evaluate (String statement, ref DataTable table)
    {
      SQLiteCommand command = this.connection_.CreateCommand ();
      command.CommandText = statement;

      SQLiteDataAdapter adapter = new SQLiteDataAdapter (command);
      adapter.Fill (table);
    }

    public DataTable Data
    {
      get
      {
        SQLiteCommand command = this.connection_.CreateCommand ();
        command.CommandText = "SELECT * FROM vtable";

        SQLiteDataAdapter adapter = new SQLiteDataAdapter (command);
        DataTable table = new DataTable ();
        adapter.Fill (table);

        return table;
      }
    }

    /**
     * Clear all the rows in the database.
     */
    public void Clear ()
    {
      SQLiteCommand command = this.connection_.CreateCommand ();
      command.CommandText = "DELETE FROM vtable";
      command.ExecuteNonQuery ();
    }

    /**
     *
     */
    protected void create_i (String schema, bool drop_existing)
    {
      SQLiteCommand command = this.connection_.CreateCommand ();

      if (drop_existing)
      {
        // First, drop the 'vtable' if it already exists.
        command.CommandText = "DROP TABLE IF EXISTS vtable";
        command.ExecuteNonQuery ();
      }

      // Now, create the variable table in the database.
      StringBuilder builder = new StringBuilder ("CREATE TABLE vtable (");
      builder.Append (schema);
      builder.Append (")");

      // Create the table in the database.
      command.CommandText = builder.ToString ();
      command.ExecuteNonQuery ();
    }

    public void Compact ()
    {
      // First, get the names of all the columns in the 'vtable'
      SQLiteCommand command = this.connection_.CreateCommand ();
      command.CommandText = "PRAGMA table_info (vtable)";

      List<string> columns = new List<string> ();
      SQLiteDataReader reader = command.ExecuteReader ();

      while (reader.Read ())
        columns.Add (reader.GetString (1) + " IS NULL");

      // Close the reader.
      reader.Close ();

      // Construct the SQL statement for purging incomplete rows.
      string partial = String.Join (" OR ", columns.ToArray ());
      command.CommandText = String.Format ("DELETE FROM vtable WHERE {0}", partial);

      // Execute the SQL statement.
      command.ExecuteNonQuery ();
    }

    /**
     * Helper method to normalize a column name.
     */
    private String normalize (String str)
    {
      return str.Replace ('.', '_');
    }

    /**
     * SQLite database connection for the variable table.
     */
    private SQLiteConnection connection_ = new SQLiteConnection ();

    /**
     * Location of the variable table.
     */
    private string pathname_;
  }
}
