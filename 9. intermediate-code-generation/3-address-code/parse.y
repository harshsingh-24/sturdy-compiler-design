%{
    #include <iostream> 
    #include <fstream>
    #include "lex.yy.c"
    using namespace std;
    bool flag = false;
    bool divideByZeroException = false;
    void yyerror(const char *str);

    ofstream file("ast-graph.md");

    int k = 0;
    string generateKey() {
        string ans = "t" + to_string(k);
        k++;
        return ans;
    }
%}

%union  { // typedef struct {} yylval;
    float value;
    Node* node;
}

%token DIV FLOATCONST MINUS MULT PLUS

%left PLUS MINUS
%left MULT DIV

%start S

%%

S: E { 
    cout << "Evaluation Result: " << $<node>1->val << endl;
};

E: E PLUS T 
{
    // Node* temp = new Node(true, 1, $<node>1, $<node>3, $<node>1->val + $<node>3->val);
    string key = generateKey();
    cout << key << " = " << $<node>1->label << " + " << $<node>3->label << endl;  
    Node* temp  = new Node(key, $<node>1->val + $<node>3->val);
    $<node>$ = temp;
}
| E MINUS T 
{
    // Node* temp = new Node(true, 2, $<node>1, $<node>3, $<node>1->val - $<node>3->val);
    string key = generateKey();
    cout << key << " = " << $<node>1->label << " - " << $<node>3->label << endl;  
    Node* temp  = new Node(key, $<node>1->val - $<node>3->val);
    $<node>$ = temp;
}
| T 
{
    $<node>$ = $<node>1;
}
;

T: T MULT F 
{
    /* Evaluate */
    // Node* temp = new Node(true, 3, $<node>1, $<node>3, $<node>1->val * $<node>3->val);
    string key = generateKey();
    cout << key << " = " << $<node>1->label << " * " << $<node>3->label << endl;  
    Node* temp  = new Node(key, $<node>1->val * $<node>3->val);
    $<node>$ = temp;
}
| T DIV F   
{
    // Node* temp = new Node(true, 4, $<node>1, $<node>3, $<node>1->val / $<node>3->val);
    string key = generateKey();
    cout << key << " = " << $<node>1->label << " / " << $<node>3->label << endl;  
    Node* temp  = new Node(key, $<node>1->val / $<node>3->val);
    $<node>$ = temp;
}
| F
{
    $<node>$ = $<node>1;
}
;

F: FLOATCONST 
{
    Node* temp  = new Node(to_string($<value>1), $<value>1);
    $<node>$ = temp; // This is where integer nodes are getting created
}
;

%%


int main() 
{ 
    yyin = fopen("input.txt", "r");
    yyparse();
    if(!flag)
	    printf("\n Entered arithmetic expression is Valid.\n"); 
    if(divideByZeroException) 
        printf("\n Divide By Zero Exception");
    return 0;
} 

void yyerror(const char *str) { 
	printf("Entered arithmetic expression is Invalid.\n"); 
    flag = true; 
} 

