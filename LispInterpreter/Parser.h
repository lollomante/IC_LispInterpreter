#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>

#include "Token.h"
#include "Exceptions.h"
#include "Program.h"
#include "MemoryManager.h"

// Function object for program parsing
class ProgramParse {
public:
    ProgramParse(std::vector<Token>& inputTokens, MemoryManager& m, SimbleTable& s) :
        inputTokens{ inputTokens }, m{ m }, s{ s } { }

    bool operator()(std::vector<Token>& inputTokens) {
        int index = 0;
        statementblock = StatementBlockParse(inputTokens, index);
        return ((index == inputTokens.size())&&(statementblock != nullptr));
    }

    //Access method    
    StatementBlock* getStmBlock() {
        return statementblock;
    }

private:
    //Input program
    std::vector<Token>& inputTokens;
    //NumExpr analyzed 
    NumExpr* numexpr;
    //BoolExpr analyzed
    BoolExpr* boolexpr;
    //statementblock analyzed
    StatementBlock* statementblock;
    
    //Reference to memory manager
    MemoryManager& m;
    //Reference to symbletable
    SimbleTable& s;

    //Utility function to recognise a statement
    bool isStatement(std::vector<Token>& inputTokens, int& index);
    //Utility funtion to recognise a NumOp
    bool isNumOp(Token token);
    //Utility funtion to recognise a bynari BoolOp (AND,OR)
    bool isBoolOp(Token token);
    //Utility funtion to recognise a RelOp 
    bool isRelOp(Token token);

    // number parse function
    bool ParseNumber(Token inputNumber);    

    // Number expression parser
    NumExpr* NumExprParse(std::vector<Token>& inputTokens, int& index);

    // Boolean Expression Parser
    BoolExpr* BoolExprParse(std::vector<Token>& inputTokens, int& index);

    //Statement parser
    StatementBlock* SatementParse(std::vector<Token>& inputTokens, int& index);

    //Block parser
    StatementBlock* BlockParse(std::vector<Token>& inputTokens, int& index);

    //Statement block parser
    StatementBlock* StatementBlockParse(std::vector<Token>& inputTokens, int& index);
};
#endif

