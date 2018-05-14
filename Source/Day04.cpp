#include "Days.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

bool AreAnagrams(string s1, string s2)
{
	if(s1.length() == s2.length())
	{
		sort(s1.begin(), s1.end());
		sort(s2.begin(), s2.end());
		return s1 == s2;
	}
	return false;
}

template <>
void Run<Day04>(Part part, istream& is, ostream& os)
{
	int validPhrases = 0;

	string arg;
	while(getline(is, arg))
	{
		// Split phrase into vector of strings
		istringstream iss(arg);
		vector<string> tokens;
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));

		if(part == Part01)
		{
			// Sort strings
			sort(tokens.begin(), tokens.end());

			// Call unique to find first duplicate, will return tokens.end() if none
			auto dupeIt = unique(tokens.begin(), tokens.end());
			if(tokens.size() > 0 && dupeIt == tokens.end())
			{
				++validPhrases;
			}
		}
		else if(part == Part02)
		{
			bool bNoAnagrams = true;
			for(unsigned int i = 0; i < tokens.size() && bNoAnagrams; ++i)
			{
				for(unsigned int j = i + 1; j < tokens.size() && bNoAnagrams; ++j)
				{
					bNoAnagrams &= !AreAnagrams(tokens[i], tokens[j]);
				}
			}
			if(bNoAnagrams)
			{
				++validPhrases;
			}
		}
	}

	os << "Valid phrases: " << validPhrases;
}