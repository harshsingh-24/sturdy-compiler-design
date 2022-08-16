<h1 align = "center"> Lexical Analyser using Flex </h1>
Lexical Analyser is a process of converting a sequence of characters (such as in a computer program) into a sequence of lexical tokens (strings with an assigned and thus identified meaning). FLEX (fast lexical analyzer generator) is a tool/computer program for generating lexical analyzers (scanners or lexers).

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

<h2 id="usage"> 📋 Usage Instructions </h2>

1. Clone this repository using
`git clone https://github.com/harshsingh-24/sturdy-compiler-design.git` or downloading the zip-file.
2. Convert Lex to C program using the following command -  `lex <file_name>.l`
2. Compile the `lex.yy.c` file using `gcc lex.yy.c` 
3. Run the executable generated using `./a.exe`
4. Provide the input to the program. Currently, the Lexical Analyser generates tokens only for if, else, then, numbers, identifiers and whitespaces present in a sequence. 

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

<h2 id="usage"> 🎁 Context Free Grammar </h2>

``Language Support : `` The Context Free Grammar for which our Lexical Analyser is able to generate tokens is as follows - 

```
stmt -> if expr then stmt | if expr then stmt else stmt | epsilon

expr -> term relop term | term

term -> identifier | number
```

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

<h2 id="usage"> 💥 Pattern for Tokens </h2>

The patterns for the tokens in the above language are described below:

```
digit -> [0-9]
digits -> digit+
number -> digits  (. digits)?(E[+-]? digits)?
letter -> [A-Za-z]
identifier -> letter (letter | digit)*
if -> if
then -> then
else -> else
relop -> < | > | <= | >= | == | !=
main -> main
int -> int
assignmentOp -> =
arithmeticOp -> - | + | * | /
logicalOp -> && | || | !
seperator -> [,;(){}]
unaryOp -> ++ | --
```

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

<h2 id="usage"> ✨ Examples </h2>

### 1. `Input:`

```
main()
{
    int i=0;
    int total=0;
    float count;
    read(count);
    for(i=0, j=0;i<10 && j<15; i++, j+=2)
    {
        read(x);
        total= total+x;
    }
    print(total);
}
```

`Output Tokens:`

```
(mainFunction,main)
(separator,"(")      
(separator,")")      
(separator,"{")      
(dataType,int)       
(id,i)
(assignmentOp,=)     
(number,0)
(separator,";")      
(dataType,int)       
(id,total)
(assignmentOp,=)     
(number,0)
(separator,";")      
(dataType,float)     
(id,count)
(separator,";")      
(inputConstruct,read)
(separator,"(")      
(id,count)
(separator,")")      
(separator,";")
(loopKeyword,for)
(separator,"(")
(id,i)
(assignmentOp,=)
(number,0)
(separator,",")
(id,j)
(assignmentOp,=)
(number,0)
(separator,";")
(id,i)
(relOp,<)
(number,10)
(logicalOp,&&)
(id,j)
(relOp,<)
(number,15)
(separator,";")
(id,i)
(unaryOp,++)
(separator,",")
(id,j)
(assignmentOp,+=)
(number,2)
(separator,")")
(separator,"{")
(inputConstruct,read)
(separator,"(")
(id,x)
(separator,")")
(separator,";")
(id,total)
(assignmentOp,=)
(id,total)
(arithmeticOp,+)
(id,x)
(separator,";")
(separator,"}")
(outputConstruct,print)
(separator,"(")
(id,total)
(separator,")")
(separator,";")
(separator,"}")
```

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

<!-- CREDITS -->
<h2 id="credits"> 🎇 Credits</h2>

Harsh Singh Jadon 

[![Twitter Badge](https://img.shields.io/badge/Twitter-1DA1F2?style=for-the-badge&logo=twitter&logoColor=white)](https://twitter.com/harshsjadon)
[![GitHub Badge](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/harshsingh-24)
[![LinkedIn Badge](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/harsh-singh-jadon-55ab4519a/)
