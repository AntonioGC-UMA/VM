#pragma once

#include <deque>

#include "Data.h"




struct Parser
{
	vector<Token>* tokens;

	deque<Node> nodes;

	size_t idx = 0;

	Node* new_node(node_type);

	Node* parse_program(vector<Token>* source);

	Node* parse_statement();
	Node* parse_expresion();
};