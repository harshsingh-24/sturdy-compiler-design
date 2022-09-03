/***  Lexical Analyser ***/
%{

    /** TERMINALS **/
    #define ERROR -1
    #define _AE 1
    #define _BE 2
    #define _D 3
    #define _DL 4
    #define _E 5
    #define _F 6
    #define _ES 7
    #define _IOS 8
    #define _IS 9
    #define _NE 10
    #define _P 11
    #define _PE 12
    #define _RE 13
    #define _S 14
    #define _SL 15
    #define _T 16
    #define _TY 17
    #define _VL 18
    #define _WS 19

    /** NON_TERMINALS **/
    #define PLUS 20
    #define MINUS 21
    #define MULTIPLY 22
    #define DIVIDE 23
    #define EQUAL 24
    #define LT 25
    #define GT 26
    #define OPENPARANTHESES 27
    #define CLOSEPARANTHESES 28
    #define OPENBRACES 29
    #define CLOSEBRACES 30
    #define ASSIGNMENT 31
    #define SEMICOLON 32
    #define AND 33
    #define ELSE 34
    #define END 35
    #define IC 36
    #define ID 37
    #define IF 38
    #define INT 39
    #define DO 40
    #define FC 41
    #define FLOAT 42
    #define NOT 43
    #define OR 44
    #define PRINT 45
    #define PROG 46
    #define SCAN 47
    #define STR 48
    #define THEN 49
    #define WHILE 50

    /** EXTRA CHARACTERS **/
    #define ARROW 51
    #define PIPE 52
    #define WHITESPACE 53
    #define NEWLINE 54
    #define EPSILON 55
%}

AE                  {AE}
BE                  {BE}
D                   {D}
DL                  {DL}
E                   {E}
F                   {F}
ES                  {ES}
IOS                 {IOS}
IS                  {IS}
NE                  {NE}
P                   {P}
PE                  {PE}
RE                  {RE}
S                   {S}
SL                  {SL}
T                   {T}
TY                  {TY}
VL                  {VL}
WS                  {WS}

plus                (\+)
minus               (-)
multiply            (\*)
divide              (/)
equal               (=)
lt                  (<)
gt                  (>)
openparantheses     (\()
closeparantheses    (\))
openbraces          (\{)
closebraces         (\})
assignment          (:=)
semicolon           (;)
and                 (and)
else                (else)
end                 (end)
if                  (if)
int                 (int)
do                  (do)
float               (float)
not                 (not)
or                  (or)
print               (print)
prog                (prog)
scan                (scan)
then                (then)
while               (while)

digit               [0-9]
letter              [a-zA-Z]
digits              ({digit}+)
l_or_d              ({letter}|{digit})
ic                  [-]?{digits}
id                  ({letter}{l_or_d}*)
fc                  [-]?{digits}(\.{digits})?(E[+-]?{digits})?
str                 (\"([^\\\"]|\\.)*\")

arrow               (->)
pipe                (|)
whitespace          [ \t]+
newline             [\n]+
epsilon             (#)

%%

{AE}                {return _AE;}
{BE}                {return _BE;}
{D}                 {return _D;}
{DL}                {return _DL;}
{E}                 {return _E;}
{F}                 {return _F;}
{ES}                {return _ES;}
{IOS}               {return _IOS;}
{IS}                {return _IS;}
{NE}                {return _NE;}
{P}                 {return _P;}
{PE}                {return _PE;}
{RE}                {return _RE;}
{S}                 {return _S;}
{SL}                {return _SL;}
{T}                 {return _T;}
{TY}                {return _TY;}
{VL}                {return _VL;}
{WS}                {return _WS;}

{plus}                {return PLUS;}
{minus}               {return MINUS;}
{multiply}            {return MULTIPLY;}
{divide}              {return DIVIDE;}
{equal}               {return EQUAL;}
{lt}                  {return LT;}
{gt}                  {return GT;}
{openparantheses}     {return OPENPARANTHESES;}
{closeparantheses}    {return CLOSEPARANTHESES;}
{openbraces}          {return OPENBRACES;}
{closebraces}         {return CLOSEBRACES;}
{assignment}          {return ASSIGNMENT;}
{semicolon}           {return SEMICOLON;}
{and}                 {return AND;}
{else}                {return ELSE;}
{end}                 {return END;}
{ic}                  {return IC;}
{id}                  {return ID;}
{if}                  {return IF;}
{int}                 {return INT;}
{do}                  {return DO;}
{fc}                  {return FC;}
{float}               {return FLOAT;}
{not}                 {return NOT;}
{or}                  {return OR;}
{print}               {return PRINT;}
{prog}                {return PROG;}
{scan}                {return SCAN}
{str}                 {return STR;}
{then}                {return THEN;}
{while}               {return WHILE;}

{arrow}               {return ARROW;}
{pipe}                {return PIPE;}
{whitespace}          {return WHITESPACE;}
{newline}             {return NEWLINE;}
{epsilon}             {return EPSILON;}
.                     {return ERROR;}

%%

int yywrap(void) {return 1;}

int main() {
    int token;
    yyin = fopen("input.txt", "r");
    while((token=yylex()) != 0) {
        
        
             
    }
} 


