#include "Days.h"
#include "AdventUtils.h"
#include "Point2D.h"

#include <vector>
#include <map>

// Using Doubled Hex Offset: https://www.redblobgames.com/grids/hexagons/
void UpdateLocation(Point2D& Location, const string& dir)
{
	if(dir == "n")
	{
		Location.y -= 2;
	}
	else if(dir == "s")
	{
		Location.y += 2;
	}
	else if(dir[1] == 'e')
	{
		++Location.x;
		if(dir[0] == 'n')
		{
			--Location.y;
		}
		else if(dir[0] == 's')
		{
			++Location.y;
		}
	}
	else if(dir[1] == 'w')
	{
		--Location.x;
		if(dir[0] == 'n')
		{
			--Location.y;
		}
		else if(dir[0] == 's')
		{
			++Location.y;
		}
	}
}

int GetHexDist(const Point2D& Location)
{
	int x = abs(Location.x);
	int y = abs(Location.y);
	return x + max(0, (y - x)/2);
}

template <>
void Run<Day11>(Part part, istream& is, ostream& os)
{
	string arg;
	Point2D Location = Point2D();
	int distMax = 0;

	while(getline(is, arg))
	{
		// Split into vector of directions
		const vector<string> dirs = split(arg, ',');
		for(const string& dir : dirs)
		{
			UpdateLocation(Location, dir);
			distMax = max(distMax, GetHexDist(Location));
		}
	}

	if(part == Part01)
	{
		os << "Hex Path Distance: " << GetHexDist(Location);
	}
	else if(part == Part02)
	{
		os << "Hex Path Max Distance: " << distMax;
	}
}