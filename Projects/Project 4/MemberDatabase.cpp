#include "MemberDatabase.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

MemberDatabase::MemberDatabase()
{
}


MemberDatabase::~MemberDatabase()
{
}


bool MemberDatabase::LoadDatabase(string filename)
{
	std::ifstream file(filename);
	if (!file)
		return false;

	string line;

	set<string> allEmails; //Used to check if a duplicate email is in the text file

	while (getline(file, line))
	{
		int LineNumber = 1;
		string name = "";
		string email = "";

		//LOOP FOR FINDING NAME AND EMAIL
		while (line != "" && LineNumber < 4)
		{
			if (LineNumber == 1)
				name = line;

			else if (LineNumber == 2)
				email = line;

			if (!getline(file, line)) //go to the next line
			{
				break;
			}
			LineNumber++; //Line number increased
		}

		//Check for duplicate profile (duplicate email) before anything else
		if (!allEmails.insert(email).second)
			return false;

		//Creating new profile with the received name and email
		PersonProfile* newProfile = new PersonProfile(name, email);

		//This vector will be filled with the AttValPairs that will then be added to the profile
		vector<AttValPair> pairVector;

		//LOOP - CONTAINS ONLY THE ATT_VAL_PAIRS
		while (line != "" && LineNumber >= 4)
		{
			bool duplicate = false;
			string currentAttValPair = line;

			/////////////////////////////////////////////////////////////////////////////////////////////
			//////////////////////       MAP ATT_VAL_PAIRS TO EMAIL SET        //////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////

			set<string>* pointerToEmailSet = m_attValPairToEmails.search(currentAttValPair);

			if (pointerToEmailSet != nullptr) //current pair exists
			{
				if (!pointerToEmailSet->insert(email).second) //insert the email
					duplicate = true;                         //if false, attribute has this email already
			}
			else  //current pair doesn't exist
			{
				m_attValPairToEmails.insert(currentAttValPair, set<string>{ email });
			}

			/////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////           GET ATT_VAL_PAIR VECTOR           ///////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////
			if (!duplicate)
			{
				int commaCounter = 0;
				string currentAtt = "";
				string currentVal = "";
				for (char c : line)
				{
					if (c == ',')
					{
						commaCounter++;
					}
					else if (commaCounter == 0)
					{
						currentAtt += c;
					}
					else if (commaCounter > 0)
					{
						currentVal += c;
					}
				}
				pairVector.push_back(AttValPair(currentAtt, currentVal)); //add the pair
			}
			if (!getline(file, line)) //iterate to the next line - loop ends if it is "" or no more line
			{
				break;
			}
			LineNumber++;
		}

		//Add pairs to the profile
		for (int i = 0; i < pairVector.size(); i++)
		{
			newProfile->AddAttValPair(pairVector[i]);
		}

		//Add profile to Radix Tree
		m_emailsToProfiles.insert(email, *newProfile);
		delete newProfile;
	}

	return true; //All lines have been parsed - no two emails are the same
}

vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
	vector<string> matchingMembers;

	string pair = input.attribute + "," + input.value;

	set<string>* setOfPairs = m_attValPairToEmails.search(pair);

	if (setOfPairs != nullptr)
	{
		for (auto i : *setOfPairs)
		{
			matchingMembers.push_back(i);
		}
	}

	return matchingMembers;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
	return m_emailsToProfiles.search(email);
}