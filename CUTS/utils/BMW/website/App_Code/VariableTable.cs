using System;
using System.Data;
using System.Collections;

namespace CUTS
{
  public class Variable_Table
  {
    private DataTable variables_;

    private string name_;

    public Variable_Table (string name)
    {
      this.name_ = name;
      this.variables_ = new DataTable (this.name_);
    }

    public Variable_Table (string name, Hashtable vars)
    {
      this.name_ = name;
      this.reset_i (vars);
    }

    public void clear ()
    {
      this.variables_.Clear ();
    }

    /**
     * Reset the variable table. This will delete all the data from the
     * data table, including its columns. It will then construct a new
     * data table using the variables defined in \a columns as the
     * columns for the data table.
     */
    public void reset (Hashtable columns)
    {
      // Reset the data table.
      this.variables_ = new DataTable (this.name_);

      // Recreate the columns for the table.
      this.reset_i (columns);
    }

    /**
     * Implementation of the reset () method. This method set the
     * columns for the data table. It is assumed that the data table
     * is an uninitialized one.
     */
    private void reset_i (Hashtable columns)
    {
      foreach (DictionaryEntry item in columns)
        this.insert_column ((string)item.Key, (string)item.Value);
    }

    /**
     * Helper method to insert a column into the data table. This will
     * only work if the colunm does not have any data.
     *
     * @param[in]       name              Name of the column
     * @param[in]       typename          Typename of the column
     */
    private void insert_column (string name, string typename)
    {
      Type type;

      switch (typename)
      {
        case "INT":
          type = typeof (System.Int32);
          break;

        case "STRING":
          type = typeof (System.String);
          break;

        default:
          throw new Exception ("variable '" + name + "' has an invalid type : " + typename);
      }

      // Insert the new column into the table.
      this.variables_.Columns.Add (name, type);
    }

    /**
     *
     */
    public void update_value (int row, string column, object value)
    {
      if (row < this.variables_.Rows.Count)
      {
        // Update an existing row in the table.
        this.variables_.Rows[row][column] = value;
      }
      else if (row == this.variables_.Rows.Count)
      {
        // Create a new data row for the table.
        DataRow new_row = this.variables_.NewRow ();
        new_row[column] = value;

        // Insert the data row into the table.
        this.variables_.Rows.Add (new_row);
      }
      else
      {
        throw new Exception ("row is greater than row count");
      }
    }

    /**
     *
     */
    public void add_value (string column, object value)
    {
      // First, locate the last row in the data table that does not have
      // a value, i.e., has a NULL value. If we find it, then we need to
      // set its value and return.
      for (int i = 0; i < this.variables_.Rows.Count; ++i)
      {
        if (this.variables_.Rows[i][column] == DBNull.Value)
        {
          // Update the value of the column.
          this.variables_.Rows[i][column] = value;
          return;
        }
      }

      // Create a new row in the data table.
      DataRow new_row = this.variables_.NewRow ();

      // Initialize the column of the new row.
      new_row[column] = value;

      // Insert the new row into the data table.
      this.variables_.Rows.Add (new_row);
    }

    public DataTable data
    {
      get
      {
        return this.variables_;
      }
    }

    /**
     * Add the values of the variables to the row. This will append the
     * values to the current variable table.
     */
    public void add_values (Hashtable variables)
    {
      // Create a new row in the data table.
      DataRow row = this.variables_.NewRow ();

      // Set the values of the new row.
      foreach (DictionaryEntry variable in variables)
      {
        string var_name = (string)variable.Key;
        row[var_name] = variable.Value;
      }

      // Add the new row into the table.
      this.variables_.Rows.Add (row);
    }

    public void add_values (Hashtable variables,
                            CUTS.Relation filter_relation,
                            bool rhs_filter)
    {
      // Determine what side of the relation is the filter, and what
      // side is the target values for the filter.
      string[] filter_column_names =
        rhs_filter ? filter_relation.rhs : filter_relation.lhs;

      string[] target_column_names =
        rhs_filter ? filter_relation.lhs : filter_relation.rhs;

      // Create a filter for each of the columns, making sure to insert
      // them into a listing for joining.
      ArrayList filter_list = new ArrayList ();

      for (int i = 0; i < filter_column_names.Length; ++i)
      {
        string filter_column_name = filter_column_names[i];
        string column_filter = String.Format ("({0} = ", filter_column_name);

        string target_column_name = target_column_names[i];
        object target_value = variables[target_column_name];

        switch (target_value.GetType ().ToString ())
        {
          case "System.String":
            column_filter += "'" + (string)target_value + "'";
            break;

          default:
            column_filter += target_value;
            break;
        }

        // Close the equality.
        column_filter += ")";

        // Insert the equality into the filter list.
        filter_list.Add (column_filter);
      }

      // Finally, create the complete filter for the relation.
      string filter =
        String.Join (" AND ", (string[])filter_list.ToArray (typeof (string)));

      // Select the rows in the data table that match this filter.
      DataRow[] candidate_rows = this.variables_.Select (filter);

      // Update the values in the row.
      foreach (DataRow row in candidate_rows)
      {
        foreach (DictionaryEntry entry in variables)
        {
          string var_name = (string)entry.Key;
          row[var_name] = entry.Value;
        }
      }
    }
  }
}
