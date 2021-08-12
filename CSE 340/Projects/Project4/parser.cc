//
// Created by kumal on 4/15/2020.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "parser.h"

using namespace std;

void Parser::syntax_error()
{
    cout << "Syntax Error &!#@\n";
    exit(1);
}

Token Parser::expect(TokenType expected_type)
{
    Token t = lexer.GetToken();
    if(t.token_type != expected_type)
        syntax_error();
    return t;
}

Token Parser::peek()
{
    Token t = lexer.GetToken();
    lexer.UngetToken(t);
    return t;
}

string Parser::print_mismatch_msg(int lineNo, string type)
{
    stringstream ss;
    string error("TYPE MISMATCH ");
    ss << lineNo;
    string tmp = ss.str();
    return error + tmp + " " + type;
}

string Parser::print_decl_msg(float type, string var)
{
    stringstream  ss;
    string error("ERROR CODE ");
    ss << fixed << setprecision(1) << type;
    string tmp = ss.str();
    return error + tmp + " " + var;
}

void Parser::print_error_msg(double type)
{
    if(type == 1.1)
    {
        for(int i = 0; i < error1.size(); i++)
            cout << print_decl_msg(1.1, error1[i]) << endl;
    }
    else if(type == 1.2)
    {
        for(int i = 0; i < error2.size(); i++)
            cout << print_decl_msg(1.2, error2[i]) << endl;
    }
    else if(type == 1.3)
    {
        for(int i = 0; i < error3.size(); i++)
            cout << print_decl_msg(1.3, error3[i]) << endl;
    }
}

void Parser::print_type_msg(string type)
{
    if(type == "C1")
    {
        for(int i = 0; i < c1type.size(); i++)
            cout << print_mismatch_msg(c1type[i], type) << endl;
    }
    else if(type == "C2")
    {
        for(int i = 0; i < c2type.size(); i++)
            cout << print_mismatch_msg(c2type[i], type) << endl;
    }
    else if(type == "C3")
    {
        for(int i = 0; i < c3type.size(); i++)
            cout << print_mismatch_msg(c3type[i], type) << endl;
    }
    else if(type == "M1")
    {
        for(int i = 0; i < m1type.size(); i++)
            cout << print_mismatch_msg(m1type[i], type) << endl;
    }
    else if(type == "C4")
    {
        for(int i = 0; i < c4type.size(); i++)
            cout << print_mismatch_msg(c4type[i], type) << endl;
    }
    else if(type == "C5")
    {
        for(int i = 0; i < c5type.size(); i++)
            cout << print_mismatch_msg(c5type[i], type) << endl;
    }
    else if(type == "C6")
    {
        for(int i = 0; i < c6type.size(); i++)
            cout << print_mismatch_msg(c6type[i], type) << endl;
    }
    else if(type == "C7")
    {
        for(int i = 0; i < c7type.size(); i++)
            cout << print_mismatch_msg(c7type[i], type) << endl;
    }
    else if(type == "C8")
    {
        for(int i = 0; i < c8type.size(); i++)
            cout << print_mismatch_msg(c8type[i], type) << endl;
    }
    else if(type == "C8'")
    {
        for(int i = 0; i < c8type2.size(); i++)
            cout << print_mismatch_msg(c8type2[i], type) << endl;
    }
    else if(type == "C9")
    {
        for(int i = 0; i < c9type.size(); i++)
            cout << print_mismatch_msg(c9type[i], type) << endl;
    }
    else if(type == "C10")
    {
        for(int i = 0; i < c10type.size(); i++)
            cout << print_mismatch_msg(c10type[i], type) << endl;
    }
    else if(type == "C11")
    {
        for(int i = 0; i < c11type.size(); i++)
            cout << print_mismatch_msg(c11type[i], type) << endl;
    }
    else if(type == "M2")
    {
        for(int i = 0; i < m2type.size(); i++)
            cout << print_mismatch_msg(m2type[i], type) << endl;
    }

}

bool Parser::if_exist(vector<string> temp, string element)
{
    bool flag = false;
    for(int i = 0; i < temp.size(); i++)
    {
        if(temp[i] == element)
            flag = true;
    }
    return flag;
}

vector<string> Parser::compare_vect(vector<string> vect1, vector<string> vect2)
{
    vector<string> temp;
    for(int i = 0; i < vect1.size(); i++)
    {
        if(find(vect2.begin(), vect2.end(), vect1[i]) == vect2.end()) // did not find element
            temp.push_back(vect1[i]);
    }
    return temp;
}

