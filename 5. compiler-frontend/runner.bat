lex lex-files\grammar-tokenizer.l
gcc lex-files\lex.yy.c -o grammarTokenizer
start lex-files\grammarTokenizer.exe 

lex lex-files\input-tokeniser.l 
gcc lex-files\lex.yy.c -o inputTokeniser 
start lex-files\inputTokeniser.exe 

g++ logic\remove-left-recursion.cpp -o remove-left-recursion 
start logic\remove-left-recursion.exe 

g++ logic\left-factored-grammar.cpp -o left-factored-grammar 
start logic\left-factored-grammar.exe 

g++ logic\first-follow-computation.cpp -o first-follow-computation
start logic\first-follow-computation.exe

g++ logic\predictive-parsing-table.cpp -o predictive-parsing-table
start logic\predictive-parsing-table.exe 

g++ logic\parsing-input.cpp -o parsing-input
start logic\parsing-input.exe 

start text-files\output.txt