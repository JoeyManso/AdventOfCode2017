#include "Days.h"
#include "AdventMath.h"

template <>
void Run<Day01>(Part part, istream& is, ostream& os)
{
    if(part == Part01)
    {
		int sum = 0;

		string arg;
		while(getline(is, arg))
		{
			if(arg.length() > 1)
			{
				for(unsigned int i = 0; i < arg.length(); ++i)
				{
					// First index should compare to last, all others should compare to previous
					size_t j = (i == 0) ? arg.length() - 1 : i - 1;
					if(arg[i] == arg[j])
					{
						sum += ToInt(arg[i]);
					}
				}
			}
		}
		os << sum;
    }
    else if(part == Part02)
    {
		int sum = 0;

		string arg;
		while(getline(is, arg, ','))
		{
			if(arg.length() > 1 && arg.length() % 2 == 0)
			{
				size_t step = (arg.length() / 2);
				for(unsigned int i = 0; i < arg.length(); ++i)
				{
					// Adjust j to wrap around
					size_t j = i + step;
					if(j >= arg.length())
					{
						j -= arg.length();
					}
					if(arg[i] == arg[j])
					{
						sum += ToInt(arg[i]);
					}
				}
			}
		}
		os << sum;
    }
}