bool Parser::lookup(struct Node* scope, string element)
{
    if(scope != nullptr)
    {
        if(!local_lookup(scope, element)) // not found
            return lookup(scope->prev, element);
        else
            return local_lookup(scope, element); // found
    }
    else
        return false;
}

bool Parser::local_lookup(struct Node* scope, string element)
{
    return scope->data.find(element) != scope->data.end(); // not found
}

TokenType Parser::find_in_map(string value)
{
    Node *temp = curr;
    TokenType tmp = END_OF_FILE;
    if(!lookup(temp, value))
        return tmp;
    else
    {
        while(temp != nullptr)
        {
            if(local_lookup(temp, value))
                return temp->data.find(value)->second;
            else
                temp = temp->prev;
        }
    }
}

void Parser::insert_end()
{
    Node *newNode = new Node();

    newNode->prev = curr;
    newNode->next = nullptr;
    curr = newNode;
}

void Parser::delete_last()
{
    Node *temp = curr;
    curr = curr->prev;
    delete(temp);
}
void Parser::parse_program()
{
    parse_scope();
}

void Parser::parse_scope()
{
    expect(LBRACE);
    insert_end();
    parse_scope_list();
    error3 = compare_vect(allIDs, decl);
    expect(RBRACE);
    delete_last();
}

void Parser::parse_scope_list()
{
    Token t = lexer.GetToken();
    if(t.token_type == LBRACE)
    {
        lexer.UngetToken(t);
        parse_scope();
    }
    else if(t.token_type == ID || t.token_type == WHILE)
    {
        Token t2 = peek();
        if(t2.token_type == COLON || t2.token_type == COMMA)
        {
            lexer.UngetToken(t);
            parse_var_decl();
        }
        else if(t2.token_type == EQUAL || t2.token_type == LPAREN)
        {
            lexer.UngetToken(t);
            parse_stmt();
        }
        else
            syntax_error();
    }
    Token t3 = peek();
    if(t3.token_type == ID || t3.token_type == WHILE || t3.token_type == LBRACE)
        parse_scope_list();
}

void Parser::parse_var_decl()
{
    parse_id_list(); // vector of ids
    expect(COLON);
    TokenType type = parse_type_name(); // type of id
    for (int i = 0; i < t1.size(); i++)
        curr->data[t1[i]] = type;
    t1.clear();
    expect(SEMICOLON);
}

void Parser::parse_id_list()
{
    Token id = expect(ID);
    if(!if_exist(curr->vect, id.lexeme)) // not found
    {
        curr->vect.push_back(id.lexeme);
        allIDs.push_back(id.lexeme);
        t1.push_back(id.lexeme);
    }
    else
        error1.push_back(id.lexeme);
    Token t = peek();
    if (t.token_type == COMMA)
    {
        expect(COMMA);
        parse_id_list();
    }
}

TokenType Parser::parse_type_name()
{
    Token t = peek();
    if(t.token_type == REAL)
        return expect(REAL).token_type;
    else if(t.token_type == INT)
        return expect(INT).token_type;
    else if(t.token_type == BOOLEAN)
        return expect(BOOLEAN).token_type;
    else if(t.token_type == STRING)
        return expect(STRING).token_type;
    else
        syntax_error();
}

void Parser::parse_stmt_list()
{
    parse_stmt();
    Token t = peek();
    if(t.token_type == ID || t.token_type == WHILE)
        parse_stmt_list();
}

void Parser::parse_stmt()
{
    Token t = peek();
    if(t.token_type == ID)
        parse_assign_stmt();
    else if(t.token_type == WHILE)
        parse_while_stmt(t.line_no);
    else
        syntax_error();
}

void Parser::parse_assign_stmt()
{
    Token t = expect(ID);
    if(!lookup(curr, t.lexeme))
        error2.push_back(t.lexeme);
    if(!if_exist(decl, t.lexeme))
        decl.push_back(t.lexeme);
    expect(EQUAL);
    TokenType lhs = find_in_map(t.lexeme);
    TokenType rhs = parse_expr(t.line_no);
    if((lhs == BOOLEAN && rhs != BOOLEAN) || (lhs == STRING && rhs != STRING))
        c1type.push_back(t.line_no);
    else if(lhs == INT  && (rhs != INT && rhs != BOOLEAN))
        c2type.push_back(t.line_no);
    else if(lhs == REAL && (rhs != INT && rhs != REAL))
        c3type.push_back(t.line_no);
    expect(SEMICOLON);
}

