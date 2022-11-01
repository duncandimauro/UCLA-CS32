#ifndef _MATCHMAKER_H_
#define _MATCHMAKER_H_

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include "provided.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include "utility.h"

using namespace std;

class MatchMaker
{
public:

	//This constructs a MatchMaker object with the indicated parameters
	MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);

	//You may define a destructor for MatchMaker if you need one to free any dynamically
	//allocated memory used by your object.
	~MatchMaker();

	vector<EmailCount> IdentifyRankedMatches(string email, int threshold) const;

private:
	const MemberDatabase* m_database;
	const AttributeTranslator* m_translator;
};

#endif //_MATCHMAKER_H_