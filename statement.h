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
#include "parser.h"
/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter
 */
enum StatementType { NUL,INPUT,PRINT,LET,REM,END,IF,GOTO };

bool isKey(string x);

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

   virtual void execute(EvalState & state);
   virtual StatementType  getStatementType()=0;
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

//要写的class Ifstate gotostate inputstate letstate endstate remstate

/*
 * Implementation notes: the Inputstate subclass
 * ------------------------------------------------
 * The Inputstate subclass declares a statement starts with token input
 * It gets the name of variable and read it when execute.
 */
class Inputstate :public Statement{
private:
	string identif;
public:
	Inputstate(TokenScanner &input);
	~Inputstate();
	void execute(EvalState & state);
	StatementType  getStatementType();
};
/*
 * Implementation notes: the Printstate subclass
 * ------------------------------------------------
 * The Printstate subclass declares a statement starts with token input
 * It gets the needed expression and print it when execute.
 */
class Printstate :public Statement{
private:
	Expression *exp;
public:
	Printstate(TokenScanner &input);
	~Printstate();
	void execute(EvalState & state);
	StatementType  getStatementType();
};
/*
 * Implementation notes: the Printstate subclass
 * ------------------------------------------------
 * The Printstate subclass declares a statement starts with token input
 * It gets the needed expression and print it when execute.
 */
class Letstate :public Statement{
private:
    string x;
	Expression* exp;
public:
	Letstate(TokenScanner &input);
	~Letstate();
	void execute(EvalState & state);
	StatementType  getStatementType();
};
/*
 * Implementation notes: the Remstate subclass
 * ------------------------------------------------
 * The Remstate subclass declares a statement starts with token input
 * It gets the needed expression and Rem it when execute.
 */
class Remstate :public Statement{
public:
	Remstate(TokenScanner &Rem);
	~Remstate();
	void execute(EvalState & state);
	StatementType  getStatementType();
};
/*
 * Implementation notes: the Endstate subclass
 * ------------------------------------------------
 * The Endstate subclass declares a statement starts with token input
 * It gets the needed expression and End it when execute.
 */
class Endstate :public Statement{
public:
	Endstate(TokenScanner &End);
	~Endstate();
	void execute(EvalState & state);
	StatementType  getStatementType();
};
/*
 * Implementation notes: the Ifstate subclass
 * ------------------------------------------------
 * The Ifstate subclass declares a statement starts with token input
 * It gets the needed expression and If it when execute.
 */
class Ifstate :public Statement{
private:
	Expression* exp1;
	Expression* exp2;
	string cop;
	int targetline;
public:
	Ifstate(TokenScanner &If);
	~Ifstate();
	void execute(EvalState & state);
	StatementType  getStatementType();
};
/*
 * Implementation notes: the Gotostate subclass
 * ------------------------------------------------
 * The Gotostate subclass declares a statement starts with token input
 * It gets the needed expression and Goto it when execute.
 */
class Gotostate :public Statement{
private:
	int targetline;
public:
	Gotostate(TokenScanner &Goto);
	~Gotostate();
	void execute(EvalState & state);
	StatementType  getStatementType();
};
#endif
