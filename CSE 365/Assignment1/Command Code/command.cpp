#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	cout << argc-1 << endl; // prints the number of arguments entered

	for(int i = argc-1; i > 0; i--) // loop backwards til first arg
		cout << argv[i] << " ";
	
	if(argc-1 != 0)
		cout << endl;

	return 0;
}
