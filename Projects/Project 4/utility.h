#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <string>
#include "provided.h"

using namespace std;

bool operator < (const AttValPair& lhs, const AttValPair& rhs);

bool operator > (const AttValPair& lhs, const AttValPair& rhs);

bool operator > (const EmailCount& lhs, const EmailCount& rhs);

bool operator < (const EmailCount& lhs, const EmailCount& rhs);

bool operator == (const EmailCount& lhs, const EmailCount& rhs);

/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////                 EDGE STRUCT                  /////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
template <typename ValueType>
struct Node;

template <typename ValueType>
struct Edge
{
	//Create a new edge which goes to a new node
	Edge(string myLabel);

	//Create a new edge which will go to the node passed into the constructor
	Edge(string myLabel, Node<ValueType>* goHere);

	string label;
	Node<ValueType>* nextNode;
};

/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////                 NODE STRUCT                  /////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
template <typename ValueType>
struct Node
{
	//Constructing a node and saying whether it is a leaf or not
	Node(bool leaf);

	~Node();

	//returns the edge whose label starts with transitionChar. It is nullptr by default.
	Edge<ValueType>* findNextEdge(char transitionChar);

	//Adds an edge with the label "label" that points to a new node which is created
	//Returns a pointer to the new node created
	void newEdgeAndNewNode(string label);

	//Creates a new edge and attaches it to the current node passed into the function
	void newEdgeToDesiredNode(string label, Node* next);

	bool isLeaf;
	int numEdges;
	Edge<ValueType>* edges[128]; //each spot in the array represents the ASCII value of a character
	ValueType* valP;
};

/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////                EDGE IMPLEMENTATIONS                  ///////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

template <typename ValueType>
Edge<ValueType>::Edge(string myLabel)
	: label(myLabel), nextNode((new Node<ValueType>(true))) {}

template <typename ValueType>
Edge<ValueType>::Edge(string myLabel, Node<ValueType>* goHere)
	: label(myLabel), nextNode(goHere) {}

/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////                 NODE IMPLEMENTATIONS                 ///////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
template <typename ValueType>
Node<ValueType>::Node(bool leaf)
	: isLeaf(leaf), numEdges(0), edges(), valP(nullptr)
{
}

template <typename ValueType>
Node<ValueType>::~Node()
{
	for (int k = 0; k < 128; k++)
	{
		Edge<ValueType>* temp = edges[k];
		delete temp;
	}
}

template <typename ValueType>
Edge<ValueType>* Node<ValueType>::findNextEdge(char transitionChar)
{
	if (edges[int(transitionChar)] != nullptr)
	{
		return edges[int(transitionChar)];
	}

	return nullptr;
}

template <typename ValueType>
void Node<ValueType>::newEdgeAndNewNode(string label)
{
	//places new edge at index of the first char in the string
	if (edges[int(label.at(0))] != nullptr)
	{
		delete edges[int(label.at(0))];
	}

	edges[int(label.at(0))] = new Edge<ValueType>(label);
	numEdges++;
}

template <typename ValueType>
void Node<ValueType>::newEdgeToDesiredNode(string label, Node<ValueType>* next)
{
	edges[int(label.at(0))] = new Edge<ValueType>(label, next);
	numEdges++;
}

#endif //_UTILITY_H_