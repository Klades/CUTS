using System.Collections.Generic;

namespace CUTS.Data.UnitTesting
{
  public class UnitTestDefinition
  {
    public UnitTestDefinition ()
    {

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

    public string Description
    {
      get
      {
        return this.description_;
      }

      set
      {
        this.description_ = value;
      }
    }

    public LogFormatCollection LogFormats
    {
      get
      {
        return this.formats_;
      }
    }

    public LogFormatRelationCollection Relations
    {
      get
      {
        return this.relations_;
      }
    }

    public LogFormatVariableCollection Grouping
    {
      get
      {
        return this.grouping_;
      }
    }

    public string EvalFunction
    {
      get
      {
        return this.eval_;
      }

      set
      {
        this.eval_ = value;
      }
    }

    public string AggrFunction
    {
      get
      {
        return this.aggr_;
      }

      set
      {
        this.aggr_ = value;
      }
    }

    private string name_;

    private string description_;

    private LogFormatCollection formats_ = new LogFormatCollection ();

    private LogFormatRelationCollection relations_ = new LogFormatRelationCollection ();

    private LogFormatVariableCollection grouping_ = new LogFormatVariableCollection ();

    private string eval_;

    private string aggr_;
  }
}
