#include "Interpreter.h"

int Interpreter::interpret(Node* node)
{
	int res = 0;
	switch (node->tag)
	{
	case node_type::BLOCK:
	{
		for (Node* child : node->children)
		{
			res = interpret(child);
		}
	}break;
	case node_type::ASSIGMENT:
	{
		res = interpret(node->children.front());
		variables[string(node->token->c, node->token->i)] =  res;
	}break;
	case node_type::PRINT:
	{
		res = interpret(node->children.front());
		cout << res << endl;
	}break;
	case node_type::VARIABLE:
	{
		res = variables[string(node->token->c, node->token->i)];
	}break;
	case node_type::LITERAL:
	{
		res = node->token->i;
	}break;
	default:
		res = -1;
	}
	return res;
}
