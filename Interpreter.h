#pragma once

#include "Data.h"

#include <unordered_map>

struct Interpreter
{
	unordered_map<string, int> variables;

	int interpret(Node* node);
};

