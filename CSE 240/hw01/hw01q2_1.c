#include <stdio.h>
int main() {
char ch = '+';
int a = 10, b = 20;
double f = 0;

printf("ch = %c\n", ch);
switch (ch) {
case '+':
	f = a + b;
	printf("f = %d\n",(int)f);
	break;
case '-':
	f = a - b;
	printf("f = %d\n",(int)f);
	break;
case '*':
	f = a * b;
	printf("f = %d\n",(int)f);
	break;
case '/':
	f = a / b;
	printf("f = %d\n",(int)f);
	break;
default:
	printf("invalid operator\n");
}

ch = '-';
printf("ch = %c\n", ch);
switch (ch) {
case '+':
	f = a + b;
	printf("f = %d\n",(int)f);
	break;
case '-':
	f = a - b;
	printf("f = %d\n",(int)f);
	break;
case '*':
	f = a * b;
	printf("f = %d\n",(int)f);
	break;
case '/':
	f = a / b;
	printf("f = %d\n",(int)f);
	break;
default:
	printf("invalid operator\n");
}

ch = '*';
printf("ch = %c\n", ch);
switch (ch) {
case '+':
	f = a + b;
	printf("f = %d\n",(int)f);
	break;
case '-':
	f = a - b;
	printf("f = %d\n",(int)f);
	break;
case '*':
	f = a * b;
	printf("f = %d\n",(int)f);
	break;
case '/':
	f = a / b;
	printf("f = %d\n",(int)f);
	break;
default:
	printf("invalid operator\n");
}

ch = '/';
printf("ch = %c\n", ch);
switch (ch) {
case '+':
	f = (double)a + b;
	printf("f = %.2f\n",f);
	break;
case '-':
	f = (double)a - b;
	printf("f = %.2f\n",f);
	break;
case '*':
	f = (double)a * b;
	printf("f = %.2f\n",f);
	break;
case '/':
	f = (double)a / b;
	printf("f = %.2f\n",f);
	break;
default:
	printf("invalid operator\n");
}

ch = '%';
printf("ch = %c\n", ch);
switch (ch) {
case '+':
	f = a + b;
	printf("f = %f\n",(int)f);
	break;
case '-':
	f = a - b;
	printf("f = %f\n",(int)f);
	break;
case '*':
	f = a * b;
	printf("f = %f\n",(int)f);
	break;
case '/':
	f = a / b;
	printf("f = %f\n",(int)f);
	break;
default:
	printf("invalid operator\n");
}
	return 0;
}
