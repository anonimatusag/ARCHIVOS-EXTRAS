#include<stdio.h>
#include<conio.h>
int main()
{
	int num[3][3];
	int f,c;
	for(f=0 ;  f<3 ; f++)
	{
		for(c=0 ; c<3 ; c++)
		{
	    printf("ingrese los datos ",f,c);	
	    scanf("%d", &num[f][c]);
		}
	}
	for(f=0 ; f<3 ; f++)
	{
		for(c=0 ;  c<3 ; c++)
		{
		printf("%d \n",num[f][c]);
		}
	}
	printf("\n ");
	getch();
	return 0;
}
