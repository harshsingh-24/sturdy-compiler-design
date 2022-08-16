%{
    #define ERROR -1
    int zeroCount = 0, oneCount = 0;
%}
%%
0  {zeroCount++; return 1;}
1  {oneCount++; return 2;}
\n {return 0;}
. {return ERROR;}
%%
int yywrap(void) {return 1;}
int main() {
    yyin = fopen("input.txt", "r");
    while((yylex()) != 0) {;}
    if(zeroCount % 2 == 0 && oneCount % 2 == 1) {
        printf("Accepted\n");
    } else {
        printf("Rejected\n");
    }
} 