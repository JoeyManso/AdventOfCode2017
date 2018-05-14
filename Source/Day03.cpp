#include "Days.h"
#include <vector>
#include "AdventMath.h"

int GetAdjacentSum(const vector<vector<int>>& Grid, int i, int j)
{
	int sum = 0;
	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			unsigned int adjI = i + x;
			unsigned int adjJ = j + y;
			if(adjI < Grid.size() && adjJ < Grid.size())
			{
				sum += Grid[adjI][adjJ];
			}
		}
	}
	return Max(sum, 1);
}

vector<vector<int>> GenerateSpiralGrid(int GRID_SIZE)
{
	vector<vector<int>> Grid = vector<vector<int>>();
	Grid.resize(GRID_SIZE);
	for(auto& col : Grid)
	{
		col.resize(GRID_SIZE);
	}

	int distNext = 1;
	int dirH = 1;
	int dirV = -1;
	int distH = distNext;
	int distV = distNext;

	// Start at grid center and spiral out, filling in values
	int i = (GRID_SIZE / 2);
	int j = (GRID_SIZE / 2);
	for(int x = 1; x <= GRID_SIZE * GRID_SIZE; ++x)
	{
		Grid[i][j] = x;
		if(distH > 0)
		{
			// Move Horizontal
			j += dirH;
			--distH;
		}
		else if(distV > 0)
		{
			// Move Vertical
			i += dirV;
			--distV;

			if(distV == 0)
			{
				++distNext;
				dirH = -dirH;
				dirV = -dirV;
				distH = distNext;
				distV = distNext;
			}
		}
	}

	return Grid;
}

// Almost same as above, but assigns 'adjacent sum' as value to the grid coordinate
// Returns that value when it exceeds the given threshold
int GenerateSpiralGridAdjacentSum(int GRID_SIZE, int threshold)
{
	vector<vector<int>> Grid = vector<vector<int>>();
	Grid.resize(GRID_SIZE);
	for(auto& col : Grid)
	{
		col.resize(GRID_SIZE);
	}

	int distNext = 1;
	int dirH = 1;
	int dirV = -1;
	int distH = distNext;
	int distV = distNext;

	// Start at grid center and spiral out, filling in values
	int i = (GRID_SIZE / 2);
	int j = (GRID_SIZE / 2);
	for(int x = 1; x <= GRID_SIZE * GRID_SIZE; ++x)
	{
		Grid[i][j] = GetAdjacentSum(Grid, i, j);
		if(Grid[i][j] > threshold)
		{
			return Grid[i][j];
		}
		if(distH > 0)
		{
			// Move Horizontal
			j += dirH;
			--distH;
		}
		else if(distV > 0)
		{
			// Move Vertical
			i += dirV;
			--distV;

			if(distV == 0)
			{
				++distNext;
				dirH = -dirH;
				dirV = -dirV;
				distH = distNext;
				distV = distNext;
			}
		}
	}

	return 0;
}

pair<int, int> GetGridCoords(const vector<vector<int>>& Grid, int value)
{
	for(unsigned int i = 0; i < Grid.size(); ++i)
	{
		for(unsigned int j = 0; j < Grid.size(); ++j)
		{
			if(Grid[i][j] == value)
			{
				return make_pair(i, j);
			}
		}
	}
	return make_pair(-1, -1);
}

void PrintGrid(const vector<vector<int>>& Grid, ostream& os)
{
	for(unsigned int i = 0; i < Grid.size(); ++i)
	{
		for(unsigned int j = 0; j < Grid.size(); ++j)
		{
			int num = Grid[i][j];
			char* spacing = "   ";
			if(num >= 10)
			{
				spacing = "  ";
			}
			else if(num >= 100)
			{
				spacing = "   ";
			}

			os << Grid[i][j] << spacing;
		}
		os << endl;
	}
}

template <>
void Run<Day03>(Part part, istream& is, ostream& os)
{
	int num = stoi(string(istreambuf_iterator<char>(is), {}));
	if(num > 0)
	{
		int GridSize = static_cast<int>(ceil(sqrt(num)));
		if(GridSize % 2 == 0)
		{
			++GridSize;
		}
		
		if(part == Part01)
		{
			/* 
			 * How many steps are required to carry the data from the square identified in your puzzle input 
			 * all the way to the access port? 
			 */
			const vector<vector<int>> Grid = GenerateSpiralGrid(GridSize);
			//PrintGrid(Grid, os);

			pair<int, int> coordsAccess = GetGridCoords(Grid, 1);
			pair<int, int> coordsNum = GetGridCoords(Grid, num);

			os << "Manhattan Distance to " << num << ": " << abs(coordsNum.first - coordsAccess.first) + abs(coordsNum.second - coordsAccess.second);

		}
		else if(part == Part02)
		{
			/*
			 * As a stress test on the system, the programs here clear the grid and then store the value 1 in square 1.
			 * Then, in the same allocation order as shown above, they store the sum of the values in all adjacent squares, including diagonals.
			 */
			//PrintGrid(Grid, os);

			os << GenerateSpiralGridAdjacentSum(GridSize, num);
		}
	}
}