/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;

Program::Program() {
   sentences.clear();
   built.clear();
   // Replace this stub with your own code
}

Program::~Program() {
   sentences.clear();
   built.clear();
   // Replace this stub with your own code
}

void Program::clear(EvalState &state) {
   sentences.clear();
   built.clear();
   state.clear();
   // Replace this stub with your own code
}

void Program::addSourceLine(int lineNumber, string line) {

   removeSourceLine(lineNumber);
   sentences.insert(pair<int, string>(lineNumber,line));
   // Replace this stub with your own code
}

void Program::removeSourceLine(int lineNumber) {
   if (sentences.find(lineNumber)!=sentences.end()) sentences.erase(lineNumber);
   if (built.find(lineNumber)!=built.end()) built.erase(lineNumber);
   // Replace this stub with your own code
}

string Program::getSourceLine(int lineNumber) {
   auto iter=sentences.find(lineNumber);
   if (iter==sentences.end()) return "";
   return iter->second;
   // Replace this stub with your own code
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {

   built.insert(pair<int, Statement*>(lineNumber,stmt));
   // Replace this stub with your own code
}

Statement *Program::getParsedStatement(int lineNumber) {
   return  built.find(lineNumber)->second;
   // Replace this stub with your own code
}
void Program::build(int lineNumber)
{
   string str=getSourceLine(lineNumber);
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(str);
   string token = scanner.nextToken();
   Statement *temp=nullptr;
   if (scanner.getTokenType(token)==NUMBER)token = scanner.nextToken();
   if (scanner.getTokenType(token)!=WORD) error("SYNTAX ERROR");
   if (token=="INPUT") temp=new Inputstate(scanner);
   if (token=="PRINT") temp=new Printstate(scanner);
   if (token=="LET") temp=new Letstate(scanner);
   if (token=="REM") temp=new Remstate(scanner);
   if (token=="END") temp=new Endstate(scanner);
   if (token=="GOTO") temp=new Gotostate(scanner);
   if (token=="IF") temp=new Ifstate(scanner);
   setParsedStatement(lineNumber,temp);
}
void Program::list()
{
   int i=getFirstLineNumber();
   while (i!=-1)
   {
      std::cout<<getSourceLine(i)<<std::endl;
      i=getNextLineNumber(i);
   }
}

void Program::run(EvalState &state)
{
   int i=getFirstLineNumber();
   while (i!=-1)
   {
   	  state.sweepjump();
      if (built.find(i)==built.end()) build(i);
      if ((built.find(i)->second)->getStatementType()==END) break;
      (built.find(i)->second)->execute(state);

      if (state.isDefined("_DefaultLineJump"))
      {
      	int j=state.getValue("_DefaultLineJump");
      	if (sentences.find(j)==sentences.end())
      		error("LINE NUMBER ERROR");
      	i=j;
      }
      else i=getNextLineNumber(i);
   }
}

int Program::getFirstLineNumber() {
   auto iter=sentences.begin();
   if (iter==sentences.end()) return -1;
   return iter->first;
        // Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
   auto iter=sentences.find(lineNumber);
   iter++;
   if (iter==sentences.end()) return -1;
   return iter->first;     // Replace this stub with your own code
}
