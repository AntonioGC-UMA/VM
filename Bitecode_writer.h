#pragma once

#include "Data.h"

#include <unordered_map>

struct Bitecode_writer
{
	vector<int> instructions;

	unordered_map<string, int> variables;

	int counter = 0;

	void visit(Node* node);
};

