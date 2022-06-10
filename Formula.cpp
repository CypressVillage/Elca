#include "Formula.h"

int priority( string op ){
    if( op == "~" ) return 5;
    if( op == "!" ) return 5;
    if( op == "*" ) return 3;
    if( op == "^" ) return 2;
    if( op == "+" ) return 1;
    if( op == "null") return 0;
    return 0; 
}

string FormulaAnalyzer::find_first_var( string standerd ){
    for( int i = 0; i < variableArr.size(); ++i ){
        if( standerd.find(variableArr[i],0) == 0 ){
            return variableArr[i];
        }
    }
    return "null";
}

int FormulaAnalyzer::get_value_of_var(string a, vector<int> valueArr ){
    int i = 0;
    while(1){
        if( variableArr[i] == a ) return valueArr[i];
        i++;
    }
}

FormulaAnalyzer::FormulaAnalyzer( string s, vector<string> v, vector<string> t ):
formula(s), variableArr(v), targetArr(t) {}

FormulaAnalyzer::~FormulaAnalyzer(){}

string FormulaAnalyzer::replaceTarget( string ans, string formulas[] ){
    int left = 0;
    string s = ans;
    for( int i = targetArr.size()-1; i >=0; --i ){
        while( (left = s.find(targetArr[i], 0)) != -1 ){
            s.erase(left, targetArr[i].length());
            s.insert(left,"(");
            s.insert(left+1,formulas[i]);
            s.insert(left+1+formulas[i].length(),")");
        }
    }
    return s;
}

string FormulaAnalyzer::standard_form( string s ){
    /* add '*' */
    string ans, ElementNow, temp = "(" + s + ")";
    int left = 0; // check whether add '*' or not
    while( temp.length() != 1 ){
        left = 0;
        ElementNow = find_first_var(temp);
        if( ElementNow != "null" ){
            left = 1;
            ans += ElementNow;
            temp.erase(0, ElementNow.size());
        }else{
            ElementNow = temp.at(0);
            if( ElementNow == ")" ) left = 1;
            ans += ElementNow;
            temp.erase(0, 1);
        }

        if(left){
            ElementNow = find_first_var(temp);
            if( ElementNow != "null" ){
                ans += "*";
            }else{
                ElementNow = temp.at(0);
                if ( ElementNow == "(" || ElementNow == "!" || ElementNow == "~" ) ans += "*";
            }
        }


    }
    ans += temp;
    return ans;
}

string FormulaAnalyzer::postfixExpression( string standerd ){
    Stack<string> s;
    string ans;

    while( !standerd.empty() ){

        /* for variables, just out */
        string firstElement = find_first_var(standerd);
        if( firstElement != "null" ){
            standerd.erase( 0, firstElement.length() );
            ans += firstElement;
            ans += '#';
        }
        if( standerd.empty() ) break;

        firstElement = standerd.at(0);
        /* () */
        if(firstElement=="("){
            s.push("(");
            standerd.erase(0, 1);
        }else if(firstElement==")"){
            while( s.topElement() != "(" ){
                ans += s.pop();
                ans += '#';
            }
            s.pop();
            standerd.erase(0, 1);
        }else if( firstElement=="~" || firstElement=="!" ){
            /* operators */
            s.push(firstElement);
            standerd.erase(0, 1);
        }else if(firstElement=="+" || firstElement=="*" || firstElement=="^" ){
            if( priority(firstElement) > priority(s.topElement())){
                s.push(firstElement);
                standerd.erase(0, 1);
            }else{
                while( priority(firstElement) <= priority(s.topElement()) && !s.empty() ){
                    ans += s.pop();
                    ans += '#';
                }
                s.push(firstElement);
                standerd.erase(0, 1);
            }
        }
    }
    while(!s.empty()){
        ans += s.pop();
        ans += '#';
    }
    return ans;
}

int FormulaAnalyzer::calculate( vector<int> valueArr, string formulas[] ){
    string postfix = this->postfixExpression(this->standard_form(replaceTarget(formula, formulas)));
    Stack<int> s;
    while(!postfix.empty()){
        string ElementNow = find_first_var(postfix);
        if( ElementNow != "null" ){
            int intElementNow = get_value_of_var( ElementNow, valueArr );
            s.push(intElementNow);
            postfix.erase(0, ElementNow.length()+1);
            continue;
        }else{
            char op = postfix.at(0);
            if( op == '~' || op == '!' ){
                int a = !s.pop();
                s.push(a);
            }else{
                int a = s.pop();
                int b = s.pop();
                if( op == '+' ){
                    s.push( a || b );
                }else if( op == '*' ){
                    s.push( a && b );
                }else if( op == '^' ){
                    s.push( a^b );
                }
            }
            postfix.erase(0, 2);
        }
    }
    return s.pop();
}
