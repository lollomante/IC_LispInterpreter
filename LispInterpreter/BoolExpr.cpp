#include "BoolExpr.h"

bool BoolConst::interpret() const {
    if (t.tag == t.TRUE) {
        return true;
    }
    else if (t.tag == t.FALSE) {
       return false;
    }
}

bool BoolOp::interpret() const {
    if (token.tag == token.AND) {
        bool lval = left->interpret();
        if (lval == false) {
            return lval;
        }
        bool rval = right->interpret();
        return (lval && rval);
    }
    else if (token.tag == token.OR) {
        bool lval = left->interpret();
        if (lval == true) {
            return lval;
        }
        bool rval = right->interpret();
        return (lval || rval);
    }
    else if (token.tag == token.NOT) {
        bool lval = left->interpret();
        return (!lval);
    }
}

bool RelOp::interpret() const {
    long lval = left->interpret();
    long rval = right->interpret();
    if (token.tag == token.GT) {
        return (lval > rval);
    }
    else if (token.tag == token.LT) {
        return (lval < rval);
    }
    else if (token.tag == token.EQ) {
        return (lval == rval);
    }
}