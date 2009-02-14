using System.Collections.Generic;

namespace CUTS.Data.UnitTesting
{
  public class LogFormatRelationCollection : List<LogFormatRelation>
  {
    public LogFormatRelationCollection ()
    {

    }

    public LogFormatRelationCollection (LogFormatRelation[] relations)
      : base (relations)
    {

    }
  }
}
