#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <iostream>
#include <map>
#include "grammar.h"
#include "compiler.h"

using namespace std;

struct InstructionNode* parse_generate_intermediate_representation()
{
    grammar obj;
    return obj.parse_program();
}

void grammar::syntax_error()
{
    cout << "SYNTAX ERROR !!!\n";
    exit(1);
}

Token grammar::expect(TokenType expected_type)
{
    Token t = lexer.GetToken();
    if(t.token_type != expected_type)
        syntax_error();
    return t;
}

Token grammar::peek()
{
    Token t = lexer.GetToken();
    lexer.UngetToken(t);
    return t;
}

int grammar::location(string key)
{
    return address_map.find(key)->second;
}

bool grammar::is_in_memory(string key)
{
    if(address_map.count(key) > 0)
        return true;
    else
        return false;
}
// Grammar rules

struct InstructionNode* grammar::parse_program()
{
    struct InstructionNode* i = new InstructionNode;
    parse_var_section();
    i = parse_body();
    parse_inputs();

    return i;
}

void grammar::parse_var_section()
{
    parse_id_list();
    expect(SEMICOLON);
}

void grammar::parse_id_list()
{
    Token id = expect(ID);
    mem[next_available] = 0;
    address_map[id.lexeme] = next_available; // map of string to index 
    next_available++;
    
    Token t = peek();
    if(t.token_type == COMMA)
    {
        expect(COMMA);
        parse_id_list();
    }
}

struct InstructionNode* grammar::parse_body()
{
    struct InstructionNode* i = new InstructionNode; 
    expect(LBRACE);
    i = parse_stmt_list();
    expect(RBRACE);

    return i;
}

struct InstructionNode* grammar::parse_stmt_list()
{
    struct InstructionNode* i = new InstructionNode;
    struct InstructionNode* temp;
    i = parse_stmt();
    temp = i;
    Token t = peek();

    if(t.token_type == ID || t.token_type == WHILE || t.token_type == IF || t.token_type == SWITCH || t.token_type == FOR || t.token_type == OUTPUT || t.token_type == INPUT)
    {
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = parse_stmt_list();
    }
    return i;
}

struct InstructionNode* grammar::parse_stmt()
{
    Token t = peek();

    if(t.token_type == ID)
        return parse_assign_stmt();
    else if(t.token_type == WHILE)
        return parse_while_stmt();
    else if(t.token_type == IF)
        return parse_if_stmt();
    else if(t.token_type == SWITCH)
        return parse_switch_stmt();
    else if(t.token_type == FOR)
        return parse_for_stmt();
    else if(t.token_type == OUTPUT)
        return parse_output_stmt();
    else
        return parse_input_stmt();

}

struct InstructionNode* grammar::parse_assign_stmt() 
{
    Token id = expect(ID);
    struct InstructionNode* i = new InstructionNode;
    if(is_in_memory(id.lexeme) == false) // not found, so add into memory
    {
        mem[next_available] = 0;
        address_map[id.lexeme] = next_available;
        next_available++;
    }
        
    expect(EQUAL);
    Token t = lexer.GetToken(); // consumes either ID or NUM
    Token t2 = peek();

    if(t2.token_type == PLUS || t2.token_type == MINUS || t2.token_type == MULT || t2.token_type == DIV) //expr
    {
        lexer.UngetToken(t);
        i = parse_expr();
        i->assign_inst.left_hand_side_index = location(id.lexeme);
        expect(SEMICOLON);
    }
    else //primary 
    {  
        lexer.UngetToken(t);
        string term = parse_primary();
        i->type = ASSIGN;
        i->assign_inst.left_hand_side_index = location(id.lexeme);
        i->assign_inst.op = OPERATOR_NONE;
        i->assign_inst.operand1_index = location(term);
        i->next = NULL;
        expect(SEMICOLON);
    }
        return i;
}

struct InstructionNode* grammar::parse_expr()
{  
    struct InstructionNode* temp = new InstructionNode;
    string first = parse_primary();
    Token t = parse_op();
    string last = parse_primary();

