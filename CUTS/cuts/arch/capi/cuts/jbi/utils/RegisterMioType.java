// -*- java -*-

//==============================================================================
/**
 * @file            RegisterMioType.java
 *
 * $Id$
 *
 * @author          James H. Hill
 *
 * Utility application for registering MIO types with the Apollo
 * server
 */
//==============================================================================

package cuts.jbi.utils;
import mil.af.rl.im.capi.client.impl.ConnectionManager;
import mil.af.rl.im.capi.client.impl.typemgt.InfoObjectDescriptor;
import mil.af.rl.im.capi.client.impl.typemgt.TypeDescriptor;

import org.infospherics.jbi.client.Connection;
import org.infospherics.jbi.client.exception.*;
import org.infospherics.jbi.client.typemgt.MetadataRepository;

import org.apache.log4j.Logger;
import org.apache.log4j.BasicConfigurator;

import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * @class RegisterMioType
 *
 * Helper class that is responsible for registering a given MIO type
 * with the server.
 */
public class RegisterMioType
{
    private String username_ = null;

    private String password_ = null;

    private String mioType_ = null;

    private String serverAddress_ = "localhost";

    private String version_ = "1.0";

    private final Logger logger_ = Logger.getLogger ("RegisterMioType");

    private String schemasDir_ = ".";

    public RegisterMioType ()
    {

    }

    public void run ()
        throws FileNotFoundException, IOException,
               PermissionDeniedException, ConnectionException
    {
        // Construct the name of the MIO type's schema file
        String xmlSchemaFilename =
            this.schemasDir_ + File.separatorChar +
            this.mioType_.replace ('.', File.separatorChar) +
            File.separatorChar +
            this.mioType_ + ".xsd";

        // Type to open the file for reading.
        this.logger_.debug ("loading XML schema from file [" + xmlSchemaFilename + "]");
        File schemaFile = new File (xmlSchemaFilename);
        FileReader fileReader = new FileReader (schemaFile);
        BufferedReader xmlSchemaReader = new BufferedReader (fileReader);

        // Buffer the input of the file into a string.
        String xmlSchema = new String ();

        while (xmlSchemaReader.ready ())
            {
                String line = xmlSchemaReader.readLine ();

                if (line != null)
                    xmlSchema += line;
            }

        // Close the reader and the file.
        xmlSchemaReader.close ();
        fileReader.close ();

        ConnectionManager manager = null;
        Connection connection = null;

        try
            {
                // Create a new connection manager for the application.
                manager = new ConnectionManager ();

                // Generate the connection string.
                String connString =
                    ConnectionString.generate (this.serverAddress_);

                // Establish a connection with the server.
                connection =
                    manager.createConnection ("RegisterMioType", connString);

                // Authenticate the connection.
                String credentials =
                    UserCredentials.generate (this.username_, this.password_);

                connection.authenticate (credentials);
                connection.connect ();

                // Get the metdata repository from the connection.
                MetadataRepository repo = connection.getMetadataRepository ();

                // Create the info object descriptor for the new type.
                InfoObjectDescriptor iod = new InfoObjectDescriptor ();
                iod.setType (this.mioType_);
                iod.setVersion (this.version_);
                iod.setMetadataXMLSchema (xmlSchema);
                iod.setParentType (new TypeDescriptor ("baseObject", "1.5"));

                // Add the new type to the repo.
                this.logger_.info (xmlSchema);
                repo.addInfoObjectDescriptor (iod);
            }
        catch (Exception e)
            {
                e.printStackTrace ();
            }
        finally
            {
                if (manager != null)
                    {
                        if (connection != null)
                            manager.destroyConnection (connection);
                    }
            }
    }

    public void parseArgs (String [] args)
        throws Exception
    {
        for (int i = 0; i < args.length; i ++)
            {
                String arg = args[i];

                if (arg.equals ("-username"))
                    this.username_ = args[++ i];
                else if (arg.equals ("-password"))
                    this.password_ = args[++ i];
                else if (arg.equals ("-mio-type"))
                    this.mioType_ = args[++ i];
                else if (arg.equals ("-server"))
                    this.serverAddress_ = args[++ i];
                else if (arg.equals ("-version"))
                    this.version_ = args[++ i];
                else if (arg.equals ("-schemas-dir"))
                    this.schemasDir_ = args[++ i];
            }

        if (this.mioType_ == null)
            throw new Exception ("argument missing: -mio-type");

        if (this.username_ == null)
            throw new Exception ("argument missing: -username");

        if (this.password_ == null)
            throw new Exception ("argument missing: -password");
    }

    public static void main (String [] args)
    {
        BasicConfigurator.configure ();
        Logger logger = Logger.getLogger ("RegisterMioType");

        try
            {
                // Create a new instance of the application.
                RegisterMioType app = new RegisterMioType ();

                // Parse the command-line arguments.
                app.parseArgs (args);

                // Run the main part of the application.
                logger.debug ("running the application");
                app.run ();
            }
        catch (Exception e)
            {
                logger.error ("caught exception", e);
            }
    }
}
