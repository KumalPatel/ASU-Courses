#include <iostream>
#include <string>

using namespace std;

char input[] = "BZKVBNYNRAOTKOZUZMBAKOKWXIVZYFDANHYHLIZUMYENFBMMLJKOKYLGPVCFPDZUMYLJTPXHREKPZBXORKJWBOJLJYLPYLPFMWELYJBISHYXVWEKHFFJSYOIDAILGHEAUBVFKZJUGWBZZAGXFPWSGXEAUVBJODVHJYEADLYXXCVDGXPDFYZFKZZAYWXZZVZJIAXYGUEPIHTXJEJZOTKPFVQTKHPUOSBIZUAYBOSHOSYNZKMJEWUPZFIHSFZMBOKHZNLJJWKWPKEUKQMQEJNJAPYLOSQAIJKUQAUTKXPWXLUSXPVSKYVLVAGUBZZHRJAWEBSGBNFUZMBPVSKYVLVDXNQAILDHEWENKFKZNOKSQDVJUSKATAOTKDRKHJBJDHJJCAUANJQWGLOSQKRTKHEWEPIFIPIHTXJEKAKWQDRAMTYXCLJNQQGHZBLNUZVJOIZUAYBPYLOSQAIJKUQNVHVUBWILJTKWGHMJMNZUZJOEEYUTJKWANJKW";
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
    for(int i = 0; i < inputSize-1; i++) // stores ascii representation in array
        cast[i] = (int)input[i];
    
    int count = 0;

    for(int i = 0; i < castSize-1; i++)
    {
        if(i % 6 == 0 && cast[i] == 84)
            count++;
    }

    cout << count << endl;
 
    return 0;
}
