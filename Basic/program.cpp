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
   // Replace this stub with your own code
}

Program::~Program() {
   // Replace this stub with your own code
}

void Program::clear() {
   lineTable.clear();
   stateTable.clear();
   nowline = 0;
   maxline = 0;
}

void Program::addSourceLine(int lineNumber, string line) {
   lineTable.put(lineNumber,line);
   if (lineNumber > maxline) maxline = lineNumber; 
}

void Program::removeSourceLine(int lineNumber) {
   lineTable.remove(lineNumber);
   stateTable.remove(lineNumber);
}

string Program::getSourceLine(int lineNumber) {
   if (!lineTable.containsKey(lineNumber)) return "";
   string tem = lineTable.get(lineNumber);
   return tem;
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
   stateTable.put(lineNumber,stmt);
}

Statement *Program::getParsedStatement(int lineNumber) {
   if (!stateTable.containsKey(lineNumber)) return NULL;  
   Statement *tem = stateTable.get(lineNumber);
   return tem;
}

int Program::getFirstLineNumber() {
   if (lineTable.isEmpty()) return 0;
   int count = 1;
   while (true){
      if (lineTable.containsKey(count)){
         nowline = count;
         return count;
      }
      if (count >= maxline) return 0;
      count++;
   }
}

int Program::getNextLineNumber(int lineNumber) {
   if (lineTable.isEmpty()) return 0;
   int count = nowline+1; 
   while (true){
      if (lineTable.containsKey(count)){
         nowline = count;
         return count;
      }
      if (count >= maxline) return 0;
      count++;
   }
}

void Program::setNowline(int lineNumber){
   if (lineTable.containsKey(lineNumber))
      nowline = lineNumber;
}
