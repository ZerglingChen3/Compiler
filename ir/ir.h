//
// Created by chenjiyuan3 on 2021/11/6.
//

#ifndef COMPILER_IR_H
#define COMPILER_IR_H

#include <list>
#include <cstring>
#include "ir_code.h"

class IR {
private:
    vector <IrCode*> irList;
    int globalDeclEnd;
public:
    IR() = default;
    string toString() {
        string ret;
        for (auto ir: irList) {
            ret += ir->toString() + "\n";
        }
        return ret;
    }

    void add(IrCode* irCode) {
#ifdef DEBUG
        cout << "New line~~~~~~~: " << irCode->toString() << endl;
#endif
        irList.push_back(irCode);
    }

    void setGlobalDeclEnd() {
        globalDeclEnd = (int)irList.size();
    }

    int getGlobalDeclEnd() const {
        return globalDeclEnd;
    }

    vector <IrCode*>* getIrList() {
        return &irList;
    }
};

#endif //COMPILER_IR_H
