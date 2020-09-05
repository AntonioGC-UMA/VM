#include "Tokenizer.h"

#include <unordered_map>


unordered_map<string, token_type> keyword_map = { {"if", token_type::IF}, {"else", token_type::ELSE},  {"print", token_type::PRINT},
		{"then", token_type::THEN}, {"while", token_type::WHILE}, {"do", token_type::DO}, {"not", token_type::NOT},
		{"and", token_type::AND} , {"or", token_type::OR}, {"true", token_type::TRUE},  {"false", token_type::FALSE} };



bool is_number(char c)
{
	return c >= '0' && c <= '9';
}

bool is_leter(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}


bool is_identifier(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || is_number(c) || c == '_';
}

bool is_end(char c)
{
	return c == '\0';
}

void Tokenizer::new_token(token_type tag)
{
	switch (tag)
	{
	case token_type::IDENTIFIER:
	{
		auto it = keyword_map.find(string(start, current - start));
		if (it != keyword_map.end()) tag = it->second;
		tokens.push_back({ tag, line, colum, (int)(current - start),  0.0f, start });
		break;
	}
	case token_type::INT:
		tokens.push_back({ tag, line, colum, std::stoi({start, (size_t)(current - start)}), 0.0f, nullptr });
		break;
	case token_type::FLOAT:
		tokens.push_back({ tag, line, colum, 0,  std::stof({start, (size_t)(current - start)}), nullptr });
		break;
	case token_type::STRING:
		tokens.push_back({ tag, line, colum, (int)(current - start - 1),  0.0f, start + 1 });
		break;
	default:
		tokens.push_back({ tag, line, colum, 0, 0.0f, nullptr });
	}
}

void Tokenizer::check_eq(token_type tag)
{
	current++;

	if (is_end(*current) || *current != '=')
	{
		new_token(tag);
		current--;
		return;
	}

	switch (tag)
	{
	case token_type::MORE: new_token(token_type::MORE_EQ); break;
	case token_type::LESS: new_token(token_type::LESS_EQ); break;
	case token_type::EQ_EQ: new_token(token_type::EQ_EQ); break;
	}
}

void Tokenizer::tokenize()
{
	while (!is_end(*current))
	{		
		start = current;

		switch (*current)
		{
		case ' ': break;
		case '\t': break;
		case '\n': break;
		case '+': new_token(token_type::PLUS); break;
		case '-': new_token(token_type::MINUS); break;
		case '*': new_token(token_type::MULT); break;
		case '/': new_token(token_type::DIV); break;
		case '=': check_eq(token_type::EQ); break;
		case '<': check_eq(token_type::LESS); break;
		case '>': check_eq(token_type::MORE); break;
		case '{': new_token(token_type::OPEN_B); break;
		case '}': new_token(token_type::CLOSE_B); break;
		case '(': new_token(token_type::OPEN_P); break;
		case ')': new_token(token_type::CLOSE_P); break;
		case ',': new_token(token_type::COMMA); break;
		case '"': {
			do current++; while (*current != '"' && !is_end(*current));
			new_token(token_type::STRING);
		} break;
		default:
			if (is_number(*current))
			{
				do current++; while (is_number(*current) && !is_end(*current));

				if (*current != '.')
				{
					new_token(token_type::INT);
					continue;
				}

				do current++; while (is_number(*current) && !is_end(*current));

				new_token(token_type::FLOAT);
				continue;
			}
			else if (is_leter(*current))
			{
				do current++; while (is_identifier(*current) && !is_end(*current));

				new_token(token_type::IDENTIFIER);
				continue;
			}
			else
			{
				throw string("Error, simbol is not valid:", *current);
			}
			break;
		}
		current++;
	}

	new_token(token_type::END_OF_FILE);
}
