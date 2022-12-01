#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define max 20		//only 20 blocks on disk
struct block
{
	int flag;
}b[max];

struct file
{
	char name[20];
	int isalloc;
	int size;
	int blocks[max];
	int blockcount;
	int index;
};

void seq()
{
	struct file f[20];
	int nof;
	int i,j,k;
	int p=0,st;
	printf("enter the no of files = ");
	scanf("%d",&nof);
	
	for(k=0;k<nof;k++)
	f[k].isalloc=0;
	
	for(k=0;k<nof;k++)//traverse files
	{
		f[k].blockcount=0;
		printf("enter name of the file = ");
		scanf("%s",f[k].name);//name of the file k
		printf("enter size of file = ");
		scanf("%d",&f[k].size);//size of the file k
		
		if(p+f[k].size>max)//sequential file check
		{
			printf("file size exceeds no of blocks!\n");
			continue;
		}
		st=p;
		for(i=st;i<st+f[k].size;i++)//traverse blocks sequentially
		{
			b[i].flag=1;
			f[k].blocks[f[k].blockcount]=i;
			f[k].blockcount++;
			p++;	
		}
		f[k].isalloc=1;
	}
	printf("filename\tno of blocks\tblocks\n");
	for(k=0;k<nof;k++)
	{
		if(f[k].isalloc==1)
		{
			printf("%s\t\t\t%d\t",f[k].name,f[k].size);
			for(j=0;j<f[k].blockcount;j++)
			printf("%d ",f[k].blocks[j]);
			printf("\n");
		}
		else
		{
			printf("%s\t\t\t%d\t",f[k].name,f[k].size);	
			printf("couldn't be allocated!\n");
		}		
	}
}
void link()
{
	struct file f[20];
	
	time_t t;
	srand((unsigned) time(&t));
	
	int nof;
	int j,k;
	int loc,free;
	printf("enter the no of files = ");
	scanf("%d",&nof);//read no of files
	
	for(k=0;k<nof;k++)
	f[k].isalloc=0;//set all files as unallocated
	
	for(k=0;k<nof;k++)//traverse files
	{
		f[k].blockcount=0;//initialise no of blocks occupied for kth file as 0
		printf("enter name of the file = ");
		scanf("%s",f[k].name);//name of the file k
		printf("enter size of file = ");
		scanf("%d",&f[k].size);//size of the file k
		if(f[k].size>max)//linked file check
		{
			printf("file size exceeds no of blocks!\n");
			continue;
		}
		while(f[k].blockcount<f[k].size)//traverse blocks randomly
		{
			free=0;
			loc=rand() % 20;
			//printf("\n%d\n",loc)
			if(b[loc].flag==0)//if random block is empty
			{
				b[loc].flag=1;
				f[k].blocks[f[k].blockcount]=loc;
				f[k].blockcount++;
			}
			else
			{
				for(j=0;j<max;j++)//check if required no of blocks are free
				{
					if(b[j].flag==0)
					{
						free++;
					}
				}
				if(free<f[k].size-f[k].blockcount)//if no of free blocks is less than no of required blocks
				{
					printf("required no of blocks are not present!\n");
					break;
				}
			}
		}
		//now file has been successfully allocated in blocks
		if(f[k].blockcount==f[k].size)
		f[k].isalloc=1;
	}
	printf("filename\tno of blocks\tblocks\n");
	for(k=0;k<nof;k++)
	{
		if(f[k].isalloc==1)
		{
			printf("%s\t\t\t%d\t",f[k].name,f[k].size);
			for(j=0;j<f[k].blockcount;j++)
			printf("%d ",f[k].blocks[j]);
			printf("\n");
		}
		else
		{
			printf("%s\t\t\t%d\t",f[k].name,f[k].size);	
			printf("couldn't be allocated!\n");
		}				
	}
}
void ind()
{
	struct file f[20];
	
	time_t t;
	srand((unsigned) time(&t));
	
	int nof;
	int j,k;
	int loc,free;
	printf("enter the no of files = ");
	scanf("%d",&nof);//read no of files
	
	for(k=0;k<nof;k++)
	f[k].isalloc=0;//set all files as unallocated
	
	for(k=0;k<nof;k++)//traverse files
	{
		f[k].blockcount=0;//initialise no of blocks occupied for kth file as 0
		printf("enter name of the file = ");
		scanf("%s",f[k].name);//name of the file k
		printf("enter size of file = ");
		scanf("%d",&f[k].size);//size of the file k
		printf("enter index of file = ");
		scanf("%d",&f[k].index);//index of file k
		if(f[k].size>max)
		{
			printf("file size exceeds no of blocks!\n");
			continue;
		}
		if(b[f[k].index].flag==1)
		{
			printf("index is already allocated!\n");
			continue;	
		}
		b[f[k].index].flag=1;
		while(f[k].blockcount<f[k].size)//traverse blocks randomly
		{
			free=0;
			loc=rand() % 20;
			//printf("\n%d\n",loc)
			if(b[loc].flag==0)//if random block is empty and random location is not index
			{
				b[loc].flag=1;
				f[k].blocks[f[k].blockcount]=loc;
				f[k].blockcount++;
			}
			else
			{
				for(j=0;j<max;j++)//check if required no of blocks are free
				{
					if(b[j].flag==0&&j!=f[k].index)
					{
						free++;
					}
				}
				if(free<f[k].size-f[k].blockcount)//if no of free blocks is less than no of required blocks
				{
					printf("required no of blocks are not present!\n");
					break;
				}
			}
		}
		//now file has been successfully allocated in blocks
		if(f[k].blockcount==f[k].size)
		f[k].isalloc=1;
	}
	printf("filename\tno of blocks\tindex\tblocks\n");
	for(k=0;k<nof;k++)
	{
		if(f[k].isalloc==1)
		{
			printf("%s\t\t\t%d\t%d\t",f[k].name,f[k].size,f[k].index);
			for(j=0;j<f[k].blockcount;j++)
			printf("%d ",f[k].blocks[j]);
			printf("\n");
		}
		else
		{
			printf("%s\t\t\t%d\t%d\t",f[k].name,f[k].size,f[k].index);
			printf("couldn't be allocated!\n");
		}				
	}
}
void main()
{
	int ch,i;
	while(1)
	{
		for(i=0;i<max;i++)
		b[i].flag=0;
		printf("1.sequential\n2.linked\n3.indexed\n4.exit\nenter choice = ");
		scanf("%d",&ch);
		if(ch==1)
		seq();
		else if(ch==2)
		link();
		else if(ch==3)
		ind();
		else if(ch==4)
		exit(0);
		else
		printf("wrong choice!\n");
	}
}
