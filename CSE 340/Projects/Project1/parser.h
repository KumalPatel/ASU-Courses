/* 
 * Copyright (C) Rida Bazzi, 2019
 * Do not share this file with anyone
 */

#ifndef __PARSER_H__
#define __PARSER_H__
#include <string>
#include "lexer.h"
#include <vector>

using namespace std;

struct monomial {
    int index;
    int power;  
} ;  

struct symbol {
	int index;
	string var;
};


class Parser {
  private:
    LexicalAnalyzer lexer;
    void syntax_error();
    Token expect(TokenType expected_type);
    Token peek();

  public:  
    void parse_input();
    void parse_program();
    void parse_poly_decl_section();
    void parse_poly_decl();
    vector<string> parse_polynomial_header();
    void parse_id_list(vector <string>);
    Token parse_polynomial_name();
    void parse_polynomial_body();
    void parse_term_list();
    void parse_term();
    vector <monomial*> parse_monomial_list();
    struct monomial* parse_monomial();
    int  parse_exponent();
    void parse_add_operator();
    int  parse_coefficient();
    void parse_start();
    void parse_inputs();
    void parse_statement_list();
    void parse_statement();
    void parse_poly_evaluation_statement();
    void parse_input_statement();
    void parse_polynomial_evaluation();
    void parse_argument_list();
    void parse_argument();
    void error_code_1();
    void error_code_2();
    void error_code_3();
    void error_code_4();
    void error_code_5();
};  




#endif


