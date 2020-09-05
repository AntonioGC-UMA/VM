#include "Bitecode_writer.h"

void Bitecode_writer::visit(Node* node)
{
	switch (node->tag)
	{
	case node_type::BLOCK:
	{
		instructions.push_back((int)op_code::Begin);
		for (Node* child : node->children)
		{
			visit(child);
		}
		instructions.push_back((int)op_code::End);
	}break;
	case node_type::ASSIGMENT:
	{		
		instructions.push_back((int)op_code::Store);
		auto it = variables.find(string(node->token->c, node->token->i));
		if (it == variables.end())
		{
			instructions.push_back(counter);
			variables.emplace(string(node->token->c, node->token->i), counter++);		
		}
		else
		{
			instructions.push_back(it->second);
		}
		
		visit(node->children.front());
	}break;
	case node_type::PRINT:
	{
		instructions.push_back((int)op_code::Print);
		visit(node->children.front());
	}break;
	case node_type::VARIABLE:
	{
		instructions.push_back((int)op_code::Load);
		instructions.push_back(variables[string(node->token->c, node->token->i)]);
	}break;
	case node_type::LITERAL:
	{
		instructions.push_back(node->token->i);
	}break;
	default:
		break;
	}
}
