#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void display()
{
	FILE *fsym,*fin,*flen;
	char addr[20],label[20],opcode[20],operand[20];
	char sym[20],symaddr[20];
	char len[20];
	
	//display intermediate file
	fin=fopen("intermediate.txt","r");
	fscanf(fin,"%s %s %s",label,opcode,operand);
	printf("intermediate file:\n");
	printf("\t%s\t%s\t%s\n",label,opcode,operand);//print first line in intermediate file(no address)
	fscanf(fin,"%s %s %s %s",addr,label,opcode,operand);
	while(!feof(fin))
	{
		printf("%s\t%s\t%s\t%s\n",addr,label,opcode,operand);
		fscanf(fin,"%s %s %s %s",addr,label,opcode,operand);
	}
	fclose(fin);
	
	//display symtab
	fsym=fopen("symtab.txt","r");
	printf("\nSymtab:\n");
	fscanf(fsym,"%s %s",sym,symaddr);
	while(!feof(fsym))
	{
		printf("%s\t%s\n",sym,symaddr);
		fscanf(fsym,"%s %s",sym,symaddr);
	}
	fclose(fsym);
	
	//display length file
	flen=fopen("length.txt","r");
	printf("\nLength:\n");
	fscanf(flen,"%s",len);
	printf("%s",len);
	fclose(flen);
	
}
void main()
{
	FILE *fip,*fop,*fsym,*fin,*flen;	
	char label[20],opcode[20],operand[20];
	int locctr,flag;
	char code[20],mnemonic[20];
	char sym[20],addr[20];
	char start[20];
	fip=fopen("input.txt","r");
	fin=fopen("intermediate.txt","w");
	fscanf(fip,"%s %s %s",label,opcode,operand);//read first input line
	if(strcmp(opcode,"START")==0)//if opcode is start
	{
		strcpy(start,operand);//save operand as starting address
		locctr=strtol(start,NULL,16);//initialize locctr to starting address
		fprintf(fin,"\t%s\t%s\t%s\n",label,opcode,operand);//write line to intermediate file
		fscanf(fip,"%s %s %s",label,opcode,operand);//read next input line	
	}
	else
		locctr=0;//initialize locctr to 0
	while(strcmp(opcode,"END")!=0)//while opcode!=END
	{
		fprintf(fin,"%X\t%s\t%s\t%s\n",locctr,label,opcode,operand);//write line to intermediate file
		if(strcmp(label,";")!=0)//if not comment line
		{
			if(strcmp(label,"-")!=0&&strcmp(label,"START")!=0)//if there is a symbol in the label field and it is not start
			{
				fsym=fopen("symtab.txt","r");
				flag=0;
				fscanf(fsym,"%s %s",sym,addr);
				while(!feof(fsym))//search symtab for label
				{
					if(strcmp(label,sym)==0)
					{
						printf("error!:duplicate symbol\n");//if found set error flag
						flag=1;
						break;
					}
					fscanf(fsym,"%s %s",sym,addr);
				}
				fclose(fsym);
				if(strcmp(label,sym)==0)//to get last symbol in symtab
				{
					printf("error!:duplicate symbol\n");//if found set error flag
					flag=1;
				}
				if(flag==0)
				{
					fsym=fopen("symtab.txt","a");//open symtab in append mode to write to end of it
					fprintf(fsym,"%s\t%X\n",label,locctr);//not found then insert label,locctr into symtab 
					fclose(fsym);
				}
			}
		}
		fop=fopen("optab.txt","r");
		fscanf(fop,"%s %s",code,mnemonic);
		flag=0;
		while(!feof(fop))//search optab for opcode
		{
			if(strcmp(opcode,code)==0)
			{
				flag=1;
				break;
			}
			fscanf(fop,"%s %s",code,mnemonic);
		}
		fclose(fop);
		if(strcmp(opcode,code)==0)//to get last opcode in optab
			flag=1;
		if(flag==1)//if opcode found in optab,add 3 to locctr
			locctr+=3;
		else if(strcmp(opcode,"RESW")==0)
			locctr+=3*atoi(operand);
		else if(strcmp(opcode,"RESB")==0)
			locctr+=atoi(operand);
		else if(strcmp(opcode,"WORD")==0)
			locctr+=3;
		else if(strcmp(opcode,"BYTE")==0)
		{
			if(operand[0]=='X')
				locctr+=1;
			else//C'
				locctr+=(strlen(operand)-2);
		}
		else
			printf("error!:invalid symbol\n");//opcode not found anywhere 
		fscanf(fip,"%s %s %s",label,opcode,operand);//read next input line
	}
	fprintf(fin,"%X\t%s\t%s\t%s\n",locctr,label,opcode,operand);//write last line to intermediate file
	flen=fopen("length.txt","w");
	fprintf(flen,"%d",locctr-strtol(start,NULL,16));//save locctr-start as program length
	fclose(flen);
	fclose(fip);
	fclose(fin);
	display();//display the file contents
}

/*Input.txt
COPY		START 	1000
START 	LDA		ALPHA
- 		ADD		ONE
- 		SUB 		TWO
- 		+STA 		BETA
- 		RSUB 	-
ALPHA	BYTE		C'HELLO
ONE		RESB		2
TWO		WORD	5
BETA		RESW	1
- 		END		START
*/

/*Optab.txt
LDA	00
STA	0C
ADD	18
SUB	1C
RSUB	4C
*/

