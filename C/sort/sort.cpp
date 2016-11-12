#include<stdio.h>

void select_sort(int *num,int len);
void bubble_sort(int *num,int len);
void display(int *num,int len);

void main()
{
	int num[10]={23,12,54,2,56,76,2,45,56,16};
	printf("—°‘Ò≈≈–ÚÀ„∑®£∫\n");
	select_sort(num,10);
	display(num,10);
	printf("√∞≈›≈≈–ÚÀ„∑®£∫\n");
	bubble_sort(num,10);
	display(num,10);

}


void select_sort(int *num,int len)
{
	for(int i=0;i<len-1;i++)
	{
		for(int j=i+1;j<len;j++)
		{
			if(num[i]>num[j])
			{
				int temp;
				temp=num[i];
				num[i]=num[j];
				num[j]=temp;
			}
		}
	}
}

void bubble_sort(int *num,int len)
{
	for(int i=0;i<len-1;i++)
	{
		for(int j=0;j<len-i-1;j++)
		{
			if(num[j]>num[j+1])
			{
				int temp;
				temp=num[j];
				num[j]=num[j+1];
				num[j+1]=temp;
			}
		}
	}
}

void display(int *num,int len)
{
	for(int i=0;i<len;i++)
	{
		printf("%5d",num[i]);
	}
	printf("\n");
}