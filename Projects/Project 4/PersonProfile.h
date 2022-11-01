#ifndef _PERSONPROFILE_H_
#define _PERSONPROFILE_H_

#include <string>
#include <vector>
#include <set>
#include <list>
#include "provided.h"
#include "RadixTree.h"
#include <iostream>
#include "utility.h"

using namespace std;

class PersonProfile
{
public:

	//This constructs a PersonProfile object, specifying the member’s name and email address
	PersonProfile(string name, string email);

	//You may define a destructor for PersonProfile if you need one.
	~PersonProfile();

	//The GetName method returns the member’s name.
	string GetName() const;

	//The GetEmail method returns the member’s email address.
	string GetEmail() const;

	//The AddAttValPair method is used to add a new attribute-value pair to the member’s profile. If
	//the person’s profile already has an attribute - value pair with the same attribute and value as the
	//attval parameter, then this method should do nothing.More than one attribute - value pair in the
	//map can have the same attribute, as long as their corresponding values are different.We place
	//no requirements on the order that you must store your attribute - value pairs
	void AddAttValPair(const AttValPair& attval);

	//This method returns the total number of distinct attribute-value pairs associated with this member.
	int GetNumAttValPairs() const;

	//This method gets the attribute-value pair specified by attribute_num 
	//(where 0 <= attribute_num < GetNumAttValPairs()) and places it in the attval parameter.
	//The method returns true if it successfully retrieves an attribute; otherwise, it returns
	//false and leaves attval unchanged. SEE SPEC FOR LOOP
	bool GetAttVal(int attribute_num, AttValPair& attval) const;

private:
	string m_name;
	string m_email;
	int num_pairs;
	RadixTree<set<string>> m_pairTree;
	vector<AttValPair> m_pairs;
};

#endif //_PERSONPROFILE_H_