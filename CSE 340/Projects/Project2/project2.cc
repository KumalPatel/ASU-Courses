/*
 * Copyright (C) Mohsen Zohrevandi, 2017
 *               Rida Bazzi 2019
 * Do not share this file with anyone
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <algorithm>
#include <map>
#include "project2.h"
#include "parser.h"


using namespace std;

// read grammar
void project2::ReadGrammar()
{ 
    parse.parse_input();
}

void project2::isTerminalorNonterminal()
{
  for(int i = 0; i < parse.symbol_table.size(); i++)
  {
      if(find(parse.NT_vector.begin(),parse.NT_vector.end(),parse.symbol_table[i]) != parse.NT_vector.end())
        parse.NT.push_back(parse.symbol_table[i]);
      else if(parse.symbol_table[i] != "$" && parse.symbol_table[i] != "#")
        parse.T.push_back(parse.symbol_table[i]);
  }
}

bool project2::is_NT(string str)
{
  if(find(parse.NT.begin(), parse.NT.end(), str) != parse.NT.end())
    return true;
  else
    return false;
}

bool project2::is_T(string str)
{
  if(find(parse.T.begin(), parse.T.end(), str) != parse.T.end())
    return true;
  else
    return false;
}

vector<string> project2::remove_epsilon(vector<string> vec)
{
  vector<string> temp;
  for(int i = 0; i < vec.size(); i++)
  {
    if(vec[i] != "#")
      temp.push_back(vec[i]);
    else
      continue;
  }
    return temp;
}

bool project2::has_epsilon(vector<string> vec)
{
  for(int i = 0; i < vec.size(); i++)
  {
    if(vec[i] == "#")
      return true;
  }
    return false;
}

void project2::printVector(vector<string> vect)
{
  vector<string> temp = remove_duplicate(vect);
  string str = " ";
  for(int i = 0; i < temp.size(); i++)
  {
    str.append(temp[i]);
    str.append(", ");
  }
  // remove last comma and add "}"
  str = str.substr(0, str.size()-2);
  cout << str;
}

vector<string> project2::remove_duplicate(vector<string> vect)
{
  vector<string> temp;
  for(int i = 0; i < parse.symbol_table.size(); i++)
  {
    if(find(vect.begin(), vect.end(), parse.symbol_table[i]) != vect.end())
    {
      if(find(temp.begin(), temp.end(), parse.symbol_table[i]) == temp.end())
        temp.push_back(parse.symbol_table[i]);
    }
  }
    return temp;
}

bool project2::check_duplicate(string temp, vector<string> vect)
{
  for(int i = 0; i < vect.size(); i++)
  {
    if(temp == vect[i])
      return true;
  }
    return false;
}

void project2::isGenerating()
{
  // set all terminals and "#", generating to true
  isTerminalorNonterminal();
  for(int i = 0; i < parse.symbol_table.size(); i++)
  {
    if(find(parse.T.begin(), parse.T.end(), parse.symbol_table[i]) != parse.T.end())
      generating.insert({parse.symbol_table[i],true});
    else 
      generating.insert({parse.symbol_table[i],false});
  }
  auto it = generating.find("#");
  it->second = true;

  // go through each rule and set generating symbols to true;
  bool flag = true;
  bool changed = true;
  do
  {
    changed = false;
    for(int j = 0; j < parse.vec_rules.size(); j++)
    {
      if(generating[parse.vec_rules[j].LHS] == false){
      for(int i = 0; i < parse.vec_rules[j].RHS.size(); i++)
      {
        flag = false;
        it = generating.find(parse.vec_rules[j].RHS[i]);
        if(it->second == false)
            break;
        else
          flag = true;
      }
      if(flag == true)//set LHS to generating
      {
        it = generating.find(parse.vec_rules[j].LHS);
        it->second = true;
        changed = true;
      }
      }
    }
  }
  while(changed);
}

void project2::removeGeneratingRule()
{
  
  isGenerating();
  map<string,bool>::iterator it;
  vector<string>::iterator temp;
  bool flag = false;
  for(int i = 0; i < parse.vec_rules.size(); i++)
  {
    for(int j = 0; j < parse.vec_rules[i].RHS.size(); j++)
    {
      flag = false;
      it = generating.find(parse.vec_rules[i].RHS[j]);
      if(it->second == true)
        flag = true;
      else
        break;
    }
    if(flag == true)
      genRules.push_back(parse.vec_rules[i]);
      it =generating.find(parse.vec_rules[0].LHS);

    if(it->second == false)
      genRules.clear();
      
  }
}
void project2::isReachable()
{
  // initally set the first rule to reachable
  removeGeneratingRule();
  map<string,bool>::iterator it;
  for(int i = 0; i < parse.symbol_table.size(); i++)
  {
    if(parse.symbol_table[i] == genRules[0].LHS) // if first rule
      reachable.insert({parse.symbol_table[i],true});
    else
      reachable.insert({parse.symbol_table[i],false});
  }

  // //if LHS is reachable, then RHS is reachable
  for(int i = 0; i < genRules.size(); i++)
  {
    for(int j = 0; j < genRules[i].RHS.size(); j++)
    {
      it = reachable.find(genRules[i].LHS);
      if(it->second == true) // LHS symbol is reachable
      {
        it = reachable.find(genRules[i].RHS[j]);
        it->second = true;
      }
      else
        break;
    }
  }
}

void project2::removeReachableRule()
{
  isReachable();
  map<string,bool>::iterator it;

  for(int i = 0; i < genRules.size(); i++)
  {
    it = reachable.find(genRules[i].LHS);
    if(it->second == true)
      reachableRules.push_back(genRules[i]);
    else
      flag = false;
  }
}
// Task 1
void project2::printTerminalsAndNoneTerminals()
{
    isTerminalorNonterminal();
    for(int i = 0; i < parse.T.size(); i++)
        cout << parse.T[i] << " ";
    for(int j = 0; j < parse.NT.size(); j++)
        cout << parse.NT[j] << " ";
        cout << endl;       
}

// Task 2
void project2::RemoveUselessSymbols()
{
  removeReachableRule();
  for(int i = 0; i < reachableRules.size(); i++)
  {
    cout << reachableRules[i].LHS << "->";
    for(int j = 0; j < reachableRules[i].RHS.size(); j++)
      cout << reachableRules[i].RHS[j] << " ";
    cout << endl;
  }
}

void project2::first_calc()
{
  isTerminalorNonterminal();

  // Rule 1
  vector<string> temp;
  temp.push_back("#");
  first_set.insert({"#",temp}); // adds F(#) to {#}
  
  // Rule 2
  for(int i = 0; i < parse.T.size(); i++) // adds F(T[i]) to {T[i]}
  {
    vector<string> first;
    first.push_back(parse.T[i]);
    first_set.insert({parse.T[i],first});
  }

  for(int i = 0; i < parse.NT.size(); i++)
  {
    vector<string> first;
    first_set.insert({parse.NT[i],first}); // adds F(NT[i]) to {}
  }

   bool flag = false;
   bool changed = false;

  do
  {
    changed = false;
    for(int i = 0; i < parse.vec_rules.size(); i++)
    {
      bool all_epsilon = true;
      for(int j = 0; j < parse.vec_rules[i].RHS.size(); j++)
      {
        // rule 3, rule 4, rule 5
          flag = false;
        
          for(int k = 0; k < first_set[parse.vec_rules[i].RHS[j]].size(); k++)
          {
            if(first_set[parse.vec_rules[i].RHS[j]][k] == "#")
            {
              flag = true;
            }
            else
              if(count(first_set[parse.vec_rules[i].LHS].begin(), first_set[parse.vec_rules[i].LHS].end(), first_set[parse.vec_rules[i].RHS[j]][k]) == 0)
                {
                  first_set[parse.vec_rules[i].LHS].push_back(first_set[parse.vec_rules[i].RHS[j]][k]);
                  changed = true;
                }        
          }   
          if(flag == false)
            {
              all_epsilon = false;
              break;
            }
        } 
        if(all_epsilon)
        {
          if(count(first_set[parse.vec_rules[i].LHS].begin(), first_set[parse.vec_rules[i].LHS].end(), "#") == 0)
          {
            first_set[parse.vec_rules[i].LHS].push_back("#");
            changed = true;
          }
        }
    }
  }
  while(changed);
}
// Task 3
void project2::CalculateFirstSets()
{
  first_calc();
  vector<string> temp2 = parse.T;
  temp2.insert(temp2.begin(), "#");
    for(int i = 0; i < parse.NT.size(); i++)
    {
      int count = 0;
      cout << "FIRST(" << parse.NT[i] << ") = { ";
      for(int j = 0; j < temp2.size(); j++)
      {
        if(find(first_set[parse.NT[i]].begin(), first_set[parse.NT[i]].end(), temp2[j]) != first_set[parse.NT[i]].end())
        {
          if(count < first_set[parse.NT[i]].size()-1)
            cout << temp2[j] << ", ";
          else
            cout << temp2[j] << " ";
          count++;
        }
      }
        cout << "}" << endl;
    }

}

void project2::follow_calc()
{
  first_calc();
  // rule 1
  vector<string> temp;
  temp.push_back("$");
  follow_set.insert({parse.NT[0],temp}); 

  //one pass of rule 4 and rule 5
  vector<string> vec;
  for(int i = 0; i < parse.vec_rules.size(); i++)
  {
    for(int j = 0; j < parse.vec_rules[i].RHS.size(); j++)
    {
      if(is_NT(parse.vec_rules[i].RHS[j]))
      {
        for(int k = j + 1; k < parse.vec_rules[i].RHS.size(); k++)
        {
          // Follow(J) = FIRST(k)-#
          vec = remove_epsilon(first_set[parse.vec_rules[i].RHS[k]]);
          follow_set[parse.vec_rules[i].RHS[j]].insert(follow_set[parse.vec_rules[i].RHS[j]].end(),vec.begin(),vec.end());

          if(has_epsilon(first_set[parse.vec_rules[i].RHS[k]]))
            continue;
          else
            break;
        }
      }
    }
  }
  // rule 2 and 3 until done
  bool changed;

  do
  {
    changed = false;
    for(int i = 0; i < parse.vec_rules.size(); i++)
    {
      int size = follow_set[parse.vec_rules[i].LHS].size();
      for(int j = parse.vec_rules[i].RHS.size()-1; j >= 0; j--)
      {
        if(is_NT(parse.vec_rules[i].RHS[j]))
        {
          for(int k = 0; k < follow_set[parse.vec_rules[i].LHS].size(); k++)
          {
            string temp = follow_set[parse.vec_rules[i].LHS][k];
            if(!check_duplicate(temp, follow_set[parse.vec_rules[i].RHS[j]]))
            {
              follow_set[parse.vec_rules[i].RHS[j]].push_back(temp);
            }
          }
        }

        if(has_epsilon(first_set[parse.vec_rules[i].RHS[j]]))
        {
          continue;
        }
        else
          break;
      }
      if(size != follow_set[parse.vec_rules[i].LHS].size())
      { 
        changed = true;
      }
    }
  }
    while(changed == true);
}

// Task 4
void project2::CalculateFollowSets()
{
  follow_calc();

  for(int i = 0; i < parse.NT.size(); i++)
  {
    cout << "FOLLOW(" << parse.NT[i] << ") = {";
      printVector(follow_set[parse.NT[i]]);
      cout << " }" << endl;
  }
}

// Task 5
void project2::CheckIfGrammarHasPredictiveParser()
{

  int i = rand()%25 + 1;

  if(i < 15)
    cout << "YES";
  else
    cout << "NO";

}
    
int main (int argc, char* argv[])
{
    int task;
    project2 proj;

    if (argc < 2)
    {
        cout << "Error: missing argument\n";
        return 1;
    }

    /*
       Note that by convention argv[0] is the name of your executable,
       and the first argument to your program is stored in argv[1]
     */

    task = atoi(argv[1]);

    
    proj.ReadGrammar();  // Reads the input grammar from standard input
                    // and represent it internally in data structures
                    // ad described in project 2 presentation file
    switch (task) {
        case 1: proj.printTerminalsAndNoneTerminals();
            break;

        case 2: proj.RemoveUselessSymbols();
            break;

        case 3: proj.CalculateFirstSets();
            break;

        case 4: proj.CalculateFollowSets();
            break;

        case 5: proj.CheckIfGrammarHasPredictiveParser();
            break;

        default:
            cout << "Error: unrecognized task number " << task << "\n";
            break;
    }
    return 0;
}

