#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class op_code
{
	Load, Store, Print, Begin, End
};

enum class token_type
{
	PLUS, MINUS, MULT, DIV, MORE, LESS, EQ, NOT, MORE_EQ, LESS_EQ, EQ_EQ, AND, OR, WHILE, DO, IF, THEN, ELSE, PRINT,
	OPEN_B, CLOSE_B, OPEN_P, CLOSE_P, COMMA, IDENTIFIER, INT, FLOAT, STRING, TRUE, FALSE, END_OF_FILE
};

struct Token
{
	token_type tag;
	int line, colum;
	int i;
	float f;
	char* c;
};

enum class node_type
{
	BINARY, UNARY, LITERAL, DECLARATION, ASSIGMENT, IF, WHILE, BLOCK, PRINT, VARIABLE
};

struct Node
{
	node_type tag = node_type::BLOCK;
	Token* token = nullptr;
	vector<Node*> children = {};

	Node() = default;
};

ostream& operator<<(ostream& os, const Token& t);
ostream& operator<<(ostream& os, const Node& n);