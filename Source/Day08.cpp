#include "Days.h"

#include "AdventMath.h"

#include <iostream>
#include <map>
#include <string>
#include <regex>
#include <vector>

struct Instruction
{
	enum EInsType
	{
		I_NOP,
		I_INC,
		I_DEC
	};

	enum EOpType
	{
		O_NOP,
		O_EQUAL,
		O_NOTEQUAL,
		O_GT,
		O_GTEQUAL,
		O_LT,
		O_LTEQUAL
	};

	static EInsType GetInsType(string TypeStr)
	{
		if(TypeStr == "inc")
		{
			return I_INC;
		}
		if(TypeStr == "dec")
		{
			return I_DEC;
		}
		return I_NOP;
	}

	static EOpType GetOpType(string TypeStr)
	{
		if(TypeStr == "==")
		{
			return O_EQUAL;
		}
		if(TypeStr == "!=")
		{
			return O_NOTEQUAL;
		}
		if(TypeStr == ">")
		{
			return O_GT;
		}
		if(TypeStr == ">=")
		{
			return O_GTEQUAL;
		}
		if(TypeStr == "<")
		{
			return O_LT;
		}
		if(TypeStr == "<=")
		{
			return O_LTEQUAL;
		}
		return O_NOP;
	}


	EInsType InsType;
	EOpType OpType;
	string InsAddress;
	string OpAddress;
	int InsAmount;
	int OpAmount;

	Instruction() :
		InsType(I_NOP), OpType(O_NOP), InsAddress(""), OpAddress(""), InsAmount(0), OpAmount(0)
	{
	}

	static vector<Instruction> GetInstructions(istream& is)
	{
		const regex RX_INSTRUCTION(R"((\w+) (inc|dec) (-?\d+) if (\w+) ([!><=]+) (-?\d+))");

		vector<Instruction> instructions = vector<Instruction>();
		string arg;
		while(getline(is, arg))
		{
			Instruction ins = Instruction();
			smatch match;
			if(regex_match(arg, match, RX_INSTRUCTION))
			{
				ins.InsAddress = match.str(1);
				ins.InsType = GetInsType(match.str(2));
				ins.InsAmount = atoi(match.str(3).c_str());

				ins.OpAddress = match.str(4);
				ins.OpType = GetOpType(match.str(5));
				ins.OpAmount = atoi(match.str(6).c_str());
				instructions.push_back(ins);
			}
		}
		return instructions;
	}

	void Execute(map<string, int>& dataMap) const
	{
		if(CanPerformOp(dataMap))
		{
			PerformInstruction(dataMap);
		}
	}

private:
	void PerformInstruction(map<string, int>& dataMap) const
	{
		if(dataMap.find(InsAddress) == dataMap.end())
		{
			dataMap.emplace(InsAddress, 0);
		}
		switch(InsType)
		{
			case I_INC:
				dataMap[InsAddress] += InsAmount;
				break;
			case I_DEC:
				dataMap[InsAddress] -= InsAmount;
				break;
			case I_NOP:
			default:
				break;
		}
	}

	bool CanPerformOp(map<string, int>& dataMap) const
	{
		if(dataMap.find(OpAddress) == dataMap.end())
		{
			dataMap.emplace(OpAddress, 0);
		}
		switch(OpType)
		{
			case O_EQUAL:
				return dataMap[OpAddress] == OpAmount;
			case O_NOTEQUAL:
				return dataMap[OpAddress] != OpAmount;
			case O_GT:
				return dataMap[OpAddress] > OpAmount;
			case O_GTEQUAL:
				return dataMap[OpAddress] >= OpAmount;
			case O_LT:
				return dataMap[OpAddress] < OpAmount;
			case O_LTEQUAL:
				return dataMap[OpAddress] <= OpAmount;
			case O_NOP:
			default:
				break;
		}
		return false;
	}
};

template <>
void Run<Day08>(Part part, istream& is, ostream& os)
{
	vector<Instruction> instructions = Instruction::GetInstructions(is);
	map<string, int> dataMap;

	int largestValEver = INT_MIN;
	for(const auto& instruction : instructions)
	{
		instruction.Execute(dataMap);
		for(const auto& dataPair : dataMap)
		{
			if(dataPair.second > largestValEver)
			{
				largestValEver = dataPair.second;
			}
		}
	}

	if(part == Part01)
	{
		int largestValEnd = INT_MIN;
		for(const auto& dataPair : dataMap)
		{
			if(dataPair.second > largestValEnd)
			{
				largestValEnd = dataPair.second;
			}
		}
		os << "Largest Val End: " << largestValEnd;
	}
	else if(part == Part02)
	{
		os << "Largest Val Ever: " << largestValEver;
	}
}