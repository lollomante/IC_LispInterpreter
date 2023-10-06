#ifndef CONTEXT_H
#define CONTEXT_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "Token.h"
#include "Exceptions.h"

//forward declarations
class NumExpr;
class BoolExpr;


// class variable
class variable {
public:
    variable(std::string name, long value ): name { name }, value { value } {}
    ~variable() = default;
    variable(const variable& other) = default;
    variable& operator=(const variable& other) = default;
    std::string getName() const {
        return name;
    }
    long getValue() const {
        return value;
    }
    void setValue(long number) {
        value = number;
    }

private:
    long value;
    std::string name;
};

class SimbleTable {
public:
    SimbleTable() = default;
    ~SimbleTable() = default;
    SimbleTable(const SimbleTable& other) = delete;
    SimbleTable& operator=(const SimbleTable& other) = delete;
   
    void setVariable(Token name, long value) {
        for (int i = 0; i < context.size(); i++) {
            if (name.word == context[i].getName()) {
                context[i].setValue(value);
                return;
            }            
        }
        context.push_back(variable(name.word, value));
    }

    long readVariable(Token name) {
        for (int i = 0; i < context.size(); i++) {
            if (name.word == context[i].getName()) {
                return context[i].getValue();
            }
        }
        std::stringstream temp{};
        temp << "Variable " << name.word << " not defined ";
        throw ContextError(temp.str());
    }

private:
    std::vector <variable> context;
};
 
#endif
