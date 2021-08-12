#include "lexer.h"
#include <map>

#ifndef __PARSER__H__
#define __PARSER__H__

using namespace std;

struct rules
{
    string LHS;
    vector<string> RHS;
};

class parser
{
    private:
        LexicalAnalyzer lexer;
        void syntax_error();
        Token expect(TokenType expected_type);
        Token peek();
    
    public:
        void parse_input();
        void parse_rule_list();
        void parse_id_list();
        void parse_rule();
        void parse_right_hand_side();
        vector<string> symbol_table;
        vector<struct rules> vec_rules;
        vector<string> NT;
        vector<string> T;
        vector<string> vect;
        vector<string> NT_vector;
}; 
#endif // END __PARSER__H__


