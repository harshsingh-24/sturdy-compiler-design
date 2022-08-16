%{
    #define ERROR -1
%}
%%
(0|1)*0 {printf("ACCEPTED");}
.* {printf("REJECTED");}
%%
int yywrap(void) {return 1;}
int main() {
    yyin = fopen("input.txt", "r");
    while((yylex()) != 0) 
        printf("%s \n", yytext);
} 