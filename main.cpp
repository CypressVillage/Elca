#include <iostream>
#include "Logic.h"
using namespace std;

// g++ main.cpp Stack.hpp Formula.h Formula.cpp Logic.h Logic.cpp QM.h QM.cpp

int main(){
    system("chcp 65001 > nul");
    while( 1 ){
        cout << "select mode:" << endl << "1.classic 2.handful 3.zen 4.minium" << endl;
        int mode; cin >> mode;
        if(!mode) break;
    
        CombinedLogic cl;
        cl.init(mode);
        cl.outputTruthTable();
        cl.outputMinimum();
        cl.outputSOP();
        cl.outputKarnaughTable();
        cout << "export the file in Markdown? (y&n)" << endl;
        string ex; cin >> ex;
        if( ex == "y" || ex == "Y" ){
            cout << "please input the file name" << endl;
            cin >> ex;
            cl.exportMarkdowm(ex);
        }
        cout << endl;
    }
    system("chcp 936 > nul");
    return 0;
}