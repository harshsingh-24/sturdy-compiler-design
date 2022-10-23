%{
    #include <iostream> 
    #include <fstream>
    #include <unordered_map>
    #include <unordered_set>
    #include "lex.yy.c"
    using namespace std;
    bool flag = false;
    bool divideByZeroException = false;
    void yyerror(const char *str);

    ofstream file("ast-graph.md");

    unordered_map<string, Node*> m;
    unordered_set<Node*> v;

    Node* searchNode(string t, Node* a, Node* b) {
        string sa = to_string((long long)a);
        string sb = to_string((long long)b);

        string s = t + sa + sb;
        cout << "Formed String Key: " << s << endl;

        if(m.find(s) != m.end()) {
            return m[s];
        }
        return NULL;
    }

    void printMap() {
        for(auto i: m) {
            cout << i.first << endl;
        }
    }

    void inorder(Node* node) {
        if(v.find(node)!=v.end()) return;
        v.insert(node);
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

    printMap();
};

E: E PLUS T 
{
    Node* node = searchNode("+", $<node>1, $<node>3);
    if(node == NULL) {
        string sa = to_string((long long)$<node>1);
        string sb = to_string((long long)$<node>3);

        string s = "+" + sa + sb;
        Node* temp = new Node(1, $<node>1, $<node>3, $<node>1->val + $<node>3->val, s);
        $<node>$ = temp;
        m[s] = temp;
    } else {
        $<node>$ = node;
    }
}
| E MINUS T 
{
    Node* node = searchNode("-", $<node>1, $<node>3);
    if(node == NULL) {
        string sa = to_string((long long)$<node>1);
        string sb = to_string((long long)$<node>3);

        string s = "-" + sa + sb;
        Node* temp = new Node(2, $<node>1, $<node>3, $<node>1->val - $<node>3->val, s);
        $<node>$ = temp;
        m[s] = temp;
    } else {
        $<node>$ = node;
    }
}
| T 
{
    $<node>$ = $<node>1;
}
;

T: T MULT F 
{
    Node* node = searchNode("*", $<node>1, $<node>3);
    if(node == NULL) {
        string sa = to_string((long long)$<node>1);
        string sb = to_string((long long)$<node>3);

        string s = "*" + sa + sb;
        Node* temp = new Node(3, $<node>1, $<node>3, $<node>1->val * $<node>3->val, s);
        $<node>$ = temp;
        m[s] = temp;
    } else {
        $<node>$ = node;
    }
}
| T DIV F   
{
    Node* node = searchNode("/", $<node>1, $<node>3);
    if(node == NULL) {
        string sa = to_string((long long)$<node>1);
        string sb = to_string((long long)$<node>3);

        string s = "/" + sa + sb;
        Node* temp = new Node(4, $<node>1, $<node>3, $<node>1->val / $<node>3->val, s);
        $<node>$ = temp;
        m[s] = temp;
    } else {
        $<node>$ = node;
    }
}
| F
{
    $<node>$ = $<node>1;
}
;

F: FLOATCONST 
{
    string constant = to_string($<value>1);
    if(m.find(constant) != m.end()) {
        $<node>$ = m[constant];
    } 
    else {
        Node* temp = new Node(constant, $<value>1);
        m[constant] = temp;
        $<node>$ = temp;
    }
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

