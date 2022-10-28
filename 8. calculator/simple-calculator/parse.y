%{
    #include <iostream> 
    #include "lex.yy.c"
    using namespace std;
    bool flag = false;
    bool divideByZeroException = false;
    void yyerror(const char *str);
%}

%token DIV INTCONST MINUS MULT PLUS

%left PLUS MINUS
%left MULT DIV

%start S

%%

S: E { 
    if(!divideByZeroException)
        printf("Answer = %d\n", $$); 
    return 0;
};

E: E PLUS T {$$ = $1 + $3;}
| E MINUS T {$$ = $1 - $3;}
| T 
;

T: T MULT F {$$ = $1 * $3;}
| T DIV F   
{
    if($3 != 0)
        $$ = $1 / $3;
    else {
        divideByZeroException = true;
    }
}
| F
;

F: INTCONST {$$ = $1;}
;

%%


int main() 
{ 
    yyin = fopen("input.txt", "r");
    yyparse();
    if(!flag)
	    printf("Entered arithmetic expression is Valid.\n"); 
    if(divideByZeroException) 
        printf("Divide By Zero Exception");
    return 0;
} 

void yyerror(const char *str) { 
	printf("Entered arithmetic expression is Invalid.\n"); 
    flag = true; 
} 