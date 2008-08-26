// -*- C# -*-

//=============================================================================
/**
 * @file        Node.cs
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

using System.Collections;

namespace CUTS.Graph
{
  /**
   * @class Node
   *
   * Representation of a node in a graph.
   */
  public class Node
  {
    /**
     * Initializing constructor.
     *
     * @param[in]         name        Name of the node.
     */
    public Node (string name)
    {
      this.name_ = name;
    }

    /**
     * Get the name of the node.
     */
    public string name
    {
      get
      {
        return this.name_;
      }
    }

    /**
     * Get the properties associated with this node.
     */
    public Hashtable properties
    {
      get
      {
        return this.properties_;
      }
    }

    /**
     * Set the value of a property.
     *
     * @param[in]       name        Name of the property.
     * @param[in]       value       Value of the property.
     */
    public void property (string name, object value)
    {
      this.properties_.Add (name, value);
    }

    /**
     * Get the specified property.
     *
     * @param[in]       name        Name of the property.
     */
    public object property (string name)
    {
      return this.properties_[name];
    }

    /**
     * Test if an object equals this node. Two nodes are equal
     * iff they have the same name.
     */
    public override bool Equals (object obj)
    {
      Node node = (Node)obj;
      return this.name_ == node.name_;
    }

    public override int GetHashCode ()
    {
      return base.GetHashCode ();
    }

    /**
     * Unique name assigned to the node.
     */
    private string name_;

    /**
     * Properties associated with this node.
     */
    private Hashtable properties_ = new Hashtable ();
  }
}
