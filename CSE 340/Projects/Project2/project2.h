#include "lexer.h"
#include "parser.h"
#include <map>
#include <unordered_map>

#ifndef __PROJECT_2__H__
#define __PROJECT_2__H__

class project2
{
    private:
        parser parse;

    public:
        void ReadGrammar();
        void printTerminalsAndNoneTerminals();
        void RemoveUselessSymbols();
        void CalculateFirstSets();
        void CalculateFollowSets();
        void CheckIfGrammarHasPredictiveParser();
        void isTerminalorNonterminal();
        void isGenerating();
        void removeGeneratingRule();
        void isReachable();
        void removeReachableRule();
        bool is_NT(string str);
        bool is_T(string str);
        void first_calc();
        void follow_calc();
        bool has_epsilon(vector<string> vec);
        vector<string> remove_epsilon(vector<string> vec);
        void printVector(vector<string>);
        bool check_duplicate(string temp, vector<string> vect);
        vector<string> remove_duplicate(vector<string> vect);
        bool flag = true;

        map<string,bool> generating;
        map<string,bool> reachable;
        vector<struct rules> genRules;
        vector<struct rules> reachableRules;
        vector<string> first;
        vector<string> follow;
        map<string, vector<string>> first_set;
        map<string, vector<string>> follow_set;

        
};
#endif // ENDIF PROJECT_2_H

