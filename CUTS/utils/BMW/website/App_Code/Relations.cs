using System;
using System.Collections;

namespace CUTS
{
  public class Relations
  {
    private ArrayList relations_ = new ArrayList ();

    public Relations ()
    {

    }

    public void insert (string lhs, string rhs)
    {
      this.insert (new CUTS.Relation (lhs, rhs));
    }

    public void insert (Relation relation)
    {
      this.relations_.Add (relation);
    }

    public int update (string variable, object value)
    {
      // First, locate the first relation that contains this variable
      // name.
      int row = -1, i;

      for (i = 0; i < this.relations_.Count; ++i)
      {
        // Get the next relation in the listing.
        CUTS.Relation relation = (Relation)this.relations_[i];

        // Determine if this variable is a member of this relation. If it
        // is, then we should insert the value. This will, in turn, give us
        // the row that will need to update in the variable table.
        if (relation.is_member (variable))
        {
          row = relation.insert_value (variable, value);
          break;
        }
      }

      // Second, set the value of the remaining relations. We should also
      // validate that the row index for the remaining relations is equal
      // to the index of the previously found relation. Otherwise, we have
      // some inconsistency in the data.
      for (++i; i < this.relations_.Count; ++i)
      {
        CUTS.Relation relation = (Relation) this.relations_[i];

        if (relation.is_member (variable))
        {
          if (row != relation.insert_value (variable, value))
            throw new Exception ("relation row is inconsistent [" + relation.ToString () + "]");
        }
      }

      return row;
    }

    public int count
    {
      get
      {
        return this.relations_.Count;
      }
    }

    /**
     * Determine if the specified variable appears in any relation.
     *
     * @param[in]         name          Name of variable
     */
    public bool is_relation_variable (string name)
    {
      foreach (CUTS.Relation relation in this.relations_)
      {
        if (relation.is_member (name))
          return true;
      }

      return false;
    }
  }
}
