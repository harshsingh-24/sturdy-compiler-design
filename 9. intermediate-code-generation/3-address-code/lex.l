%{
    // DEFINITIVE SECTION
    #include<stdio.h>
    #include<string> 
    #include "stringwrapper.h"
    #include "parse.tab.h" 
%}

%option yylineno

div         (\/)
minus       (-)
mult        (\*)
plus        (\+)
digit       [0-9]
digits      ({digit}+)
floatconst  {digits}(\.{digits})?(E[+-]?{digits})?

%%
{div}               {return DIV;}
{minus}             {return MINUS;}
{mult}              {return MULT;}
{plus}              {return PLUS;}
{floatconst}          { 
                        float temp = atof(yytext);
                        yylval.value = temp;
                        return FLOATCONST;
                    }
[\t\n" "]           {};  
%%

int yywrap() 
{ 
	return 1; 
} 