#pragma once

#include "Data.h"


struct Tokenizer
{
	const char* source;
	vector<Token> tokens;

	char* start;
	char* current;

	int line = 1, colum = 1;

	Tokenizer(const char* source) : source(source), start((char*)source), current((char*)source) {}

	void new_token(token_type tag);
	void check_eq(token_type tag);

	void tokenize();

};

