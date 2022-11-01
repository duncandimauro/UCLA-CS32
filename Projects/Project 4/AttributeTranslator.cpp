#include "AttributeTranslator.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>

using namespace std;

AttributeTranslator::AttributeTranslator()
{
}


AttributeTranslator::~AttributeTranslator()
{
}


bool AttributeTranslator::Load(string filename)
{
	std::ifstream file(filename);
	if (!file)
	{
		return false;
	}
	string line;
	while (getline(file, line))
	{
		if (line == "")
		{
			continue;
		}
		else
		{
			int commaCounter = 0;
			string SourceAttValPair = "";
			string compatAtt = "";
			string compatVal = "";
			for (char c : line)
			{
				if (c == ',')
				{
					commaCounter++;
					if (commaCounter == 1)
						SourceAttValPair += c;
				}
				else if (commaCounter < 2)
				{
					SourceAttValPair += c;
				}
				else if (commaCounter == 2)
				{
					compatAtt += c;
				}
				else if (commaCounter == 3)
				{
					compatVal += c;
				}
			}

			set<AttValPair>* pointerToSet = m_CompatiblePairTree.search(SourceAttValPair);
			AttValPair compatiblePair = AttValPair(compatAtt, compatVal);

			if (pointerToSet != nullptr) //CHECK IF THE SOURCE PAIR ALREADY EXISTS
			{
				if (pointerToSet->find(compatiblePair) == pointerToSet->end()) //if compatible pair doesn't already exist
				{
					pointerToSet->insert(compatiblePair); //add the value to the value list
				}
			}
			else //Create new source pair with new compatible pair set
			{
				m_CompatiblePairTree.insert(SourceAttValPair, set<AttValPair>{ compatiblePair });
			}
		}
	}
	return true;
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
	string SourceAttValPair = source.attribute + "," + source.value;

	auto pointsToPairSet = m_CompatiblePairTree.search(SourceAttValPair);
	if (pointsToPairSet == NULL)
	{
		return vector<AttValPair>{source};
	}
	else
	{
		vector<AttValPair> tempVector;
		for (auto i : *pointsToPairSet)
		{
			tempVector.push_back(i);
		}
		return tempVector;
	}
}