void Parser::parse_while_stmt(int lineNo)
{
    expect(WHILE);
    expect(LPAREN);
    TokenType condition = parse_condition(lineNo);
    if(condition != BOOLEAN)
        c10type.push_back(lineNo);
    expect(RPAREN);
    Token t = peek();
    if(t.token_type  == ID || t.token_type == WHILE)
        parse_stmt();
    else if(t.token_type == LBRACE)
    {
        expect(LBRACE);
        parse_stmt_list();
        expect(RBRACE);
    }
    else
        syntax_error();
}

TokenType Parser::parse_expr(int lineNo)
{
    Token t = peek();
    if(t.token_type == ID || t.token_type == NUM || t.token_type == REALNUM || t.token_type == STRING_CONSTANT || t.token_type == TRUE || t.token_type == FALSE)
        return parse_primary();
    else if(t.token_type == PLUS || t.token_type == MINUS || t.token_type == MULT || t.token_type == DIV)
        return parse_arithmetic_expr(lineNo);
    else if(t.token_type == AND || t.token_type == OR || t.token_type == XOR || t.token_type == GREATER || t.token_type == GTEQ || t.token_type == LESS || t.token_type == NOTEQUAL || t.token_type == LTEQ || t.token_type == NOT)
        return parse_boolean_expr(lineNo);
    else
        syntax_error();
}

TokenType Parser::parse_arithmetic_expr(int lineNo)
{
    Token tmp;
    Token t = peek();
    if(t.token_type == PLUS || t.token_type == MINUS || t.token_type == MULT || t.token_type == DIV)
    {
        parse_arithmetic_operator();
        TokenType type1 = parse_arithmetic_expr(lineNo);
        TokenType type2 = parse_arithmetic_expr(lineNo);

        if((type1 != REAL && type1 != INT && type1 != STRING) || (type2 != REAL && type2 != INT && type2 != STRING))
            c4type.push_back(lineNo);
        if(type1 == STRING && type2 != STRING)
            c7type.push_back(lineNo);
        if(type2 == STRING && t.token_type == MULT && type1 != STRING && type1 != INT)
            c8type.push_back(lineNo);
        if(type2 == STRING && t.token_type != MULT && type1 != STRING)
            c8type2.push_back(lineNo);
        if(c4type.empty() && c7type.empty() && c8type.empty() && c8type2.empty())
        {
            if (type1 == REAL || type2 == REAL)
                return REAL;
            else if (type1 == STRING || type2 == STRING)
                return STRING;
        }
        if(t.token_type == PLUS || t.token_type == MINUS || t.token_type == MULT && type1 == INT && type2 == INT)
            return INT;

        if(t.token_type == DIV && type1 == INT && type2 == INT)
            return REAL;
    }
    else
        return parse_arithmetic_primary();
}

TokenType Parser::parse_boolean_expr(int lineNo)
{
    Token tmp;
    Token t = peek();
    if(t.token_type == AND || t.token_type == OR || t.token_type == XOR)
    {
        parse_binary_boolean_operator();
        TokenType type1 = parse_boolean_expr(lineNo);
        TokenType type2 = parse_boolean_expr(lineNo);

        if(type1 != BOOLEAN && type2 != BOOLEAN)
            c5type.push_back(lineNo);
        else
            return BOOLEAN;

    }
    else if(t.token_type == GREATER || t.token_type == GTEQ || t.token_type == LESS || t.token_type == NOTEQUAL || t.token_type == LTEQ)
    {
        parse_relational_operator();
        TokenType type1 = parse_expr(lineNo);
        TokenType type2 = parse_expr(lineNo);

        if((type1 != INT && type1 != REAL) && (type2 != INT && type2 != REAL))
        {
            if((type1 != STRING || type2 != STRING) && (type1 != BOOLEAN || type2 != BOOLEAN))
                c6type.push_back(lineNo);
        }
        if((type1 == INT || type1 == REAL) || (type2 == INT || type2 == REAL))
        {
            if((type1 == INT && type2 != INT) || (type2 == INT && type1 != INT))
                c9type.push_back(lineNo);
            else if((type1 == REAL && type2 != REAL) || (type2== REAL && type1 != REAL))
                c9type.push_back(lineNo);
        }
        else
            return BOOLEAN;
    }
    else if(t.token_type == NOT)
    {
        expect(NOT);
        TokenType type = parse_boolean_expr(lineNo);
        if(type != BOOLEAN)
            c11type.push_back(lineNo);
    }
    else if(t.token_type == ID || t.token_type == TRUE || t.token_type == FALSE)
        return parse_boolean_primary();
    else
        syntax_error();
}

void Parser::parse_arithmetic_operator()
{
    Token t = peek();
    if(t.token_type == PLUS)
        expect(PLUS);
    else if(t.token_type == MINUS)
        expect(MINUS);
    else if(t.token_type == MULT)
        expect(MULT);
    else if(t.token_type == DIV)
        expect(DIV);
    else
        syntax_error();
}

