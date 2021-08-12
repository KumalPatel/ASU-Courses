#ifndef GRAMMAR_H_
#define GRAMMAR_H_

#include <iostream>
#include <map>
#include "lexer.h"

using namespace std;

class grammar 
{
    private:
        LexicalAnalyzer lexer;
        void syntax_error();
        Token expect(TokenType expected_type);
        Token peek();

    public:
        struct InstructionNode* parse_program();
        void parse_var_section();
        void parse_id_list();
        struct InstructionNode* parse_body();
        struct InstructionNode* parse_stmt_list();
        struct InstructionNode* parse_stmt();
        struct InstructionNode* parse_assign_stmt();
        struct InstructionNode* parse_expr();
        string parse_primary();
        Token parse_op();
        struct InstructionNode* parse_output_stmt();
        struct InstructionNode* parse_input_stmt();
        struct InstructionNode* parse_while_stmt();
        struct InstructionNode* parse_if_stmt();
        struct InstructionNode* parse_condition();
        Token parse_relop();
        struct InstructionNode* parse_switch_stmt();
        struct InstructionNode* parse_for_stmt();
        struct InstructionNode* parse_case_list(Token id, struct InstructionNode* i2);
        struct InstructionNode* parse_case(Token id, struct InstructionNode* i2);
        struct InstructionNode* parse_default_case(struct InstructionNode* i2);
        void parse_inputs();
        void parse_num_list();
        int location(string key);
        bool is_in_memory(string key);

        map<string,int> address_map;   
};



#endif /* GRAMMAR */