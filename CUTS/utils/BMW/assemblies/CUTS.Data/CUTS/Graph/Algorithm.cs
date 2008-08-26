// -*- C# -*-

//=============================================================================
/**
 * @file          Algorithm.cs
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

using System;
using System.Collections;

namespace CUTS.Graph
{
  public class Algorithm
  {
    /**
     * Topologically sort a single connected graph.
     *
     * @param[in]           graph           Source graph to sort
     * @return              Nodes of graph in topological order.
     */
    public static Node[] topological_sort (DirectedGraph graph)
    {
      // The list for storing the nodes.
      ArrayList sort_list = new ArrayList ();

      // Sort the graph based on the edges. We are making the assumption
      // the graph is acyclic and connected.
      topological_sort_i (graph.edges, ref sort_list);

      return (Node [])sort_list.ToArray (typeof (Node));
    }

    /**
     * Implementation/helper method for the topological sort.er.
     */
    private static void topological_sort_i (DirectedEdge[] edges,
                                            ref ArrayList current)
    {
      ArrayList unresolved = new ArrayList ();

      foreach (DirectedEdge edge in edges)
      {
        Node source = edge.source;
        Node target = edge.target;

        if (current.Count > 0)
        {
          // Get the indices of the source and target node.
          int source_index = current.IndexOf (source);
          int target_index = current.IndexOf (target);

          if (source_index == -1 && target_index == -1)
          {
            // Ok, we have not encountered any of these nodes neighbors
            // in the graph. So, let's safe this edge for another pass.
            unresolved.Insert (0, edge);
          }
          else if (source_index == -1)
          {
            // Place the source node after the target node.
            current.Insert (target_index + 1, source);
          }
          else if (target_index == -1)
          {
            // Place the target node before the source node.
            current.Insert (source_index, target);
          }
          else if (target_index >= source_index)
          {
            // The graph must be acyclic in order to apply this sort.
            throw new Exception ("graph is not acyclic");
          }
        }
        else
        {
          // Initialize the current sort list.
          current.Insert (0, target);
          current.Insert (1, source);
        }
      }

      // Ok, let's make sure we dont' have any unresolved edges, or
      // nodes, in the graph.
      if (unresolved.Count > 0)
      {
        DirectedEdge [] temp =
          (DirectedEdge [])unresolved.ToArray (typeof (DirectedEdge));

        topological_sort_i (temp, ref current);
      }
    }
  }
}
