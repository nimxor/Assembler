# Assembler

###Steps to generate opcode and symbol table:
######Symbol table is generated in "symbol1.txt" . 
1. :  We have two input files for our program in assembly language name "inp1.txt" and "inp2.txt".
2. :  1.c is Code to generate every assembly instruction into 32 bit binary instuction .
3. :  After Execution of 1.c corresponding to "inp1.txt" , "out1.txt" will be generated along with "symbol1.txt" .
4. :  2.c is Code to generate final output ,states of flag registers and ALU control signals are displayed .

###Execution of code
```bash
 gcc 1.c
 ```
 ```bash
 ./a.out
 ```
 ```bash
 gcc 2.c
 ```
 ```bash
 ./a.out
 ```
