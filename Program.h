#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>

#include "Token.h"
#include "NumExpr.h"
#include "BoolExpr.h"
#include "Context.h"

class StatementBlock {
public:
    virtual ~StatementBlock () {}
    virtual void interpret() const = 0;
};

class Block : public StatementBlock {
public:
    Block(std::vector <StatementBlock*> v) : v{ v } {}
    ~Block() {};
    void interpret() const override;

private:
    std::vector <StatementBlock*> v;
};

class Statement : public StatementBlock{
public:
    virtual ~Statement() {}
    virtual void interpret() const = 0;
};

class SetStm : public Statement {
public:
    SetStm(Token t, NumExpr* num, SimbleTable& s) : t{ t }, num{ num }, s{ s } {}
    ~SetStm() = default;
    SetStm(const SetStm& other) = default;
    SetStm& operator=(const SetStm& other) = default;

    //access methods
    Token getToken() const {
        return t;
    }
    NumExpr* getNum() const {
        return num;
    }

    void interpret() const override;

private:
    Token t;
    NumExpr* num;
    SimbleTable& s;
};

class PrintStm : public Statement {
public:
    PrintStm(NumExpr* num) : num{ num } { }
    ~PrintStm() = default;
    PrintStm(const PrintStm& other) = default;
    PrintStm& operator=(const PrintStm& other) = default;

    //Access method
    NumExpr* getNum() const {
        return num;
    } 
    void interpret() const override;
private:
    NumExpr* num;
};

class InputStm : public Statement {
public:
    InputStm(Token name, SimbleTable& s) : name{ name }, s{ s } {}
    ~InputStm() = default;
    InputStm(const InputStm& other) = default;
    InputStm& operator=(const InputStm& other) = default;

    //Access method
    Token getToken() const {
        return name;
    }

    void interpret() const override;
private:
    Token name;
    SimbleTable& s;
};

//Derive class IF istruction
class IFStm : public Statement {
public:
    IFStm(BoolExpr* cond, StatementBlock* ifblock, StatementBlock* elseblock) : cond{ cond }, ifblock{ ifblock },  elseblock { elseblock } { }
    ~IFStm() = default;
    IFStm(const IFStm& other) = default;
    IFStm& operator=(const IFStm& other) = default;

    //Access methods
    BoolExpr* getNum() const {
        return cond;
    }
    StatementBlock* getIfblock() const {
        return ifblock;
    }
    StatementBlock* getElseblock() const {
        return elseblock;
    }

    //override interpret method
    void interpret() const override;
private:
    BoolExpr* cond;
    StatementBlock* elseblock;
    StatementBlock* ifblock;
};

//Derive class WHILE istruction
class WhileStm : public Statement {
public:
    WhileStm(BoolExpr* cond, StatementBlock* then) : cond{ cond }, then{ then } { }
    ~WhileStm() = default;
    WhileStm(const WhileStm& other) = default;
    WhileStm& operator=(const WhileStm& other) = default;

    //Access methods
    BoolExpr* getNum() const {
        return cond;
    }
    StatementBlock* getThen() const {
        return then;
    }

    //Override interpret method 
    void interpret() const override;
private:
    BoolExpr* cond;
    StatementBlock* then;
};

#endif

