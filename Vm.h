#pragma once

#include "Data.h"

#include <unordered_map>
#include <deque>

struct Vm
{
	vector<int> instructions;

	vector<int> variables;

	vector<int> memoria;

	size_t idx = 0;

	int pop();
	void execute();
};

