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
intconst    {digits}
leftparen   (\()
rightparen  (\))
exponent    (^)
modulo      (\%)



%%
{div}               {return DIV;}
{minus}             {return MINUS;}
{mult}              {return MULT;}
{plus}              {return PLUS;}
{intconst}          { 
                        yylval = atoi(yytext);
                        return INTCONST;
                    }
{leftparen}         {return LEFTPAREN;}
{rightparen}        {return RIGHTPAREN;}
{exponent}          {return POWER;}
{modulo}            {return MOD;}
[\t\n" "]           {};  
%%

int yywrap() 
{ 
	return 1; 
} 