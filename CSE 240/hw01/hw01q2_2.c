#include <stdio.h>

int main(){
char ch = '+';
int a = 10, b = 20;
double f = 0;

	for(int i = 0; i < 5; i++)
	{
		printf("Enter the math operation: ");
		ch = getchar();
		fflush(stdin);
		printf("ch = %c\n",ch);

	if(ch == '+')
	{
		f = a + b;
		printf("f = %d\n",(int)f);
	}
	else if(ch == '-')
	{
		f = a - b;
		printf("f = %d\n",(int)f);
	}
	else if(ch == '*')
	{
		f = a * b;
		printf("f = %d\n",(int)f);
	}
	else if(ch == '/')
	{
		f = (double) a / b;
		printf("f = %.2f\n",f);
	}
	else if(ch == '%')
	{
		f = a % b;
		printf("f = %d\n",(int)f);
	}
	else
		printf("Invalid Operator\n");
	}

	return 0;
}