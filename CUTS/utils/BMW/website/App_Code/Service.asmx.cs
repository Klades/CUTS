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
using System.Web.Services;
using System.Web.Services.Protocols;
using System.Xml;

using MySql.Data.MySqlClient;
using CUTS.Data.UnitTesting;

//=============================================================================
/**
 * @class BMW_Web_Service
 *
 * @brief Web service for the CUTS Benchmark Manager Web utility.
 */
//=============================================================================

namespace CUTS.Web
{
  [WebService(Namespace = "http://www.dre.vanderbilt.edu/CUTS",
              Name="CUTS BMW Web Service",
              Description="Remotely execute BMW operations")]
  [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
  public class Service : System.Web.Services.WebService
  {
    /**
     * Default constructor.
     */
    public Service ()
    {
      this.database_.Connection.Open ();
    }

    /**
     * Destructor
     */
    ~Service ()
    {
      this.database_.Connection.Close ();
    }

    /**
     * List all the test suites.
     *
     * @return    List of all the test suites.
     */
    [WebMethod (
      Description="List all the test suites")]
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
    [WebMethod (
      Description="List unit test for the given test suite")]
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
    [WebMethod (
      Description="Evaulate an unit test for the given test")]
    public string EvaluateUnitTest (string UUID, string UnitTest)
    {
      // Get the test number for the uuid.
      int test = this.database_.get_test_number (UUID);
      int utid = this.database_.get_unit_test_id (UnitTest);

      UnitTestEvaluator evaluator = new UnitTestEvaluator (this.database_.Connection,
                                                           new CUTS.Data.MySqlDataAdapterFactory (),
                                                           Server.MapPath ("~/db"));

      string eval;
      string[] groups;
      DataTable result = evaluator.evaluate (test, utid, true, out groups, out eval);

      // Since we are aggregating the results, there should only be
      // one row in the result section until grouping is supported.
      return result.Rows[0]["result"].ToString ();
    }

    /**
     * List all the known tests in the database. This does not take
     * the state of the test into account.
     */
    [WebMethod (
      Description="List all the known tests")]
    public string[] ListTests ()
    {
      ArrayList list = new ArrayList ();

      return (string[])list.ToArray (typeof (string));
    }

    /**
     * CUTS database utility component. This object is created
     * at construction time and a the default connection is
     * established. The methods do not have to worry about
     * closing the connection because it is handled when the
     * object is destroyed.
     */
    private CUTS.Data.Database database_ =
      new CUTS.Data.Database (
      new MySqlConnection (ConfigurationManager.AppSettings["MySQL"]),
      new CUTS.Data.MySqlDataAdapterFactory ());
  }
}
