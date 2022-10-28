%{
    // DEFINITIVE SECTION
    #include<stdio.h> 
    #include "parse.tab.h" 
    extern int yylval;
%}

%option yylineno

div         (\/)
minus       (-)
mult        (\*)
plus        (\+)
digit       [0-9]
digits      ({digit}+)
intconst   {digits}

%%
{div}               {return DIV;}
{minus}             {return MINUS;}
{mult}              {return MULT;}
{plus}              {return PLUS;}
{intconst}          { 
                        yylval = atoi(yytext);
                        return INTCONST;
                    }
[\t\n" "]           {};  
%%

int yywrap() 
{ 
	return 1; 
} 