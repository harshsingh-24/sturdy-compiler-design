<h1 align = "center"> Compiler Intermediate Representation </h1>
A compiler can broadly be divided into two phases based on the way they compile. 

The front-end of the compiler or the analysis phase of the compiler reads the source program, divides it into core parts and then checks for lexical, grammar and syntax errors. The analysis phase generates an intermediate code representation of the source program and symbol table, which should be fed to the backend as input.

In the analysis-synthesis model of a compiler, the front end of a compiler translates a source program into an independent intermediate code, then the back end of the compiler uses this intermediate code to generate the target code (which can be understood by the machine). Intermediate Representation can translate the source program into the machine program. Intermediate code is generated because the compiler can’t generate machine code directly in one pass. Therefore, first, it converts the source program into intermediate code, which performs efficient generation of machine code further. The intermediate code can be represented in the form of 3-address code, Abstract Syntax Trees and Directed Acyclic Graph.

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

<h2 id="usage"> 📋 Usage Instructions </h2>

Note: Every folder comprises of seperate .y and .l files for respective tasks. 

1. Clone this repository using
`git clone https://github.com/harshsingh-24/sturdy-compiler-design.git` or downloading the zip-file.
2. Input files: `input.txt`
3. Compile the `parse.y` program using `yacc parse.y -d'. The result of the compilation are these two files - `parse.tab.h` and `parse.tab.c`.
4. Compile the `lex.l` program using `lex tokenizer.l`.
5. Compile `parse.tab.c` using `g++ parse.tab.c -o parser`
6. Execute the parser using `./parser.exe`

Note: We will consider grammar for a simple calculator supporting operations like addition, subtraction, multiplication and division for the above mentioned Intermediate Code Generators.


![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

<h2 id="usage"> 🎁 Abstract Syntax Tree </h2>

``Language Support : `` The Context Free Grammar for which our Frontend is checking the syntax of given input is - 

```
P -> prog DL SL end
DL -> D DL | #
D -> TY VL ;
TY -> int | float
VL -> id VL | id
SL -> S SL | #
S -> ES | IS | WS | IOS
ES -> id := E;
IS -> if BE then SL end | if BE then SL else SL end
WS -> while BE do SL end
IOS -> print PE | scan id
PE -> E | str
BE -> BE or AE | AE
AE -> AE and NE | NE
NE -> not NE | {BE} | RE
RE -> E=E | E<E | E>E
E -> E+T | E-T | T
T -> T*F | T/F | F
F -> (E) | id | ic | fc
```

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

<h2 id="usage"> 💥 Architecture Diagram </h2>

<p align = "center">
<img src="images/architecture.png" style="width:105%; height:90%;"/>
</p>

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

<h2 id="usage"> ✨ Sample Input (Accepted) </h2>

1. 

```
prog 
    int alpha beta;
    float gamma;
    alpha := (4.2E18+304) * (alpha-beta/gamma);
    if alpha>beta or beta<gamma and not gamma=alpha then
        delta := chi;
        print "tau&123"
    else 
        scan lambda
    end 
    while count > 5.2 do 
        omega := omega+1;
    end 
end
```
2. 

```
prog
    int i;
    int j;
    int sum;
    int count;
    float num;
    int temp;
    
    sum:=0;
    count:=5;
    scan count      
    print sum
    
    if count=3 then 
        sum:=2;
    else
        if count < 4 then 
            sum:=2.3E-18;
            if j < i then
                num := 65.42E-90;
            else
                if j < sum then
                    num := 56.7834;
                    print "Harsh Singh@#"
                end

                scan temp
            end
        end
        while count>2.3 do 
            sum:=sum-1;
        end
    end
    
    while sum > 0 do
        count:=count+1;
        i := 1.2345;
        
        if count=3 then 
            sum:=2;
        end
    end
end
```

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

<!-- CREDITS -->
<h2 id="credits"> 🎇 Credits</h2>

Harsh Singh Jadon 

[![Twitter Badge](https://img.shields.io/badge/Twitter-1DA1F2?style=for-the-badge&logo=twitter&logoColor=white)](https://twitter.com/harshsjadon)
[![GitHub Badge](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/harshsingh-24)
[![LinkedIn Badge](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/harsh-singh-jadon-55ab4519a/)
