#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include <vector>

#include "Token.h"

//forward declarations
class NumExpr;
class BoolExpr;
class Program;

class MemoryManager {
public:
    MemoryManager(SimbleTable& s) : s{ s } {}
    ~MemoryManager() {
        for (auto i = NumAllocated.begin(); i != NumAllocated.end(); ++i) {
            delete(*i);
        }
        for (auto i = BoolAllocated.begin(); i != BoolAllocated.end(); ++i) {
            delete(*i);
        }
        for (auto i = stmBlockAllocated.begin(); i != stmBlockAllocated.end(); ++i) {
            delete(*i);
        }
    }
    //Blocking copy and assignment
    MemoryManager(const MemoryManager& other) = delete;
    MemoryManager& operator=(const MemoryManager& other) = delete;

    //creating number object
    NumExpr* makeNumber(Token t) {
        NumExpr* n = new Number(t);
        NumAllocated.push_back(n);
        return n;
    }
    //crerating NumOperator object
    NumExpr* makeNumOperator(Token t, NumExpr* (left), NumExpr* (right)) {
        NumExpr* n = new Operator(t, left, right);
        NumAllocated.push_back(n);
        return n;
    }
    //creating NumVar object
    NumExpr* makeNumVar(Token t) {
        NumExpr* n = new NumVar(t, s);
        NumAllocated.push_back(n);
        return n;
    }

    //crerating BoolCostant object
    BoolExpr* makeBoolConstant(Token t) {
        BoolExpr* n = new BoolConst(t);
        BoolAllocated.push_back(n);
        return n;
    }
    //creating BoolOperator object
    BoolExpr* makeBoolOp(Token t, BoolExpr* left, BoolExpr* right) {
        BoolExpr* n = new BoolOp(t, left, right);
        BoolAllocated.push_back(n);
        return n;
    }
    //creating relational bool operator object
    BoolExpr* makeRelOp(Token t, NumExpr* left, NumExpr* right) {
        BoolExpr* n = new RelOp(t, left, right);
        BoolAllocated.push_back(n);
        return n;
    }
    //creating SET object
    Statement* makeSET(Token t, NumExpr* num, SimbleTable& s) {
        Statement* st = new SetStm(t, num, s);
        stmBlockAllocated.push_back(st);
        return st;
    }
    //creating print object
    StatementBlock* makePrint(NumExpr* num) {
        StatementBlock* st = new PrintStm(num);
        stmBlockAllocated.push_back(st);
        return st;
    }
    //creating input object
    StatementBlock* makeInput(Token t, SimbleTable& s) {
        Statement* st = new InputStm(t, s);
        stmBlockAllocated.push_back(st);
        return st;
    }
    //creating if object
    StatementBlock* makeIf(BoolExpr* cond, StatementBlock* ifblock, StatementBlock* elseblock) {
        StatementBlock* st = new IFStm(cond, ifblock, elseblock);
        stmBlockAllocated.push_back(st);
        return st;
    }
    //creating while object
    Statement* makeWile(BoolExpr* cond, StatementBlock* then) {
        Statement* st = new WhileStm(cond, then);
        stmBlockAllocated.push_back(st);
        return st;
    }
    //creating block object
    StatementBlock* makeBlock(std::vector <StatementBlock*> temp) {
        StatementBlock* b = new Block(temp);
        stmBlockAllocated.push_back(b);
        return b;
    }
private:
    //reference to simbletable
    SimbleTable& s;
    //allocated vectors
    std::vector<NumExpr*> NumAllocated;
    std::vector<BoolExpr*> BoolAllocated;
    std::vector<StatementBlock*> stmBlockAllocated;
};


#endif

