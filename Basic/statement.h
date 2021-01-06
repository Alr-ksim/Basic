/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

//enum StateType { REM, LET, INPUT, PRINT, END, GOTO, IF, THEN };

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute(EvalState & state) = 0;

};

class REM: public Statement {
  public:
    REM(string rem):Rem(rem) {};

    ~REM() {};

    void execute(EvalState & state){
      printf("\n//%s\n",Rem);
      return;
    }

  private:
    string Rem;
};

class LET: public Statement {
  public:
    LET(Expression *exp): Exp(exp) {};

    ~LET(){
      delete Exp;
    }

    void execute(EvalState & state){
      value = Exp->eval(state);
    }

  private:
    Expression *Exp;
    int value;
};

class INPUT: public Statement {
  public:
    INPUT(string xx):x(xx){};

    ~INPUT() = default;

    void execute(EvalState & state){
      int tem;
      scanf("%d",&tem);
      state.setValue(x,tem);
    };

  private:
    string x;
};

class PRINT: public Statement {
  public:
    PRINT(Expression *exp): Exp(exp) {};

    ~PRINT(){
      delete Exp;
    }

    void execute(EvalState & state){
      value = Exp->eval(state);
      printf("%d\n",value);
    }

  private:
    Expression *Exp;
    int value;
};

class END: public Statement {
  public:
    END(bool & Endflag){
      Endflag = 1;
    }

    ~END(){}

    void execute(EvalState & state){}
};

class GOTO: public Statement {
  public:
    GOTO(Expression *exp, int *Setflag):Exp(exp),Sfg(Setflag) {}

    ~GOTO(){}

    void execute(EvalState & state){
      int lineNumber = Exp->eval(state);
      *Sfg = lineNumber;
    }

  private:
    Expression *Exp;
    int *Sfg;
};

class IF: public Statement {
  public:
    IF(Expression *exp,Expression *exps, int *Setflag)
    :Exp(exp),Exps(exps),Sfg(Setflag) {}

    ~IF(){}

    void execute(EvalState & state){
      if (Exp->eval(state)) *Sfg = Exps->eval(state);
      else *Sfg = 0;
    }
  
  private:
    Expression *Exp,*Exps;
    int *Sfg;
};

class CLEAR: public Statement {
  public:
    CLEAR(bool & flag){
      flag = 1;
    }

    ~CLEAR(){}

    void execute(EvalState & state){}
};

class RUN: public Statement {
  public:
    RUN(bool & flag){
      flag = 1;
    }

    ~RUN(){}

    void execute(EvalState & state){}
};

class LIST: public Statement {
  public:
    LIST(bool & flag){
      flag = 1;
    }

    ~LIST(){}

    void execute(EvalState & state){}
};

class HELP: public Statement {
  public:
    HELP(bool & flag){
      flag = 1;
    }

    ~HELP(){}

    void execute(EvalState & state){}
};
/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

#endif
