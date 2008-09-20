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
using MySql.Data.MySqlClient;

namespace CUTS.Data
{
  /**
   * @class MySqlDataAdapterFactory
   *
   * Implementation of the IDbDataAdapterFactory for creating data adapters
   * for MySQL database.
   */
  public class MySqlDataAdapterFactory : IDbDataAdapterFactory
  {
    /**
     * Create a default data adapter.
     *
     * @return        Data adapter for MySQL
     */
    IDbDataAdapter IDbDataAdapterFactory.CreateDbDataAdapter ()
    {
      return new MySqlDataAdapter ();
    }

    /**
     * Create an adapter using the specified command. This will try to
     * cast the \a select_comand to a MySqlCommand object. If the specified
     * command is not of the right type, an exception will be thrown.
     *
     * @param[in]     select_command        Initial select command for adapter
     * @return        Data adapter for MySQL
     */
    IDbDataAdapter IDbDataAdapterFactory.CreateDbDataAdapter (IDbCommand select_command)
    {
      return new MySqlDataAdapter ((MySqlCommand) select_command);
    }
  }
}
