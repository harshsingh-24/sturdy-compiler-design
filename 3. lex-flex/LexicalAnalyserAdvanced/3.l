/***  Lexical Analyser ***/
%{
    #define ERROR -1
    #define IF 1
    #define THEN 2
    #define ELSE 3
    #define ID 4
    #define NUMBER 5
    #define RELOP 6
    #define ASSIGNOP 7
    #define ARITHMETICOP 8
    #define LOGICALOP 9
    #define DATATYPE 10
    #define LOOPCONSTRUCT 11
    #define SEPARATOR 12
    #define INPUTOP 13
    #define OUTPUTOP 14
    #define MAIN 15
    #define UNARYOP 16
    #define WHITESPACE 17
%}

delim               [ \t\n]
whitespace          ({delim}+)
digit               [0-9]
letter              [a-zA-Z]
digits              ({digit}+)
l_or_d              ({letter}|{digit})
if                  (if)
else                (else)
datatype            (int|float)
loopconstruct       (for|while)
inputop             (read)
outputop            (print)
main                (main)
relop               (<|>|<=|>=|!=|==)
arithmeticop        [-+*/]
assignop            ({arithmeticop})?=
logicalop           (&&|\|\||!)
separator           [;,(){}]
unaryop             (\+\+|--)
number              {digits}(\.{digits})?(E[+-]?{digits})?
identifier          ({letter}{l_or_d}*)

%%
{whitespace}        {return WHITESPACE;}
{if}                {return IF;}
{else}              {return ELSE;}
{datatype}          {return DATATYPE;}
{loopconstruct}     {return LOOPCONSTRUCT;}
{inputop}           {return INPUTOP;}
{outputop}          {return OUTPUTOP;}
{main}              {return MAIN;}
{relop}             {return RELOP;}
{assignop}          {return ASSIGNOP;}
{arithmeticop}      {return ARITHMETICOP;}
{logicalop}         {return LOGICALOP;}
{separator}         {return SEPARATOR;}
{unaryop}           {return UNARYOP;}
{number}            {return NUMBER;}
{identifier}        {return ID;}
.                   {return ERROR;}
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
            printf("(relOp,%s)\n", yytext);
        } else if(token == 7) {
            printf("(assignmentOp,%s)\n", yytext);
        } else if(token == 8) {
            printf("(arithmeticOp,%s)\n", yytext);
        } else if(token == 9) {
            printf("(logicalOp,%s)\n", yytext);
        } else if(token == 10) {
            printf("(dataType,%s)\n", yytext);
        } else if(token == 11) {
            printf("(loopKeyword,%s)\n", yytext);
        } else if(token == 12) {
            printf("(separator,\"%s\")\n", yytext);
        } else if(token == 13) {
            printf("(inputConstruct,%s)\n", yytext);
        } else if(token == 14) {
            printf("(outputConstruct,%s)\n", yytext);
        } else if(token == 15) {
            printf("(mainFunction,%s)\n", yytext);
        } else if(token == 16) {
            printf("(unaryOp,%s)\n", yytext);
        } else if(token == 17) {
            continue;
        } else {
            printf("ERROR!");
            break;
        }
    }
} 