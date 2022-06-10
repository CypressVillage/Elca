#include "Logic.h"

inline int to_Gray( int x ){
    return (x^x>>1);
}

/* x is the num to convert, y is the width */
string to_bin( int x, int y ){
    string ans = "";
    while( x ){
        if( x%2 ) ans.insert(0, "1");
        else ans.insert(0, "0");
        x /= 2;
    }
    while( ans.length() != y ) ans.insert(0,"0");
    return ans;
}

void string_replace(string&s1,const string&s2,const string&s3){
	string::size_type pos=0;
	string::size_type a=s2.size();
	string::size_type b=s3.size();
	while((pos=s1.find(s2,pos))!=string::npos){
		s1.erase(pos,a);
		s1.insert(pos,s3);
		pos+=b;
	}
}

string latex( string str ){
    string s = str;
    string_replace( s, "!", "\\overline " );
    string_replace( s, "~", "\\overline " );
    /* when variable has q^2, there will be a bug, so don't input ^ in var */
    string_replace( s, "^", "\\oplus " );
    string_replace( s, "(", "{(" );
    string_replace( s, ")", ")}" );
    return s;
}

string latex( int a ){
    return to_string(a);
}

void CombinedLogic::zenAddVariable( string s ){
    // + * 
}

CombinedLogic::CombinedLogic():Formulas(nullptr), simplifiedFormulas(nullptr) {}

CombinedLogic::CombinedLogic( vector<string> V, vector<string> T, string F[])
: VariableArr(V), TargetArr(T)
{
    Formulas = new string[TargetArr.size()];
    for( int i = 0; i < TargetArr.size(); ++i ){
        Formulas[i] = F[i];
    }
}

CombinedLogic::~CombinedLogic(){
    delete []binTable;
    delete []truthTable;
    if(!Formulas) delete []Formulas;
    if(!simplifiedFormulas) delete []simplifiedFormulas;
}

void CombinedLogic::init( int mode ){
    if( mode == 1){
        inputVariableArr();
        inputTargetArr();
        inputFormula();
        latexInputSimplify();
        makeBinTable();
        calculateTruthTable();
        simplifyFormula();
    }else if( mode == 2 ){
        inputVariableArr();
        inputTargetArr();
        makeBinTable();
        inputTruthTable();
        simplifyFormula();
    }else if( mode == 3 ){
        inputZenFormula();
        makeBinTable();
        calculateTruthTable();
    }else if( mode == 4 ){
        inputVariableArr();
        inputTargetArr();
        makeBinTable();
        inputMinimum();
        simplifyFormula();
    }else{
        exit(0);
    }
    
}

void CombinedLogic::inputVariableArr(){
    string temp;
    int i = 0, eq;
    cout << "please input vars name" << endl;
    while( cin >> temp ){
        if( temp == "0" ) break;
        VariableArr.push_back(temp);
        if( (eq = VariableArr[i].find("=")) != string::npos ){
            string toReplace = VariableArr[i].substr(0, eq);
            string tobeReplaced = VariableArr[i].substr(eq+1);
            cout << "var " << i+1 << " : " << tobeReplaced << "(" << toReplace << ")" << endl;
            i++;
        }else{
            cout << "var " << i+1 << " : " << VariableArr[i++] << endl;
        }

    }
}

void CombinedLogic::inputTargetArr(){
    string temp;
    int i = 0, eq;
    cout << "please input targets name" << endl;
    while( cin >> temp ){
        if( temp == "0" ) break;
        TargetArr.push_back(temp);
        if( (eq = TargetArr[i].find("=")) != string::npos ){
            string toReplace = TargetArr[i].substr(0, eq);
            string tobeReplaced = TargetArr[i].substr(eq+1);
            cout << "target " << i+1 << " : " << tobeReplaced << "(" << toReplace << ")" << endl;
            i++;
        }else{
            cout << "target " << i+1 << " : " << TargetArr[i++] << endl;
        }
    }
}

void CombinedLogic::inputTruthTable(){
    int v_col = VariableArr.size(), row = pow(2, v_col);
    int t_col = TargetArr.size();
    truthTable = new int[row*t_col];
    for( int k = 0; k < t_col; ++k ){

        for( int i = 0; i < v_col; ++i ) cout << VariableArr[i] << "  ";
        for( int i = 0; i < t_col; ++i ) cout << TargetArr[i] << "  ";
        cout << endl;

        for( int i = 0; i < row; ++i ){
            for( int j = 0; j < VariableArr.size(); ++j ) cout << binTable[i*v_col+j] << "  ";
            for( int j = 0; j < k; ++j ) cout << truthTable[i*t_col+j] << "  ";

            cin >> truthTable[i*t_col+k];
        }
        cout << endl;
    }    
}

