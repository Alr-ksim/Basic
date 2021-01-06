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
#include "statement.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

void run(Program & program, EvalState & state);

void Help(){
   printf("NO HELP\n");
   return;
}

bool Endflag = 0, Starflag = 0, Listflag = 0, Helpflag = 0, Clearflag = 0;

int Setflag = 0;

/* Main program */

int main() {
   EvalState state;
   Program program;
   cout << "Stub implementation of BASIC" << endl;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         cerr << "Error: " << ex.getMessage() << endl;
      }
   }
   run(program, state);
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

int turndigit(string key){
   if (key == "REM") return 0;
   if (key == "LET") return 1;
   if (key == "INPUT") return 2;
   if (key == "PRINT") return 3;
   if (key == "END" || "QUIT") return 4;
   if (key == "GOTO") return 5;
   if (key == "IF") return 6;
   if (key == "CLEAR") return 7;
   if (key == "LIST") return 8;
   if (key == "RUN") return 9;
   if (key == "HELP") return 10;
   return -1;
}

void processLine(string line, Program & program, EvalState & state) {
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   string token = scanner.nextToken();
   TokenType type = scanner.getTokenType(token);
   int lineNumber = 0;
   if (type == NUMBER){
      lineNumber = stringToInteger(token);
      program.addSourceLine(lineNumber,line);
      token = scanner.nextToken();
      type = scanner.getTokenType(token);
   } 
   if (type == WORD){
      int swt = turndigit(token);
      Statement *stmt;
      switch (swt)
      {
      case 0:{
         REM tem0(line);
         stmt = &tem0;
         break;
      }
         
      case 1:{
         Expression *exp1 = parseExp(scanner);
         LET tem1(exp1);
         stmt = &tem1;
         break;
      }
         
      case 2:{
         token = scanner.nextToken();
         INPUT tem2(token);
         stmt = &tem2;
         break;
      }
         
      case 3:{
         Expression *exp3 = parseExp(scanner);
         PRINT tem3(exp3);
         stmt = &tem3;
         break;
      }
         
      case 4:{
         END tem4(Endflag);
         stmt = &tem4;
         break;
      }
         
      case 5:{
         Expression *exp5 = parseExp(scanner);
         GOTO tem5(exp5,&Setflag);
         stmt = &tem5;
         break;
      }

      case 6:{
         Expression *exp6 = parseExp(scanner);
         token = scanner.nextToken();
         Expression *exp6s = nullptr;
         if (token == "THEN") exp6s = parseExp(scanner);
         IF tem6(exp6,exp6s,&Setflag);
         stmt = &tem6;
         break; 
      }
      
      case 7:{
         CLEAR tem7(Clearflag);
         stmt = &tem7;
         break;
      }

      case 8:{
         LIST tem8(Listflag);
         stmt = &tem8;
         break;
      }

      case 9:{
         RUN tem9(Starflag);
         stmt = &tem9;
         break;
      }

      case 10:{
         HELP tem10(Helpflag);
         stmt = &tem10;
         break;
      }
      default:
         break;
      }
   } 
   Expression *exp = parseExp(scanner);
   int value = exp->eval(state);
   cout << value << endl;           
   delete exp;
}

void run(Program & program, EvalState & state) {
   int stat = program.getFirstLineNumber();
   while (stat != 0){
      program.setNowline(stat);
      Statement *stmt = program.getParsedStatement(stat);
      if (Starflag) stmt->execute(state);
      if (Listflag){
         printf("%d\n",stat);
         Listflag = 0;
      }
      if (Endflag) exit(0);
      if (Clearflag){
         program.clear();
         state.clear();
         stat = program.getFirstLineNumber();
         Clearflag = 0;
      }
      if (Helpflag){
         Help();
         Helpflag = 0;
      }
      if (Setflag) {
         stat = Setflag;
         Setflag = 0;
      }else stat = program.getNextLineNumber(stat);
   }
}