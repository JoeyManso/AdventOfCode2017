#include "Days.h"
#include "AdventMath.h"
#include <regex>

template <>
void Run<Day02>(Part part, istream& is, ostream& os)
{
	// Regex to match digits of variable length
	const std::regex RX_DIGIT("\\d+");

	if(part == Part01)
	{
		/* 
		 * Calculate the spreadsheet's checksum. For each row, determine the difference between the largest value 
		 * and the smallest value; the checksum is the sum of all of these differences.
		 */
		int checksum = 0;
		string arg;
		while(getline(is, arg))
		{
			// Determine lower and upper of each line
			int lower = static_cast<int>(1e9);
			int upper = -static_cast<int>(1e9);
			smatch match;
			while(regex_search(arg, match, RX_DIGIT))
			{
				int num = stoi(match.str());
				lower = Min(num, lower);
				upper = Max(num, upper);
				arg = match.suffix().str();
			}
			
			// Add difference of numbers to checksum
			checksum += abs(upper - lower);
		}

		os << "Checksum: " << checksum;
	}
	else if(part == Part02)
	{
		/* 
		 * Find the only two numbers in each row where one evenly divides the other - that is, 
		 * where the result of the division operation is a whole number.They would like you to find those 
		 * numbers on each line, divide them, and add up each line's result.
		 */
		int checksum = 0;
		string arg1;
		while(getline(is, arg1))
		{
			int quotient = 0;
			smatch match;
			while(regex_search(arg1, match, RX_DIGIT) && !quotient)
			{
				int num1 = stoi(match.str());
				arg1 = match.suffix().str();

				string arg2 = arg1;
				while(regex_search(arg2, match, RX_DIGIT) && !quotient)
				{
					int num2 = stoi(match.str());
					if(num1 % num2 == 0)
					{
						quotient = num1 / num2;
					}
					else if(num2 % num1 == 0)
					{
						quotient = num2 / num1;
					}

					arg2 = match.suffix().str();
				}
			}

			// Add each resolved quotient to checksum
			checksum += quotient;
		}

		os << "Checksum: " << checksum;
	}
}