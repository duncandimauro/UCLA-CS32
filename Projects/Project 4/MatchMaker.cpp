#include "MatchMaker.h"

#include <string>
#include <vector>
#include <set>
#include <algorithm>

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
	: m_database(&mdb), m_translator(&at)
{
}

MatchMaker::~MatchMaker()
{
}

vector<EmailCount> MatchMaker::IdentifyRankedMatches(string email, int threshold) const
{
	const PersonProfile* thisPerson = m_database->GetMemberByEmail(email);

	vector<EmailCount> temp;

	set<string> matchedEmails; //used to store all emails which have at least 1 match

	RadixTree<int> emailsAndMatches; //maps emails to the amount of matches they have so far

	set<AttValPair> CompatibleAttValPairs; //All compatible AttVal Pairs

	//Get all compatible AttVal Pairs, no duplicates
	for (int k = 0; k != thisPerson->GetNumAttValPairs(); k++)
	{
		AttValPair av;
		thisPerson->GetAttVal(k, av);

		vector<AttValPair> pairsForThisAtt = m_translator->FindCompatibleAttValPairs(av);

		for (AttValPair p : pairsForThisAtt)
		{
			CompatibleAttValPairs.insert(p);
		}
	}

	//For each compatible AttValPair
	for (AttValPair i : CompatibleAttValPairs)
	{
		//Find all member emails who have this pair
		vector<string> EmailsWithThisPair = m_database->FindMatchingMembers(i);

		//Loop through all these emails
		for (string email : EmailsWithThisPair)
		{
			int* numMatches = emailsAndMatches.search(email);

			if (numMatches != nullptr) //if the email already has at least 1 match
			{
				(*numMatches)++;
			}
			else if (matchedEmails.insert(email).second)
			{
				emailsAndMatches.insert(email, 1); //otherwise, insert the email into radix tree
			}
		}
	}

	//For all emails found to have at least one match
	for (string e : matchedEmails)
	{
		int* numMatches = emailsAndMatches.search(e);

		//If the email has at least threshold amount of matches
		if (*numMatches >= threshold)
		{
			temp.push_back(EmailCount(e, *numMatches)); //insert it into the final vector
		}
	}

	sort(temp.begin(), temp.end(), greater<EmailCount>());

	return temp;
}
