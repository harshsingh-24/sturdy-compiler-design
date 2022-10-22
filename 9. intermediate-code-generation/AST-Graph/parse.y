%{
    #include <iostream> 
    #include <fstream>
    #include "lex.yy.c"
    using namespace std;
    bool flag = false;
    bool divideByZeroException = false;
    void yyerror(const char *str);

    ofstream file("ast-graph.md");

    void inorder(Node* node) {

        if(node -> left) {
            file << node << "[\"" << node->mermaid << "\"]"<< "-->" << node->left << "[\"" << node->left->mermaid << "\"];\n";
            inorder(node->left);
        }
        if(node -> right) {
            file << node << "[\"" << node->mermaid << "\"]"<< "-->" << node->right << "[\"" << node->right->mermaid << "\"];\n";
            inorder(node->right);
        }

        return;
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
    
    // Pre-requisistes
    file << "```mermaid\n";
    file << "graph TD;\n";
    inorder($<node>1);
    file << "```\n";
    return 0;
};

E: E PLUS T 
{
    Node* temp = new Node(true, 1, $<node>1, $<node>3, $<node>1->val + $<node>3->val);
    $<node>$ = temp;
}
| E MINUS T 
{
    Node* temp = new Node(true, 2, $<node>1, $<node>3, $<node>1->val - $<node>3->val);
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
    Node* temp = new Node(true, 3, $<node>1, $<node>3, $<node>1->val * $<node>3->val);
    $<node>$ = temp;
}
| T DIV F   
{
    Node* temp = new Node(true, 4, $<node>1, $<node>3, $<node>1->val / $<node>3->val);
    $<node>$ = temp;
}
| F
{
    $<node>$ = $<node>1;
}
;

F: FLOATCONST 
{
    Node* node = new Node(false, $<value>1);
    $<node>$ = node; // This is where integer nodes are getting created
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

