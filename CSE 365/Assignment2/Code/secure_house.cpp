#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <bits/stdc++.h> 

using namespace std;

int main(int argc, char** argv)
{
	//local variables
	string input;
	string owner_name;
	string user_name;
	string key;
	string del = " ";
	vector<string> user;
	int temp = 0;
	bool leave = false;
	bool flag = false;
	vector<string> authorized_keys; // used to keep track which keys are authorized

	owner_name = argv[1]; // in-case owner names needs to be referred back to

	int j = 1;
	int i = 2;
	
	authorized_keys.insert(authorized_keys.begin(),"FIREFIGHTER_SECRET_KEY");

	while(i < argc) // setting authorized_key to have a list of all keys listed from command args
	{
		authorized_keys.insert(authorized_keys.begin()+j, argv[i]);
		j++;
		i++;
	}
	

	while(getline(cin, input)) // loops back while there is input
	{	
		string name = input.substr(0, input.find(del)); // used to determine which input 
		if(name.compare("INSERT") == 0)
		{
			string token = input.substr(0, input.find(del)); 
			input.erase(0, input.find(del)+del.length());
			token = input.substr(0, input.find(del));
			input.erase(0, input.find(del)+del.length());

			token = input.substr(0, input.find(del));
			user_name = token;
					
			input.erase(0, input.find(del)+del.length());
			token = input.substr(0,input.find(del));
			key = token;

			cout << "KEY " << key << " INSERTED BY " << user_name << endl; 

		}
		else if(name.compare("TURN") == 0)
		{	
			string token = input.substr(0, input.find(del)); 
			input.erase(0, input.find(del)+del.length());
			token = input.substr(0,input.find(del));
			input.erase(0,input.find(del)+del.length());
			token = input.substr(0,input.find(del));
			input.erase(0,input.find(del)+del.length());

			//if(token != user_name)
			//	cout << "ERROR" << endl;
			
			//{
				if(find(authorized_keys.begin(),authorized_keys.end(),key) != authorized_keys.end() && token == user_name)
				{
					flag = true;
					cout << "SUCCESS " << token << " TURNS KEY " << key << endl;
				}
				else
				{
					flag = false;
					cout << "FAILURE " << token << " UNABLE TO TURN KEY " << key << endl;
				}	
			//}
			
		}
		else if(name.compare("ENTER") == 0)
		{
			string token = input.substr(0, input.find(del)); 
			input.erase(0, input.find(del)+del.length());
			token = input.substr(0,input.find(del));
			input.erase(0,input.find(del)+del.length());
			token = input.substr(0,input.find(del));
			input.erase(0,input.find(del)+del.length());

			if(token != user_name)
				cout << "ACCESS DENIED" << endl;
			else
			{
				if(flag == true)
					{
						user.push_back(user_name); // stores user names in the vector
						cout << "ACCESS ALLOWED" << endl;
						temp++;
					}
				else
					cout << "ACCESS DENIED" << endl;
			}
		}
		else if(name.compare("WHO'S") == 0)
		{	
			if(user.empty())
				cout << "NOBODY HOME" << endl;
			else
				{
					bool first = true;
					for(int i = 0; i < user.size(); i++)
					{
						if(first)
							first = false;
						else
							cout << ", ";
						
						cout << user[i];
					}

					cout << endl;
				}
		}
		else if(name.compare("CHANGE") == 0) // house can be rekeyed with new keys only by the owner, and only if the owner is inside the house
		{	
			string token = input.substr(0, input.find(del)); 
			input.erase(0, input.find(del)+del.length());
			token = input.substr(0,input.find(del));
			input.erase(0,input.find(del)+del.length());
			token = input.substr(0,input.find(del));
			input.erase(0,input.find(del)+del.length());

			istringstream str(input); // stores the input string into the string stream
			vector <string> keys;

			if(token != owner_name)
				cout << "ACCESS DENIED" << endl;
			else
			{
				if((find(user.begin(), user.end(), owner_name) != user.end()))
				{
					cout << "OK" << endl;
					
					do
					{
						string word;
						str >> word; // reads word one at a time from string stream
						
						if(!(word.empty())) // if empty rekey
			 			{
							keys.push_back(word);
						}
					}
					while(str);

					authorized_keys = keys;
					authorized_keys.push_back("FIREFIGHTER_SECRET_KEY");
				}
				else
					cout << "ACCESS DENIED" << endl;
			}
		}
		else if(name.compare("LEAVE") == 0)
		{
			string token = input.substr(0, input.find(del)); 
			input.erase(0, input.find(del)+del.length());
			token = input.substr(0,input.find(del));
			input.erase(0,input.find(del)+del.length());
			token = input.substr(0,input.find(del));
			input.erase(0,input.find(del)+del.length());

			int temp = 0;

			for(int i = 0; i < user.size(); i++)
			{
				temp = i;

				if(token == user[i])
				{
					leave = true;
					break;
				}
				else
					leave = false;
			}

			if(leave == false)
				cout << token << " NOT HERE" << endl;
			else
			{
				user.erase(user.begin() + temp);
				cout << "OK" << endl;
			}
		}
		else
			cout << "ERROR" << endl;
	}
	return 0;
}
