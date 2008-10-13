// -*- C# -*-

using System;
using System.Collections;
using System.Data;

namespace CUTS.Data
{
  /**
   * @class Relation
   */
  [Serializable]
  public class Relation
  {
    /**
     * Default constructor.
     */
    public Relation ()
    {
      this.lhs_ = new ArrayList ();
      this.rhs_ = new ArrayList ();
    }

    public Relation (int capacity)
    {
      this.lhs_ = new ArrayList (capacity);
      this.rhs_ = new ArrayList (capacity);
    }

    public Relation (object lhs, object rhs)
    {
      this.lhs_ = new ArrayList ();
      this.lhs_.Add (lhs);

      this.rhs_ = new ArrayList ();
      this.rhs_.Add (rhs);
    }

    public void add (object lhs, object rhs)
    {
      this.lhs_.Add (lhs);
      this.rhs_.Add (rhs);
    }

    public void update (int index, object lhs, object rhs)
    {
      this.lhs_[index] = lhs;
      this.rhs_[index] = rhs;
    }

    public void insert (int index, object lhs, object rhs)
    {
      this.lhs_.Insert (index, lhs);
      this.rhs_.Insert (index, rhs);
    }

    public void update_left_value (int index, object value)
    {
      this.lhs_[index] = value;
    }

    public void update_right_value (int index, object value)
    {
      this.rhs_[index] = value;
    }

    /**
     * Clear the relations object.
     */
    public void clear ()
    {
      this.lhs_.Clear ();
      this.rhs_.Clear ();
    }

    /**
     * Read-only property for getting the size of the relation.
     */
    public int Count
    {
      get
      {
        return this.lhs_.Count;
      }
    }

    /**
     * Property associated with the values of the left-hand side of
     * the relation.
     */
    public object[] LeftValues
    {
      get
      {
        return this.lhs_.ToArray ();
      }
    }

    /**
     * Property associated with the values of the right-hand side of
     * the relation.
     */
    public object[] RightValues
    {
      get
      {
        return this.rhs_.ToArray ();
      }
    }

    /**
     *
     */
    public override bool Equals (object obj)
    {
      if (obj == null)
        return false;

      if (!(obj is Relation))
        return false;

      Relation r = (Relation)obj;

      if (this.rhs_.Count != r.RightValues.Length ||
          this.lhs_.Count != r.LeftValues.Length)
      {
        return false;
      }

      int count = this.lhs_.Count;

      for (int i = 0; i < count; ++ i)
      {
        if (!this.lhs_[i].Equals (r.lhs_[i]) ||
            !this.rhs_[i].Equals (r.rhs_[i]))
        {
          return false;
        }
      }

      return true;
    }

    public override int GetHashCode ()
    {
      return base.GetHashCode ();
    }

    private ArrayList lhs_;

    private ArrayList rhs_;
  }
}
