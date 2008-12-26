// -*- C# -*-

using System;
using System.Collections;
using System.Collections.Generic;
using System.Web.Security;

namespace CUTS.BMW.Security
{
  /**
   * @class RoleProvider
   */
  public class RoleProvider : System.Web.Security.RoleProvider
  {
    public RoleProvider ()
    {

    }

    public override void AddUsersToRoles (string[] usernames, string[] roleNames)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override string ApplicationName
    {
      get
      {
        throw new System.Exception ("The method or operation is not implemented.");
      }
      set
      {
        throw new System.Exception ("The method or operation is not implemented.");
      }
    }

    public override void CreateRole (string roleName)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override bool DeleteRole (string roleName, bool throwOnPopulatedRole)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override string Description
    {
      get
      {
        return base.Description;
      }
    }

    public override string[] FindUsersInRole (string roleName, string usernameToMatch)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override string[] GetAllRoles ()
    {
      List<string> roles = new List<string> ();

      roles.Add ("User");
      roles.Add ("Administrator");

      return roles.ToArray ();
    }

    public override string[] GetRolesForUser (string username)
    {
      List<string> roles = new List<string> ();

      if (!username.Equals ("admin"))
        roles.Add ("User");
      else
        roles.Add ("Administrator");

      return roles.ToArray ();
    }

    public override string[] GetUsersInRole (string roleName)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override bool IsUserInRole (string username, string roleName)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override string Name
    {
      get
      {
        return base.Name;
      }
    }

    public override void Initialize (string name, System.Collections.Specialized.NameValueCollection config)
    {
      base.Initialize (name, config);
    }

    public override void RemoveUsersFromRoles (string[] usernames, string[] roleNames)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }

    public override bool RoleExists (string roleName)
    {
      throw new System.Exception ("The method or operation is not implemented.");
    }
  }
}
