#include "QM.h"
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <iostream>
using namespace std;

int main(){
    vector<string> vararr = { "a", "b", "c", "d", "e" };
    vector<int> min = { 12,13,14,15,18,19,26,27,29 };
    
    QM qm( min, vararr );
    cout << qm.outputResult();

// cout <<( ceil(log2( fabs(3^3) )) - floor(log2( fabs(3^3) )));

    return 0;
}