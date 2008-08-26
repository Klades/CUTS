// -*- C# -*-

using System;
using System.Collections;
using System.Data;
using System.Web.UI;

namespace CUTS
{
  public class Relation
  {
    private ArrayList lhs_;

    private ArrayList rhs_;

    /**
     * Default constructor.
     */
    public Relation ()
    {
      this.lhs_ = new ArrayList ();
      this.rhs_ = new ArrayList ();
    }

    /**
     * Initailizing constructor. Initalizes the size of the relation.
     *
     * @param[in]       count         Number of elements in relation.
     */
    public Relation (int count)
    {
      this.lhs_ = new ArrayList (count);
      this.rhs_ = new ArrayList (count);
    }

    public void insert_equality (int index, string lhs, string rhs)
    {
      this.lhs_.Insert (index, lhs);
      this.rhs_.Insert (index, rhs);
    }

    /**
     * Locate the next row in the table where the right-hand side of the
     * relation is equal to the left hand side of the relation.
     */
    public void update_variables (ref CUTS.Variable_Table variables,
                                  Hashtable lhs_vars)
    {
      // Create a filter for each of the columns, making sure to insert
      // them into a listing for joining.
      ArrayList filter_list = new ArrayList ();

      for (int i = 0; i < this.rhs_.Count; ++i)
      {
        string rhs_name = (string)this.rhs_[i];
        string column_filter = String.Format ("({0} = ", rhs_name);

        object lhs_value = lhs_vars[this.lhs_[i]];

        switch (lhs_value.GetType ().ToString ())
        {
          case "System.String":
            column_filter += "'" + (string)lhs_value + "'";
            break;

          default:
            column_filter += lhs_value;
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
      DataRow[] candidate_rows = variables.data.Select (filter);

      // Update the values in the row.
      foreach (DataRow row in candidate_rows)
      {
        foreach (DictionaryEntry entry in lhs_vars)
        {
          string var_name = (string)entry.Key;
          row[var_name] = entry.Value;
        }
      }
    }

    /**
     * Property associated with the values of the left-hand side of
     * the relation.
     */
    public string[] lhs
    {
      get
      {
        return (string[])this.lhs_.ToArray (typeof (string));
      }
    }

    /**
     * Property associated with the values of the right-hand side of
     * the relation.
     */
    public string[] rhs
    {
      get
      {
        return (string[])this.rhs_.ToArray (typeof (string));
      }
    }
  }
}
