#include "Program.h"

void Block::interpret() const {
    for (auto i = 0; i < v.size(); ++i) {
        v[i]->interpret();
    }
}

void SetStm::interpret() const {
    long value = num->interpret();
    s.setVariable(t, value);
}

void PrintStm::interpret() const {
    int val = num->interpret();
    std::cout << val << " " << std::endl;
}

void InputStm::interpret() const {
    std::string number;
    std::cout << "Insert value: ";
    std::cin >> number;
    bool correct;
    int ceck = 0;
    if (number[0] == '-') {
        ceck++;
    }
    for (int i = 0; i < number.size(); i++) {
        if (std::isdigit(number[i])) {
            ceck++;
        }
    }
    //the string contains only digits and optional '-'
    if (ceck == number.size()) {
        if (number[0] == '-') {
            if (number.size() == 1) {
                correct = false;
            }
            else if ((number[1] == '0') && (number.size() != 2)) {
                correct = false;
            }
            else correct = true;
        }
        else {
            //only number '0' can start with 0
            if ((number[0] == '0') && (number.size() != 1)) {
                correct = false;
            }
            else correct = true;
        }
        if (correct) {
            long value = std::stol(number);
            s.setVariable(name, value);
        }
        else throw InputError("Error: input is not an integer");
    }
    else throw InputError("Error: input is not an integer");
}

void IFStm::interpret() const {
    if (cond->interpret()) {
        ifblock->interpret();
    }
    else {
        elseblock->interpret();
    }
}

void WhileStm::interpret() const {
    while (cond->interpret()) {
        then->interpret();
    }
}