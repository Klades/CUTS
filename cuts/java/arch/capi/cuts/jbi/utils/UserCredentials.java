// -*- java -*-

//==============================================================================
/**
 * @file            UserCredentials.java
 *
 * $Id$
 *
 * @author          James H. Hill
 */
//==============================================================================

package cuts.jbi.utils;

/**
 * @class UserCredentials
 *
 * Helper class for generating the user credentials used by clients when
 * logging onto the server.
 */
public class UserCredentials
{
    public static String generate (String username, String password)
    {
        String userCredentials =
            new String ("<credentials>" +
                        "<username>"+ username + "</username>" +
                        "<password>"+ password +"</password>" +
                        "</credentials>");

        return userCredentials;
    }
}
