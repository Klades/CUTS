using System;
using System.Collections;
using System.Data;
using System.Configuration;
using System.Web;



namespace cuts
{
  /**
   * @class In_Order_Expression_Tree_Iterator
   * @brief This class is meant to iterate a binary tree in order
   * @author James Edmondson
   */

  public class In_Order_Expression_Tree_Iterator
  {

    /// Construct an Post_Order_Expression_Tree_Iterator. If end_iter is set to true,
    /// the iterator points to the end of the tree

    public In_Order_Expression_Tree_Iterator(Expression_Tree tree)
    {
      stack_ = new Stack();
      root_ = tree.get_root();
      // if the caller doesn't want an end iterator, insert the root tree
      // into the queue.
      if (tree.get_root().GetType() != typeof(Composite_Null))
      {
        Component_Node current = root_;

        // while current is not null, push current and then set current to its left child
        while (current.GetType() != typeof(Composite_Null))
        {
          stack_.Push(current);
          current = current.left();
        }
      }
    }

    /// Helper function to advance the iterator by manipulating the queue

    private void advance()
    {
      // we know that at this point there is no left () of top ()
      // because we would have already visited it.

      if (!done())
      {
        //if (!stack_.is_empty())
        if (stack_.Count != 0)
        {

          Component_Node peek = (Component_Node)stack_.Peek();
          // if we have nodes greater than ourselves
          if (peek.right().GetType() != typeof(Composite_Null))
          {
            // push the right child node onto the stack
            // and pop the old parent (it's been visited now)
            stack_.Pop();
            stack_.Push(peek.right());

            peek = peek.right();

            // keep pushing until we get to the left most child
            while (peek.left().GetType() != typeof(Composite_Null))
            {
              stack_.Push(peek.left());
              peek = peek.left();
            }
          }
          else
            stack_.Pop();

        }
      }
    }

    /// Returns the Node that the iterator is pointing to (non-const version)

    public Component_Node value()
    {
      if (!done())
      {
        return (Component_Node)stack_.Peek();
      }
      return new Composite_Null();
    }

    /// moves the iterator to the next node (pre-increment)

    public void next()
    {
      advance();
    }

    /// checks two iterators for equality

    public bool done()
    {
      return stack_.Count == 0 || stack_.Peek().GetType() == typeof(Composite_Null);
    }

    /// Our current position
    private Stack stack_;
    private Component_Node root_;
  }

  /**
   * @class Post_Order_Expression_Tree_Iterator_Impl
   * @brief This class is meant to iterate a binary tree in
   *        post order.
   * @author James Edmondson
   */

  public class Post_Order_Expression_Tree_Iterator
  {

    /// Construct an Post_Order_Expression_Tree_Iterator. If end_iter is set to true,
    /// the iterator points to the end of the tree

    public Post_Order_Expression_Tree_Iterator(Expression_Tree tree)
    {
      stack_ = new Stack();
      root_ = tree.get_root();
      // if the caller doesn't want an end iterator, insert the root tree
      // into the queue.
      if (tree.get_root().GetType() != typeof(Composite_Null))
      {
        Component_Node current = tree.get_root();
        stack_.Push(root_);


        while (current.GetType() != typeof(Composite_Null))
        {
          if (current.right().GetType() != typeof(Composite_Null))
            stack_.Push(current.right());
          if (current.left().GetType() != typeof(Composite_Null))
          {
            // if there was a left, then update current
            // this is the case for all non-negations
            stack_.Push(current.left());
            current = current.left();
          }
          else
          {
            // if there was not a left, then current = current->right_
            // this handles cases of unary nodes, like negations
            current = current.right();
          }
        }
      }
    }

    /// Helper function to advance the iterator by manipulating the queue

    private void advance()
    {
      // we know that at this point there is no left () of top ()
      // because we would have already visited it.

      if (!done())
      {
        // we need to pop the node off the stack before pushing the
        // children, or else we'll revisit this node later

        Component_Node current = (Component_Node)stack_.Pop();

        // This is where stuff gets a little confusing.

        //if (!stack_.is_empty())
        if (stack_.Count != 0)
        {
          Component_Node peek = (Component_Node)stack_.Peek();
          if (peek.left() != current && peek.right() != current)
          {
            current = peek;
            while (current.GetType() != typeof(Composite_Null))
            {
              if (current.right().GetType() != typeof(Composite_Null))
                stack_.Push(current.right());
              if (current.left().GetType() != typeof(Composite_Null))
              {
                // if there was a left, then update current
                // this is the case for all non-negations
                stack_.Push(current.left());
                current = current.left();
              }
              else
              {
                // if there was not a left, then current = current->right_
                // this handles cases of unary nodes, like negations
                current = current.right();
              }
            }
          }
        }
      }
    }

    /// Returns the Node that the iterator is pointing to (non-const version)

    public Component_Node value()
    {
      if (!done())
      {
        return (Component_Node)stack_.Peek();
      }
      return new Composite_Null();
    }

    /// moves the iterator to the next node (pre-increment)

    public void next()
    {
      advance();
    }

    /// checks two iterators for equality

    public bool done()
    {
      return stack_.Count == 0 || stack_.Peek().GetType() == typeof(Composite_Null);
    }

    /// Our current position
    private Stack stack_;
    private Component_Node root_;
  }
}
