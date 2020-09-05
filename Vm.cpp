#include "Vm.h"

int Vm::pop()
{
	int res = memoria.back();
	memoria.pop_back();
	return res;
}

void Vm::execute()
{
	switch (instructions[idx])
	{
	case (int)op_code::Begin:
	{
		idx++;
		while (idx < instructions.size() && instructions[idx] != (int)op_code::End) execute();
		idx++;
	}break;
	case (int)op_code::Load:
	{
		idx++;
		memoria.push_back(variables[instructions[idx]]);
		idx++;
	}break;
	case (int)op_code::Print:
	{
		idx++;
		execute();
		cout << pop() << endl;
	}break;
	case (int)op_code::Store:
	{
		idx++;
		int location = instructions[idx];
		idx++;
		execute();
		if (location == variables.size()) variables.push_back(pop());
		else variables[location] = pop();
	}break;
	default:
		memoria.push_back(instructions[idx]);
		idx++;
	}
	
}
