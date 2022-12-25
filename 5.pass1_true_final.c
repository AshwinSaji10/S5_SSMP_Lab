#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int hextoint(int n)
{
	int c=n;
	int x,i,j,sum=0;
	int digit_count=0;
	int mult=1;
	while(c!=0)
	{
		c=c/10;
		digit_count+=1;	
	}
	c=n;
	for(i=0;i<digit_count;i++)
	{
		mult=1;
		x=c%10;
		for(j=0;j<i;j++)
		mult=mult*16;
		sum=sum+x*mult;
		c=c/10;
	}
	return sum;
}
void display()
{
	FILE *f1,*f2,*f3;
	char loc[10]="",label[10],opcode[10],operand[10];
	char symbol[10],mnemonic[10];
	char length[10];
	f1=fopen("intermediate.txt","r");
	f2=fopen("symtab.txt","r");
	f3=fopen("length.txt","r");
	fscanf(f1,"\t%s\t%s\t%s",label,opcode,operand);
	printf("intermediate file:\n");
	while(!feof(f1))
	{
		printf("%s\t%s\t%s\t%s\n",loc,label,opcode,operand);
		fscanf(f1,"%s\t%s\t%s\t%s",loc,label,opcode,operand);
	}
	fclose(f1);
	fscanf(f2,"%s\t%s",symbol,mnemonic);
	printf("\nsymtab:\n");
	while(!feof(f2))
	{
		printf("%s\t%s\n",symbol,mnemonic);
		fscanf(f2,"%s\t%s",symbol,mnemonic);
	}
	fclose(f2);
	fscanf(f3,"%s",length);
	printf("\nlength of code = %s\n",length);
	fclose(f3);
}
void main()
{
	FILE *f1,*f2,*f3,*f4,*f5;
	char label[20],opcode[20],operand[20];
	char code[20];
	int mnemonic;
	int start,locctr;
	int flag;
	
	f1=fopen("input.txt","r");
	//f2=fopen("optab.txt","r");
	f3=fopen("symtab.txt","w");
	f4=fopen("intermediate.txt","w");
	f5=fopen("length.txt","w");
	
	fscanf(f1,"%s\t%s\t%s",label,opcode,operand);//read first line from input.txt
	
	if(strcmp(opcode,"START")==0)//if opcode="START" then
	{
		start=hextoint(atoi(operand));//convert hex operand to number and then convert it to integer and store as starting address
		locctr=start;//initialize locctr to starting address
		fprintf(f4,"\t%s\t%s\t%s\n",label,opcode,operand);//write line to intermediate.txt
		fscanf(f1,"%s\t%s\t%s",label,opcode,operand);//read next line from input.txt
	}
	else
	locctr=0;//initialize locctr to 0
	while(strcmp(opcode,"END")!=0)//while opcode not equal to "END"
	{
		fprintf(f4,"%X\t%s\t%s\t%s\n",locctr,label,opcode,operand);//write last line to intermediate file
		
		if ((strcmp(label,"-")!= 0)&&(strcmp(label,"START")!= 0))//if this is not a comment line then and if label is not START
		fprintf(f3,"%s\t%X\n",label,locctr);//insert label,locctr into symtab
            	
            	
        f2=fopen("optab.txt","r");    	
        fscanf(f2,"%s\t%d",code,&mnemonic);//read next value from optab
        flag=0;
        while (!feof(f2))//search optab.txt for opcode 
        {
            if(strcmp(opcode,code)==0)//if found then    
            {     
                flag=1;
                break;
            }
            fscanf(f2,"%s\t%d",code,&mnemonic);//read from optab
        }
        fclose(f2);
	if(flag==1)
	locctr=locctr+3;  
	else if(opcode[0]=='+')//format 4
	locctr=locctr+4;	
        else if(strcmp(opcode,"WORD")==0)
        locctr=locctr+3;
        else if(strcmp(opcode,"RESW")==0)
        locctr=locctr+(3*atoi(operand));
        else if(strcmp(opcode,"RESB")==0)
        locctr=locctr+atoi(operand);
        else if(strcmp(opcode,"BYTE")==0)//find length of constant in bytes
        {
        	if(operand[0]=='X')//single byte
		locctr++;    	
		else//multiple bytes
		locctr=locctr+(strlen(operand)-2);
    	}
        //%X to convert to hexadecimal
        //fprintf(f4,"%X\t%s\t%s\t%s\n",locctr,label,opcode,operand);//write last line to intermediate file
        fscanf(f1,"%s\t%s\t%s",label,opcode,operand);//read next input line
    }
    fprintf(f4,"%X\t%s\t%s\t%s\n",locctr,label,opcode,operand);//write last line to intermediate file
        
    fclose(f1);
    //fclose(f2);
    fclose(f3);
    fclose(f4);
        
    //length=locctr-start;
    fprintf(f5,"%d",locctr-start);
    fclose(f5);
    //printf("\nThe length of the code = %d\n",length);
    display();
      
}


