# PascalCompilerLinux
This copmiler relies on linux syscalls to operate with files.
My compiler is capable of doing the following:
- outputting pcode from expressions
- emulating pcode expressions from file
- parsing pascal declarations and adding varaibles to symbol table
- outputting human readible pcode
- basic syntax error message on line number

There are 3 flags defined at the top of main.cpp to adjust, they are:
- DEBUG
- BINARY
- EXP_PARSER

If the DEBUG flag is set then all scanned token will be printed in terminal. 

If the BINARY flag is set then the compiler will output a binary pcode file and the emulator will run it. If it is false then the compiler will output human readible pcode which is not emulated, such as:
```
PUSHI 5
PUSHI 2
ADD
```

If the EXP_PARSER flag is set then the input file should only be an expression such as:

```
((4234+545)*144)%5
end.
```

If the EXP_PARSER flag is not set then we can only do varaible declarations and no pcode will be generated, such as:

```
var x,y,z : integer;
r, p : real;
t : char;
begin
end.
```

To download, compile and run the code, paste these comands in your terminal:
```
git clone https://github.com/Matthew1172/PascalCompilerLinux
cd PascalCompilerLinux/cmake-build-debug
make
./PascalCompilerLinux <input-file> <output-file>
```

to run a test example, make sure DEBUG flag is ON, EXP_PARSER flag is ON, BINARY flag is ON. Create a file in the 'cmake-build-debug' directory called `mytest.pascal' which looks like:
```
(25252+4363634+124*2 DIV 7) / 2.1
end;
```
Then run:
```
./PascalCompilerLinux mytest.pascal mytest_output.pcode
```
The result will be printed in the terminal.

Although it is mainly an expression parser right now, it can be used to insert variables into a symbol table with all appropriate attributes. However, I did not get to assignment and statements this semester. If you have a debugger, set a breakpoint on line 212. Set DEBUG to ON, set EXP_PARSER to OFF, set BINARY to OFF. Create a file in the 'cmake-build-debug' directory called `myVarsTest.pascal` and copy the following code:
```
var x,y,z : integer;
j,k : real;
p : char;
begin
end.
```
And then debug the code and inspect the `vars` symbol table. It will be a C++ map keyed by the name of the variable and it's value is a `MyVar` class with the specific attributes set.
