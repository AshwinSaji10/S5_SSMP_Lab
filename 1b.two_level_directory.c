#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct dir
{
	char dname[20];
	char fname[10][20];
	int fcount;
};

struct dir d[20];
int dcount=0;

void createdir()
{
	printf("enter name of directory = ");
	scanf("%s",d[dcount].dname);
	d[dcount].fcount=0;
	dcount++;
	printf("\ndirectory successfully created!");
}
void deletedir()
{
	if(dcount==0)
	{
		printf("\nNo directories found!");
		return;
	}
	char temp[20];
	int i,j,flag=0,found;
	printf("enter name of directory = ");
	scanf("%s",temp);
	for(i=0;i<dcount;i++)
	{
		if(strcmp(temp,d[i].dname)==0)
		{
			flag=1;
			found=i;
			break;
		}
	}
	if(flag==0)
	{
		printf("\ndirectory %s not found!",temp);
		return;	
	}
	for(i=found;i<dcount-1;i++)
	{
		strcpy(d[i].dname,d[i+1].dname);
		for(j=0;j<d[i+1].fcount;j++)
		{
			strcpy(d[i].fname[j],d[i+1].fname[j]);
		}
		d[i].fcount=d[i+1].fcount;
	}
	dcount--;
	printf("\ndirectory %s has been deleted!",temp);	
}
void createfile()
{
	if(dcount==0)
	{
		printf("\nNo directories found!");
		return;
	}
	char temp[20];
	int i;
	printf("enter name of directory = ");
	scanf("%s",temp);
	for(i=0;i<dcount;i++)
	{
		if(strcmp(temp,d[i].dname)==0)
		{
			printf("enter name of file = ");
			scanf("%s",d[i].fname[d[i].fcount]);
			d[i].fcount++;
			printf("\nfile created!");
			break;
		}
	}
	if(i==dcount)
	{
		printf("\ndirectory %s not found!",temp);
		return;
	}
}
void deletefile()
{
	if(dcount==0)
	{
		printf("\nNo directories found!");
		return;
	}
	char temp[20];
	int i,flag=0,foundd,foundf;
	printf("enter name of directory = ");
	scanf("%s",temp);
	for(i=0;i<dcount;i++)
	{
		if(strcmp(temp,d[i].dname)==0)
		{
			flag=1;
			foundd=i;
			break;
		}
	}
	if(flag==0)
	{
		printf("\ndirectory %s not found!",temp);
		return;	
	}	
	flag=0;
	printf("enter name of file to delete = ");
	scanf("%s",temp);
	for(i=0;i<d[foundd].fcount;i++)
	{
		if(strcmp(temp,d[foundd].fname[i])==0)
		{
			flag=1;
			foundf=i;
			break;
		}
	}
	if(flag==0)
	{
		printf("\nfile %s not found!",temp);
		return;	
	}
	for(i=foundf;i<d[foundd].fcount-1;i++)
	{
		strcpy(d[foundd].fname[i],d[foundd].fname[i+1]);
	}
	d[foundd].fcount--;	
	printf("\nfile %s has been deleted!",temp);
}
void searchfile()
{
	if(dcount==0)
	{
		printf("\nNo directories found!");
		return;
	}
	char tempd[20],tempf[20];
	int i,flag=0,found;
	printf("enter name of directory = ");
	scanf("%s",tempd);
	for(i=0;i<dcount;i++)
	{
		if(strcmp(tempd,d[i].dname)==0)
		{
			flag=1;
			found=i;
			break;
		}
	}
	if(flag==0)
	{
		printf("\ndirectory %s not found!",tempd);
		return;	
	}	
	flag=0;
	printf("enter name of file to search = ");
	scanf("%s",tempf);
	//printf("\n%d\n",d[found].fcount);
	for(i=0;i<d[found].fcount;i++)
	{
		//printf("\n%s\n",d[found].fname[i]);
		if(strcmp(tempf,d[found].fname[i])==0)
		{
			//printf("hello");
			flag=1;
			printf("\nfile found at /%s/%s",tempd,tempf);
			break;
		}
	}
	if(flag==0)
	{
		printf("\nfile %s not found!",tempf);
		return;	
	}	
}
void display()
{
	if(dcount==0)
	{
		printf("\nNo directories found!");
		return;
	}
	int i,j;
	for(i=0;i<dcount;i++)
	{
		printf("directory:%s\n",d[i].dname);
		for(j=0;j<d[i].fcount;j++)
		{
			printf("%d)%s\n",j+1,d[i].fname[j]);
		}
	}
}
void main()
{
	int ch;
	while(1)
	{
		printf("\n1.create directory\n2.delete directory\n3.create file\n4.delete file\n5.search file\n6.display\n7.exit\n");
		scanf("%d",&ch);
		if(ch==1)
		createdir();
		else if(ch==2)
		deletedir();
		else if(ch==3)
		createfile();
		else if(ch==4)
		deletefile();
		else if(ch==5)
		searchfile();
		else if(ch==6)
		display();
		else if(ch==7)
		exit(0);
		else
		printf("\nwrong choice!");
	}
}
