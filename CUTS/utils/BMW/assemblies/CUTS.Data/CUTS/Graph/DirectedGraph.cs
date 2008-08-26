// -*- C# -*-

//=============================================================================
/**
 * @file          DirectedGraph.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System.Collections;

namespace CUTS.Graph
{
  /**
   * @class DirectedGraph
   *
   * Implementation of a directed graph.
   */
  public class DirectedGraph
  {
    /**
     * Default constructor.
     */
    public DirectedGraph ()
    {

    }

    /**
     * Insert a new node into the graph.
     *
     * @retval      true        Successfully inserted new node
     * @retval      false       Failed to insert new node
     */
    public bool insert_node (Node node)
    {
      if (!this.nodes_.ContainsKey (node.name))
      {
        this.nodes_.Add (node.name, node);
        return true;
      }
      else
        return false;
    }

    /**
     * Create a new edget in the graph between the two nodes.
     *
     * @param[in]       source        Source node.
     * @param[in]       target        Target node.
     */
    public DirectedEdge create_edge (string source, string target)
    {
      // Create a new edge. Right now, we make the assumption that the
      // nodes already exist in the graph.
      Node source_node = (Node)this.nodes_[source];
      Node target_node = (Node)this.nodes_[target];

      DirectedEdge edge = new DirectedEdge (source_node, target_node);

      // Inert the edge into the graph.
      this.edges_.Insert (0, edge);

      // Return the new edge.
      return edge;
    }

    /**
     * Collection of nodes that are in the graph.
     */
    public Node[] nodes
    {
      get
      {
        ArrayList nodes = new ArrayList (this.nodes_.Values);
        return (Node[])nodes.ToArray (typeof (Node));
      }
    }

    /**
     * Collection of edges that are in the graph.
     */
    public DirectedEdge[] edges
    {
      get
      {
        return (DirectedEdge[])this.edges_.ToArray (typeof (DirectedEdge));
      }
    }

    public Node node (string name)
    {
      return (Node)this.nodes_[name];
    }

    /**
     * Edges in the graph.
     */
    private ArrayList edges_ = new ArrayList ();

    /**
     * Nodes in the graph stored by their name.
     */
    private Hashtable nodes_ = new Hashtable ();
  }
}
