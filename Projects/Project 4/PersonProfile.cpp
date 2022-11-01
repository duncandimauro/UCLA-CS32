
#include "PersonProfile.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>

using namespace std;

PersonProfile::PersonProfile(string name, string email)
	:m_name(name), m_email(email), num_pairs(0)
{
}


PersonProfile::~PersonProfile()
{
}


string PersonProfile::GetName() const
{
	return m_name;
}


string PersonProfile::GetEmail() const
{
	return m_email;
}


void PersonProfile::AddAttValPair(const AttValPair& attval)
{
	string att = attval.attribute;
	string val = attval.value;

	set<string>* ValueSetPointer = m_pairTree.search(att); //points to the relevant value set

	if (ValueSetPointer != nullptr) //CHECK IF THE ATTRIBUTE ALREADY EXISTS
	{
		if (ValueSetPointer->find(val) != ValueSetPointer->end())
		{
			return;
		}
		ValueSetPointer->insert(val); //add the value to the value list
		num_pairs++;
	}
	else
	{   //Add new attribute to tree with new vector that includes its relevant value
		m_pairTree.insert(att, set<string>{ val });
		num_pairs++;
	}

	m_pairs.push_back(attval); //add to the vector of pairs
}

int PersonProfile::GetNumAttValPairs() const
{
	return num_pairs;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
	if (attribute_num >= m_pairs.size())
		return false;

	attval = m_pairs[attribute_num];
	return true;
}
