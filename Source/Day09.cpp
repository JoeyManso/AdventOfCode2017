#include "Days.h"

#include <stack>
template <>
void Run<Day09>(Part part, istream& is, ostream& os)
{
	size_t GroupCount = 0;
	size_t GarbageCharacters = 0;

	string arg;
	while(getline(is, arg))
	{
		stack<char> GroupStack;
		
		bool bInGarbage = false;
		for(int i = 0; i<arg.length(); ++i)
		{
			const char c = arg[i];

			if(c == '!')
			{
				++i;
			}
			else if(bInGarbage)
			{
				switch(c)
				{
					case '>':
						bInGarbage = false;
						break;
					default:
						++GarbageCharacters;
						break;
				}
			}
			else
			{
				switch(c)
				{
					case '{':
						GroupStack.push(c);
						break;
					case '}':
						GroupCount += GroupStack.size();
						GroupStack.pop();
						break;
					case '<':
						bInGarbage = true;
						break;
				}
			}
		}
	}

	if(part == Part01)
	{
		cout << "Group Count: " << GroupCount;
	}
	else if(part == Part02)
	{
		cout << "Garbage Characters: " << GarbageCharacters;
	}
}