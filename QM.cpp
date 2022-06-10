#include "QM.h"

using namespace std;

Items::Items(){}

Items::Items( int _m, int _r ): r(_r), m(_m){
    simp = false;
    q = 0;
}

void Items::set( int _m, int _r, bool _s=false, int _q=0 ){
    m = _m;
    r = _r;
    simp = _s;
    q = _q;
}

Items Items::operator+( Items it ){
    int _m = min( m, it.m );
    int _r = (abs( m - it.m ) | r);
    Items *ans = new Items( _m, _r );
    return *ans;
}

bool Items::operator<( const Items& o ) const{
    if( m < o.m ){
        return true;
    }else if( r < o.r ){
        return true;
    }else if( q < o.q ){
        return true;
    }
    return false;
}


/**********************************************************************/

QM::QM( vector<int> m, vector<string> v )
: min(m), VariableArr(v){
    for( int i = 0; i < m.size(); ++i ){
        it.push_back( Items(m[i], 0) );
    }
}

QM::~QM(){}

void QM::expandItemMap(){
    for( int i = 0; i < it.size(); ++i ){
        for( int j = i+1; j < it.size(); ++j ){
            if( it[i].r != it[j].r ) continue;
            // emmm it works, though I thought there will be a bug
            double x = log2( fabs(it[i].m ^ it[j].m) );
            if( fabs(floor(x) - ceil(x)) < 0.00001 ){ 
                it.push_back( it[i] + it[j] );
                it[i].q ++;          it[j].q ++;
                it[i].simp = true;   it[j].simp = true;
            }
        }
    }
}

void QM::createVset(){
    for( int i = 0; i < min.size(); ++i ){
        V.insert(min[i]);
    }
}

void QM::createUsetbyN(){
    for( int i = 0; i < it.size(); ++i ){
        if( it[i].simp == false ){
            U.insert(it[i]);
            moveItemsFromU(it[i]);
        }
    }
}

void QM::moveItemsFromU( Items i ){
    /* get preview items */
    int j = 1;
    vector<int> add;
    add.push_back((i).m);
    V.erase( add[0] );
    while( j <= (i).r ){
        int ad = j & (i).r;
        if( ad != 0 ){
            int addSizeNow = add.size();
            for( int k = 0; k < addSizeNow; ++k ){
                add.push_back( add[k] + ad );
                V.erase( add[k] + ad );
            }
        }
        j = (j << 1);
    }
    /* end get items */
    U.erase( i );
    ans.insert( i );
}

void QM::heuristic(){
    createVset();
    createUsetbyN();
    
    set<Items>::iterator i;
	for( i=U.begin(); i!=U.end(); ++i ){
        // the v has only u
        if( (*i).q == 1 ){
            moveItemsFromU( *i );
        }
    }

    while( !V.empty() ){
        // get max q in U
        int maxq = 1;
        for( i=U.begin(); i!=U.end(); ++i ){
            if( (*i).q > maxq ) maxq = (*i).q;
        }
        for( i=U.begin(); i!=U.end(); ++i ){
            if( (*i).q == maxq ) moveItemsFromU( *i );
        }
    }
}

string QM::outputResult(){
    this->expandItemMap();
    this->heuristic();
    // showAnsMap();
    string output;
    set<Items>::iterator i;
    for( i=ans.begin(); i!=ans.end(); ++i ){
        int _r = (*i).r, _m = (*i).m;
        int k = VariableArr.size() - 1;
        while( k != -1 ){
            if( _r%2 == 1 ){
                _m = (_m>>1);
                _r = (_r>>1);
                k--;
                continue;
            }
            if( _m%2 == 0 ){
                output += "!";
                output += VariableArr[k];
            }
            if( _m%2 == 1 ) output += VariableArr[k];

            _m = (_m>>1);
            _r = (_r>>1);
            k--;
        }
        output += "+";
    }
    output.erase(output.length()-1);
    return output;
}