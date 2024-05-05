#include "Parser.h"

bool ProgramParse::isStatement(std::vector<Token>& inputTokens, int& index) {
    return ((inputTokens[index].tag == inputTokens[index].LP) &&
            ((inputTokens[index + 1].tag == inputTokens[index + 1].SET) ||
            (inputTokens[index + 1].tag == inputTokens[index + 1].PRINT) ||
            (inputTokens[index + 1].tag == inputTokens[index + 1].INPUT) ||
            (inputTokens[index + 1].tag == inputTokens[index + 1].IF) ||
            (inputTokens[index + 1].tag == inputTokens[index + 1].WHILE)));
}
bool ProgramParse::isNumOp(Token token) {
    return ((token.tag == token.ADD)||
            (token.tag == token.SUB)||
            (token.tag == token.MUL)||
            (token.tag == token.DIV));
}
bool ProgramParse::isBoolOp(Token token) {
    return ((token.tag == token.AND) ||
            (token.tag == token.OR));
}
bool ProgramParse::isRelOp(Token token) {
    return ((token.tag == token.LT) ||
            (token.tag == token.GT) ||
            (token.tag == token.EQ));
}

bool ProgramParse::ParseNumber(Token inputNumber) {
    std::string number = inputNumber.word;
    if (number[0] == '-') {
        if (number.size() == 1) {
            return false;
        }
        else if ((number[1] == '0')) {
            return false;
        }
        else return true;
    }
    else {
        //only number '0' can start with 0
        if ((number[0] == '0') && (number.size() != 1)) {
            return false;
        }
        else return true;
    }



}
   
NumExpr* ProgramParse::NumExprParse(std::vector<Token>& inputTokens, int& index) {
    //Read number
    if ((inputTokens[index].tag == inputTokens[index].NUMBER)&&index<inputTokens.size()) {
        if (ParseNumber(inputTokens[index])) {            
            //creating "number" node
            numexpr = m.makeNumber(inputTokens[index]);
            index++;            
            if (numexpr != nullptr) return numexpr;
        }
        else
            throw ParseError("Parse error in number");
        return nullptr;
    }
    //Read a variable name
    if ((index<inputTokens.size())&&(inputTokens[index].tag == inputTokens[index].VARIABLE)) {
        int varindex = index;
        index++;
        //Creating "variable" node
        numexpr = m.makeNumVar(inputTokens[varindex]);
        if (numexpr != nullptr) return numexpr;
    }
    //Read '('
    if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].LP)) {
        index++;
        //Read ADD, SUB, MUL, Div
        if ((index < inputTokens.size()) && isNumOp(inputTokens[index])) {
            int tokenIndex = index;
            index++;
            //Ceck left num_expr
            NumExpr* left = NumExprParse(inputTokens, index);
            //Ceck rigt num_expr
            NumExpr* right = NumExprParse(inputTokens, index);
            //Read ')'
            if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].RP)) {
                index++;
                if ((left != nullptr) && (right != nullptr)) {
                    //creating "NumOp" node
                    numexpr = m.makeNumOperator(inputTokens[tokenIndex], left, right);
                    return numexpr;
                }
            }
        }
    }
    //Read unrecognised token
    throw ParseError("Parse error in Num Expression ");
    return nullptr;
}

BoolExpr* ProgramParse::BoolExprParse(std::vector<Token>& inputTokens, int& index) {
     //Read TRUE,FALSE
    if ((index < inputTokens.size()) && ((inputTokens[index].tag == inputTokens[index].TRUE)||
        inputTokens[index].tag == inputTokens[index].FALSE)) {
        //creating "boolConst" node
        boolexpr = m.makeBoolConstant(inputTokens[index]);
        index++;
        if (boolexpr != nullptr) return boolexpr;
    }  
    //Read '('
    if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].LP)) {
        index++;
         //Read LT, GT, EQ
        if ((index < inputTokens.size()) && isRelOp(inputTokens[index])) {
            int tokenIndex = index;
            index++;
            // Ceck left num_expr
            NumExpr* left = NumExprParse(inputTokens, index);
            //Ceck rigt num_expr
            NumExpr* right = NumExprParse(inputTokens, index);            
            //Read ')'
            if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].RP)) {
                index++;
                if ((left != nullptr) && (right != nullptr)) {
                    //creating "relOp" node
                    boolexpr = m.makeRelOp(inputTokens[tokenIndex], left, right);
                    return boolexpr;
                }
            }
        }
        //Read AND, OR
        if ((index < inputTokens.size()) && isBoolOp(inputTokens[index])) {
            int tokenIndex = index;
            index++;
            //Ceck left bool_expr
            BoolExpr* left = BoolExprParse(inputTokens, index);
            //Ceck rigt bool_expr
            BoolExpr* right = BoolExprParse(inputTokens, index);
            //Read ')'
            if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].RP)) {
                index++;
                if ((left != nullptr) && (right != nullptr)) {
                    //Creating "boolOp" node
                    boolexpr = m.makeBoolOp(inputTokens[tokenIndex], left, right);
                    return boolexpr;
                }
            }
        }
        //Read NOT
        if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].NOT)) {
            int tokenIndex = index;
            index++;
            //Ceck bool_expr
            BoolExpr* left = BoolExprParse(inputTokens, index);
            //Read ')'
            if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].RP)) {
                index++;
                if (left != nullptr) {
                    //creating "not" "boolOp" node
                    // NOT operator only use first BoolExpr parameter, so the second can be anything.
                    boolexpr = m.makeBoolOp(inputTokens[tokenIndex], left, nullptr);
                    return boolexpr;
                }
            }
        }

    }
    throw ParseError("Parse error in Bool Statement");
    return nullptr;
}