    temp->type = ASSIGN;
    if(t.token_type == PLUS)
        temp->assign_inst.op = OPERATOR_PLUS;
    else if(t.token_type == MINUS)
        temp->assign_inst.op = OPERATOR_MINUS;
    else if(t.token_type == MULT)
        temp->assign_inst.op = OPERATOR_MULT;
    else 
        temp->assign_inst.op = OPERATOR_DIV;

    temp->assign_inst.operand1_index = location(first);
    temp->assign_inst.operand2_index = location(last);
    temp->next = NULL;

    return temp;
}

string grammar::parse_primary()
{
    Token id;
    Token t = peek();

    if(t.token_type == ID)
    {
        id = expect(ID);
        
        if(is_in_memory(id.lexeme) == false)
        {
            mem[next_available] = 0;
            address_map[id.lexeme] = next_available;
            next_available++;
        }
    }
    else
    {
        id = expect(NUM);
        int num = stoi(id.lexeme);
    
        mem[next_available] = num;
        address_map[id.lexeme] = next_available;
        next_available++;
    }
        return id.lexeme;
}

Token grammar::parse_op()
{
    Token t = peek();

    if(t.token_type == PLUS)
        expect(PLUS);
    else if(t.token_type == MINUS)
        expect(MINUS);
    else if(t.token_type == MULT)
        expect(MULT);
    else
        expect(DIV);

        return t;
}

struct InstructionNode* grammar::parse_output_stmt()
{
    struct InstructionNode *i = new InstructionNode();
    expect(OUTPUT);
    i->type = OUT;
    Token id = expect(ID);
    
    i->output_inst.var_index = location(id.lexeme);
    i->next = NULL;
    expect(SEMICOLON);
    return i;
}

struct InstructionNode* grammar::parse_input_stmt()
{
    struct InstructionNode *i = new InstructionNode();
    expect(INPUT);
    i->type = IN;
    Token id = expect(ID);

    if(is_in_memory(id.lexeme) == false)
    {
        mem[next_available] = 0;
        address_map[id.lexeme] = next_available;
        next_available++;
    }

    i->input_inst.var_index = location(id.lexeme);
    i->next = NULL;
    expect(SEMICOLON);
    return i;
}

struct InstructionNode* grammar::parse_while_stmt()
{
    struct InstructionNode* i = new InstructionNode;
    struct InstructionNode* i2 = new InstructionNode;
    struct InstructionNode* i3 = new InstructionNode;
    struct InstructionNode* temp;

    expect(WHILE);
    i = parse_condition();
    i->next = parse_body();
    temp = i->next;
    i->cjmp_inst.target = i2;

    while(temp->next != NULL)
        temp = temp->next;
    
    temp->next = i3;

    i2->type = NOOP;
    i2->next = NULL;

    i3->type = JMP;
    i3->jmp_inst.target = i;
    i3->next = i2;

    return i;
}

struct InstructionNode* grammar::parse_if_stmt()
{
    struct InstructionNode* i = new InstructionNode;
    struct InstructionNode* i2 = new InstructionNode;
    struct InstructionNode* temp;

    expect(IF);
    i = parse_condition();
    i->next = parse_body(); // if true
    temp = i->next;
    i->cjmp_inst.target = i2; // else false

     while(temp->next != NULL) // set last statement in body to i
         temp = temp->next;

     temp->next = i2; // point last statement in body next to noop
    
    i2->type = NOOP;
    i2->next = NULL;

    return i;
}

struct InstructionNode* grammar::parse_condition()
{
    struct InstructionNode* temp = new InstructionNode;
    string first = parse_primary();
    Token condition = parse_relop();
    string last = parse_primary();

    temp->type = CJMP;
    if(condition.token_type == GREATER)
        temp->cjmp_inst.condition_op = CONDITION_GREATER;
    else if(condition.token_type == LESS)
        temp->cjmp_inst.condition_op = CONDITION_LESS;
    else
        temp->cjmp_inst.condition_op = CONDITION_NOTEQUAL;
    temp->cjmp_inst.operand1_index = location(first);
    temp->cjmp_inst.operand2_index = location(last);

    return temp;
}

