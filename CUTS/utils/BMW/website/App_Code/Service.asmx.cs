// -*- C# -*-

//=============================================================================
/**
 * @file    Service.cs
 *
 * $Id$
 *
 * @author  James H. Hill
 */
//=============================================================================

using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Web;
using System.Web.Security;
using System.Web.Services;
using System.Web.Services.Protocols;
using System.Xml;
using CUTS.Data;
using CUTS.Data.UnitTesting;
using MySql.Data.MySqlClient;

//=============================================================================
/**
 * @class BMW_Web_Service
 *
 * @brief Web service for the CUTS Benchmark Manager Web utility.
 */
//=============================================================================

namespace CUTS.Web
{
  public class UserCredentials : System.Web.Services.Protocols.SoapHeader
  {
    public string Username
    {
      get
      {
        return this.username_;
      }

      set
      {
        this.username_ = value;
      }
    }

    public string Password
    {
      get
      {
        return this.password_;
      }

      set
      {
        this.password_ = value;
      }
    }

    private string username_;

    private string password_;
  }

  public class InvalidUserCredentials : Exception
  {

  }

  [WebService(Namespace = "http://www.dre.vanderbilt.edu/CUTS",
              Name="CUTS BMW Web Service",
              Description="Remotely execute BMW operations")]
  [WebServiceBinding(Name="CUTS",
                     ConformsTo = WsiProfiles.BasicProfile1_1)]
  public class Service : System.Web.Services.WebService
  {
    /**
     * Default constructor.
     */
    public Service ()
    {
      this.database_.Open (ConfigurationManager.AppSettings["MySQL"]);
    }

    /**
     * Destructor
     */
    ~Service ()
    {
      this.database_.Close ();
    }

    /**
     * List all the test suites.
     *
     * @return    List of all the test suites.
     */
    [WebMethod (Description="List all the test suites")]
    [SoapDocumentMethod (Binding="CUTS")]
    [SoapHeader ("consumer_")]
    public string[] ListTestSuites ()
    {
      ArrayList list = new ArrayList ();

      return (string[])list.ToArray (typeof (string));
    }

    /**
     * List all the unit test for a particular test suite.
     *
     * @return    List of all the unit tests.
     */
    [WebMethod (Description="List unit test for the given test suite")]
    [SoapDocumentMethod (Binding="CUTS")]
    [SoapHeader ("consumer_")]
    public string[] ListUnitTests (string TestSuite)
    {
      DataTable table =
        this.database_.select_unit_tests_in_test_suite (TestSuite);

      ArrayList list = new ArrayList ();

      foreach (DataRow row in table.Rows)
        list.Add (row["name"]);

      return (string[])list.ToArray (typeof (string));
    }

    /**
     * Evaluate a unit test for the give test UUID.
     *
     * @param[in]       TestUUID        Test UUID of interest
     * @param[in]       testname        Name of the unit test
     * @return          Evaluation of the unit test
     *
     * @todo   Right now, we make the assumption that grouping is not
     *         supported. Eventually, we will need to add support to
     *         all result to maintain grouping.
     */
    [WebMethod (Description="Evaulate an unit test for the given test")]
    [SoapDocumentMethod (Binding="CUTS")]
    [SoapHeader ("consumer_")]
    public UnitTestResult EvaluateUnitTest (string UUID, string UnitTest)
    {
      // Get the unit test id from the database.
      int utid = this.database_.get_unit_test_id (UnitTest);

      // Create a new evaluator for the unit test.
      UnitTestEvaluator evaluator = new UnitTestEvaluator (new MySqlClientFactory ());
      evaluator.TempPath = Server.MapPath ("~/db");
      evaluator.ConnectionString = ConfigurationManager.AppSettings["MySQL"];
      evaluator.Open ();

      try
      {
        string test_datafile = String.Format ("{0}/{1}.cdb",
                                              Server.MapPath ("~/db/archive"),
                                              UUID);

        return evaluator.Reevaluate (test_datafile, utid, true);
      }
      finally
      {
        evaluator.Close ();
      }
    }

    /**
     * List all the known tests in the database. This does not take
     * the state of the test into account.
     */
    [WebMethod (Description="List all the known tests")]
    [SoapDocumentMethod (Binding="CUTS")]
    [SoapHeader ("consumer_")]
    public string[] ListTests ()
    {
      ArrayList list = new ArrayList ();

      return (string[])list.ToArray (typeof (string));
    }

    /**
     * Helper method to validate user credentials. This should be invoked
     * before every web method processes its request.
     */
    private void validate_credentials ()
    {
      if (this.consumer_.Username.Equals ("testuser") &&
          this.consumer_.Password.Equals ("testpass"))
      {
        return;
      }

      throw new InvalidUserCredentials ();
    }

    /**
     * CUTS database utility component. This object is created
     * at construction time and a the default connection is
     * established. The methods do not have to worry about
     * closing the connection because it is handled when the
     * object is destroyed.
     */
    private Database database_ = new Database (new MySqlClientFactory ());

    public UserCredentials consumer_;
  }
}
