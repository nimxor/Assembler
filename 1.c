/*
Program to convert Assembly Language code into its Binary Representation
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//String which contain binary representation of given integer
char ss[6];
//Function to convert decimal to binary 
void convert_binary(int n)
{
	int i=1;
	memset(ss,'0',sizeof(ss));
	while(n!=0)
	{
		ss[5-i]=(n%2)+'0';
		n/=2;
		i++;
	}
	ss[5]='\0';
}
//Function to determine the opcode
char * opcode(char *str)
{

	if(strcmp(str,"MOV")==0)
		return "00000000000000000000";
	if(strcmp(str,"ADD")==0)
		return "00000000000000000011";
	if(strcmp(str,"SUB")==0)
		return "00000000000000000100";
	if(strcmp(str,"XOR")==0)
		return "00000000000000000101";
	if(strcmp(str,"AND")==0)
		return "00000000000000000110";
	if(strcmp(str,"OR")==0)
		return "00000000000000000111";
	if(strcmp(str,"CMP")==0)
		return "00000000000000001000";
	if(strcmp(str,"NOT")==0)
		return "00000000000000001001";
	if(strcmp(str,"JMP")==0)
		return "100000000000000000000000000";
	if(strcmp(str,"JEQ")==0)
		return "100000000000000000000000001";
	if(strcmp(str,"JNE")==0)
		return "100000000000000000000000010";
	if(strcmp(str,"HLT")==0)
		return "11000000000000000000000000000000";
	if(strcmp(str,"IN")==0)
		return "1110000000000000000000000";
	if(strcmp(str,"OUT")==0)
		return "1110000000000000000000001";
}
int main()
{
	
	char str[1001];
	char a[100],b[3];
	int i,j,k,cnt=0;
	char *st;
        //fin=File pointer to input file
        //fout=File pointer to output file 
        //fsymbol=File pointer to symbol file 
	FILE *fin,*fout,*fsymbol;
	
	fin=fopen("inp1.txt","r");
	
	fout=fopen("out1.txt","w+");
	
	fsymbol=fopen("symbol1.txt","w+");
	
	if(fin==NULL)
	{
		printf("No input file exists\n");
		exit(1);
	}
	else
	{
		while(fgets(str,sizeof(str),fin)!=NULL)
		{
			cnt++;
		//Handling Labels			
			if(str[2]==':')
			{
				b[0]=str[0];b[1]=str[1];b[2]='\0';
				fprintf(fsymbol , "%s %d\n" , b,cnt);
				continue;
			}
		//Handling IN Operation
			else if(str[0]=='I')
			{
				st = opcode("IN");
				fprintf(fout, "%s",st);
				convert_binary((str[4]-'0')*10 + str[5]-'0');
				fprintf(fout , "%s10\n" , ss);
			}
		//Handling OUT Operation
			else if(str[0]=='O' && str[1]=='U' && str[2]=='T')
			{
				st = opcode("OUT");
				fprintf(fout, "%s11",st);
				convert_binary((str[10]-'0')*10 + str[11]-'0');
				fprintf(fout , "%s\n" , ss);
			}
		//Handling OR Operation
			else if(str[0]=='O' && str[1]=='R')
			{
				st = opcode("OR");
				fprintf(fout, "%s",st);
				if(str[3]=='R')
				{
					//Determining Addressing mode
					fprintf(fout , "%s" , "11");
					convert_binary((str[4]-'0')*10 + str[5]-'0');
					//Determining Binary Representation
					fprintf(fout , "%s" , ss);
					convert_binary((str[8]-'0')*10 + str[9]-'0');
					fprintf(fout , "%s\n" , ss);
				}
				else
				{
					//Determining Addressing mode
					fprintf(fout , "%s" , "10");
					convert_binary((str[4]-'0')*10 + str[5]-'0');
					//Determining Binary Representation
					fprintf(fout , "%s" , ss);
					convert_binary((str[8]-'0')*10 + str[9]-'0');
					//Writing to Output File
					fprintf(fout , "%s\n" , ss);
				}
			}
			//Handling Other Operations
			else
			{
				for(i=0;i<3;i++)
					a[i]=str[i];
				a[i]='\0';
				
				st = opcode(a);
				if(strlen(st)==32)//For HLT
					fprintf(fout, "%s\n",st);
				if(strlen(st)==20)//For 2 Address Instructions 
				{
					fprintf(fout, "%s",st);
					if(str[4]=='R')
					{
						fprintf(fout , "%s" , "11");
						convert_binary((str[5]-'0')*10 + str[6]-'0');
						fprintf(fout , "%s" , ss);
						convert_binary((str[9]-'0')*10 + str[10]-'0');
						fprintf(fout , "%s\n" , ss);
					}
					else
					{
						fprintf(fout , "%s" , "10");
						convert_binary((str[5]-'0')*10 + str[6]-'0');
						fprintf(fout , "%s" , ss);
						convert_binary((str[9]-'0')*10 + str[10]-'0');
						fprintf(fout , "%s\n" , ss);
					}
					
				}
				else if(strlen(st)==27)//For 1 Address Instruction
				{
					fprintf(fout,"%s",st);
					convert_binary(str[6]-'0');
					fprintf(fout , "%s\n" , ss);
				}
			
			}
		}
	}
	//Closing File Pointers
	fclose(fin);
	fclose(fout);
	fclose(fsymbol);
	
	return 0;
}
