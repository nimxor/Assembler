/*
Team Members :
Name :                 	        Roll No:
Shubham Gupta    		14ucs115
Samriddh Kulshrestha            14ucs100
Shailesh Singh			14ucs106
Rahul Vyas			14ucs092	
*/

//Steps to generate opcode and symbol table:
Symbol table is generated in "symbol1.txt" . 
Step1 :	We have two input files for our program in assembly language name "inp1.txt" and "inp2.txt".
Step2 : 1.c : Code to generate every assembly instruction into 32 bit binary instuction .
Step3 : After Execution of 1.c corresponding to "inp1.txt" , "out1.txt" will be generated along with "symbol1.txt" .
Step4 :	2.c : Code to generate final output ,states of flag registers and ALU control signals are displayed .

//Execution of code
1 . gcc 1.c
2 . ./a.out
3 . gcc 2.c
4 . ./a.out

//ISA Design Instruction
Note : In immediate Addressing mode we are only able to pass integer values ranging from 0 to 31 as we have alloted 5 bit for the constant
Note : HERE WE CAN ONLY TAKE LABEL IN THE FORM OF ONE ALPHABET  AND ONE NUMERICAL VALUE THAT IS L1 .
Note : We have used R31 as our special purpose register. */

MOV #16,ROO  /* HERE WE MOVE VALUE 16 INTO REGISTER R00 */
MOV ROO,RO2  /* HERE WE MOVE THE CONTENT OF R00 AND STORES IT INTO R02 */
SUB #1,R00   /* HERE WE SUBSTRACT NUMBER 1 FROM THE CONTENT OF R00 AND 	STORE THE RESULT INTO R00 */
AND R00,RO2  /* HERE WE TAKE THE CONTENT OF R00 AND R02 THEN WE PERFORM  BITWISE AND ON THOSE VALUES AND FINALLY WE STORE THE 			RESULT INSIDE R02*/ 
XOR R00,RO2  /* HERE WE TAKE THE CONTENT OF R00 AND R02 THEN WE PERFORM  BITWISE XOR ON THOSE VALUES AND FINALLY WE STORE THE 			RESULT INSIDE R02*/ 
ADD R00,R01  /* HERE WE ADD THE CONTENTS OF R00 AND RO1 THEN STORES THE RESULTS IN R01 */                   
OR R00,R01   /* HERE WE TAKE THE CONTENT OF R00 AND R02 THEN WE PERFORM  BITWISE OR ON THOSE VALUES AND FINALLY WE STORE THE 			RESULT INSIDE R02*/
NOT R01,R02  /* R01 = !R02 */
CMP #00,R02  /* HERE WE COMPARE THE CONTENT OF R02 FROM THE VALUE 0 AND 
		IF 0=R02 THEN THE STATUS FLAG Z WILL BE SET.
		IF 0<R02  THEN THE SIGN FLAG WILL BE SET.
		IF 0>R02   THEN THE SIGN FLAG WILL BE UNSET.*/
JEQ $L1      /* JUMP TO THE INSTRUCTION ADDRESS L1 IF LAST COMPARISON IS EQUAL TO 0 .
JNE $L2      /* JUMP TO THE INSTRUCTION ADDRESS L2 IF THE LAST COMPARISSION IS NOT EQUAL TO 0*/
IN R01,PORT  /* TAKES VALUE FROM USER IN REGISTER R01*/
OUT PORT,R01 /* PRINTS THE REQUIRED RESULT*/		
L1:          /* IT IS A LABEL*/
HLT          /* AFTER THIS HLT INSTRUCTION EXECUTION OF PROGRAM WILL STOP */
