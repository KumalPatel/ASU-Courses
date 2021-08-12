//
// Created by kumal on 4/15/2020.
//

#include "lexer.h"
#include <map>

#ifndef PROJECT4_PARSER_H
#define PROJECT4_PARSER_H

class Parser
{
private:
    LexicalAnalyzer lexer;
    void syntax_error();
    Token expect(TokenType expected_type);
    Token peek();
public:
    // functions
    void parse_program();
    void parse_scope();
    void parse_scope_list();
    void parse_var_decl();
    void parse_id_list();
    TokenType parse_type_name();
    void parse_stmt_list();
    void parse_stmt();
    void parse_assign_stmt();
    void parse_while_stmt(int);
    TokenType parse_expr(int);
    TokenType parse_arithmetic_expr(int);
    TokenType parse_boolean_expr(int);
    void parse_arithmetic_operator();
    void parse_binary_boolean_operator();
    void parse_relational_operator();
    TokenType parse_primary();
    TokenType parse_arithmetic_primary();
    TokenType parse_boolean_primary();
    TokenType parse_bool_const();
    TokenType parse_condition(int);
    std::string print_decl_msg(float, std::string);
    std::string print_mismatch_msg(int, std::string);
    bool if_exist(std::vector<std::string>, std::string); // if false not found , else true found
    bool lookup(struct Node*, std::string); // if false not found in scopes, else true exists in scopes
    bool local_lookup(struct Node*, std::string);
    std::vector<std::string> compare_vect(std::vector<std::string>, std::vector<std::string>); // iterates through vect1
    void insert_end();
    void delete_last();
    void print_error_msg(double);
    TokenType find_in_map(std::string); // looks up id and return its type
    void print_type_msg(std::string);

    // data structures
    struct Node* curr = nullptr;
    std::vector<std::string> error1; // duplicate var declaration
    std::vector<std::string> error2; // undeclared var, and used in assign stmts
    std::vector<std::string> error3; // declared, but not used in assign stmts
    std::vector<std::string> allIDs;
    std::vector<std::string> decl;
    std::vector<int> c1type;
    std::vector<int> c2type;
    std::vector<int> c3type;
    std::vector<int> m1type;
    std::vector<int> c4type;
    std::vector<int> c5type;
    std::vector<int> c6type;
    std::vector<int> c7type;
    std::vector<int> c8type;
    std::vector<int> c8type2;
    std::vector<int> c9type;
    std::vector<int> c10type;
    std::vector<int> c11type;
    std::vector<int> m2type;
    std::vector<std::string> t1; // temp for id_list
};

struct Node // each node representing a scope
{
    std::map<std::string, TokenType> data;
    std::vector<std::string> vect;

    struct Node* next;
    struct Node* prev;
//    Node()
//    {
//        next = nullptr;
//        prev = nullptr;
//    }
};


#endif //PROJECT4_PARSER_H
