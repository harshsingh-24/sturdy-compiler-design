%{
    #include<stdio.h>
    #include<cstring> 
    #include "stringwrapper.h"
    #include "parse.tab.h" 
    #define ERROR -1
%}

%option yylineno

digit [0-9]
letter [a-zA-Z]

%%
and return AND;
:= return ASSIGN;
: return COLON;
\/ return DIV;
else return ELSE;
end return END;
= return EQ;

(%d|%s) {
    char* temp = strdup(yytext);
    yylval.identifier = temp;
    return FORMAT;
};

>= return GE;
global return GLOBAL;
> return GT;
if return IF;
int return INT;
\( return LEFT_PAREN;
\<\= return LE;
\< return LT;
- return MINUS;
mod return MOD;
\* return MULT;
\<\> return NE;
not return NOT;
or return OR;
\+ return PLUS;
print return PRINT;
read return READ;
\) return RIGHT_PAREN;
; return SEMICOLON;

\"([^\\\"]|\\.)*\" {
    char* temp = strdup(yytext);
    yylval.identifier = temp;
    return STRING;
}

while return WHILE;

{digit}{digit}*(E[+-]?{digit}{digit}*)? { 
    int temp = atoi(yytext);
    yylval.value = temp;
    return INT_CONST;
}

{letter}({letter}|{digit})*  {
    char* temp = strdup(yytext);
    yylval.identifier = temp;
    return ID;
}

\/\/.*\n {}
[ \t\n] {}
. return ERROR;


%%
int yywrap(void) {return 1;}