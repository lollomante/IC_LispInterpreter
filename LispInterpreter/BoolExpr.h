#ifndef BOOLEXPR_H
#define BOOLEXPR_H

#include <string>
#include <vector>

#include "Token.h"
#include "NumExpr.h"

// Class for boolean expression
class BoolExpr {
public:
    virtual ~BoolExpr() {};
    virtual bool interpret() const = 0;
};

//Class for boolean constant
class BoolConst : public BoolExpr {
public:
    BoolConst(Token t) : t{ t } { }
    ~BoolConst() = default;
    BoolConst(const BoolConst& other) = default;
    BoolConst& operator = (const BoolConst& other) = default;
    Token get_token() const {
        return t;
    }

    // Override of "interpret" method
    bool interpret() const override;

private:
    Token t;
};

//Class for boolean operators (AND, OR, NOT)
class BoolOp : public BoolExpr {
public:
    BoolOp(Token t, BoolExpr* left, BoolExpr* right) : token{ t }, left{ left }, right{ right } { }
    ~BoolOp() = default;
    BoolOp(const BoolOp& other) = default;
    BoolOp& operator=(const BoolOp& other) = default;
    Token get_token() const {
        return token;
    }
    BoolExpr* getLeft() const {
        return left;
    }
    BoolExpr* getRight() const {
        return right;
    }

    // Override of "interpret" method
    bool interpret() const override;

private:
    Token token;
    BoolExpr* left;
    BoolExpr* right;
};

//Class for relational boolean operators (GT, LT, EQ)
class RelOp : public BoolExpr {
public:
    RelOp(Token t, NumExpr* left, NumExpr* right) : token{ t }, left{ left }, right{ right } { }
    ~RelOp() = default;
    RelOp(const RelOp& other) = default;
    RelOp& operator=(const RelOp& other) = default;
    Token get_token() const {
        return token;
    }
    NumExpr* getLeft() const {
        return left;
    }
    NumExpr* getRight() const {
        return right;
    }

    // Override of "interpret" method
    bool interpret() const override;

private:
    Token token;
    NumExpr* left;
    NumExpr* right;

};
#endif

