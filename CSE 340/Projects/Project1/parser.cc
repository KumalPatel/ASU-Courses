/*
 * Copyright (C) Rida Bazzi, 220
 * Do not share this file with anyone
 * Do not post this file or derivatives of
 * of this file online
 */
#include <iostream>
#include <cstdlib>
#include "parser.h"
#include "lexer.h"
#include <vector>
#include <algorithm>
#include<map>
#include<iterator>
using namespace std;


// global varriables
int next_available = 0;
vector<symbol> symbol_table;
vector<int> memory;
vector<int> num;
vector<string> tmp;
vector<monomial*> vec;
vector<Token> tokens;
vector<int> line;
struct monomial *mono;
map<string,vector<int>> all_names;
vector<string> input;
vector<string> poly;
vector<int> lines;
vector<int> error;
int countID = 0;
int countArgs = 0;
vector<int> lineNum;

void Parser::syntax_error()
{
    cout << "SYNTAX ERROR !!!\n";
    exit(1);
}

// this function gets a token and checks if it is
// of the expected type. If it is, the token is
// returned, otherwise, synatx_error() is generated
// this function is particularly useful to match
// terminals in a right hand side of a rule.
// Written by Mohsen Zohrevandi

Token Parser::expect(TokenType expected_type)
{
    Token t = lexer.GetToken();
    if (t.token_type != expected_type)
        syntax_error();
    return t;
}
// this function simply checks the next token without
// consuming the input
// Written by Mohsen Zohrevandi

Token Parser::peek()

{
    Token t = lexer.GetToken();
    lexer.UngetToken(t);
    return t;
}

// Parsing
void Parser::parse_input()
{
   parse_program();
   parse_inputs();
}

void Parser::parse_program()
{
	parse_poly_decl_section();
	parse_start();
}

void Parser::parse_poly_decl_section()
{
	parse_poly_decl();
	Token t = peek();

	if(t.token_type == POLY)
	{
		parse_poly_decl_section();
	}
}

void Parser::parse_poly_decl()
{
	expect(POLY);
	parse_polynomial_header(); 
	expect(EQUAL);
	parse_polynomial_body();
	expect(SEMICOLON);
}

vector<string> Parser::parse_polynomial_header()
{
	Token temp = parse_polynomial_name();
	all_names[temp.lexeme].push_back(temp.line_no);
	Token token;
	token = peek();

	if(token.token_type == LPAREN)
	{
		token = lexer.GetToken();
		//countID++; 
		vector<string> poly_para;
		parse_id_list(poly_para);
		expect(RPAREN);
		return poly_para;
	}	
	else
		return tmp;
	}

void Parser::parse_id_list(vector<string> poly_para)
{
	Token token; 
	Token t = expect(ID);
	poly_para.push_back(t.lexeme);
	token = peek();

	if(token.token_type == COMMA)
	{
		lexer.GetToken();
		parse_id_list(poly_para);
	}
}

Token Parser::parse_polynomial_name()
{
	return expect(ID); 
}

void Parser::parse_polynomial_body()
{
	parse_term_list();
}

void Parser::parse_term_list()
{
	parse_term();
	Token token = peek();

	if(token.token_type == PLUS || token.token_type == MINUS)
	{
		parse_add_operator();
		parse_term_list();		
	}  
}

void Parser::parse_term()
{
	Token token = peek();
	if(token.token_type == ID)
	{
		parse_monomial_list();
	}

	else if(token.token_type == NUM)
	{
		parse_coefficient();
		token = peek();
		
		if(token.token_type == ID)
		{
			parse_monomial_list();
		}
	}
	else
		syntax_error();
}

vector <monomial*> Parser::parse_monomial_list()
{
	mono = parse_monomial();
	vec.push_back(mono);
	Token token = peek();
	
	if(token.token_type == ID)
	{
		parse_monomial_list();
	}	  
	return vec;
}

struct monomial* Parser::parse_monomial()
{
	struct monomial *temp = new monomial();
	int t_index;
	int t_power;
	Token t = expect(ID);
	Token token = peek();

	if(token.token_type == POWER)
	{
		for(int i = 0; i < symbol_table.size(); i++)
		{
			if(symbol_table[i].var == t.lexeme)
				t_index = symbol_table[i].index;
		}
		t_power = parse_exponent();		  
	}	
	temp->index = t_index;
	temp->power = t_power;   

	return temp;
}

int Parser::parse_exponent()
{
	expect(POWER);
	Token t = expect(NUM); 
	return stoi(t.lexeme);

}

void Parser::parse_add_operator()
{
	Token token = peek();

	if(token.token_type == PLUS)
	{
		lexer.GetToken();		  
	}

	else if(token.token_type == MINUS)
	{
		lexer.GetToken();		  
	}
	else
	{
		syntax_error();	  
	}	  
}

