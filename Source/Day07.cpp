#include "Days.h"
#include "AdventUtils.h"

#include <regex>


struct ProgramNode
{
	string Name;
	int Weight;
	ProgramNode* Parent;
	vector<ProgramNode*> ChildNodes;
	vector<string> ChildNames;
};

int GetNodeWeight(const ProgramNode* node)
{
	int totalWeight = node->Weight;
	for(const ProgramNode* child : node->ChildNodes)
	{
		totalWeight += GetNodeWeight(child);
	}
	return totalWeight;
}

bool AreChildrenEqual(const ProgramNode* node)
{
	if(node->ChildNodes.size() > 1)
	{
		for(int i = 1; i < node->ChildNodes.size(); ++i)
		{
			int value1 = GetNodeWeight(node->ChildNodes[i - 1]);
			int value2 = GetNodeWeight(node->ChildNodes[i]);
			if(value1 != value2)
			{
				return false;
			}
		}
	}
	return true;
}

void PrintBadChildren(const ProgramNode* node, ostream& os, int d)
{
	os << node->Weight << "(" << GetNodeWeight(node) << ")";
	if(!AreChildrenEqual(node))
	{	
		os << " **";
		++d;
		for(auto child : node->ChildNodes)
		{
			os << endl;
			for(int i = 0; i < d; ++i)
			{
				os << "  ";
			}
			os << " + ";
			PrintBadChildren(child, os, d);
		}
	}
}

template <>
void Run<Day07>(Part part, istream& is, ostream& os)
{
	// Regex to match token + digit + tokens
	const regex RX_PROGRAM_TOP(R"((\w+) \((\d+)\) -> (.+))");
	const regex RX_PROGRAM_BOT(R"((\w+) \((\d+)\))");

	vector<ProgramNode*> programNodes;
	string arg;
	while(getline(is, arg))
	{
		ProgramNode* n = new ProgramNode();

		smatch match;
		if(regex_search(arg, match, RX_PROGRAM_TOP))
		{
			n->Name = match.str(1);
			n->Weight = stoi(match.str(2));
			n->ChildNames = split(match.str(3), ',');
			for(auto& s : n->ChildNames)
			{
				ltrim(s);
			}
		}
		else if(regex_search(arg, match, RX_PROGRAM_BOT))
		{
			n->Name = match.str(1);
			n->Weight = stoi(match.str(2));
		}
		else
		{
			os << "Failed to match " << arg;
		}
		programNodes.push_back(n);
	}

	for(int i = 0; i < programNodes.size(); ++i)
	{
		ProgramNode* Node1 = programNodes[i];
		if(Node1->ChildNames.size() > 0)
		{
			for(int j = 0; j < programNodes.size() && Node1->ChildNames.size() > Node1->ChildNodes.size(); ++j)
			{
				ProgramNode* Node2 = programNodes[j];
				if(contains(Node1->ChildNames, Node2->Name))
				{
					Node1->ChildNodes.push_back(Node2);
					Node2->Parent = Node1;
				}
			}
		}
	}

	ProgramNode* bottomNode = nullptr;
	for(auto node : programNodes)
	{
		if(node->Parent == NULL)
		{
			bottomNode = node;
			break;
		}
	}

	if(part == Part01)
	{
		os << "Bottom Node: " << bottomNode->Name;
	}
	else if(part == Part02)
	{
		// Recursive printing of unbalanced nodes
		PrintBadChildren(bottomNode, os, 0);
	}

	for(auto node : programNodes)
	{
		delete node;
	}
}