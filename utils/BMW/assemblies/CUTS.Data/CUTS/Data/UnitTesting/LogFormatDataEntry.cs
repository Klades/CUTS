// -*- C# -*-

//=============================================================================
/**
 * @file        LogFormatDataEntry.cs
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

using System;
using System.Collections;
using System.Data;
using System.Data.SQLite;

namespace CUTS.Data.UnitTesting
{
  /**
   * @class LogFormatDataEntry
   */
  public class LogFormatDataEntry
  {
    /**
     *
     */
    public LogFormatDataEntry (VariableTable vtable, String[] variables)
    {
      // Create a command object for this entry object.
      SQLiteConnection conn = vtable.Connection;
      this.command_ = conn.CreateCommand ();

      // Prepare an insert command.
      this.prepare_insert_command (variables);
    }

    /**
     *
     */
    public LogFormatDataEntry (VariableTable vtable,
                               String [] variables,
                               Relation relation)
    {
      // Create a command object for this entry object.
      SQLiteConnection conn = vtable.Connection;
      this.command_ = conn.CreateCommand ();

      if (relation == null)
        this.prepare_insert_command (variables);
      else
        this.prepare_update_command (variables, relation);
    }

    /**
     *
     */
    public void Process (Hashtable variables)
    {
      String var_name;
      String param_name;

      // Update the parameters.
      foreach (DictionaryEntry entry in variables)
      {
        var_name = (String)entry.Key;
        param_name = this.parameter_name (var_name);

        this.command_.Parameters[param_name].Value = entry.Value;
      }

      // Execute the command.
      this.command_.ExecuteNonQuery ();
    }

    /**
     *
     */
    private void prepare_insert_command (String[] vars)
    {
      // First, construct the list of parameters for the statement. Make
      // sure to use the variable's name since this will make it a LOT
      // easier to update the parameters.
      ArrayList param_list = new ArrayList ();
      ArrayList column_list = new ArrayList ();

      foreach (String name in vars)
      {
        String safe_name = this.normalize (name);
        String param_name = this.parameter_name (name);

        column_list.Add (safe_name);
        param_list.Add (param_name);

        // Instantiate a parameter in the command.
        SQLiteParameter param = this.command_.CreateParameter ();
        param.ParameterName = param_name;
        param.Direction = ParameterDirection.Input;

        // Save the parameter
        this.command_.Parameters.Add (param);
      }

      String column_names = String.Join (", ", (String[])column_list.ToArray (typeof (String)));
      String value_params = String.Join (", ", (String[])param_list.ToArray (typeof (String)));

      // Set the SQL statement for the command.
      String sql_command = String.Format ("INSERT INTO vtable ({0}) VALUES ({1})",
                                          column_names,
                                          value_params);

      this.command_.CommandText = sql_command;
    }

    /**
     *
     */
    private void prepare_update_command (String[] variables, Relation relation)
    {
      // Construct the SET clause for the SQL statement.
      String safe_name, param_name, stmt;
      SQLiteParameter param;
      ArrayList set_list = new ArrayList ();

      foreach (String name in variables)
      {
        safe_name = this.normalize (name);
        param_name = this.parameter_name (name);

        stmt = String.Format ("{0}={1}", safe_name, param_name);
        set_list.Add (stmt);

        // Create a parameter for this statement.
        param = this.command_.CreateParameter ();
        param.ParameterName = param_name;
        param.Direction = ParameterDirection.Input;

        // Insert the parameter into the command.
        this.command_.Parameters.Add (param);
      }

      String set_stmt = String.Join (", ", (String[])set_list.ToArray (typeof (String)));

      // Construct the WHERE clause for the SQL statement.
      String cause, effect;
      object[] causes = relation.LeftValues;
      object[] effects = relation.RightValues;
      ArrayList where_list = new ArrayList ();

      for (int i = 0; i < relation.Count; ++i)
      {
        cause = this.normalize ((String)causes[i]);
        effect = this.normalize ((String)effects[i]);

        stmt = String.Format ("{0}={1}", effect, this.parameter_name (cause));
        where_list.Add (stmt);
      }

      String where_stmt = String.Join (" AND ", (String[])where_list.ToArray (typeof (String)));

      String sql_statement = String.Format ("UPDATE vtable SET {0} WHERE {1}",
                                            set_stmt,
                                            where_stmt);

      // Set the SQL statement for the command.
      this.command_.CommandText = sql_statement;
    }

    private String parameter_name (String name)
    {
      return this.normalize (String.Format ("@{0}", name));
    }

    private String normalize (String name)
    {
      return name.Replace ('.', '_');
    }

    private SQLiteCommand command_;
  };
}
