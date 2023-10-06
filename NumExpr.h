#ifndef NUMEXPR_H
#define NUMEXPR_H

#include <stdexcept>
#include <string>
#include <vector>

#include "Token.h"
#include "Exceptions.h"
#include "Context.h"

// Base Class for numeric expressions
class NumExpr {
public:
    virtual ~NumExpr() {};
    virtual long interpret() const = 0;
};

//Derive class for numbers
class Number : public NumExpr {
public:
    Number(Token t) : token{ t } { }
    ~Number() = default;
    Number(const Number& other) = default;
    Number& operator=(const Number& other) = default;
    long get_Value() const {
        return std::stoi(token.word);
    }

    //override interpret method
    long interpret() const override;

private:
    Token token;
};

// derive class for numeric expression with operator
class Operator : public NumExpr {
public:
    Operator(Token t, NumExpr* lop, NumExpr* rop) :
        token{ t }, left{ lop }, right{ rop } { }
    ~Operator() = default;
    Operator(const Operator& other) = default;
    Operator& operator=(const Operator& other) = default;

    //Access methods
    Token getToken() const {
        return token;
    }
    NumExpr* getLeft() const {
        return left;
    }
    NumExpr* getRight() const {
        return right;
    }

    // Override del metodo interpret: 
    long interpret() const override;

private:
    Token token;
    NumExpr* left;
    NumExpr* right;
};

// classe derivata per le variabili
class NumVar : public NumExpr {
public:
    NumVar(Token t, SimbleTable& s) : t{ t }, s{ s } { }
    ~NumVar() = default;

    long interpret() const override {
        return s.readVariable(t);
    }

private:
    Token t;
    SimbleTable& s;
};


#endif


