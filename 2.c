#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define ull unsigned long long int

char str[80];
char str1[80];
int R[32];
int flag=0;
ull nn;
FILE *fin,*fsymbol;

// Prints the status of flag registers .
void PrintFlag()
{
	if(R[31] & (1<<7))
		printf("**Status of Sign Flag : %d \n",1);
	else
		printf("**Status of Sign Flag : %d \n",0);
	if(R[31] & (1<<1))
		printf("**Status of Zero Flag : %d \n",1);
	else
		printf("**Status of Zero Flag : %d \n",0);
}

// Set the value of flags
void setFlag(int r)
{
	if(r<0){
		R[31] |= (1<<7);
	}
	if(r==0){
		R[31] |= (1<<1);
	}
	PrintFlag();
}

// Returns the opcode in the range (st,en)
int checkBin(int st,int en)
{
	int i,k=1,op=0;
	for(i=st;i<=en;i++)
	{
		if(nn & 1<<i){
			op=k+op;
		}
		k*=10;
	}
	return op;
}

// Converts the binary into Decimal Representation .
ull convertDecimal(int start,int end)
{
	ull ans=0;
	ull k=1;
	int i;
	for(i=end;i>=start;i--)
	{ 
		ans+=k*(str[i]-'0');
		k*=2;
	}
	return ans;
}

// Moves the content
void MOV()
{
	int r1,r2;
	if((nn & 1<<10))
	{
		// Register Addressing Mode
		r1=convertDecimal(22,26);
		r2=convertDecimal(27,31);
		R[r2] = R[r1];	
	}
	else
	{
		// Immediate Addressing Mode
		r1=convertDecimal(22,26);
		r2=convertDecimal(27,31);
		R[r2] = r1;
	}
	printf("MOV R[%d] %d\n",r2,R[r2]);
	setFlag(R[r2]);
}

// Add the contents 
void ADD()
{
	int r1,r2;;
	if((nn & 1<<10))
	{
		// Register Addressing Mode
		r1=convertDecimal(22,26);
		r2=convertDecimal(27,31);
		R[r2] += R[r1];	
	}
	else
	{
		// Immediate Addressing Mode
		r1=convertDecimal(22,26);
		r2=convertDecimal(27,31);
		R[r2] += r1;
	}
	
	printf("ADD R[%d] %d\n",r2,R[r2]);
	setFlag(R[r2]);
}

// Subtract the contents
void SUB()
{
	int r1,r2;;
	if((nn & 1<<10))
	{
		// Register Addressing Mode
		r1=convertDecimal(22,26);
		r2=convertDecimal(27,31);
		R[r2] -= R[r1];	
	}
	else
	{
		// Immediate Addressing Mode
		r1=convertDecimal(22,26);
		r2=convertDecimal(27,31);
		R[r2] -= r1;
	}
	
	printf("SUB R[%d] %d\n",r2,R[r2]);
	setFlag(R[r2]);
}

// Bitwise XOR of the contents
void XOR()
{
	int r1,r2;;
	if((nn & 1<<10))
	{
		// Register Addressing Mode
		r1=convertDecimal(22,26);
		r2=convertDecimal(27,31);
		R[r2] ^= R[r1];	
	}
	else
	{
		// Immediate Addressing Mode
		r1=convertDecimal(22,26);
		r2=convertDecimal(27,31);
		R[r2] ^= r1;
	}
	
	printf("XOR R[%d] %d\n",r2,R[r2]);
	setFlag(R[r2]);
}

// Bitwise AND of the contents
void AND()
{
	int r1,r2;;
	if((nn & 1<<10))
	{
		// Register Addressing Mode
		r1=convertDecimal(22,26);
		r2=convertDecimal(27,31);
		R[r2] &= R[r1];	
	}
	else
	{
		// Immediate Addressing Mode
		r1=convertDecimal(22,26);
		r2=convertDecimal(27,31);
		R[r2] &= r1;
	}
	
	printf("AND R[%d] %d\n",r2,R[r2]);
	setFlag(R[r2]);
}

// Bitwise OR of the contents
void OR()
{
	int r1,r2;;
	if((nn & 1<<10))
	{
		// Register Addressing Mode
		r1=convertDecimal(22,26);
		r2=convertDecimal(27,31);
		R[r2] |= R[r1];	
	}
	else
	{
		// Immediate Addressing Mode
		r1=convertDecimal(22,26);
		r2=convertDecimal(27,31);
		R[r2] |= r1;
	}
	
	printf("OR R[%d] %d\n",r2,R[r2]);
	setFlag(R[r2]);
}