void CombinedLogic::inputFormula(){
    int eq;
    Formulas = new string[TargetArr.size()];
    cout << "please input each formula:" << endl;
    for( int i = 0; i < TargetArr.size(); ++i ){
        if( (eq = TargetArr[i].find("=")) != string::npos )
        cout << TargetArr[i].substr(eq+1) << "(" << TargetArr[i].substr(0, eq) << ")=";
        else cout << TargetArr[i] << "=";

        cin >> Formulas[i];
    }
}

void CombinedLogic::inputZenFormula(){
    cout << "here it go:" << endl;
    string input; cin >> input;

    int tarnum, lastequal = 0;
    while( lastequal = input.find( "=", lastequal ) != string::npos ){
        tarnum ++;
    }

    Formulas = new string[tarnum];

    int i = 0;
    while( 1 ){
        // find =, add tar, add formulas, when add formulas, find new var
        
        int equal = input.find( "=" );
        int comma = input.find( "," );
        TargetArr.push_back( input.substr(0,equal) );
        Formulas[i++] = input.substr(equal+1,comma);
        input.erase( 0, equal+1 );
        for( int l = 0; Formulas[i-1][l] != ','; l++ ){
            if( 
                Formulas[i-1][l] == '+' ||
                Formulas[i-1][l] == '*' ||
                Formulas[i-1][l] == '!' ||
                Formulas[i-1][l] == '^' ||
                Formulas[i-1][l] == '(' ||
                Formulas[i-1][l] == ')'
            ){
                continue;
            }else{
                VariableArr.push_back( string(Formulas[i-1][l], 1 ) );
            }
        }
        input.erase(0,1);
    }

}

void CombinedLogic::inputMinimum(){
    int v_col = VariableArr.size(), row = pow(2, v_col);
    int t_col = TargetArr.size();
    truthTable = new int[row*t_col];

    for( int i = 0; i < t_col; ++i ){
        /* basic information */
        cout << TargetArr[i] << "(";
        for( int j = 0; j < v_col; ++j ){
            cout << VariableArr[j];
            if(j!=v_col-1) cout << ",";
        }
        cout << ") = \u03A3m(";
        string input; cin >> input;

        /* add 0 to truthTable */
        for( int j = 0; j < pow(2, v_col); ++j ) truthTable[j*t_col+i] = 0;

        /* add 1 to truthTable */
        while( !input.empty() ){
            int comma = input.find(",", 0);
            if( comma == -1 ){
                comma = input.find(")", 0);
            }
            int add = atoi( input.substr(0, comma).c_str() );
            truthTable[add*t_col+i] = 1;
            input.erase(0, comma+1);
        }
    }
}

void CombinedLogic::latexInputSimplify( void ){
    int eq;
    for( int i = 0; i < VariableArr.size(); ++i ){
        if( (eq = VariableArr[i].find("=")) == string::npos ) continue;
        string toReplace = VariableArr[i].substr(0, eq);
        string tobeReplaced = VariableArr[i].substr(eq+1);

        for( int j = 0; j < TargetArr.size(); ++j ){
            string_replace( Formulas[j], tobeReplaced, toReplace );
        }
        VariableArr[i] = toReplace;
    }
    for( int i = 0; i < TargetArr.size(); ++i ){
        if( (eq = TargetArr[i].find("=")) == string::npos ) continue;
        string toReplace = TargetArr[i].substr(0, eq);
        string tobeReplaced = TargetArr[i].substr(eq+1);

        for( int j = 0; j < TargetArr.size(); ++j ){
            string_replace( Formulas[j], tobeReplaced, toReplace );
        }
        TargetArr[i] = toReplace;
    }
}

void CombinedLogic::makeBinTable(){
    int col = VariableArr.size();
    int row = pow(2, col);
    binTable = new int[row*col];

    int repeatTime = row/2;
    for( int j = 0; j < col; ++j ){
        for( int i =0; i < row; ++i ){
            binTable[i*col+j] = i/repeatTime % 2 == 0 ? 0 : 1;
        }
        repeatTime /= 2;
    }
}

