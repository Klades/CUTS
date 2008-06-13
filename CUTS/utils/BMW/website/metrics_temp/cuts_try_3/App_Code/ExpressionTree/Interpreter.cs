using System;
using System.Collections;
using System.Data;
using System.Configuration;
using System.Web;

namespace edu.vanderbilt.Trees
{


  /**
   * @class Interpreter_Context
   * @brief Stores variables for later usage
   * @author James Edmondson
   */

  class Interpreter_Context : DictionaryBase
  {

    /// constructor
    public Interpreter_Context ()
      {
      }

    public Int32 this[String key]
      {
        get
          {
            return  (Int32)Dictionary[key];
          }
        set
          {
            Dictionary[key] = value;
          }
      }


    public ICollection Keys
      {
        get
          {
            return Dictionary.Keys;
          }
      }

    public ICollection Values
      {
        get
          {
            return Dictionary.Values;
          }
      }

    public bool Contains (String key)
      {
        return Dictionary.Contains (key);
      }


    /// return the value of a variable
    public Int32 get (String variable)
      {
        return  (Int32)Dictionary[variable];
      }

    // set the value of a variable
    public void set (String variable, Int32 value)
      {
        Dictionary[variable] = value;
      }

    /// print all variables and their values
    public void print ()
      {
        foreach  (DictionaryEntry myDE in this)
          Console.WriteLine (myDE.Key + " = " + myDE.Value);
      }

    // clear all variables and their values
    public void reset ()
      {
        Dictionary.Clear ();
      }
  }

  /**
   * @class Symbol
   * @brief Abstract base class of all parse tree nodes
   * @author James Edmondson
   */

  class Symbol
  {

    /// constructor
    public Symbol ()
      {
      }

    /// constructor
    public Symbol (Symbol left, Symbol right)
      {
        left_ = left;
        right_ = right;
      }

    /// abstract method for returning precedence level  (higher
    /// value means higher precedence
    public virtual int precedence ()
      {
        return 0;
      }

    /// abstract method for building an Expression Expression_Tree Node

    public virtual Component_Node build ()
      {
        return new Composite_Null ();
      }

    /// left and right pointers

    public Symbol left_;
    public Symbol right_;
  }

  /**
   * @class Null
   * @brief Null pattern for checking for null references
   * @author James Edmondson
   * @see   Add, Subtract, Multiply, Divide
   */

  class Null : Symbol
  {
    public Null ()
      {
      }
  }

  /**
   * @class Operator
   * @brief Abstract base class for all parse tree node operators
   * @author James Edmondson
   * @see   Add, Subtract, Multiply, Divide
   */

  class Operator : Symbol
  {
    /// constructor
    public Operator (Symbol left, Symbol right)
      : base (left, right)
      {
      }
  }

  /**
   * @class Operator
   * @brief Abstract base class for all parse tree node operators
   * @author James Edmondson
   * @see   Add, Subtract, Multiply, Divide
   */

  class Unary_Operator : Symbol
  {
    // constructor
    public Unary_Operator (Symbol right)
      : base (new Null (), right)
      {
      }
  }

  /**
   * @class Number
   * @brief Leaf node of parse tree
   * @author James Edmondson
   */

  class Number : Symbol
  {
    // constructor
    public Number (String input)
      : base (new Null (), new Null ())
      {
        item_ = System.Convert.ToInt32 (input, 10);
      }

    // constructor
    public Number (int input)
      : base (new Null (), new Null ())
      {
        item_ = input;
      }

    // returns the precedence level
    public override int precedence ()
      {
        return 4;
      }

    // builds an equivalent Expression_Tree node
    public override Component_Node build ()
      {
        return new Leaf_Node (item_);
      }

    /// contains the value of the leaf node
    private int item_;
  }

  /**
   * @class Subtract
   * @brief Subtraction node of the parse tree
   * @author James Edmondson
   */

  class Subtract : Operator
  {
    // constructor
    public Subtract ()
      : base (new Null (), new Null ())
      {
      }

    // returns the precedence level
    public override int precedence ()
      {
        return 1;
      }

    // builds an equivalent Expression_Tree node
    public override Component_Node build ()
      {
        return new Composite_Subtract_Node (left_.build (), right_.build ());
      }

  }

  /**
   * @class Add
   * @brief Addition node of the parse tree
   * @author James Edmondson
   */

  class Add : Operator
  {
    // constructor
    public Add ()
      : base (new Null (), new Null ())
      {
      }

    // returns the precedence level
    public override int precedence ()
      {
        return 1;
      }

    // builds an equivalent Expression_Tree node
    public override Component_Node build ()
      {
        return new Composite_Add_Node (left_.build (), right_.build ());
      }
  }

