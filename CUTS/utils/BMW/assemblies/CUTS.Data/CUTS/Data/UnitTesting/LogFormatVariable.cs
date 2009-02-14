using System;

namespace CUTS.Data.UnitTesting
{
  public class LogFormatVariable
  {
    public LogFormatVariable ()
    {

    }

    public LogFormatVariable (int id, string name)
    {
      this.id_ = id;
      this.name_ = name;
    }

    public string Name
    {
      get
      {
        return this.name_;
      }

      set
      {
        this.name_ = value;
      }
    }

    public int ID
    {
      get
      {
        return this.id_;
      }

      set
      {
        this.id_ = value;
      }
    }

    private string name_;

    private int id_;
  }
}