void CombinedLogic::calculateTruthTable(){
    int col = TargetArr.size(), row = pow(2, VariableArr.size());
    truthTable = new int[col*row];
    for( int j = 0; j < col; ++j ){
        FormulaAnalyzer analyzer(Formulas[j], VariableArr, TargetArr);
        for( int i = 0; i < row; ++i ){
            vector<int> valueArr;
            for( int k = 0; k < VariableArr.size(); ++k ) valueArr.push_back(binTable[i*VariableArr.size()+k]);
            truthTable[i*col+j] = analyzer.calculate(valueArr, Formulas);
        }
    }
}

void CombinedLogic::simplifyFormula(){
    simplifiedFormulas = new string[TargetArr.size()];
    for( int i = 0; i < TargetArr.size(); ++i ){
        vector<int> minium;
        for( int j = 0; j < pow(2, VariableArr.size()); ++j ){
            if( truthTable[j*TargetArr.size()+i] == 1 ){
                minium.push_back(j);
            }
        }
        QM qm( minium, VariableArr );
        simplifiedFormulas[i] = qm.outputResult();
    }
}

void CombinedLogic::outputTruthTable(){
    cout << endl << "truth table:" << endl;
    for( int i = 0; i < VariableArr.size(); ++i ) cout << VariableArr[i] << "  ";
    cout << " ";
    for( int i = 0; i < TargetArr.size(); ++i ) cout << TargetArr[i] << "  ";
    cout << endl;
    for( int i = 0; i < pow(2,VariableArr.size()); ++i ){
        for( int j = 0; j < VariableArr.size(); ++j ){
            cout << binTable[i*VariableArr.size()+j] << "  ";
        }
        cout << " ";
        for( int j = 0; j < TargetArr.size(); ++j ){
            cout << truthTable[i*TargetArr.size()+j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void CombinedLogic::outputKarnaughTable(){
    int rightNum = TargetArr.size(), leftNum = VariableArr.size();
    int i = 0; // create i map
    while( i < rightNum ){
        int row_element = leftNum/2, col_element = leftNum - row_element;
        int K_row = pow(2, row_element), K_col = pow(2, col_element);
        int K_row_i = 0, K_col_i = 0; // for for ~

        cout << "Karnaugh map of " << TargetArr[i] << ":" << endl;
        /* first line */
        for( int i = 0; i < leftNum; ++i ){
            cout << VariableArr[i];
            if( i == leftNum/2-1 ) cout << "\\";
        }
        for( int i = 0; i < K_col; ++i ){
            cout << " " << to_bin(to_Gray(i), col_element);
            if( i == K_col - 1 ) cout << "\n";
        }

        /* other line */
        for( K_row_i = 0; K_row_i < K_row; ++K_row_i ){
            cout << setw(leftNum+1) << to_bin(to_Gray(K_row_i), row_element);
            for( K_col_i = 0; K_col_i < K_col; ++K_col_i ){
                for(int m=0; m<col_element; ++m) cout << " ";
                cout << truthTable[(to_Gray(K_row_i)*(K_col)+to_Gray(K_col_i))*rightNum+i];
            }
            cout << endl;
        }
        cout << endl;
        ++i;
    }
}

void CombinedLogic::outputMinimum(){
    int v_col = VariableArr.size(), row = pow(2, v_col);
    int t_col = TargetArr.size();
    for( int i = 0; i < t_col; ++i ){
        cout << TargetArr[i] << "(";
        for( int j = 0; j < v_col; ++j ){
            cout << VariableArr[j];
            if( j != v_col-1 ) cout << ",";
        }
        cout << ") = \u03A3m(";
        // to get the last 1
        vector<int> minium;
        for( int j = 0; j < row; ++j ){
            if( truthTable[j*t_col+i] == 1 ){
                minium.push_back(j);
            }
        }
        for( int j = 0; j < minium.size(); ++j ){
            cout << minium[j];
            if( j != minium.size()-1 ) cout << ",";
        }
        cout << ")" << endl;
    }
    cout << endl;
}

void CombinedLogic::outputSOP(){
    if(simplifiedFormulas!=nullptr){
        for( int i = 0; i < TargetArr.size(); ++i ){
            cout << TargetArr[i] << " = " << simplifiedFormulas[i] << endl;
        }
    }else{
        for( int i = 0; i < TargetArr.size(); ++i ){
            cout << TargetArr[i] << " = " << Formulas[i] << endl;
        }
    }
    cout << endl;
}

void CombinedLogic::exportMarkdowm( string filename ){
    string path = "D:/zbc/Desktop/";
    string totalpath = path+filename+".md";
    ofstream ofs;
    ofs.open(totalpath, ios::out);
    if( !ofs.is_open() ) exit(0);

    int v_col = VariableArr.size(), row = pow(2, v_col);
    int t_col = TargetArr.size();

    ofs << "# " << filename << endl << endl;
    /* formula */
    if(Formulas!=nullptr){
        ofs << "## formula" << endl << endl;
        for( int i = 0; i < t_col; ++i ){
            ofs << "> " << "$" << latex(TargetArr[i])
            << "=" << latex(Formulas[i]) << "$" << endl;
        }
        ofs << endl;
    }
    /* truth table */
    ofs << "## truth table:" << endl << endl;
    for( int i = 0; i < v_col; ++i ){ ofs << "|" << "$" << latex(VariableArr[i]) << "$"; }
    for( int i = 0; i < t_col; ++i ){ ofs << "|" << "$" << latex(TargetArr[i]) << "$"; }
    ofs << "|" << endl;
    for( int i = 0; i < v_col + t_col; ++i ) ofs << "|:-:";
    ofs << "|" << endl;
    for( int i = 0; i < row; ++i ){
        for( int j = 0; j < v_col; ++j ){
            ofs << "|" << binTable[i*v_col+j];
        }
        for( int j = 0; j < TargetArr.size(); ++j ){
            ofs << "|" << truthTable[i*t_col+j];
        }
        ofs << "|" << endl;
    }
    ofs << endl;
    /* minium */
    for( int i = 0; i < t_col; ++i ){
        ofs << "> " << "$" << latex(TargetArr[i]) << latex("(");
        for( int j = 0; j < v_col; ++j ){
            ofs << latex(VariableArr[j]);
            if( j != v_col-1 ) ofs << latex(",");
        }
        ofs << latex(") = \\sum m(");
        // to get the last 1
        vector<int> minium;
        for( int j = 0; j < row; ++j ){
            if( truthTable[j*t_col+i] == 1 ){
                minium.push_back(j);
            }
        }
        for( int j = 0; j < minium.size(); ++j ){
            ofs << minium[j];
            if( j != minium.size()-1 ) ofs << ",";
        }
        ofs << latex(")") << "$" << endl;
    }
    ofs << endl;
    /* standerd SOP */
    if(simplifiedFormulas!=nullptr){
        ofs << "$Minium\\enspace SOP\\enspace expressions:$" << endl;
        for( int i = 0; i < TargetArr.size(); ++i ){
            ofs << "> $" << TargetArr[i] << " = " << latex(simplifiedFormulas[i]) << "$" << endl;
        }
        ofs << "> " << endl << endl;
    }
    /* Karnaugh Map */
    ofs << "## Karnaugh Map" << endl << endl;
    int i = 0; // create i map
    while( i < t_col ){
        int row_element = v_col/2, col_element = v_col - row_element;
        int K_row = pow(2, row_element), K_col = pow(2, col_element);
        int K_row_i = 0, K_col_i = 0; // for for ~

        ofs << "$" << "Karnaugh\\enspace map\\enspace of\\enspace " << (TargetArr[i]) << ":" << "$" << endl << endl;
        /* first line */
        ofs << "|" << "$";
        for( int i = 0; i < v_col; ++i ){
             ofs << latex(VariableArr[i]);
            if( i == v_col/2-1 ) ofs << "\\backslash ";
        }
        ofs << "$";
        for( int i = 0; i < K_col; ++i ){
            ofs << "|" << to_bin(to_Gray(i), col_element);
            if( i == K_col - 1 ) ofs << "|" << endl;
        }

        for( int i = 0; i < K_col+1; ++i ) ofs << "|:-:";
        ofs << "|" << endl;
        /* other line */
        for( K_row_i = 0; K_row_i < K_row; ++K_row_i ){
            ofs << "|" << to_bin(to_Gray(K_row_i), row_element);
            for( K_col_i = 0; K_col_i < K_col; ++K_col_i ){
                ofs << "|" << truthTable[(to_Gray(K_row_i)*(K_col)+to_Gray(K_col_i))*t_col+i];
            }
            ofs << "|" << endl;
        }

        ofs << endl;

        ++i;
    }
    ofs.close();
    system( ("start "+totalpath).c_str() );
}
