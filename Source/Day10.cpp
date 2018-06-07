#include "Days.h"
#include "AdventMath.h"
#include "AdventUtils.h"

#include <vector>

static const int LIST_LENGTH = 256;

int GetIdxWrap(int idx)
{
	while(idx >= LIST_LENGTH)
	{
		idx -= LIST_LENGTH;
	}
	return idx;
}

template <>
void Run<Day10>(Part part, istream& is, ostream& os)
{
	vector<int> lengths;
	string arg;
	int numRounds = 0;
	if(part == Part01)
	{
		while(getline(is, arg))
		{
			// Split into length vector
			vector<string> lengthsStr = split(arg, ',');
			for(const string& s : lengthsStr)
			{
				lengths.push_back(atoi(s.c_str()));
			}
		}

		numRounds = 1;
	}
	else if(part == Part02)
	{
		while(getline(is, arg))
		{
			// Push back ascii value of each character
			for(const char c : arg)
			{
				lengths.push_back(int(c));
			}
		}

		// Add these because we have to... ?
		lengths.push_back(17);
		lengths.push_back(31); 
		lengths.push_back(73); 
		lengths.push_back(47); 
		lengths.push_back(23);

		numRounds = 64;
	}

	int numList[LIST_LENGTH];
	for(int i = 0; i < LIST_LENGTH; ++i)
	{
		numList[i] = i;
	}

	int cursorIdx = 0;
	int skipSize = 0;
	for(int i = 0; i < numRounds; ++i)
	{
		for(int length : lengths)
		{
			// Perform sub section reverse
			for(int j = 0; j < length / 2; ++j)
			{
				int idx1 = GetIdxWrap(cursorIdx + j);
				int idx2 = GetIdxWrap(cursorIdx + (length - (j + 1)));

				int tmp = numList[idx1];
				numList[idx1] = numList[idx2];
				numList[idx2] = tmp;
			}
			cursorIdx = GetIdxWrap(cursorIdx + length + skipSize);
			++skipSize;
		}
	}

	if(part == Part01)
	{
		os << "Product of first two numbers: " << numList[0] * numList[1];
	}
	else if(part == Part02)
	{
		int denseHashArray[16];
		for(int i = 0; i < 16; ++i)
		{
			denseHashArray[i] = numList[i * 16];
			for(int j = 1; j < 16; ++j)
			{
				denseHashArray[i] ^= numList[i*16 + j];
			}
		}
		
		os << "Hexadecimal Hash: ";
		for(const int denseHashNum : denseHashArray)
		{
			string hashStr;
			std::stringstream ss;
			ss << std::hex << denseHashNum;
			ss >> hashStr;
			
			// Prefix hex with 0 if necessary
			if(hashStr.length() < 2)
			{
				hashStr.insert(hashStr.begin(), '0');
			}
			os << std::hex << hashStr;
		}
	}
}