  /**
   * @class Negate
   * @brief Negate node of the parse tree
   * @author James Edmondson
   */

  class Negate : Unary_Operator
  {

    // constructor
    public Negate ()
      : base (new Null ())
      {
      }

    // returns the precedence level
    public override int precedence ()
      {
        return 3;
      }

    // builds an equivalent Expression_Tree node
    public override Component_Node build ()
      {
        return new Composite_Negate_Node (right_.build ());
      }

  }

  /**
   * @class Multiply
   * @brief Multiplication node of the parse tree
   * @author James Edmondson
   */

  class Multiply : Operator
  {
    // constructor
    public Multiply ()
      : base (new Null (), new Null ())
      {
      }

    // returns the precedence level
    public override int precedence ()
      {
        return 2;
      }

    // builds an equivalent Expression_Tree node
    public override Component_Node build ()
      {
        return new Composite_Multiply_Node (left_.build (), right_.build ());
      }
  }

  /**
   * @class Divide
   * @brief Division node of the parse tree
   * @author James Edmondson
   */

  class Divide : Operator
  {
    // constructor
    public Divide ()
      : base (new Null (), new Null ())
      {
      }


    // returns the precedence level
    public override int precedence ()
      {
        return 2;
      }

    // builds an equivalent Expression_Tree node
    public override Component_Node build ()
      {
        return new Composite_Divide_Node (left_.build (), right_.build ());
      }
  }

  /**
   * @class In_Order_Interpreter
   * @brief Parses incoming expression strings into a parse tree and
   *        can generate an expression tree from the parse tree.
   * @author James Edmondson
   */

  class Interpreter
  {
    /// constructor
    public Interpreter ()
      {
        stack_ = new Stack ();
      }

    /// Converts a string and context into a parse tree, and builds an
    /// expression tree out of the parse tree.
    public Expression_Tree interpret (ref Interpreter_Context context,
                 String input)
      {
        stack_.Clear ();
        char lastValidInput = '\0';

        for  (Int32 i = 0;
           i < input.Length; ++i)
          {
            if  (is_alphanumeric (input[i]))
              {
                // we either have a variable or a static number
                if  (variableLength (input, i) > numberLength (input, i))
                  variable_insert (ref context, input, ref i);
                else
                  number_insert (input, ref i);
              }
            else if  (input[i] == '+')
              {
                // addition operation
                Add op = new Add ();

                // insert the op according to left-to-right relationships
                associative_insert (op);
              }
            else if  (input[i] == '-')
              {
                if  (lastValidInput == 0 || is_operator (lastValidInput))
                  {
                    // negation operation
                    Negate op = new Negate ();

                    // insert the op according to precedence relationships
                    precedence_insert (op);
                  }
                else
                  {
                    // subtraction operation
                    Subtract op = new Subtract ();

                    // insert the op according to left-to-right relationships
                    associative_insert (op);
                  }
              }
            else if  (input[i] == '*')
              {
                // multiplication operation
                Multiply op = new Multiply ();

                // insert the op according to precedence relationships
                precedence_insert (op);
              }
            else if  (input[i] == '/')
              {
                // division operation
                Divide op = new Divide ();

                // insert the op according to precedence relationships
                precedence_insert (op);
              }
            else if  (input[i] == ' ' || input[i] == '\n')
              {
                // skip whitespace
              }
            else
              {
                // user entered unrecognized character.

                System.Console.WriteLine ("\n\nUnknown char in parse. Parse aborted. char = " +
                  input[i]);
              }

            // store last valid input symbol. this is useful to the '-' operator
            // and will help us determine if '-' is a subtraction or a negation
            if  (input[i] != ' ' && input[i] != '\n')
              lastValidInput = input[i];
          }

        // if the list has an element in it, then return the back of the list.
        if  (stack_.Count != 0)
          {
            // Invoke a recursive Expression_Tree build starting with the root
            // symbol. This is an example of the builder pattern. See pg 97
            // in GoF book.
            Symbol symbol =  (Symbol)stack_.Peek ();

            Expression_Tree tree = new Expression_Tree (symbol.build ());
            return tree;
          }

        // If we reach this, we didn't have any symbols.
        return new Expression_Tree ();
      }

    /// method for checking if a character is a valid operator
    public static bool is_operator (char input)
      {
        return input == '+'
        || input == '-'
        || input == '*'
        || input == '/';
      }

    /// method for checking if a character is a number
    public static bool is_number (char input)
      {
        return input >= '0' && input <= '9';
      }

