#include <iostream>

using namespace std;

int foo(int x, int y) // size-n problem
{
	if (x <= 0) // stopping condition
		return y;
	else if (y <= 0) // stopping condition
		return x;
	if (x >= y)
		return x + foo(x - 1, y - 2); // size-m problem and soltion of size-n problem
	else
		return y + foo(x - 2, y - 3); // size-m problem and soltion of size-n problem
}

void main()
{
	cout << foo(5, 6) << endl;



}