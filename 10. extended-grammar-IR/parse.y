%{
    #include <iostream> 
    #include <stack>
    #include "lex.yy.c"
    using namespace std;
    bool flag = false;
    void yyerror(const char *str);

    int k = 0;
    string generateKey() {
        string ans = "t" + to_string(k);
        k++;
        return ans;
    }

    int l = 0;
    string lineTagGenerate() {
        string ans = "L" + to_string(l);
        l++;
        return ans;
    }

    stack<string> st;

    
%}

%union  { // typedef struct {} yylval;
    int value;
    char* identifier;
    Wrapper* wrapper;
}

%locations
%token AND ASSIGN COLON DIV ELSE END EQ FORMAT GE GLOBAL GT ID IF INT INT_CONST LEFT_PAREN LE LT MINUS MOD MULT NE NOT OR PLUS PRINT READ RIGHT_PAREN SEMICOLON STRING WHILE

%left PLUS MINUS
%left MULT DIV MOD
%left AND OR
%nonassoc NOT

%start S

%%
S: prog {flag = true; return 0;}

prog: GLOBAL stmtListO END
;

stmtListO: stmtList
|
;

stmtList: stmtList SEMICOLON stmt
| stmt
;

stmt: assignmentStmt
| readStmt
| printStmt
| ifStmt
| whileStmt
;

assignmentStmt: id ASSIGN exp {
    cout << $<wrapper>1->label << " = " << $<wrapper>3->label << endl;
}
;

readStmt: READ FORMAT id {
    string format = $<identifier>2;
    cout << "READ " << format << " " << $<wrapper>3->label << endl;
}
;

printStmt: PRINT STRING {
    string s = $<identifier>2;
    cout << "PRINT " << s << endl;
}
| PRINT FORMAT exp {
    string format = $<identifier>2;
    cout << "PRINT " << format << " " << $<wrapper>3->label << endl;
}
;

ifStmt: IF {
    string lineNumber1 = lineTagGenerate();
    string lineNumber2 = lineTagGenerate();

    st.push(lineNumber2);
    st.push(lineNumber1);
    st.push(lineNumber2);
    st.push(lineNumber1);
} 
bExp {
    string label = $<wrapper>3->label;
    cout << "if " << label << " <= 0 " << " goto " << st.top() << endl;
    st.pop();
}
COLON stmtList {
    cout << "goto " << st.top() << endl;
    st.pop();
    cout << st.top() << ": ";
    st.pop();
} 
elsePart {
    cout << st.top() << ": ";
    st.pop();
}
END
;

elsePart: ELSE stmtList 
| 
{
    cout << endl;
}
;


whileStmt: WHILE {
    string lineNumber1 = lineTagGenerate();
    string lineNumber2 = lineTagGenerate();

    cout << lineNumber1 << ": ";
    st.push(lineNumber2);
    st.push(lineNumber1);
    st.push(lineNumber2);
}
bExp {
    string label = $<wrapper>3->label;
    cout << "if " << label << " <= 0 " << " goto " << st.top() << endl;
    st.pop();
}
COLON stmtList {
    cout << "goto " << st.top() << endl;
    st.pop();
    cout << st.top() << ": ";
    st.pop(); 
} 
END
;

id: ID {
    string s = $<identifier>1;
    $<wrapper>$ = new Wrapper(s);
}
;

bExp: bExp OR bExp {
    string key = generateKey();
    cout << key << " = " << $<wrapper>1->label << " || " << $<wrapper>3->label << endl;  
    Wrapper* temp  = new Wrapper(key);
    $<wrapper>$ = temp;
}
| bExp AND bExp {
    string key = generateKey();
    cout << key << " = " << $<wrapper>1->label << " && " << $<wrapper>3->label << endl;  
    Wrapper* temp  = new Wrapper(key);
    $<wrapper>$ = temp;
}
| NOT bExp {
    string key = generateKey();
    cout << key << " = !" << $<wrapper>2->label << endl;  
    Wrapper* temp  = new Wrapper(key);
    $<wrapper>$ = temp;
}
| LEFT_PAREN bExp RIGHT_PAREN {
    $<wrapper>$ = $<wrapper>2;
}
| exp relOP exp {
    string key = generateKey();
    cout << key << " = " << $<wrapper>1->label << " " << $<wrapper>2->label << " " << $<wrapper>3->label << endl;  
    Wrapper* temp  = new Wrapper(key);
    $<wrapper>$ = temp;
}
;

relOP: EQ {
    $<wrapper>$ = new Wrapper("==");
}
| LE {
    $<wrapper>$ = new Wrapper("<=");
}
| LT {
    $<wrapper>$ = new Wrapper("<");
}
| GE {
    $<wrapper>$ = new Wrapper(">=");
}
| GT {
    $<wrapper>$ = new Wrapper(">");
}
| NE {
    $<wrapper>$ = new Wrapper("!=");
}
;

exp: exp PLUS exp {
    string key = generateKey();
    cout << key << " = " << $<wrapper>1->label << " + " << $<wrapper>3->label << endl;  
    Wrapper* temp  = new Wrapper(key);
    $<wrapper>$ = temp;
}
| exp MINUS exp {
    string key = generateKey();
    cout << key << " = " << $<wrapper>1->label << " - " << $<wrapper>3->label << endl;  
    Wrapper* temp  = new Wrapper(key);
    $<wrapper>$ = temp;
}
| exp MULT exp {
    string key = generateKey();
    cout << key << " = " << $<wrapper>1->label << " * " << $<wrapper>3->label << endl;  
    Wrapper* temp  = new Wrapper(key);
    $<wrapper>$ = temp;
}
| exp DIV exp {
    string key = generateKey();
    cout << key << " = " << $<wrapper>1->label << " / " << $<wrapper>3->label << endl;  
    Wrapper* temp  = new Wrapper(key);
    $<wrapper>$ = temp;
}
| exp MOD exp {
    string key = generateKey();
    cout << key << " = " << $<wrapper>1->label << " % " << $<wrapper>3->label << endl;  
    Wrapper* temp  = new Wrapper(key);
    $<wrapper>$ = temp;
}
| LEFT_PAREN exp RIGHT_PAREN {
    $<wrapper>$ = $<wrapper>2;
}
| id {
    $<wrapper>$ = $<wrapper>1;
}
| INT_CONST {
    Wrapper* temp  = new Wrapper(to_string($<value>1));
    $<wrapper>$ = temp;
}
;

%%

int main(){
    int token;
    yyin = fopen("input.txt", "r");
    yyparse();
    cout << "EXIT \n" << (flag ? "Accepted": "Rejected") << endl;
    return 0;
}

void yyerror(const char *str) 
{ 
	printf("%s at line: %d\n", str, yylineno);
} 