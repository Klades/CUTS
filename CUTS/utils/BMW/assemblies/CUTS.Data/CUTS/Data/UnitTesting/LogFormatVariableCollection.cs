using System.Collections.Generic;

namespace CUTS.Data.UnitTesting
{
  public class LogFormatVariableCollection : List<LogFormatVariable>
  {
    public LogFormatVariableCollection ()
    {

    }

    public LogFormatVariableCollection (LogFormatVariable[] variables)
      : base (variables)
    {

    }
  }
}
