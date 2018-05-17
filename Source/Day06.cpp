#include "Days.h"
#include "AdventUtils.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>

template <>
void Run<Day06>(Part part, istream& is, ostream& os)
{
	vector<int> memoryBanks;
	vector<string> memoryPatterns;
	string arg;
	while(getline(is, arg))
	{
		// Parse each memory bank into the vector
		istringstream iss(arg);
		copy(istream_iterator<int>(iss), istream_iterator<int>(), back_inserter(memoryBanks));
	}

	string memoryPattern = "";
	string memoryPatternFirstRepeat = "";
	size_t cycleCount = 0;
	size_t repeatCount = 0;
	while(true)
	{
		// Construct the current memory pattern
		memoryPattern = "";
		for(const int& bank : memoryBanks)
		{
			memoryPattern.push_back(IntToChar(bank));
		}

		if(find(memoryPatterns.begin(), memoryPatterns.end(), memoryPattern) != memoryPatterns.end())
		{
			// Mark the first loop cycle when found
			if(memoryPatternFirstRepeat == "")
			{
				cycleCount = memoryPatterns.size();
				memoryPatternFirstRepeat = memoryPattern;
			}
			// Mark the first repeat cycle and exit loop
			else if(memoryPatternFirstRepeat == memoryPattern)
			{
				repeatCount = memoryPatterns.size() - cycleCount;
				break;
			}
		}
		memoryPatterns.push_back(memoryPattern);

		// Find the largest bank and deplete it
		int largestBankSize = *max_element(memoryBanks.begin(), memoryBanks.end());
		int bankIdx = static_cast<int>(find(memoryBanks.begin(), memoryBanks.end(), largestBankSize) - memoryBanks.begin());
		memoryBanks[bankIdx] = 0;
		++bankIdx;

		// Update memory banks
		while(largestBankSize > 0)
		{
			if(bankIdx >= memoryBanks.size())
			{
				bankIdx = 0;
			}
			++memoryBanks[bankIdx];
			++bankIdx;
			--largestBankSize;
		}
	}

	if(part == Part01)
	{
		std::cout << "cycleCount: " << cycleCount;
	}
	else if(part == Part02)
	{
		std::cout << "repeatCount: " << repeatCount;
	}
}