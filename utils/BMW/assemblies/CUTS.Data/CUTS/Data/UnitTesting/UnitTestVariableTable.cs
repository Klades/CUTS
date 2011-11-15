// -*- C# -*-

using System;
using System.Collections;

namespace CUTS.Data.UnitTesting
{
  public class UnitTestVariableTable : VariableTable
  {
    public UnitTestVariableTable (String root)
    {
      this.root_ = root;
    }

    public void CreateIndices (Relation [] relations)
    {
      String index_name;
      object [] objs;
      int index_count = 0;
      ArrayList index = new ArrayList ();

      foreach (Relation relation in relations)
      {
        index_name = String.Format ("r{0}", index_count++);
        objs = relation.RightValues;

        if (index.Count != 0)
          index.Clear ();

        foreach (object obj in objs)
          index.Add (obj.ToString ());

        this.CreateIndex (index_name, (String[])index.ToArray (typeof (String)));
      }
    }

    public void Open (string test_uuid, int unit_test_id)
    {
      // Open the variable table for the unit test.
      String pathname = String.Format ("{0}//{1}-ut{2}",
                                       this.root_,
                                       test_uuid,
                                       unit_test_id);

      base.Open (pathname);

      // Store the unit test information.
      this.test_uuid_ = test_uuid;
      this.unit_test_id_ = unit_test_id;
    }

    public string TestUUID
    {
      get
      {
        return this.test_uuid_;
      }
    }

    public int UnitTestNumber
    {
      get
      {
        return this.unit_test_id_;
      }
    }

    private String root_;

    private string test_uuid_;

    private int unit_test_id_;
  }
}