StatementBlock* ProgramParse::SatementParse(std::vector<Token>& inputTokens, int& index) {
    //Read '('
    if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].LP)) {
        index++;
        //Read SET
        if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].SET)) {
            index++;
            //Ceck for variable name
            if ((index < inputTokens.size()) && (!(inputTokens[index].tag == inputTokens[index].VARIABLE))) {                
                throw ParseError("Expected variable name ");
                return nullptr;
            }
            int indexvarname = index;
            index++;
            //Read num_expr
            NumExpr* num = NumExprParse(inputTokens, index);
            //Read ')'
            if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].RP)) {
                index++;
                if (num != nullptr) {
                    //creating "set" node
                    statementblock = m.makeSET(inputTokens[indexvarname], num, s);
                    if (statementblock != nullptr) return statementblock;
                }
            }
        }
        //Read PRINT
        if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].PRINT)) {
            index++;
            //Read num_expr
            NumExpr* num = NumExprParse(inputTokens, index);
            //Read ')'
            if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].RP)) {
                index++;
                if (num != nullptr) {
                    //creating "print" node
                    statementblock = m.makePrint(num);
                    if (statementblock != nullptr) return statementblock;
                }
            }
        }
        //Read INPUT
        if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].INPUT)) {
            index++;
            //ceck for variable name
            if ((index < inputTokens.size()) && (!(inputTokens[index].tag == inputTokens[index].VARIABLE))) {
                throw ParseError("Expected variable name ");
                return nullptr;
            }
            int indexvarname = index;
            index++;
            //Read ')'
            if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].RP)) {
                index++;
                //Creating "input" node
                statementblock = m.makeInput(inputTokens[indexvarname], s);
                if (statementblock != nullptr) return statementblock;
            }
        }
        //Read IF
        if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].IF)) {
            index++;
            //Read bool_expr
            BoolExpr* cond = BoolExprParse(inputTokens, index);
            if (cond == nullptr) return nullptr;
            //Read "if" block_statement
            StatementBlock* ifblock = StatementBlockParse(inputTokens, index);
            if (ifblock == nullptr) return nullptr;
            //Read "else" block_statement
            StatementBlock* elseblock = StatementBlockParse(inputTokens, index);
            if (elseblock == nullptr) return nullptr;
            //Read ')'
            if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].RP)) {
                index++;
                if ((cond != nullptr) && (ifblock != nullptr) && (elseblock != nullptr)) {
                    //Creating "if" node
                    statementblock = m.makeIf(cond, ifblock, elseblock);
                    if (statementblock != nullptr) return statementblock;
                }
            }
        }
        //Read WHILE
        if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].WHILE)) {
            index++;
            //Read bool_expr
            BoolExpr* cond = BoolExprParse(inputTokens, index);
            if (cond == nullptr) return nullptr;
            //Read block_statement
            StatementBlock* then = StatementBlockParse(inputTokens, index);
            if (then == nullptr) return nullptr;
            //Read ')'
            if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].RP)) {
                index++;
                if ((cond != nullptr) && (then != nullptr)) {
                    //creating "while" node
                    statementblock = m.makeWile(cond, then);
                    if (statementblock != nullptr) return statementblock;
                }
            }
        }
    }
    //Read unrecognised token
    throw ParseError("Parse error in Statement ");
    return nullptr;
}

StatementBlock* ProgramParse::BlockParse(std::vector<Token>& inputTokens, int& index) {
    //Read '('
    if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].LP)) {
        index++;
        //Read BLOCK
        if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].BLOCK)) {
            index++;
            //using a temporary vector to save StatementBlock* values
            std::vector <StatementBlock*> temp;
            //Read first statement
            StatementBlock* st = SatementParse(inputTokens, index);
            if (st == nullptr) {
                throw ParseError("errore in parsing");
                return nullptr;
            }
            temp.push_back(st);
            //Read more statements (if any)
            while ((index < inputTokens.size()) && (isStatement(inputTokens, index))) {
                st = SatementParse(inputTokens, index);
                if (st == nullptr) {
                    throw ParseError("errore in parsing");
                    return nullptr;
                }
                temp.push_back(st);
            }
             // leggo ')'
            if ((index < inputTokens.size()) && (inputTokens[index].tag == inputTokens[index].RP)) {
                index++;
                //creating "block" node
                statementblock = m.makeBlock(temp);
                if (statementblock != nullptr) return statementblock;
            }
        }

    }
    throw ParseError("ERROR during block parsing");
    return nullptr;
}

StatementBlock* ProgramParse::StatementBlockParse(std::vector<Token>& inputTokens, int& index) {
    //Read statement
    if ((index < inputTokens.size()) && (isStatement(inputTokens, index))) {
        StatementBlock* st = SatementParse(inputTokens, index);
        return st;
    }
    else {
        //Read block
        StatementBlock* st = BlockParse(inputTokens, index);
        return st;
    }
}
