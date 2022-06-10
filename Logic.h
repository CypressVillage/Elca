#ifndef _LOGIC_H_
#define _LOGIC_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include "Formula.h"
#include "QM.h"

using namespace std;

class CombinedLogic {
    vector<string> VariableArr;
    vector<string> TargetArr;
    int* binTable;
    int* truthTable;
    string *Formulas;
    string *simplifiedFormulas;
public:
    CombinedLogic();
    CombinedLogic(
        vector<string> VariableArr,
        vector<string> TargetArr,
        string *Formulas
        );
    virtual ~CombinedLogic();
    void init( int mode );
    void outputTruthTable();
    void outputKarnaughTable();
    void outputMinimum();
    void outputSOP();
    void exportMarkdowm( string filename );

private:
    void inputVariableArr();
    void inputTargetArr();
    void inputTruthTable();
    void inputFormula();
    void inputMinimum();
    void inputZenFormula();

    /* 
    to simplify input such as {a_1}=a
    */
    void latexInputSimplify();
    void zenAddVariable( string s );

    void makeBinTable();
    void calculateTruthTable();
    void simplifyFormula();
};

#endif