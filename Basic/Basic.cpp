/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
   EvalState state;
   Program program;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         cout << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine (string line, Program & program, EvalState & state) {
try{
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   //My code Start
   string token = scanner.nextToken();
   TokenType type = scanner.getTokenType(token);
   if (type==NUMBER)
   {
      int linenum=stringToInteger(token);
      if (!scanner.hasMoreTokens()) program.removeSourceLine(linenum);
      else program.addSourceLine(linenum,line);
   }
   if (type==WORD)
   {
      if (token=="LET")
      {
         auto temp=new Letstate(scanner);
         (*temp).execute(state);
         delete temp;
      }
      if (token=="PRINT")
      {
         auto temp=new Printstate(scanner);
         (*temp).execute(state);
         delete temp;
      }
      if (token=="INPUT")
      {
         auto temp=new Inputstate(scanner);
         (*temp).execute(state);
         delete temp;
      }
      if (token=="RUN")
      {
         program.run(state);
      }
      if (token=="LIST")
      {
         program.list();
      }
      if (token=="HELP")
      {
         printf("Basic By 518030910411 LiYunqing 18/12/01");
      }
      if (token=="CLEAR")
      {
         program.clear(state);
      }
      if (token=="QUIT")
      {
         exit(0);
      }
   }
   }catch (ErrorException & ex) {
         cout << ex.getMessage() << endl;
      }
   //My code End
 //  Expression *exp = parseExp(scanner);
   //int value = exp->eval(state);
   //以上为对一个表达式获取值的范例


  // delete exp;
}
