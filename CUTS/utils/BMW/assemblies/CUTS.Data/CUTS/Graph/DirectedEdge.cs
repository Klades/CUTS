// -*- C# -*-

//=============================================================================
/**
 * @file        DirectedEdge.cs
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

namespace CUTS.Graph
{
  /**
   * @class DirectedEdge
   *
   * Edge that connects to nodes, and has a direction associated with
   * it. The source is the node where the edge starts. The target is
   * the node where the edge terminates.
   */
  public class DirectedEdge
  {
    /**
     * Initializing constructor. This will set the source and target
     * nodes for this directed edge.
     *
     * @param[in]       source        Source node
     * @param[in]       target        Target node
     */
    public DirectedEdge (Node source, Node target)
    {
      this.source_ = source;
      this.target_ = target;
    }

    public Node source
    {
      get
      {
        return this.source_;
      }
    }

    public Node target
    {
      get
      {
        return target_;
      }
    }

    /**
     * Source node of the edge.
     */
    private Node source_;

    /**
     * Destination node of the edge.
     */
    private Node target_;
  }
}