    /// method for checking if a character is a candidate
    /// for a part of a variable name
    public static bool is_alphanumeric (char input)
      {
        return  (input >= 'a' && input <= 'z')
        ||  (input >= 'A' && input <= 'Z')
        ||  (input == '_') ||  (input == '.') ||  (input == '$') 
        ||  (input >= '0' && input <= '9');
      }

    /// returns length of number from current position
    /// 
    public static Int32 numberLength (String input, Int32 i)
      {
        Int32 j = 0;

        for  (; i + j < input.Length && is_number (input[i + j]); ++j)
          continue;

        return j;
      }

    /// returns length of variable from current position
    /// 
    public static Int32 variableLength (String input, Int32 i)
      {
        Int32 j = 0;

        for  (; i + j < input.Length && is_alphanumeric (input[i + j]); ++j)
          continue;

        return j;
      }

    /// inserts a terminal into the parse tree
    private void terminal_insert (Symbol op)
      {
        if  (stack_.Count != 0)
          {
            // Something exists in the list, so make this number the rightmost child

            Symbol symbol =  (Symbol)stack_.Peek ();

            if  (symbol.GetType () != typeof (Null))
              {
                // while there is a right child, continue down
                for  (; symbol.right_.GetType () != typeof (Null); symbol = symbol.right_)
                  continue;

                // symbol right will be this terminal and that's all we have
                // to do.
                symbol.right_ = op;
              }
          }
        else
          // a number appeared first
          stack_.Push (op);
      }

    /// inserts a variable  (leaf node / number) into the parse tree
    private void variable_insert (ref Interpreter_Context context,
              String input,
              ref Int32 i)
      {
        // merge all consecutive number chars into a single
        // Number symbol, eg '123' = int  (123). Scope of j needs
        // to be outside of the for loop.

        Int32 j = 1;

        for  (; i + j < input.Length && is_alphanumeric (input[i + j]); ++j)
          continue;

        // lookup the variable in the context

        int value = context.get (input.Substring (i, j));

        // make a Number out of the integer

        Number number = new Number (value);

        // update i to the last character that was a number. the ++i will
        // update the i at the end of the loop to the next check.

        i += j - 1;

        terminal_insert (number);
      }

    /// inserts a leaf node / number into the parse tree
    private void number_insert (String input,
              ref Int32 i)
      {
        // merge all consecutive number chars into a single Number symbol,
        // eg '123' = int  (123). Scope of j needs to be outside of the for
        // loop.

        Int32 j = 1;

        for  (; i + j <= input.Length && is_number (input[i + j]); ++j)
          continue;

        Number number = new Number (input.Substring (i, j));

        // update i to the last character that was a number. the ++i will
        // update the i at the end of the loop to the next check.

        i += j - 1;

        terminal_insert (number);
      }

    /// inserts an addition or subtraction into the parse tree
    private void associative_insert (Symbol op)
      {
        if  (stack_.Count != 0)
          {
            // if last element was a number, then make that our left_

            op.left_ =  (Symbol)stack_.Peek ();

            // now push the add on the list

            stack_.Pop ();
            stack_.Push (op);
          }
        else
          {
            // we have an associative operation. Assume something like an
            // input of "+5-3" or "-3+5". Add a left number of 0 to make
            // everything kosher.

            op.left_ = new Number (0);
            stack_.Push (op);
          }
      }

    /// inserts a multiplication or division into the parse tree
    private void precedence_insert (Symbol op)
      {
        if  (stack_.Count != 0)
          {
            // if last element was a number, then make that our left_

            Symbol parent =  (Symbol)stack_.Peek ();
            Symbol child = parent.right_;

            if  (parent.precedence () < op.precedence ())
              {
                if  (child.GetType () != typeof (Null))
                  {
                    // while there is a child of parent, keep going down the right side
                    for  (;
                     child.GetType () != typeof (Null) && child.precedence () < op.precedence ();
                     child = child.right_)
                      parent = child;
                  }

                // op left will be the old child. new parent child will be
                // the op. To allow infinite negations, we have to check for unary_operator.

                if  (op.GetType () == typeof (Negate))
                  op.right_ = child;
                else
                  op.left_ = child;

                parent.right_ = op;
              }
            else
              {
                // if child is null, then simply set op->left to parent. if
                // the syntax was correct, this only happens if this
                // operation is the first one of the input string. Parent
                // should be a number.

                op.left_ = parent;
                stack_.Pop ();
                stack_.Push (op);
              }
          }
        else
          {
            // Divide before any type of Number or anything? This should be
            // a syntax error. We'll just make a zero in front so the
            // multiply == 0. Eh.
            op.left_ = new Number (0);
            stack_.Push (op);
          }
      }

    /// stores the parse tree. isn't entirely necessary right now, but
    /// is kept as a list for future expansion  (parentheses)
    private Stack stack_;
  }

}