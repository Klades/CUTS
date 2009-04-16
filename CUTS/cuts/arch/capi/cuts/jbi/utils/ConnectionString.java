// -*- java -*-

//==============================================================================
/**
 * @file            ConnectionString.java
 *
 * $Id$
 *
 * @author          James H. Hill
 */
//==============================================================================

package cuts.jbi.utils;

/**
 * @class ConnectionString
 *
 * Utility class for generating descriptors for establishing connections with
 * the server.
 */
public class ConnectionString
{
    public static String generate (String serverAddress)
    {
      String connString =
          new String ("<ConnectionDescriptor>" +
                      "<PlatformDescriptor>" +
                      "<platformIP>" + serverAddress + "</platformIP>" +
                      "</PlatformDescriptor>" +
                      "</ConnectionDescriptor>");

      return connString;
    }
}
