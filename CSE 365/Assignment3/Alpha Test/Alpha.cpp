#include <iostream>
#include <string>

// global
char input[] = "CUYQYWMSLEJYBWUFMQCCWCQUCPCSLGOSCYQRMAMJMPYLBQGXCUFCLQFCMNCLCBRFCKUGBCNCMNJCYJJRSPLCBYQGBCYLBQRYPRCB";
int inputSize = sizeof(input)/sizeof(*input);
int cast[sizeof(input)];
int castSize = sizeof(cast)/sizeof(*cast);

using namespace std;

void doChange(int val, int pos)
{
    int diff = 65 - val;
    int curr = 91 - diff;
    cout << (char)(curr);
}

int main()
{
    for(int i = 0; i < inputSize-1; i++) //stores ascii representation in int array
         cast[i] = (int)input[i]; 
        
    for(int j = 1; j < 26; j++)
    {
        for(int i = 0; i < castSize-1; i++)
        {
            if(cast[i]-j < 65)
                doChange(cast[i]-j,i);
            else
                cout << (char)(cast[i]-j); 
        }
        cout << endl;
    }
    return 0;
}
