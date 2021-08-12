#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "parser.h"

using namespace std;

void parser::syntax_error()
{
    cout << "SYNTAX ERROR !!!\n";
    exit(1);   
}

Token parser::expect(TokenType expected_type)
{
    Token t = lexer.GetToken();
    if(t.token_type != expected_type)
        syntax_error();
    return t;
}

Token parser::peek()
{
    Token t = lexer.GetToken();
    lexer.UngetToken(t);
    return t;
}

void parser::parse_input()
{
    symbol_table.push_back("#");
    symbol_table.push_back("$");
    parse_rule_list();
    expect(DOUBLEHASH);
}

void parser::parse_rule_list()
{
    parse_rule();
    Token t = peek();

    if(t.token_type == ID)
        parse_rule_list();
}

void parser::parse_id_list()
{
    Token t1 = peek();
    if(t1.token_type == ID)
    {
        Token t = expect(ID);
        vect.push_back(t.lexeme); // stores RHS into vector
        if(count(symbol_table.begin(),symbol_table.end(),t.lexeme) == 0)
            symbol_table.push_back(t.lexeme);
    }
    else // if epsilon
     {
        vect.push_back("#");
        return;
     }   
    Token t = peek();

    if(t.token_type == ID) 
        parse_id_list();    
}

void parser::parse_rule()
{
    struct rules R;
    Token t = expect(ID);
    if(count(NT_vector.begin(), NT_vector.end(), t.lexeme) == 0)
        NT_vector.push_back(t.lexeme);
    if(count(symbol_table.begin(),symbol_table.end(),t.lexeme) == 0) // token is not in symbol table
        symbol_table.push_back(t.lexeme); 
    
    R.LHS = t.lexeme; // NT
    expect(ARROW);
    parse_right_hand_side(); // store RHS into vector of IDs
    R.RHS = vect;
    vec_rules.push_back(R); // stores rules
    vect.clear();
    expect(HASH);
}

void parser::parse_right_hand_side()
{
    parse_id_list(); 
}