using System;
using System.Collections;
using System.Data;
using System.Configuration;
using System.Web;


namespace edu.vanderbilt.Trees
{

  /**
   * @class Component_Node
   * @brief An abstract base class defines a simple abstract
   *        implementation of an expression tree node.
   *
   *        This class plays the role of the "Component" in the
   *        Composite pattern.  The methods in this class are not
   *        defined as pure virtual so that subclasses in the Composite
   *        pattern don't have to implement methods they don't care
   *        about.  All the methods  (exception the destructor) throw the
   *        @a std::domain_error exception if called, however.
   * @author James Edmondson
   *        
   * @see   See Composite_Unary_Node and Composite_Binary_Node for nodes
   *        with right only and left and right children, respectively.
   */

  public class Component_Node
  {
    /// Return the item stored in the node  (throws std::domain_error if
    /// called directly).
    public virtual int item ()
      {
        return 0;
      }

    /// Return the left child  (throws std::domain_error
    /// if called directly).
    public virtual Component_Node left ()
      {
        return new Composite_Null ();
      }

    /// Return the right child  (throws std::domain_error
    /// if called directly).
    public virtual Component_Node right ()
      {
        return new Composite_Null ();
      }

    /// Accept a visitor to perform some action on the node's item
    /// completely arbitrary visitor template  (throws std::domain_error
    /// if called directly).
    public virtual void accept (Visitor visitor) { }

  }

  public class Composite_Null : Component_Node
  {
    public override void accept (Visitor visitor)
      {
      }
  }

  /**
   * @class Composite_Unary_Node
   * @brief Defines a right child  (but not a left one) and thus is useful for unary operations.
   * @author James Edmondson
   * @see Composite_Binary_Node
   */

  public abstract class Composite_Unary_Node : Component_Node
  {
    // Ctor

    public Composite_Unary_Node (Component_Node right)
      {
        right_ = right;
      }

    // Return the right child pointer
    public override Component_Node right ()
      {
        return right_;
      }

    /// Right child
    private Component_Node right_;
  }


  /**
   * @class Composite_Binary_Node
   * @brief Defines a left and right node  (via inheritance).
   * @author James Edmondson
   */

  public abstract class Composite_Binary_Node : Composite_Unary_Node
  {
    // Ctor
    public Composite_Binary_Node (Component_Node left,
                                  Component_Node right)
      : base (right)
      {
        left_ = left;
      }

    // Return the left child pointer
    public override Component_Node left ()
      {
        return left_;
      }

    /// left child
    private Component_Node left_;
  }

  public class Leaf_Node : Component_Node
  {
    // Ctor
    public Leaf_Node (int item)
      : base ()
      {
        item_ = item;
      }

    // Ctor
    public Leaf_Node (String item)
      : base ()
      {
        item_ = System.Convert.ToInt32 (item, 10);
      }

    // return the item
    public override int item ()
      {
        return item_;
      }

    public override void accept (Visitor visitor)
      {
        visitor.visit (this);
      }
    /// integer value for maximum mathocity.
    private int item_;
  }

  /**
   * @class Composite_Negate_Node
   * @brief A composite node containing only a right child. 
   *        The meaning of this node is -right, eg -5, -7, etc.
   * @author James Edmondson
   */

  public class Composite_Negate_Node : Composite_Unary_Node
  {
    // Ctor

    public Composite_Negate_Node (Component_Node right)
      : base (right)
      {
      }

    // accept a visitor
    public override void accept (Visitor visitor)
      {
        visitor.visit (this);
      }
  }

  /**
   * @class Composite_Add_Node
   * @brief A composite node containing left and right
   *        children. The meaning of this node is left + right
   * @author James Edmondson
   */
  public class Composite_Add_Node : Composite_Binary_Node
  {
    // Ctor

    public Composite_Add_Node (Component_Node left,
                             Component_Node right)
      : base (left, right)
      {
      }

    // accept a visitor

    public override void accept (Visitor visitor)
      {
        visitor.visit (this);
      }
  }

  /**
   * @class Composite_Subtract_Node
   * @brief A composite node containing left and right
   *        children. The meaning of this node is left - right
   * @author James Edmondson
   */

  public class Composite_Subtract_Node : Composite_Binary_Node
  {
    // Ctor
    public Composite_Subtract_Node (Component_Node left,
                                  Component_Node right)
      : base (left, right)
      {
      }

    // accept a visitor
    public override void accept (Visitor visitor)
      {
        visitor.visit (this);
      }
  }

  /**
   * @class Composite_Multiply_Node
   * @brief A composite node containing left and right
   *        children. The meaning of this node is left * right
   * @author James Edmondson
   */

  public class Composite_Multiply_Node : Composite_Binary_Node
  {
    // Ctor
    public Composite_Multiply_Node (Component_Node left,
                                  Component_Node right)
      : base (left, right)
      {
      }

    // accept a visitor
    public override void accept (Visitor visitor)
      {
        visitor.visit (this);
      }
  }

  /**
   * @class Composite_Divide_Node
   * @brief A composite node containing left and right
   *        children. The meaning of this node is left / right
   * @author James Edmondson
   */

  public class Composite_Divide_Node : Composite_Binary_Node
  {
    // Ctor
    public Composite_Divide_Node (Component_Node left,
                              Component_Node right)
      : base (left, right)
      {
      }

    // accept a visitor
    public override void accept (Visitor visitor)
      {
        visitor.visit (this);
      }
  }

  /**
   * @class Expression_Tree
   * @brief Defines a bridge to the node implementation that
   *        actually contains the data items for the tree.
   * @author James Edmondson
   */

  public class Expression_Tree
  {


    /// Default ctor
    public Expression_Tree ()
      {
        root_ = new Composite_Null ();
      }

    /// Ctor that takes a NODE *.
    public Expression_Tree (Component_Node root)
      {
        root_ = root;
      }

    // Copy ctor
    public Expression_Tree (Expression_Tree t)
      {
        root_ = t.root_;
      }

    /// gain access to the underlying root pointer
    /// functions are useful to the iterators
    public Component_Node get_root ()
      {
        return root_;
      }

    /// Check if tree is null tree.
    public bool is_null ()
      {
        return root_.GetType () == typeof (Composite_Null);
      }

    /// Return the item in the tree.
    public int item ()
      {
        return root_.item ();
      }

    /// Returns a string that is the in order representation of the tree
    public override string ToString ()
      {
        Append_Visitor visitor = new Append_Visitor ();
        In_Order_Expression_Tree_Iterator in_order = new In_Order_Expression_Tree_Iterator (this);

        for (; !in_order.done (); in_order.next ())
          visitor.visit (in_order.value ());

        return visitor.result ();
      }

    /// Evaluates the Express Tree and returns the result
    public Int32 evaluate ()
      {
        Evaluation_Visitor visitor = new Evaluation_Visitor ();
        Post_Order_Expression_Tree_Iterator post_order = new Post_Order_Expression_Tree_Iterator (this);

        for (; !post_order.done (); post_order.next ())
          visitor.visit (post_order.value ());

        return visitor.result ();
      }

    /// Return the left child.
    public Expression_Tree left ()
      {
        return new Expression_Tree (root_.left ());
      }

    /// Return the right child.
    public Expression_Tree right ()
      {
        return new Expression_Tree (root_.right ());
      }

    Component_Node root_;

  }

}
