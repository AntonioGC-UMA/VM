#include "Data.h"


vector<string> token_name =
{
	"+", "-", "*", "/", ">", "<", "=", "not", ">=", "<=", "==", "and", "or", "while", "do","if",
	"then", "else", "print", "{", "}",	"(", ")", "comma", "id", "int", "float", "string", "true", "false",
	"EOF"
};

ostream& operator<<(ostream& os, const Token& t)
{
	os << token_name.at((int)t.tag);

	if (t.tag == token_type::INT) os << " " << t.i;
	else if (t.tag == token_type::FLOAT) os << " " << t.f;
	else if (t.tag == token_type::IDENTIFIER) os << " " << string(t.c, t.i);
	else if (t.tag == token_type::STRING) os << " \"" << string(t.c, t.i) << "\"";

	return os;
}

ostream& operator<<(ostream& os, const Node& n)
{	
	switch (n.tag)
	{
	case node_type::BLOCK:
	{
		os << "{ ";
		for (Node* child : n.children)
		{
			os << *child << " ";
		}
		os << " }";
	}break;	
	case node_type::ASSIGMENT:
	{
		os << *n.token << " = " << *n.children.front();
	}break;
	case node_type::PRINT:
	{
		os << *n.token << "( " << *n.children.front() << " )";
	}break;
	default:
		os << *n.token;
	}


	return os;
}