using System;
using System.Collections;
using System.Data;
using System.Configuration;
using System.Web;
using System.Text;

namespace cuts
{
  /**
   * @class Visitor
   * @brief base class for all visitors to all classes that derive
   *        from Component_Node
   * @author James Edmondson
   */

  public class Visitor
  {
    /// need to override these in subclasses
    /// visit function - prints Leaf_Negate_Node contents to std::cout

    public virtual void visit(Component_Node node) { }
    public virtual void visit(Leaf_Node node) { }
    public virtual void visit(Composite_Negate_Node node) { }
    public virtual void visit(Composite_Add_Node node) { }
    public virtual void visit(Composite_Subtract_Node node) { }
    public virtual void visit(Composite_Divide_Node node) { }
    public virtual void visit(Composite_Multiply_Node node) { }
  }


  /**
   * @class Print_Visitor
   * @brief This class serves as a visitor for printing Node items to std::cout
   */

  public class Print_Visitor : Visitor
  {
    /// visit function - prints Leaf_Negate_Node contents to std::cout

    public override void visit(Component_Node node)
    {
      node.accept(this);
    }

    /// visit function - prints Leaf_Negate_Node contents to std::cout

    public override void visit(Leaf_Node node)
    {
      System.Console.Write(node.item());
    }

    /// visit function - prints Composite_Negate_Node contents to std::cout

    public override void visit(Composite_Negate_Node node)
    {
      System.Console.Write('-');
    }

    /// visit function - prints Composite_Add_Node contents to std::cout

    public override void visit(Composite_Add_Node node)
    {
      System.Console.Write('+');
    }

    /// visit function - prints Composite_Subtract_Node contents to std::cout

    public override void visit(Composite_Subtract_Node node)
    {
      System.Console.Write('-');
    }

    /// visit function - prints Composite_Divide_Node contents to std::cout

    public override void visit(Composite_Divide_Node node)
    {
      System.Console.Write('/');
    }

    /// visit function - prints Composite_Multiply_Node contents to std::cout

    public override void visit(Composite_Multiply_Node node)
    {
      System.Console.Write('*');
    }
  }


  /**
   * @class Evaluation_Visitor
   * @brief This class serves as a visitor for evaluating
   *        nodes in an expression tree that is being iterated
   *        in post order fashion. This does not work correctly
   *        with any other iterator.
   * @author James Edmondson
   */

  public class Evaluation_Visitor : Visitor
  {
    public Evaluation_Visitor()
    {
      stack_ = new Stack();
    }

    /// visit function - prints Leaf_Negate_Node contents to std::cout

    public override void visit(Component_Node node)
    {
      node.accept(this);
    }

    /// base evaluation for a node. This is used by Leaf_Node
    public override void visit(Leaf_Node node)
    {
      stack_.Push(node.item());
      // std::cout << "current top: " << stack_.top () << std::endl;
    }

    /// evaluation of a negation (Composite_Negate_Node)
    public override void visit(Composite_Negate_Node node)
    {
      if (stack_.Count >= 1)
        stack_.Push(-(Int32)stack_.Pop());
      //std::cout << "current top (after negation): " << stack_.top () << std::endl;
    }

    /// evaluation of an addition (Composite_Add_Node)
    public override void visit(Composite_Add_Node node)
    {
      if (stack_.Count >= 2)
        stack_.Push((Int32)stack_.Pop() + (Int32)stack_.Pop());
      // std::cout << "add current top: " << stack_.top () << std::endl;
    }

    /// evaluation of an addition (Composite_Subtract_Node)
    public override void visit(Composite_Subtract_Node node)
    {
      if (stack_.Count >= 2)
      {
        Int32 rhs = (Int32)stack_.Pop();
        stack_.Push((Int32)stack_.Pop() - rhs);
      }
    }

    /// evaluations of a division (Composite_Divide_Node)
    public override void visit(Composite_Divide_Node node)
    {
      if (stack_.Count >= 2 && (Int32)stack_.Peek() != 0)
      {
        Int32 rhs = (Int32)stack_.Pop();
        stack_.Push((Int32)stack_.Pop() / rhs);
      }
      else
      {
        System.Console.Write("\n\n**ERROR**: Division by zero is not allowed. ");
        System.Console.Write("Resetting evaluation visitor.\n\n");
        reset();
      }
    }

    /// evaluations of a division (Composite_Multiply_Node)
    public override void visit(Composite_Multiply_Node node)
    {
      if (stack_.Count >= 2)
        stack_.Push((Int32)stack_.Pop() * (Int32)stack_.Pop());
      // std::cout << "current top: " << stack_.top () << std::endl;
    }

    /// print a total for the evaluation
    public int result()
    {
      if (stack_.Count != 0)
        return (Int32)stack_.Peek();
      else
        return 0;
    }

    /// reset the evaluation
    public void reset()
    {
      stack_.Clear();
    }

    private Stack stack_;
  }

  /**
   * @class Evaluation_Visitor
   * @brief This class serves as a visitor for evaluating
   *        nodes in an expression tree that is being iterated
   *        in post order fashion. This does not work correctly
   *        with any other iterator.
   * @author James Edmondson
   */

  public class Append_Visitor : Visitor
  {
    public Append_Visitor()
    {
      string_ = new StringBuilder();
    }

    /// visit function - prints Leaf_Negate_Node contents to std::cout

    public override void visit(Component_Node node)
    {
      node.accept(this);
    }

    /// base evaluation for a node. This is used by Leaf_Node
    public override void visit(Leaf_Node node)
    {
      string_.Append(node.item() + " ");
    }

    /// evaluation of a negation (Composite_Negate_Node)
    public override void visit(Composite_Negate_Node node)
    {
      string_.Append("-");
    }

    /// evaluation of an addition (Composite_Add_Node)
    public override void visit(Composite_Add_Node node)
    {
      string_.Append("+ ");
    }

    /// evaluation of an addition (Composite_Subtract_Node)
    public override void visit(Composite_Subtract_Node node)
    {
      string_.Append("- ");
    }

    /// evaluations of a division (Composite_Divide_Node)
    public override void visit(Composite_Divide_Node node)
    {
      string_.Append("/ ");
    }

    /// evaluations of a division (Composite_Multiply_Node)
    public override void visit(Composite_Multiply_Node node)
    {
      string_.Append("* ");
    }

    /// print a total for the evaluation
    public String result()
    {
      return string_.ToString();
    }

    /// reset the evaluation
    public void reset()
    {
      string_.Remove(0, string_.Length);
    }

    private StringBuilder string_;
  }

}
