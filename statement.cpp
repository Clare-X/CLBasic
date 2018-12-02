/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"

#include "../StanfordCPPLib/strlib.h"
using namespace std;
bool isKey(string x)
{
        return (x=="LET"||x=="IF"||x=="INPUT"||x=="PRINT"||x=="RUN"||x=="END"||x=="GOTO"||x=="CLEAR"||x=="REM"||x=="LIST"||x=="QUIT");
}
/* Implementation of the Statement class */
Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

 StatementType Statement::getStatementType()
{return NUL;}

void Statement::execute(EvalState & state){}

Inputstate::Inputstate(TokenScanner &input)
{
	identif=input.nextToken();
	if (isKey(identif))error("SYNTAX ERROR");
	if (input.hasMoreTokens()) error("SYNTAX ERROR");
}
Inputstate::~Inputstate() = default;

void Inputstate::execute(EvalState & state)
{
	string temp;bool flag=true;
    int x;
	while (flag)
	{
        getline(std::cin,temp);
        flag=false;
        try{printf(" ? ");x=stringToInteger(temp);}
        catch (...) {
         cout << "INVALID NUMBER" << endl;flag=true;
        }
    }
    state.setValue(identif,x);
}
StatementType  Inputstate::getStatementType()
{
 return INPUT;
}



Printstate::Printstate(TokenScanner &input)
{
	exp = parseExp(input);
}
Printstate::~Printstate() {delete exp;}

void Printstate::execute(EvalState & state)
{
	int value = exp->eval(state);
	std::cout<<value<<std::endl;
}
StatementType  Printstate::getStatementType()
{
	return PRINT;
}


Letstate::Letstate(TokenScanner &input)
{
//while (input.hasMoreTokens())std::cout<<input.nextToken();
    x=input.nextToken();
    if (isKey(x))error("SYNTAX ERROR");
    input.nextToken();
	exp = parseExp(input);
}
Letstate::~Letstate() {delete exp;}

void Letstate::execute(EvalState & state)
{
	state.setValue(x,exp->eval(state));
}
StatementType  Letstate::getStatementType()
{
	return LET;
}


Remstate::Remstate(TokenScanner &Rem){}

Remstate::~Remstate() = default;

void Remstate::execute(EvalState & state){}

StatementType  Remstate::getStatementType()
{
	return REM;
}


Endstate::Endstate(TokenScanner &End){}

Endstate::~Endstate() = default;

void Endstate::execute(EvalState & state){}

StatementType  Endstate::getStatementType()
{
	return END;
}


Gotostate::Gotostate(TokenScanner &Goto)
{
	targetline=stringToInteger(Goto.nextToken());
	if (Goto.hasMoreTokens()) error("LINE NUMBER ERROR");
}
Gotostate::~Gotostate() = default;

void Gotostate::execute(EvalState & state)
{
	state.setValue("_DefaultLineJump",targetline);
}
StatementType  Gotostate::getStatementType()
{
	return GOTO;
}


Ifstate::Ifstate(TokenScanner &If)
{
	exp1=readE(If,1);
	cop=If.nextToken();
	exp2=readE(If,1);
	If.nextToken();
	targetline=stringToInteger(If.nextToken());
}
Ifstate::~Ifstate() {delete exp1;delete exp2;}

void Ifstate::execute(EvalState & state)
{
	if ((cop=="=")&&(exp1->eval(state)==exp2->eval(state)))
	{state.setValue("_DefaultLineJump",targetline);return;}
	if ((cop==">")&&(exp1->eval(state)>exp2->eval(state)))
	{state.setValue("_DefaultLineJump",targetline);return;}
	if ((cop=="<")&&(exp1->eval(state)<exp2->eval(state)))
	{state.setValue("_DefaultLineJump",targetline);return;}
}
StatementType  Ifstate::getStatementType()
{
	return IF;
}

