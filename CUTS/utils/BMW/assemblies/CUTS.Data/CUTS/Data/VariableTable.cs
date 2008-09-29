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
    public VariableTable (string location)
    {
      // Append the extension to the location.
      location += ".vt";

      // Make sure the file exists.
      if (!File.Exists (location))
        SQLiteConnection.CreateFile (location);

      // Save the location.
      this.location_ = location;

      // Update the connection string.
      String connstr = String.Format ("Data Source={0}", this.location_);
      this.connection_.ConnectionString = connstr;
    }

    /**
     * Delete the variable table database.
     */
    public void Delete ()
    {
      if (File.Exists (this.location_))
        File.Delete (this.location_);
    }

    /**
     * Open the variable table.
     */
    public void Open ()
    {
      this.connection_.Open ();
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
    public void Create (Hashtable columns)
    {
      // First, drop the 'vtable' if it already exists.
      SQLiteCommand command = this.connection_.CreateCommand ();
      command.CommandText = "DROP TABLE IF EXISTS vtable";
      command.ExecuteNonQuery ();

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
            column_list.Add (String.Format ("{0} INT DEFAULT NULL", entry.Key));
            break;

          default:
            throw new Exception ("Unknown data type");
        }
      }

      // Convert the list to a partial SQL statement for the columns.
      String column_stmt = String.Join (",", (string [])column_list.ToArray (typeof (string)));

      StringBuilder builder = new StringBuilder ("CREATE TABLE vtable (");
      builder.Append (column_stmt.Replace ('.', '_'));
      builder.Append (")");

      // Create the table in the database.
      command.CommandText = builder.ToString ();
      command.ExecuteNonQuery ();
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
      String filter_stmt = String.Join (" AND ", (String[])filter_list.ToArray (typeof (String)));

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

    /**
     * Purge incomplete rows from the variable table. An incomplete
     * row is one that has at least one NULL value.
     */
    public void PurgeIncompleteRows ()
    {

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
    private string location_;
  }
}
