#include "NumExpr.h"

long Number::interpret() const {
    return std::stoi(token.word);
}

long Operator::interpret() const {
    long lval = left->interpret();
    long rval = right->interpret();
    if (token.tag == token.ADD) {
        return lval + rval;
    }
    else if (token.tag == token.SUB) {
        return lval - rval;
    }
    else if (token.tag == token.MUL) {
        return lval * rval;
    }
    else if (token.tag == token.DIV) {
        if (rval != 0) {
            return lval / rval;
        }
        else {
            throw DivisionByZeroError("Error: Cannot divide by zero");
            return EXIT_FAILURE;
        }
    }
}