// Compare the contents
void CMP()
{
	int r1,r2;
	if((nn & 1<<10))
	{
		// Register Addressing Mode
		r1=convertDecimal(22,26);
		r2=convertDecimal(27,31);
		int l=R[r1]-R[r2];
		if(l==0) 	flag=1;
		else		flag=0;	
	}
	else
	{
		// Immediate Addressing Mode
		r1=convertDecimal(22,26);
		r2=convertDecimal(27,31);
		int l=r1-R[r2];
		if(l==0) 	flag=1;
		else		flag=0;
	}
	printf("Comparison\n");
	setFlag(R[r2]);
}

// Bitwise Not
void NOT()
{
	int r1,r2;;
	if((nn & 1<<10))
	{
		// Register Addressing Mode
		r1=convertDecimal(22,26);
		r2=convertDecimal(27,31);
		R[r2]=!R[r1];	
	}
	else
	{
		// Immediate Addressing Mode
		r1=convertDecimal(22,26);
		r2=convertDecimal(27,31);
		R[r2]=!r1;
	}
	
	printf("NOT R[%d] %d\n",r2,R[r2]);
	setFlag(R[r2]);
}

// Returs the required line number from the symbol table
int LineNumber()
{
	int i;
	int sum=0;
	for(i=3;str1[i]!='\n';i++)
	{
		sum=sum*10+(str1[i]-'0');
	}
	return sum;
}

// For identifying the operations
void identify2(int op)
{
	switch(op)
	{
		case 0: 	MOV();
				break;
		case 11: 	ADD();
			 	break; 
	    case 100: 	SUB();
				break;
		case 101: 	XOR();
			 	break; 
	    case 110: 	AND();
				break;
		case 111: 	OR();
			 	break; 
		case 1000: 	CMP();
				break;
		case 1001: 	NOT();
			 	break;
	  	default :
	  			break;
	}
} 

// Input from the user
void IN()
{
	int r1=convertDecimal(25,29);
	scanf("%d",&R[r1]);
	printf("IN R[%d] %d\n",r1,R[r1]);
	setFlag(R[r1]);
}

// Output from the user
void OUT()
{
	int r1=convertDecimal(27,31);
	printf("OUT %d\n",R[r1]);
	setFlag(R[r1]);
}


int main()
{
	
	int op;
	int i,cnt=0;
	
	fin=fopen("out1.txt","r");
	fsymbol=fopen("symbol1.txt","r");
	
	// Initializing registers  to 0
	memset(R,0,sizeof(R));
	
	// Return from the goto
	swag:
	while(fgets(str,sizeof(str),fin)!=NULL)
	{
		cnt++;
		printf("\nInstruction No : %d\n\n",cnt);
		R[31]=0; // This is our special Flag register 
		nn=convertDecimal(0,31);

		// 2-Address Instructions
		if(!(nn & 1<<31))
		{

			op=checkBin(12,15);
			identify2(op);
			
		}
		else	// 1-Address Instructions
		{
			if(!(nn & 1<<30))
			{
				op=checkBin(5,6);
				if(op==0) // For JMP
				{
					int r1,x;
					r1=convertDecimal(27,31);
					while(fgets(str1,sizeof(str1),fsymbol)!=NULL)
					{
						if((str1[1]-'0')==r1)
						{
							x=LineNumber();
							break;
						}
					}
					fseek(fin,33*(x-1),SEEK_SET);
					goto swag;
				}
				else if(op==1)	// For JEQ
				{
					if(flag==1)
					{
						int r1,x;
						r1=convertDecimal(27,31);
						while(fgets(str1,sizeof(str1),fsymbol)!=NULL)
						{
							if((str1[1]-'0')==r1)
							{
								x=LineNumber();
								break;
							}
						}
						fseek(fin,33*(x-1),SEEK_SET);
						goto swag;
					}
				}
				else if(op==10)	// For JNE
				{
					if(flag==0)
					{
						int r1,x;
						r1=convertDecimal(27,31);
						while(fgets(str1,sizeof(str1),fsymbol)!=NULL)
						{
							if((str1[1]-'0')==r1)
							{
								x=LineNumber();
								break;
							}
						}
						fseek(fin,33*(x-1),SEEK_SET);
						goto swag;
					}
				}
			}
			else if((nn & 1<<29))
			{	
				if(!(nn & 1<<7)) 	// For IN
					IN();
				else			// For OUT
					OUT();
			}
			else {	// 0-Address Instructions
				printf("HLT\n");
				break;
			}

		}	
	}
	// Closing the File pointers
	fclose(fin);
	fclose(fsymbol);
	return 0;
}

