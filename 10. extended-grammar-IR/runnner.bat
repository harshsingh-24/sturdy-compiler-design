yacc parse.y -d 
lex lex.l
g++ parse.tab.c 
start /b /wait a.exe
pause