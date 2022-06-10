#ifndef _FORMULA_H_
#define _FORMULA_H_

#include <string>
#include <vector>
#include "Stack.hpp"

using namespace std;

class FormulaAnalyzer{
    string formula;
    vector<string> variableArr;
    vector<string> targetArr;
public:
    FormulaAnalyzer( string s, vector<string> v, vector<string> t );
    ~FormulaAnalyzer();

    int calculate( vector<int> valueArr, string formulas[] );
private:
    /* replace target to f(variable) such as a=bc d=ab */
    string replaceTarget( string s, string formulas[] );
    /* add '*' and expand formula */
    string standard_form( string s );
    /* infix to posifix */
    string postfixExpression( string s );

    /* check if the first str is variable */
    string find_first_var( string standerd );
    /* see each var wheather 0 or 1 */
    int get_value_of_var(string a, vector<int> valueArr );
    
};

#endif