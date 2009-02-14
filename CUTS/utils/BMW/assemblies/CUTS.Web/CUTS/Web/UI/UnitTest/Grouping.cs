// -*- C# -*-

//=============================================================================
/**
 * @file          Grouping.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System;
using System.Collections;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using CUTS.Data.UnitTesting;

namespace CUTS.Web.UI.UnitTest
{
  /**
   * @class Grouping
   *
   * Custom control for inputing grouping information for a unit
   * test. The user is able to input the group variables as the
   * control will convert the readable text into variable ids.
   */
  public class Grouping : CompositeControl, INamingContainer
  {
    /**
     * Default constructor
     */
    public Grouping ()
    {

    }

    public void Clear ()
    {
      this.EnsureChildControls ();
      this.grouping_.Text = String.Empty;
    }

    /**
     * Ids of the group variables.
     */
    public LogFormatVariable [] Variables
    {
      get
      {
        // Make sure the controls are created.
        this.EnsureChildControls ();

        // Break the string into fully qualified names.
        string separator = ";";
        string[] fq_names =
          this.grouping_.Text.Split (separator.ToCharArray (),
                                     StringSplitOptions.RemoveEmptyEntries);

        Regex regex = new Regex("LF(?<lfid>\\d+)\\.(?<varname>\\S+)");
        LogFormatVariableCollection variables = new LogFormatVariableCollection ();

        // Break the fully qualified names into usable variables.
        foreach (string name in fq_names)
        {
          // Break the string into its log format and variable name.
          Match match = regex.Match (name);
          LogFormatVariable variable;

          if (match.Success)
          {
            variable = new LogFormatVariable ();

            // Extract the tagged information.
            variable.ID = int.Parse (match.Groups["lfid"].Captures[0].Value);
            variable.Name = match.Groups["varname"].Captures[0].Value;

            // Save the variable.
            variables.Add (variable);
          }
        }

        return variables.ToArray ();
      }
    }

    /**
     * Create the child controls for this custom control. This is
     * invoked by the underlying framework.
     */
    protected override void CreateChildControls ()
    {
      // Create the label for the control.
      Label label = new Label ();
      this.Controls.Add (label);

      label.Text = "Group by: ";
      label.CssClass = "title";

      // Insert the text box for inputing the groups.
      this.grouping_ = new TextBox ();
      this.Controls.Add (this.grouping_);

      this.grouping_.Width = this.Width;
    }

    private TextBox grouping_;
  }
}