int Parser::parse_coefficient()
{
	Token t = expect(NUM);		  
	return stoi(t.lexeme);
}

void Parser::parse_start()
{
	expect(START);
	parse_statement_list();	
}

void Parser::parse_inputs()
{
	expect(NUM);
	Token token = peek();

	if(token.token_type == NUM)
	{
		num.push_back(stoi(token.lexeme));	
		parse_inputs();
	}

	else if (token.token_type != NUM && token.token_type != END_OF_FILE)
		syntax_error();	  
}

void Parser::parse_statement_list()
{
	parse_statement();
	Token token = peek();

	if(token.token_type == INPUT || token.token_type == ID)
	{
		parse_statement_list();
	}
}

void Parser::parse_statement()
{
	Token token = peek();

	if(token.token_type == INPUT)
	{
		parse_input_statement();
	}

	else if(token.token_type == ID)
	{
		parse_poly_evaluation_statement();
	}

	else
		syntax_error();
}

void Parser::parse_poly_evaluation_statement()
{
	parse_polynomial_evaluation();
	expect(SEMICOLON);	
}

void Parser::parse_input_statement()
{
	expect(INPUT);
	Token t = expect(ID);
	input.push_back(t.lexeme);
	expect(SEMICOLON);	

	for(int i = 0; i < symbol_table.size(); i++)
	{
		if(t.lexeme == symbol_table[i].var)
			return;
	}	
	symbol temp;
	temp.index = next_available++;
	temp.var = t.lexeme;
	symbol_table.push_back(temp);
}

void Parser::parse_polynomial_evaluation()
{
	Token t = parse_polynomial_name();
	if(all_names[t.lexeme].size() == 0){
		error.push_back(t.line_no);
	}
	expect(LPAREN);
	parse_argument_list();
//	if(countArgs != countID)
//		lineNum.push_back(t.line_no);

	expect(RPAREN);
}

void Parser::parse_argument_list()
{
	parse_argument();
	Token token = peek();
	
	if(token.token_type == COMMA)
	{
		lexer.GetToken();
		parse_argument_list();	
	}	  
}

void Parser::parse_argument()
{
	Token token = lexer.GetToken();
	Token token2 = peek();
	Token t;
	lexer.UngetToken(token);
	bool found = false;

	if(token.token_type == ID && token2.token_type == LPAREN)
	{
		parse_polynomial_evaluation();
	}	  

	else if(token.token_type == NUM)
	{
		expect(NUM);
	}

	else if(token.token_type == ID)
	{
		t = expect(ID);
		found = true;
		//countArgs++;

		if(t.token_type == ID)
		{
			for(int i = 0; i < input.size(); i++)
			{
				if(t.lexeme == input[i])
				{
					found = false;
					break;
				}
			}
			if(found == true)
			{
				lines.push_back(t.line_no);
			}
		}	
	}

	else
		syntax_error();
}

void Parser::error_code_1()
{
	vector<int> temp;
	map<string, vector<int>> :: iterator it;

	for(it = all_names.begin(); it!= all_names.end(); it++)
	{
		if(it->second.size() > 1)
		{
			for(int i = 0; i < it->second.size(); i++)
				temp.push_back(it->second[i]);
		}
	}

	if(temp.size() > 0)
	{
		cout << "Error Code 1: ";	
		sort(temp.begin(), temp.end());	

		for(int i = 0; i < temp.size(); i++)
			cout << temp[i] << " ";
			cout << endl;
	}
}

void Parser::error_code_2()
{

}

void Parser::error_code_3()
{
	if(error.size() > 0)
	{
		cout << "Error Code 3: ";
		sort(error.begin(),error.end());

		for(int i = 0; i < error.size(); i++)
		{
			cout << error[i] << " ";
		}
			cout << endl;
		}
}

void Parser::error_code_4()
{
	if(countArgs != countID)
	{
		cout << "Error Code 4: ";
		sort(lineNum.begin(), lineNum.end());

		for(int i = 0; i < lineNum.size(); i++)
		{
			cout << lineNum[i] << " ";
		}
			cout << endl;
	}
}

void Parser::error_code_5()
{
	if(lines.size() > 0)
	{
		cout << "Error Code 5: ";
		sort(lines.begin(), lines.end());

		for(int i = 0; i < lines.size(); i++)
		{
			cout << lines[i] << " ";
		}
		cout << endl;
	}	
}

int main()

{
    LexicalAnalyzer lexer;
	Parser parser;
    Token token;

    parser.parse_input();
	parser.error_code_1();
	parser.error_code_3();
	parser.error_code_4();
	parser.error_code_5();

}


