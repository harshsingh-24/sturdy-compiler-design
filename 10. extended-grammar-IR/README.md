<h1 align = "center"> 3-address code generation </h1>

<h2 id="usage"> 📋 Usage Instructions </h2>

1. Compile the `parse.y` program using `yacc parse.y -d'. The result of the compilation are these two files - `parse.tab.h` and `parse.tab.c`.
2. Compile the `lex.l` program using `lex lex.l`.
3. Compile `parse.tab.c` using `g++ parse.tab.c -o parser`
4. Execute the parser using `./parser.exe`

Note: 
1. If you want to change the input to parser, modify `input.txt`.
2. `parse.y` has logic for grammar.
3. `lex.l` has logic for generating tokens.

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

<h2 id="usage"> ✨ Sample I/O </h2>

1. Input 

```
global 
    // assignment statements:
    test := ((a+b)*(200/12*2))mod(100*10);
    test := (r*s)+(x+y-z);

    // read statements:
    read %d y;

    // while statement:
    while (a<=b and not a>z):
        read %d test;
        test:=test+1;
        // if statement:
        if ((i mod 2)=0): 
            // print statement:
            print "#EVEN"
        else
            print "#ODD"
        end; 
        if test=100:
           print "EXIT"
        end;
        // skip statement:
        print "skip"
    end
end

```
Output

```
t0 = a + b
t1 = 200 / 12       
t2 = t1 * 2
t3 = t0 * t2        
t4 = 100 * 10       
t5 = t3 % t4        
test = t5
t6 = r * s
t7 = x + y
t8 = t7 - z
t9 = t6 + t8        
test = t9
READ %d y
L0: t10 = a <= b
t11 = a > z
t12 = !t11
t13 = t10 && t12
if t13 <= 0  goto L1
READ %d test
t14 = test + 1
test = t14
t15 = i % 2
t16 = t15 == 0
if t16 <= 0  goto L2
PRINT "#EVEN"
goto L3
L2: PRINT "#ODD"
L3: t17 = test == 100
if t17 <= 0  goto L4
PRINT "EXIT"
goto L5
L4:
L5: PRINT "skip"
goto L0
L1: EXIT
Accepted
```

2. Input 

```
global 

	x := 1;
	y := x + 5;
	z := y + x;
	
	print "x";
    print %d x;
	read %d y;
	
	if p <> q and a = 5:
		print "c";
		if b > 0: print "c" else b := b + 1 end;
		print "q"
	else
		print "a";
		print "b"
	end;

	while x > y:
		p := x + 1;
		while a > b:
			q := y + 1
		end
	end	
end
```

Output - 

```
x = 1
t0 = x + 5
y = t0
t1 = y + x
z = t1
PRINT "x"
PRINT %d x
READ %d y
t2 = p != q        
t3 = a == 5        
t4 = t2 && t3      
if t4 <= 0  goto L0
PRINT "c"
t5 = b > 0
if t5 <= 0  goto L2
PRINT "c"
goto L3
L2: t6 = b + 1     
b = t6
L3: PRINT "q"      
goto L1
L0: PRINT "a"      
PRINT "b"
L1: L4: t7 = x > y 
if t7 <= 0  goto L5
t8 = x + 1
p = t8
L6: t9 = a > b
if t9 <= 0  goto L7
t10 = y + 1
q = t10
goto L6
L7: goto L4
L5: EXIT
Accepted
```
![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

<h2 id="usage"> ✨ Code Templates </h2>

1. if (E) S1 else S2

```
code for E (result in T)
if T <= 0 goto L1 /* if T is false, jump to else part */
code for S1 /* all exits from within S1  also jump to L2 */
goto L2 /* jump to exit */
L1: code for S2 /* all exits from within S2 also jump to L2 */
L2: /* exit */
```

2. If (E) S

```
code for E (result in T)
if T <= 0 goto L1 /* if T is false, jump to else part */
code for S /* all exits from within S  also jump to L1 */
L1: /* exit */

```

3. while (E) do S

```
L1: code for E (result in T)
if T <= 0 goto L2 /* if T is false, jump to else part */
code for S /* all exits from within S  also jump to L1 */
goto L1 /* jump to exit */
L2: /* exit */
```


![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

<!-- CREDITS -->
<h2 id="credits"> 🎇 Credits</h2>

Harsh Singh Jadon 

[![Twitter Badge](https://img.shields.io/badge/Twitter-1DA1F2?style=for-the-badge&logo=twitter&logoColor=white)](https://twitter.com/harshsjadon)
[![GitHub Badge](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/harshsingh-24)
[![LinkedIn Badge](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/harsh-singh-jadon-55ab4519a/)

