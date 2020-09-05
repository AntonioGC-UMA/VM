#include "Parser.h"






Node* Parser::new_node(node_type type)
{
	nodes.emplace_back();
	nodes.back().tag = type;
	nodes.back().token = &tokens->at(idx);
	return &nodes.back();
}

Node* Parser::parse_program(vector<Token>* source)
{
	tokens = source;

	Node* root = new_node(node_type::BLOCK);

	while (tokens->at(idx).tag != token_type::END_OF_FILE)
	{
		root->children.push_back(parse_statement());
	}

	return root;
}

Node* Parser::parse_statement()
{
	Node* node = nullptr;

	switch (tokens->at(idx).tag)
	{
	case token_type::PRINT : 
	{
		node = new_node(node_type::PRINT);
		idx++;
		node->children.push_back(parse_expresion());
	} break;
	case token_type::IDENTIFIER:
	{
		node = new_node(node_type::ASSIGMENT);
		idx += 2;
		node->children.push_back(parse_expresion());
	} break;
	default:
		break;
	}

	return node;
}

Node* Parser::parse_expresion()
{
	Node* node = nullptr;

	switch (tokens->at(idx).tag)
	{
	case token_type::IDENTIFIER:
	{
		node = new_node(node_type::VARIABLE);
		idx++;
	} break;
	case token_type::INT:
	case token_type::FLOAT:
	case token_type::STRING:
	{
		node = new_node(node_type::LITERAL);
		idx++;
	} break;
	default:
		break;
	}

	return node;
}
