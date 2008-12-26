// -*- C# -*-

//=============================================================================
/**
 * @file        Database.cs
 *
 * $Id$
 *
 * @author      James H. Hill <j dot hill at vanderbilt dot edu>
 */
//=============================================================================

using System;

namespace CUTS.BMW
{
  /**
   * @class NewUserProfile
   *
   * Profile for the new user. This must be completed in order to create
   * a new user in the database.
   */
  public class NewUserProfile
  {
    public string Username
    {
      set
      {
        this.username_ = value;
      }

      get
      {
        return this.username_;
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

    public string EmailAddress
    {
      get
      {
        return this.email_;
      }

      set
      {
        this.email_ = value;
      }
    }

    /**
     * Username of the new user
     */
    private string username_;

    /**
     * Password for the new user
     */
    private string password_;

    /**
     * Email address of the new user
     */
    private string email_;
  }
}
