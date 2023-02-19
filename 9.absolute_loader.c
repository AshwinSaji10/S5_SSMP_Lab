#include<stdio.h>
#include<stdlib.h>
void main()
{
	FILE *fob,*fop;
	char line[200];
	char start[50];
	int start_hex;
	fob=fopen("obj.txt","r");
	fop=fopen("output.txt","w");
	while(fscanf(fob,"%s",line)!=EOF)
	{
		if(line[0]=='T')
		{
			int i,j;
			for(i=2,j=0;i<=7;i++,j++)
				start[j]=line[i];
			start[j]='\0';
			start_hex=strtol(start,NULL,16);
			i=12;
			while(line[i]!='$')
			{
				if(line[i]!='^')
				{
					fprintf(fop,"00%X\t%c%c\n",start_hex,line[i],line[i+1]);
					printf("00%X\t%c%c\n",start_hex,line[i],line[i+1]);
					start_hex+=1;
					i+=2;
				}
				else
					i++;
			}
		}
	}
	fclose(fob);
	fclose(fop);
}

/*object file
H^SAMPLE^001000^0035
T^001000^06^001003^071009$
T^002000^03^111111$
T^002050^06^182000^4C0000$
E^001000
*/

