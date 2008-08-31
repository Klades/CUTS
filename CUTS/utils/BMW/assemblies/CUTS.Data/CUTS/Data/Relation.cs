// -*- C# -*-

using System;
using System.Collections;
using System.Data;

namespace CUTS.Data
{
  /**
   * @class Relation
   */
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
