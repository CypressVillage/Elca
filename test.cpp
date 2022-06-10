#include <iostream>
#include <vector>
#include "Stack.hpp"
#include "Formula.h"
#include "Logic.h"
// #include "toLatex.h"
using namespace std;

// string FormulaAnalyzer::replaceTarget( string s, string *formulas ){
//     int left;
//     for( int i = 0; i < targetArr.size(); ++i ){
//         do{
//             int left = s.find(targetArr[i], 0);
//             s.erase(left, targetArr[i].length());
//             s.insert(left,"("+formulas[i]+")");
//         }while( left <= targetArr[i].length() );
//     }
//     return s;
// }

int main(){
    system("chcp 65001 > nul");
    // Stack<int> s;
    // s.push(1);
    // s.pop();
    // s.push(111);
    // cout << s.pop();

    // vector<string> v1 = { "aaa", "bbb", "ccc" };
    // vector<string> v2 = v1;
    // v2[2] = "fdsf";
    // cout << v2[2] << v1[2];
    
    // string ans;
    // cout << ans << endl;

    // vector< vector<int> > a;
    // a[0].push_back({1,2,3});

    // vector<int> v;
    // v.push_back(1);
    // v.push_back(0);
    // v.push_back(1);
    // v.push_back(1);
    // cout << f.postfixExpression("a*!(c+d)");
    // cout << f.standard_form();
    // cout << "main:" << f.calculate( v );

    // string s = "fdahf";
    // cout << s.length() << s.size();

    // CombinedLogic cl;


    vector<string> V = {"q_1=q1","w_1=w1","e"};
    vector<string> T = {"a","s"};
    string F[] = {
        "q1w1",
        "qw"
    };
    // FormulaAnalyzer f( F[0], V, T );
    // f.latexInputSimplify();
    // cout << f.replaceTarget( F[0], F ) << endl;
    // cout << F[0] << endl;
    // cout << f.standard_form(F[0]) << endl;

    CombinedLogic c(V,T,F);

    // c.makeBinTable();
    // c.calculateTruthTable();
    // c.outputTruthTable();

    // cout << "=" << "\u03A3(";

// string path = "D:/zbc/Desktop/";
//     ofstream ofs;
//     ofs.open(path+"filename"+".md", ios::out);
//     system("");
//     system("pause");

    // string a;
    // a += 22;
    // a += 1;
    // cout << a;
    // ofstream ofs;


    // latex lofs("jianshi");
    // ofs.open("D:/zbc/Desktop/test.md", ios::app);
    // ofs << "1" << (latex("a_3=!w!(a+v)")) << "jfjffj";
    // // lofs << "hasjkdfhaui" << endl;
    // ofs.close();



    return 0;
}