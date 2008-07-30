// -*- C# -*-

//=============================================================================
/**
 * @file            MySqlDataAdapterFactory.cs
 *
 * $Id$
 *
 * @author          James H. Hill
 */
//=============================================================================

using System.Data;
using System.Data.Odbc;

namespace CUTS.Data
{
  /**
   * @class OdbcDataAdapterFactory
   *
   * Implementation of the IDbDataAdapterFactory for creating data adapters
   * for ODBC database connection.
   */
  public class OdbcDataAdapterFactory : IDbDataAdapterFactory
  {
    /**
     * Create a default data adapter.
     *
     * @return        Data adapter for ODBC
     */
    IDbDataAdapter IDbDataAdapterFactory.CreateDbDataAdapter ()
    {
      return new OdbcDataAdapter ();
    }

    /**
     * Create an adapter using the specified command. This will try to
     * cast the \a select_comand to a OdbcCommand object. If the specified
     * command is not of the right type, an exception will be thrown.
     *
     * @param[in]     select_command        Initial select command for adapter
     * @return        Data adapter for ODBC
     */
    IDbDataAdapter IDbDataAdapterFactory.CreateDbDataAdapter (IDbCommand select_command)
    {
      return new OdbcDataAdapter ((OdbcCommand)select_command);
    }
  }
}
