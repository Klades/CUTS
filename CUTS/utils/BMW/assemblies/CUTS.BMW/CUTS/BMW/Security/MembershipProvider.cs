// -*- C# -*-

//=============================================================================
/**
 * @file        MembershipProvider
 *
 * $Id$
 *
 * @author      James H. Hill <j dot hill at vanderbilt dot edu>
 */
//=============================================================================

using System;
using System.Collections.Specialized;
using System.Configuration;
using System.Web;
using System.Web.Security;

namespace CUTS.BMW.Security
{
  /**
   * @class MembershipProvider
   *
   * Default implemenation of the membership provider for the BMW
   */
  public class MembershipProvider : System.Web.Security.MembershipProvider
  {
    /**
     * Default constructor
     */
    public MembershipProvider ()
    {

    }

    /**
     * Destructor
     */
    ~MembershipProvider ()
    {
      this.bmw_.Close ();
    }

    /**
     * Initialize the membership provider object
     *
     * @param[in]       name          Name of the provider
     * @param[in]       config        Configuration of the provider
     */
    public override void Initialize (string name, NameValueCollection config)
    {
      // Pass control to the base class first.
      base.Initialize (name, config);

      // Map the location of the database.
      string location = HttpContext.Current.Server.MapPath (config["path"]);

      // Discover the administrator password
      if (config.Get ("adminAppSetting") != null)
      {
        this.admin_password_ =
          ConfigurationManager.AppSettings[config["adminAppSetting"]];
      }

      // Establish a connection to the database
      this.bmw_.Open (location);
    }

    public override bool EnablePasswordReset
    {
      get { return true; }
    }

    public override bool EnablePasswordRetrieval
    {
      get { return false; }
    }

    public override bool RequiresQuestionAndAnswer
    {
      get { return false; }
    }

    public override string ApplicationName
    {
      get
      {
        return this.appname_;
      }

      set
      {
        this.appname_ = value;
      }
    }

    public override bool RequiresUniqueEmail
    {
      get { return true; }
    }

    public override int MaxInvalidPasswordAttempts
    {
      get { return 3; }
    }

    public override MembershipPasswordFormat PasswordFormat
    {
      get { return MembershipPasswordFormat.Hashed; }
    }

    public override int MinRequiredPasswordLength
    {
      get { return 8; }
    }
    public override int MinRequiredNonAlphanumericCharacters
    {
      get { return 0; }
    }

    public override int PasswordAttemptWindow
    {
      get { return 10; }
    }

    public override string PasswordStrengthRegularExpression
    {
      get { return ""; }
    }

    public override bool ValidateUser (string username, string password)
    {
      // Authenticate the normal user.
      if (!username.Equals ("admin"))
        return this.bmw_.AuthenticateUser (username, password);

      // Authenticate the adminstrator.
      return password.Equals (this.admin_password_);
    }

    public override bool DeleteUser (string username, bool deleteAllRelatedData)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override string Description
    {
      get
      {
        return "Membership provider for the CUTS Benchmark Manager Web Utility";
      }
    }

    public override MembershipUserCollection GetAllUsers (int pageIndex, int pageSize, out int totalRecords)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override MembershipUser GetUser (string username, bool userIsOnline)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override bool UnlockUser (string userName)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override string GetPassword (string username, string answer)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override MembershipUserCollection FindUsersByName (string usernameToMatch, int pageIndex, int pageSize, out int totalRecords)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override string GetUserNameByEmail (string email)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override void UpdateUser (MembershipUser user)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override int GetNumberOfUsersOnline ()
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override MembershipUserCollection FindUsersByEmail (string emailToMatch, int pageIndex, int pageSize, out int totalRecords)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override MembershipUser GetUser (object providerUserKey, bool userIsOnline)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    protected override byte[] EncryptPassword (byte[] password)
    {
      return base.EncryptPassword (password);
    }

    protected override byte[] DecryptPassword (byte[] encodedPassword)
    {
      return base.DecryptPassword (encodedPassword);
    }

    public override bool ChangePassword (string username, string oldPassword, string newPassword)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override bool ChangePasswordQuestionAndAnswer (string username, string password, string newPasswordQuestion, string newPasswordAnswer)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override MembershipUser CreateUser (string username, string password, string email, string passwordQuestion, string passwordAnswer, bool isApproved, object providerUserKey, out MembershipCreateStatus status)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override string ResetPassword (string username, string answer)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    private string appname_;

    private string admin_password_ = String.Empty;

    private CUTS.BMW.Database bmw_ = new CUTS.BMW.Database ();
  }
}
