#ifndef _MEMBERDATABASE_H_
#define _MEMBERDATABASE_H_

#include <string>
#include <vector>
#include "provided.h"
#include "PersonProfile.h"

using namespace std;

class MemberDatabase
{
public:

	//The member database constructor.
	MemberDatabase();

	//You may define a destructor for MemberDatabase if you need one to free any dynamically
	//allocated memory used by your object.
	~MemberDatabase();

	//This method loads the member database from the data file specified by the filename parameter,
	//e.g., members.txt.The method must load the data into data structures that enable efficient
	//retrieval of email addresses(meeting the big - O requirements at the top of this section).The
	//method must return true if the file was successfully loaded and false otherwise.If two members
	//in the data file have the same email address, this method returns false
	bool LoadDatabase(string filename);

	//This method must identify all members that have the specified input attribute-value pair in an
	//efficient manner(meeting the requirements at the top of this section) and return a vector
	//containing their email addresses.If there are no such members, the vector returned must be
	//empty.There is no particular order required for the email addresses in the vector returned.The
	//vector returned must not contain duplicate email addresses.
	vector<string> FindMatchingMembers(const AttValPair& input) const;

	//Given an email address, this method must determine if a member exists in the database with
	//that email address, and if so, a pointer to that member’s PersonProfile that is held in your
	//MemberDatabase object; if there is no such member, this method returns nullptr.
	const PersonProfile* GetMemberByEmail(std::string email) const;

private:
	RadixTree<set<string>> m_attValPairToEmails; //string is AttValPair
	RadixTree<PersonProfile> m_emailsToProfiles; //string is email
};

#endif //_MEMBERDATABASE_H_