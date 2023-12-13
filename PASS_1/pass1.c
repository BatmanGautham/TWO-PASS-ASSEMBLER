#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
 char label[10],opcode[10],operand[10]; // to read inputf
 char code[10],mnemonic[10]; // to read optabf
 
 int StartAddress,locctr,length;
 
 FILE *inputfp,*optabfp,*symtabfp,*intermediatefp;
 
 inputfp = fopen("input.txt","r");
 optabfp = fopen("optab.txt","r");
 
 symtabfp = fopen("symtab.txt","w");
 intermediatefp = fopen("intermediate.txt","w");
 
 fscanf(inputfp,"%s\t%s\t%s",label,opcode,operand);
 
  if(strcmp(opcode,"START")==0)
   {
    StartAddress = atoi(operand);
    locctr = StartAddress;
    
    fprintf(intermediatefp,"\t%s\t%s\t%s\n",label,opcode,operand);
    
    fscanf(inputfp,"%s\t%s\t%s",label,opcode,operand);
   }
  else
   {
    locctr = 0;
   }
   
  while(strcmp(opcode,"END")!=0)
   {
    fprintf(intermediatefp,"%d\t",locctr); //looctr placed at output file 
    
     if(strcmp(label,"**")!=0)
      {
       fprintf(symtabfp,"%s\t%d\n",label,locctr);
      }
    
    fscanf(optabfp,"%s\t%s",code,mnemonic);
    
     while(strcmp(code,"END")!=0) // in optab
      {
       if(strcmp(opcode,code)==0) // checking if opcode already exsist
        {
         locctr+=3;
         break;
        }
       fscanf(optabfp,"%s\t%s",code,mnemonic);// checking till end
      }
     
    if(strcmp(opcode,"WORD")==0)
     {
      locctr+=3;
     }
    else if(strcmp(opcode,"RESW")==0)
     {
      locctr+=3*(atoi(operand));
     }
    else if(strcmp(opcode,"RESB")==0)
     {
      locctr+=atoi(operand);
     }
    else if(strcmp(opcode,"BYTE")==0)
     {
      locctr+=strlen(operand)-3;
     }
     
   fprintf(intermediatefp,"%s\t%s\t%s\n",label,opcode,operand);
        
   fscanf(inputfp,"%s\t%s\t%s",label,opcode,operand);
  }// loops till end is found in input file
  
 fprintf(intermediatefp,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);//END placed at output file
 
 length = locctr - StartAddress;
 
 printf("\nProgram to execute Pass one of Two Pass assembler is completed.");
 printf("\nLength of program : %d",length);
 printf("\n\nPROGRAM ENDED\n\n");
}
    


/* 
INPUTS

input.txt

**	START	2000
**	LDA	FIVE
**	STA	ALPHA
**	LDCH	CHARZ
**	STCH	C1
ALPHA	RESW	2
FIVE	WORD	5
CHARZ	BYTE	C'Z'
C1	RESB	1
**	END	**

  
optab.txt
  
START	*
LDA	03
STA	2f
LDCH	53
STCH	57
END	*



  
OUTPUTS

  
intermediate.txt
  
	**	START	2000
2000	**	LDA	FIVE
2003	**	STA	ALPHA
2006	**	LDCH	CHARZ
2009	**	STCH	C1
2012	ALPHA	RESW	2
2018	FIVE	WORD	5
2021	CHARZ	BYTE	C'Z'
2022	C1	RESB	1
2023	**	END	**

  
symtab.txt
  
ALPHA	2012
FIVE	2018
CHARZ	2021
C1	2022



Program to execute Pass one of Two Pass assembler is completed.
Length of program : 23

PROGRAM ENDED
*/
  
