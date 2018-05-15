#include "Days.h"

#include <vector>

template <>
void Run<Day05>(Part part, istream& is, ostream& os)
{
	vector<int> instructions;

	string arg;
	while(getline(is, arg))
	{
		// Parse each instruction into the vector
		int i = atoi(arg.c_str());
		instructions.push_back(i);
	}

	// Loop through instructions using rules of each part
	int numSteps = -0;
	int idx = 0;
	int offset = 0;
	int jumpDelta = 0;
	while(idx >= 0 && idx < instructions.size())
	{
		offset = instructions[idx];
		if(part == Part01 || offset < 3)
		{
			jumpDelta = 1;
		}
		else
		{
			jumpDelta = -1;
		}
		instructions[idx] += jumpDelta;
		idx += offset;
		++numSteps;
	}
	cout << "numSteps: " << numSteps;
}