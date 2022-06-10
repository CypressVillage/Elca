#ifndef _QM_H_
#define _QM_H_

#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <iostream>

using namespace std;

/*
    m is the data
    if the bit is equal, the equal bit is 0: 00-0 => 0000

    r is the equal bit
    00-0 the bit equal is 2^1 = 2
    0--0 the bit equal is 2^1 + 2^2 = 6

    simp is a bool
    default is false. if the iteam has been simplified, it is true

    q is the quate time
    it sounds like the "importance", if the q is 1, it must be included

    when merge, bitequal = (data1^data2) | bitequal
*/
class Items{
public:
    int m; // data
    int r; // the equal bit
    bool simp; // wheather the item was simplified or not
    int q; // the quate time
    Items();
    Items( int m, int r );
    void set( int m, int r, bool s, int q );
    // bool canMerge();
    /* the operator is merge, not add */
    Items operator+( Items it );
    bool operator<( const Items& o ) const;
};

class QM{
    vector<string> VariableArr; // to output a formula
    vector<int> min; // include minium items
    vector<Items> it; // include all items

    set<int> V; // also include minium items
    set<Items> U;
    set<Items> ans;
public:
    QM( vector<int> m, vector<string> v );
    ~QM();
    string outputResult( void );
private:
    void expandItemMap();
    void createUsetbyN();
    void createVset();
    void heuristic();
    /* also move nums in V, and add items to ans */
    void moveItemsFromU( Items i );
    // string outputResult( void );

    void showAnsMap(){
        cout << "show ans map:" << endl;
        set<Items>::iterator i;
        for( i=ans.begin(); i!=ans.end(); ++i){
            cout << (*i).m << "," << (*i).r
            << "," << (*i).simp << "," << (*i).q << endl;
        }
        cout << "------------------------" << endl;
    }
};

#endif