#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct file
{
	char name[50];

};

struct file f[20];
int fcount=0;

void create()
{
	printf("enter the name of your file = ");
	scanf("%s",f[fcount].name);
	fcount++;
	printf("\nsuccessfully created file!");
}

void delete()
{
	if(fcount==0)
	{
		printf("\ndirectory is empty!");
		return;
	}
	int i,flag=0,foundcount=0;
	char fname[50];
	printf("enter filename to delete = ");
	scanf("%s",fname);
	for(i=0;i<fcount;i++)
	{
		if(strcmp(fname,f[i].name)==0)
		{
			printf("file at /root/%s has been successfully deleted",fname);
			foundcount=i;
			flag=1;
		}
	}
	if(flag==0)
	{
		printf("requested file has not been found!");
		return;
	}
	for(i=foundcount;i<fcount-1;i++)
	{
		strcpy(f[i].name,f[i+1].name);
	}
	fcount--;
}

void search()
{
	if(fcount==0)
	{
		printf("\ndirectory is empty!");
		return;
	}
	int i,flag=0;
	char fname[50];
	printf("enter filename to search = ");
	scanf("%s",fname);
	for(i=0;i<fcount;i++)
	{
		if(strcmp(fname,f[i].name)==0)
		{
			printf("file successfully found at /root/%s",fname);
			flag=1;
		}
	}
	if(flag==0)
	printf("requested file has not been found!");
}

void display()
{
	if(fcount==0)
	{
		printf("\ndirectory is empty!");
		return;
	}
	int i;
	printf("\ndisplaying filenames\n");
	for(i=0;i<fcount;i++)
	{
		printf("%d.%s\n",i+1,f[i].name);
	
	}
	
	printf("\n");
}

int main()
{
	int ch;
	while(1)
	{
		printf("\nMenu Options\n1.create\n2.delete\n3.search\n4.display\n5.exit\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
			create();
			break;
			case 2:
			delete();
			break;
			case 3:
			search();
			break;
			case 4:
			display();
			break;
			case 5:
			exit(0);
			break;
			default:printf("\nwrong choice");
			//break;
		}
	}
	return 0;
}
