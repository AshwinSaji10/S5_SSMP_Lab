#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define max 100

struct process
{
	int id;
	int size;
	int frag;
	int frames[50];
	int frame_count;
}p[max];

struct frame
{
	int flag;

}f[max];

int mem_size;
int frame_size;
int n;//total no of frames
int count=0;//count the no of processes

int search(int key)
{
	int i;
	for(i=0;i<count;i++)
	{
		if(p[i].id==key)
		return i;//return process location if found
	}
	return -1;
}
void insert()
{
	int i;
	int nof,rem;
	int loc;
	time_t t;
	srand((unsigned) time(&t));
	
	printf("enter process id = ");
	scanf("%d",&p[count].id);
	if(search(p[count].id)!=-1)//check if pid is already present
	{
		printf("\nprocess with given id is already present!\n");
		return;	
	}
	printf("enter size of process = ");
	scanf("%d",&p[count].size);
	//count++;
	nof=p[count].size/frame_size;//no of frames req for that process
	rem=p[count].size%frame_size;//remaining size to allocate
	p[count].frame_count=0;
	while(nof!=-1)
	{
		if(nof==0)
		{
			if(rem==0)
			{
				p[count].frag=0;
				break;
			}	
			loc=rand()%n;
			while(f[loc].flag==1)
			loc=rand()%n;
			f[loc].flag=1;
			p[count].frag=frame_size-rem;
			p[count].frames[p[count].frame_count]=loc;
			p[count].frame_count++;
		}
		else if(nof>0)
		{
			loc=rand()%n;
			while(f[loc].flag==1)
			loc=rand()%n;
			f[loc].flag=1;
			p[count].frames[p[count].frame_count]=loc;
			p[count].frame_count++;
		}
		nof--;
	}
	count++;
}
void del()
{
	int i,c;
	int key;
	printf("enter process id to delete = ");
	scanf("%d",&key);
	c=search(key);
	if(c==-1)//check if process you wish to delete is actually present
	{
		printf("\ngiven process not found!\n");
		return;
	}
	for(i=0;i<p[c].frame_count;i++)
	f[p[c].frames[i]].flag=0;//set all frames used by that process as vacant
	for(i=c;i<count-1;i++)
	p[i]=p[i+1];
	count--;
	printf("\nsuccessfully deleted process %d\n",key);
}
void display()
{
	int i,j,ifrag=0;
	printf("\nPage Table\npid\tsize\tframes\n");
	for(i=0;i<count;i++)
	{
		printf("%d\t%d\t",p[i].id,p[i].size);
		for(j=0;j<p[i].frame_count;j++)
		printf("%d ",p[i].frames[j]);
		printf("\n");
		ifrag+=p[i].frag;
	}
	printf("total internal fragmentation = %d\n",ifrag);
}
void main()
{
	int ch,i;
	printf("enter the total size of primary memory = ");
	scanf("%d",&mem_size);
	printf("enter the size of each frame = ");
	scanf("%d",&frame_size);
	n=mem_size/frame_size;
	for(i=0;i<max;i++)
	f[i].flag=0;//set all frames empty
	while(1)
	{
		printf("1.insert\n2.delete\n3.display\n4.exit\nenter your choice = ");
		scanf("%d",&ch);
		if(ch==1)
		insert();
		else if(ch==2)
		del();
		else if(ch==3)
		display();
		else if(ch==4)
		exit(0);
		else
		printf("\nwrong choice!"); 
	}	
}
