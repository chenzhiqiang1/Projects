#include<stdio.h>
#include<stdlib.h>
void main()
{
	FILE *in,*out;
	char ch;

	in=fopen("a.txt","r");
	out=fopen("b.txt","w");
	if(in==NULL)
	{
		printf("Can't open the file.\n");
		exit(0);
	}
	if(out==NULL)
	{
		printf("Can't open the file.\n");
		exit(0);
	}
	while(!feof(in))
	{
		ch=fgetc(in);
		fputc(ch,out);
		putchar(ch);
	}
	printf("\n");
	fclose(in);
	fclose(out);
}