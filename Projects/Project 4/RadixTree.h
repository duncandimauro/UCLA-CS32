#ifndef _RADIXTREE_H_
#define _RADIXTREE_H_

#include <iostream>
#include <string>
#include "utility.h"
#include <set>

using namespace std;

template <typename ValueType>

//RESOURCES / SOURCES CITED: https://iq.opengenus.org/
//Although the referenced source's RadixTree implementation is in java and is a bit different than
//my implementation of a RadixTree, I wanted to reference it since it did help me a lot and many
//of my functions are based on the functions described in the literature
class RadixTree
{
public:

	//The RadixTree constructor.
	RadixTree();

	//You may define a destructor for RadixTree if you need one to free any dynamically allocated
	//memory used by your object.
	~RadixTree();

	//The insert method must update the Radix Tree to associate the specified key string with a copy
	//of the passed - in value.Inserting the same item twice should simply replace the original value
	//with the new value.The insert method needs to consider a number of special cases and edge
	//conditions; SEE SPEC FOR A FEW TO CONSIDER.
	void insert(string key, const ValueType& value);

	//The search method is responsible for searching your Radix Tree for the specified key. If the key
	//is found, then the search method must return a pointer to the value associated with the key.If
	//the specified key was not found, the method must return nullptr.If this method returns a non - null
	//pointer, the caller is free to modify the value held within the Radix Tree, e.g.: SEE SPEC
	ValueType* search(string key) const;

private:

	Node<ValueType>* root;
	vector<ValueType*> allValues;

	//If we have a string "help" that we want to insert, and we find an edge that is labelled "hen"
	//we need to split this edge up to make an edge "he" which points to a node, which then has two 
	//edges labelled "n" and "lp". This function returns the index of the first mismatched letter, 
	//which, in this case, the index would be 2
	int indexOfMismatchedLetter(string word, string edgeLabel)
	{
		for (int k = 1; k < min(word.size(), edgeLabel.size()); k++)
		{
			if (word.at(k) != edgeLabel.at(k))
			{
				return k;
			}
		}
		return 0; //There is no mismatched letter, we are ok to proceed
	}

	void cleanup(Node<ValueType>* currentNode)
	{
		if (currentNode->isLeaf && currentNode->numEdges == 0)
		{
			delete currentNode;
			return;
		}

		for (int index = 0; index < 128; index++)//check all possible edges of the node
		{
			if (currentNode->edges[index] != NULL) //if there is an edge
			{
				Edge<ValueType>* nextEdge = currentNode->edges[index];
				//Node<ValueType>* test = 
				if (nextEdge != NULL)
				{
					if (nextEdge->nextNode != NULL)
					{
						cleanup(nextEdge->nextNode); //go to it
					}
				}
			}
		}
		delete currentNode; //Now that we've moved through all edges, delete the current Node
	}
};

template <typename ValueType>
RadixTree<ValueType>::RadixTree()
{
	root = new Node<ValueType>(false);
}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree()
{
	cleanup(root);

	////IMPORTANT - Could not figure out how to free memory for ValueType data. The code below resulted in errors.
	//for (ValueType* v : allValues)
	//{
	//	if (v != nullptr)
	//	{
	//		delete v;
	//	}
	//}
}

template <typename ValueType>
void RadixTree<ValueType>::insert(string key, const ValueType& value)
{
	Node<ValueType>* currentNodeP = root;
	int currentIndex = 0;

	//Iterate through all characters of the key
	while (currentIndex < key.length())
	{
		char transitionChar = key.at(currentIndex); //The character which will be the start of the next edge

		string currentString = key.substr(currentIndex); //make the current string only have the leftover characters

		Edge<ValueType>* currentEdgeP = currentNodeP->findNextEdge(transitionChar); //seeing if there's an existing edge we can go to

		//If there is no edge we can go to, add the rest of the string as an edge, and add the Node it points to
		if (currentEdgeP == nullptr)
		{
			//add the new edge with the new node
			currentNodeP->newEdgeAndNewNode(currentString);

			//and put the correct value in the node
			ValueType* myValue = new ValueType(value);
			allValues.push_back(myValue);
			currentNodeP->findNextEdge(transitionChar)->nextNode->valP = myValue;
			break;
		}
		else //There exists an edge that we can try to go to
		{
			int indexToSplitString = indexOfMismatchedLetter(currentString, currentEdgeP->label);
			if (indexToSplitString == 0) //if a mismatched letter does NOT exist
			{
				//If the leftover string is the SAME as the edge label (could be duplicate, might not be)
				//Therefor, we make the next node (which already exists) a leaf node, which can hold a value
				if (currentString.length() == currentEdgeP->label.length())
				{
					currentEdgeP->nextNode->isLeaf = true;
					ValueType* myValue = new ValueType(value);
					allValues.push_back(myValue);
					currentEdgeP->nextNode->valP = myValue; //add the new value to that node
					break;
				}
				//If our string is a prefix of the current edge label
				else if (currentString.length() < currentEdgeP->label.length())
				{
					string suffix = currentEdgeP->label.substr(currentString.length());
					currentEdgeP->label = currentString;//reduce the current edge label to our string (the prefix)

					Node<ValueType>* NodeAfterPrefixP = new Node<ValueType>(true); //make a new node that will come after our prefix
					
					ValueType* myValue = new ValueType(value);
					allValues.push_back(myValue);
					NodeAfterPrefixP->valP = myValue; //insert the value into this node
					Node<ValueType>* NodeAfterSuffixP = currentEdgeP->nextNode; //the current "next" node becomes our suffix node

					currentEdgeP->nextNode = NodeAfterPrefixP; //make the current edge point to the prefix Node

					//make an edge from the prefix node to the suffix node
					NodeAfterPrefixP->newEdgeToDesiredNode(suffix, NodeAfterSuffixP);

					break;
				}
				else //our string is longer than the edge label, ie, our string has leftover characters
				{
					indexToSplitString = currentEdgeP->label.length();
				}
			}
			else //a mismatched letter DOES exist
			{
				string suffix = currentEdgeP->label.substr(indexToSplitString); //suffix
				currentEdgeP->label = currentEdgeP->label.substr(0, indexToSplitString); //set current edge label to prefix
				Node<ValueType>* fullWord = currentEdgeP->nextNode; //set it equal to the previous "next" node
				currentEdgeP->nextNode = new Node<ValueType>(false); //create a new node which goes after the prefix
				currentEdgeP->nextNode->newEdgeToDesiredNode(suffix, fullWord);
			}
			currentNodeP = currentEdgeP->nextNode;
			currentIndex += indexToSplitString;
		}
	}
}

template <typename ValueType>
ValueType* RadixTree<ValueType>::search(string key) const
{
	Node<ValueType>* currentNode = root;
	int currentIndex = 0;
	while (currentIndex < key.size())
	{
		char transitionChar = key.at(currentIndex);

		Edge<ValueType>* edge = currentNode->findNextEdge(transitionChar);
		if (edge == nullptr)
		{
			return nullptr;
		}

		string currentString = key.substr(currentIndex);
		
		//checking if the edge is a prefix of the current string
		for (int k = 0; k < min(currentString.size(), edge->label.size()); k++)
		{
			if (currentString.at(k) != edge->label.at(k))
			{
				return nullptr;
			}
		}

		currentIndex += edge->label.length();
		currentNode = edge->nextNode;
	}
	if (currentNode->isLeaf)
	{
		return currentNode->valP;
	}
	else
	{
		return nullptr;
	}
}



#endif //_RADIXTREE_H_

