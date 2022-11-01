#ifndef _ATTRIBUTETRANSLATOR_H_
#define _ATTRIBUTETRANSLATOR_H_

#include <string>
#include <vector>
#include <set>
#include "provided.h"
#include "RadixTree.h"
#include "utility.h"

using namespace std;

class AttributeTranslator
{
public:

	//This is the AttributeTranslator constructor. It must take no arguments.
	AttributeTranslator();

	//You may define a destructor for AttributeTranslator if you need one to free any dynamically
	//allocated memory used by your object
	~AttributeTranslator();

	//This method loads the attribute-value translation data from the data file specified by the
	//filename parameter.The method must load the data into a data structure that enables efficient
	//translation of attribute - value pairs(meeting the big - O requirements at the top of this section).
	//The method must return true if the file was successfully loaded and false otherwise.
	bool Load(string filename);

	//This method must identify all compatible attribute-value pairs for the specified source attributevalue 
	//pair in an efficient manner (meeting the requirements at the top of this section) and return a vector 
	//containing them.If there are no compatible pairs, the vector returned must be empty. There is no 
	//particular order required for the AttValPairs in the vector returned. The vector returned must not 
	//contain two attribute - value pairs with the same attributes and values(i.e., no duplicates).
	vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;

private:
	RadixTree<set<AttValPair>> m_CompatiblePairTree;
};

#endif //_ATTRIBUTETRANSLATOR_H_