Token grammar::parse_relop()
{
    Token t = peek();

    if(t.token_type == GREATER)
        expect(GREATER);
    else if(t.token_type == LESS)
        expect(LESS);
    else
        expect(NOTEQUAL);

        return t;
}

struct InstructionNode* grammar::parse_switch_stmt()
{
    struct InstructionNode* i = new InstructionNode;
    struct InstructionNode* i2 = new InstructionNode;
    struct InstructionNode* temp;
    
    i2->type = NOOP;
    i2->next = NULL;

    expect(SWITCH);
    Token id = expect(ID);
    expect(LBRACE);
    i = parse_case_list(id, i2);
    temp = i;
    Token t = peek();

    if(t.token_type == RBRACE)
    {   
	 expect(RBRACE);
	 
     while(temp->next != NULL)
        temp = temp->next;
	temp->next = i2;
    }
    else
    {
       while(temp->next != NULL)
            temp = temp->next; // last case in list

        temp->next = parse_default_case(i2);
        expect(RBRACE);
    }
    //i2->next = NULL;
    return i;
}

struct InstructionNode* grammar::parse_for_stmt()
{
    struct InstructionNode* i = new InstructionNode;
    struct InstructionNode* i2 = new InstructionNode;
    struct InstructionNode* i3 = new InstructionNode;
    struct InstructionNode* i4 = new InstructionNode;
    struct InstructionNode* i5 = new InstructionNode;
    struct InstructionNode* i6 = new InstructionNode;
    struct InstructionNode* temp;

    expect(FOR);
    expect(LPAREN);
    i = parse_assign_stmt();
    i2 = parse_condition();
    i->next = i2;
    i2->cjmp_inst.target = i4;
    expect(SEMICOLON);
    i6 = parse_assign_stmt();
    i6->next = i5;
    expect(RPAREN);
    i3 = parse_body();
    i2->next = i3;
    temp = i3;
    
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = i6;

    i4->type = NOOP;
    i4->next = NULL;

    i5->type = JMP;
    i5->jmp_inst.target = i2;
    i5->next = i4;

    return i;
}

struct InstructionNode* grammar::parse_case_list(Token id, struct InstructionNode* i2)
{
    struct InstructionNode* i = new InstructionNode;
    struct InstructionNode* temp;

    i = parse_case(id, i2);
	i->next = NULL;
    temp = i;
    Token t = peek();

    if(t.token_type == CASE)
        temp->next = parse_case_list(id ,i2);  // temp->next is NOOP node, so temp->next->next

    return i;
}

struct InstructionNode* grammar::parse_case(Token id, struct InstructionNode* i2)
{
    struct InstructionNode* i = new InstructionNode;
    struct InstructionNode* temp;

    expect(CASE);
    Token num = expect(NUM);
    if(is_in_memory(num.lexeme) == false)
    {
        int num_ = stoi(num.lexeme);
        mem[next_available] = num_;
        address_map[num.lexeme] = next_available;
        next_available++;
    }
    expect(COLON);
    i->type = CJMP;
    i->cjmp_inst.condition_op = CONDITION_NOTEQUAL;
    i->cjmp_inst.operand1_index = location(id.lexeme);
    i->cjmp_inst.operand2_index = location(num.lexeme);
    
    i->cjmp_inst.target = parse_body(); 
    temp = i->cjmp_inst.target;

   while(temp->next != NULL)
       temp = temp->next;
    
    temp->next = i2;
    i->next = NULL;

    return i;
}

struct InstructionNode* grammar::parse_default_case(struct InstructionNode* i2)
{   
    struct InstructionNode* i = new InstructionNode;
    struct InstructionNode* temp;

    expect(DEFAULT);
    expect(COLON);
    i = parse_body();
    temp = i;

     while(temp->next != NULL)
         temp = temp->next;
     temp->next = i2;

    return i;
}

void grammar::parse_inputs()
{
    parse_num_list();
}

void grammar::parse_num_list()
{ 
    Token num = expect(NUM);
    inputs.push_back(stoi(num.lexeme));

    Token t = peek();
    if(t.token_type == NUM)
        parse_num_list();
}