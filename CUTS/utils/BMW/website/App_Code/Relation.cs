// -*- C# -*-

using System;
using System.Collections;
using System.Web.UI;

namespace CUTS
{
  public class Relation
  {
    private string lhs_;

    private string rhs_;

    private ArrayList values_ = new ArrayList ();

    private class Relation_Value
    {
      private object value_;

      public bool lhs_set_;

      public bool rhs_set_;

      public Relation_Value (object value, bool lhs_set, bool rhs_set)
      {
        this.value_ = value;

        this.lhs_set_ = lhs_set;
        this.rhs_set_ = rhs_set;
      }

      public bool equals (object value)
      {
        return this.value_.Equals (value);
      }
    }

    public Relation (string lhs, string rhs)
    {
      this.lhs_ = lhs;
      this.rhs_ = rhs;
    }

    public override string ToString ()
    {
      return this.lhs_ + " = " + this.rhs_;
    }

    public void clear ()
    {
      this.values_ = new ArrayList ();
    }

    public string left_side
    {
      get
      {
        return this.lhs_;
      }
    }

    public string right_side
    {
      get
      {
        return this.rhs_;
      }
    }

    public bool is_member (string name)
    {
      return this.lhs_ == name || this.rhs_ == name;
    }

    public int insert_value (string name, object value)
    {
      if (this.rhs_.Equals (name))
      {
        return this.insert_value_rhs (value);
      }
      else if (this.lhs_.Equals (name))
      {
        return this.insert_value_lhs (value);
      }
      else
      {
        throw new Exception (name + " is not a member of relation [" + this.ToString () + "]");
      }
    }

    private int insert_value_lhs (object value)
    {
      Relation_Value relation_value;

      for (int i = 0; i < this.values_.Count; ++ i)
      {
        relation_value = (Relation_Value) this.values_[i];

        if (relation_value.equals (value) && !relation_value.lhs_set_)
        {
          relation_value.lhs_set_ = true;
          return i;
        }
      }

      // We need to create a new relation and returns its index
      relation_value = new Relation_Value (value, true, false);
      return this.values_.Add (relation_value);
    }

    private int insert_value_rhs (object value)
    {
      Relation_Value relation_value;

      for (int i = 0; i < this.values_.Count; ++i)
      {
        relation_value = (Relation_Value)this.values_[i];

        if (relation_value.equals (value) && !relation_value.rhs_set_ )
        {
          relation_value.rhs_set_ = true;
          return i;
        }
      }

      // We need to create a new relation and return its index.
      relation_value = new Relation_Value (value, false, true);
      return this.values_.Add (relation_value);
    }
  }
}