void Parser::parse_binary_boolean_operator()
{
    Token t = peek();
    if(t.token_type == AND)
        expect(AND);
    else if(t.token_type == OR)
        expect(OR);
    else if(t.token_type == XOR)
        expect(XOR);
    else
        syntax_error();
}

void Parser::parse_relational_operator()
{
    Token t = peek();
    if(t.token_type == GREATER)
        expect(GREATER);
    else if(t.token_type == GTEQ)
        expect(GTEQ);
    else if(t.token_type == LESS)
        expect(LESS);
    else if(t.token_type == NOTEQUAL)
        expect(NOTEQUAL);
    else if(t.token_type == LTEQ)
        expect(LTEQ);
    else
        syntax_error();
}

TokenType Parser::parse_primary()
{
    Token t = peek();
    if(t.token_type == ID)
    {
        Token id = expect(ID);
        if(!lookup(curr, id.lexeme))
            error2.push_back(id.lexeme);
        if(!if_exist(decl, t.lexeme))
            decl.push_back(t.lexeme);
        return find_in_map(id.lexeme);
    }
    else if(t.token_type == NUM)
    {
        expect(NUM);
        return INT;
    }
    else if(t.token_type == REALNUM)
    {
        expect(REALNUM);
        return REAL;
    }
    else if(t.token_type == STRING_CONSTANT)
    {
        expect(STRING_CONSTANT);
        return  STRING;
    }
    else if(t.token_type == TRUE || t.token_type == FALSE)
    {
        parse_bool_const();
        return BOOLEAN;
    }
    else
        syntax_error();
}

TokenType Parser::parse_arithmetic_primary()
{
    Token t = peek();
    if(t.token_type == ID)
    {
        Token id = expect(ID);
        if(!lookup(curr, id.lexeme))
            error2.push_back(id.lexeme);
        if(!if_exist(decl, t.lexeme))
            decl.push_back(t.lexeme);
        return find_in_map(id.lexeme);
    }
    else if(t.token_type == NUM)
    {
        expect(NUM);
        return INT;
    }
    else if(t.token_type == REALNUM)
    {
        expect(REALNUM);
        return REAL;
    }
    else if(t.token_type == STRING_CONSTANT)
    {
        expect(STRING_CONSTANT);
        return STRING;
    }
    else
        syntax_error();
}

TokenType Parser::parse_boolean_primary()
{
    Token t = peek();
    if(t.token_type == ID)
    {
        Token id = expect(ID);
        if(!lookup(curr, id.lexeme))
            error2.push_back(id.lexeme);
        if(!if_exist(decl, t.lexeme))
            decl.push_back(t.lexeme);
        return find_in_map(id.lexeme);
    }
    else if(t.token_type == TRUE || t.token_type == FALSE)
    {
        parse_bool_const();
        return BOOLEAN;
    }
    else
        syntax_error();
}

TokenType Parser::parse_bool_const()
{
    Token t = peek();
    if(t.token_type == TRUE)
        return expect(TRUE).token_type;
    else if(t.token_type == FALSE)
        return expect(FALSE).token_type;
    else
        syntax_error();
}

TokenType Parser::parse_condition(int lineNo)
{
    return parse_boolean_expr(lineNo);
}

int main()
{
    LexicalAnalyzer lexer;
    Token token;
    Parser parser;
    parser.parse_program();
    parser.print_error_msg(1.1);
    parser.print_error_msg(1.2);
    parser.print_error_msg(1.3);

    if(parser.error1.empty() && parser.error2.empty() && parser.error3.empty())
    {
        // type mismatch error
        if(!parser.c4type.empty() || !parser.c5type.empty() || !parser.c6type.empty() || !parser.c7type.empty() || !parser.c8type.empty() || !parser.c8type2.empty() || !parser.c9type.empty() || !parser.c11type.empty())
        {
            parser.print_type_msg("C4");
            parser.print_type_msg("C5");
            parser.print_type_msg("C6");
            parser.print_type_msg("C7");
            parser.print_type_msg("C8");
            parser.print_type_msg("C8'");
            parser.print_type_msg("C9");
            parser.print_type_msg("C11");
        }
        else
        {
            parser.print_type_msg("C1");
            parser.print_type_msg("C2");
            parser.print_type_msg("C3");
            parser.print_type_msg("C10");
        }
    }
    else if(parser.c1type.empty())
    {
        // output unitialized error msg, sec 4.3
    }
    else
    {
        // working output, sec 4.4
    }

}