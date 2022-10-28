<h1 align = "center"> Lex Analysis and YACC Parsing </h1>
A compiler can broadly be divided into two phases based on the way they compile. 

The front-end of the compiler or the analysis phase of the compiler reads the source program, divides it into core parts and then checks for lexical, grammar and syntax errors.The analysis phase generates an intermediate representation of the source program and symbol table, which should be fed to the backend as input.

This program when given a Context Free Grammar (G) and a program (s) in the language of grammar as input, tells whether the program is valid or not.

We have used YACC and Lex to implement the same. YACC or Yet Another Compiler Compiler provides a tool to produce a parser for a given grammar. It is used to produce the source code of the syntactic analyzer of the language produced by LALR(1) grammar.
 
![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

<h2 id="usage"> 📋 Usage Instructions </h2>

1. Compile the `parse.y` program using `yacc parse.y -d'. The result of the compilation are these two files - `parse.tab.h` and `parse.tab.c`.
2. Compile the `tokenizer.l` program using `lex tokenizer.l`.
3. Compile `parse.tab.c` using `g++ parse.tab.c -o parser`
4. Execute the parser using `./parser.exe`

Note: 
1. If you want to change the input to parser, modify `input1.txt`.
2. `parse.y` has logic for grammar.
3. `tokenizer.l` has logic for generating tokens.

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

<h2 id="usage"> ✨ Sample Input </h2>

1. (Accepted)

```
global 

    def 
        xabc[12][210], tempDat, finDat1 : string
    end

    def
        x := product
                y, z[20] : nul;
                test : float
            end;
        temp1, temp2[10][11], temp3 : int;
        z : myType;
        r : x := product
                data: float;
                dataTest: int
            end
    end
    
    fun testFunction 
        param1[10], parma2[10][10], param3 : int;
        n : float;
        str : string 
    -> int
        def 
            temp[100]: int
        end
        print "This is Harsh Singh"
    end

    // assignment statements:
    test.a.x := ((a+b).(200/12.2))mod(100*10);
    test.b := (r*s)+(x:y+z, 13*2, 12.2E10*5);

    // read statements:
    read %f 100.2E-9;
    read %s (x: a, b);

    // while statement:
    while (a<=b and not a>z):
        read %d test;
        // loop statement:
        from i:= (r*s+10) to (r*r) step 10 :
            test:=test+1;
            // if statement:
            if ((i mod 2)=0): 
                // print statement:
                print "#EVEN"
            else
                print "#ODD"
            end   
        end;
        // call statement:
        (myFun: param1, parma2, param3, n, str);
        if test=100:
            // exit loop statement
           exit 
        end;
        // skip statement:
        skip
    end;

    // return statement
    return data1+data2
end
```
2. (Rejected)

```
global
    
    fun testFunction 
        param1[10], parma2[10][10], param3 : int;
        n : float;
        str : string 
    -> int
        def 
            temp[100]: int
        end
    end

    // assignment statements:
    test.a.x := ((a+b).(200/12.2))mod(100*10);
    test.b := (r*s)+(x:y+z, 13*2, 12.2E10*5);

    // read statements:
    read %f 100.2E-9;
    read %s (x: a, b);

    // while statement:
    while (a<=b and not a>z):
        read %d test;
        // loop statement:
        from i:= (r*s+10) to (r*r) step 10 :
            test:=test+1;
            // if statement:
            if ((i mod 2)=0): 
                // print statement:
                print "#EVEN";
            else
                print "#ODD"
            end   
        end
    end;

    return data1+data2
end
```

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

<!-- CREDITS -->
<h2 id="credits"> 🎇 Credits</h2>

Harsh Singh Jadon 

[![Twitter Badge](https://img.shields.io/badge/Twitter-1DA1F2?style=for-the-badge&logo=twitter&logoColor=white)](https://twitter.com/harshsjadon)
[![GitHub Badge](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/harshsingh-24)
[![LinkedIn Badge](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/harsh-singh-jadon-55ab4519a/)


