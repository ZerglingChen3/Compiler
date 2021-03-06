#include <iostream>
#include <fstream>
#include "lexical.h"
#include "grammar.h"
#include "mips/mips.h"
#include "ir/ir_new.h"
#include "mips/register.h"

using namespace std;

#define NOT_OPEN

ifstream fin("testfile.txt");
ofstream fout("output.txt");
ofstream eout("error.txt");
ofstream iout("ir.txt");
ofstream bout("before_mips.txt");
ofstream mout("mips.txt");
ofstream nout("ir_new.txt");
ofstream kout("ir_new1.txt");
ofstream gout("ir_new2.txt");
ofstream oout("ir_new3.txt");



Output output;
string input;
IR IR_1, IR_2;
Mips *mips; MipsTable* mipsTable; MipsOutput* mipsOutput;
Register* aRegister;

void read() {
    string s;
    while(getline(fin, s)) {
        s += "\n";
        input += s;
    }
}

void print(string outString, ofstream &ofs) {
    //cout << outString << endl;
    //fout << outString << endl;
    //eout << outString << endl;
    //iout << outString << endl;
    ofs << outString << endl;
}

int main() {
    read();
    //Lexical lexical = Lexical(input);
    Grammar grammar = Grammar(input);
//    print(output.to_string(), eout);
//    return 0;
    Node* root = grammar.getRoot();
    root -> traversal();
    print(IR_1.toString(), iout);
    mipsTable = new MipsTable();
    mipsOutput = new MipsOutput();
    aRegister = new Register();
    IrNew *irNew = new IrNew(&IR_1);

#ifdef NOT_OPEN
    irNew -> analysis();
    print(irNew -> toString(), nout);
    irNew -> toMips();
    print(mipsOutput -> toString(), mout);
    return 0;
#endif

    print(irNew -> toString(), nout);
    removeAddZero(irNew);
    print(irNew -> toString(), kout);
    constSpread(irNew);
//    vector<IrCode*>* temp = irNew -> toIR();
//    for (auto code: *temp)
//        IR_2.add(code);
//    IR_2.setGlobalDeclEnd(IR_1.getGlobalDeclEnd());
//    IrNew *irNew2 = new IrNew(&IR_2);
    print(irNew -> toString(), gout);
    irNew -> analysis();
    print(irNew -> toString(), oout);
    irNew -> toMips();
    //    vector<IrCode*>* temp = irNew -> toIR();
//    for (auto code: *temp)
//        IR_2.add(code);
//    IR_2.setGlobalDeclEnd(IR_1.getGlobalDeclEnd());
//    //print(irNew -> toString(), nout);
//    print(IR_2.toString(), nout);
    //mips = new Mips(IR_2, mipsTable, mipsOutput);
//    print(output.to_string(), eout);
    //print(lexical.to_string());*/
    print(mipsOutput -> toString(), mout);
    return 0;
}
