/***  Lexical Analyser ***/
%{
    #define ERROR -1
    #define IF 1
    #define THEN 2
    #define ELSE 3
    #define ID 4
    #define NUMBER 5
    #define RELOP 6
    #define WHITESPACE 7
%}

delim [ \t\n]
whitespace ({delim}+)
digit [0-9]
letter [a-zA-Z]
digits ({digit}+)
number {digits}(\.{digits})?(E[+-]?{digits})?
l_or_d ({letter}|{digit})
identifier ({letter}{l_or_d}*)
if (if)
then (then)
else (else)
relop (<|>|<=|>=|<>|=)

%%
{whitespace} {return WHITESPACE;}
{if} {return IF;}
{then} {return THEN;}
{else} {return ELSE;}
{number} {return NUMBER;}
{identifier} {return ID;}
{relop} {return RELOP;}
. {return ERROR;}
%%

int yywrap(void) {return 1;}

int main() {
    int token;
    yyin = fopen("input.txt", "r");
    while((token=yylex()) != 0) {
        if(token == 1) {
            printf("(if,)\n");
        } else if(token == 2) {
            printf("(then,)\n");
        } else if(token == 3) {
            printf("(else,)\n");
        } else if(token == 4) {
            printf("(id,%s)\n", yytext);
        } else if(token == 5) {
            printf("(number,%s)\n", yytext);
        } else if(token == 6) {
            printf("(relop,%s)\n", yytext);
        } else if(token == 7) {
            continue;
        } else {
            printf("ERROR!");
            break;
        }
    }
} 