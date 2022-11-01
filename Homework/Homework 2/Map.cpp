// Map.cpp

#include <iostream>

#include "Map.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
//  Map implementations
///////////////////////////////////////////////////////////////////////////

Map::Map() // Create an empty map (i.e., one with no key/value pairs)
	: m_size(0), head(nullptr)
{

}

Map::~Map()
// Destructor - When a Map is destroyed, the nodes in the linked list 
// must be deallocated.
{
	//Iterates through all the nodes and frees them
	Node* p = head;
	while (p != nullptr)
	{
		Node* r = p->next;
		delete p;
		p = r;
	}
}

Map::Map(const Map& src)
//Copy constructor - When a brand new Map is created as a copy of an 
//existing Map, enough new nodes must be allocated to hold a duplicate 
//of the original list.
	: m_size(0), head(nullptr)
{
	Node* temp = src.head;

	while (temp != nullptr) //traverse the src list and insert each node
	{
		insert(temp->key, temp->value);
		temp = temp->next;
	}

}

Map& Map::operator=(const Map& src)
//Assignment operator - When an existing Map (the left-hand side) is 
//assigned the value of another Map (the right-hand side), the result must 
//be that the left-hand side object is a duplicate of the right-hand side 
//object, with no memory leak of list nodes (i.e. no list node from the 
//old value of the left-hand side should be still allocated yet inaccessible)
{
	//Start by removing all existing nodes
	Node* p = head;
	while (p != nullptr)
	{
		Node* r = p->next;
		erase(p->key);
		p = r;
	}

	//Now set size to 0 and add nodes 1 by 1 via the insert function
	m_size = 0;

	Node* temp = src.head;

	while (temp != nullptr) //traverse the src list and insert each node
	{
		insert(temp->key, temp->value);
		temp = temp->next;
	}

	return (*this);

}

bool Map::empty() const // Return true if the map is empty, otherwise false.
{
	if (head == nullptr)
	{
		return true;
	}
	else
		return false;
}

int Map::size() const // Return the number of key/value pairs in the map.
{
	return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
// If key is not equal to any key currently in the map, then add
// it to the map and return true. Otherwise, make no change to the 
// map and return false
{
	if (!contains(key))
	{
		if (head == nullptr) //if head == nullptr
		{
			Node* p = new Node;
			p->key = key;
			p->value = value;
			p->next = head;
			p->prev = nullptr;
			head = p;
			m_size++;
			return true;
		}

		//If head != nullptr then add to back

		//Use a loop until you point to the last node
		Node* p = head;
		while (p->next != nullptr)
		{
			p = p->next;
		}

		//Creating the new node
		Node* n = new Node;
		n->key = key;
		n->value = value;
		n->next = nullptr; //n will become the last node in our list

		p->next = n; //the last node's "next" points to the new node n
		n->prev = p; //new node's "prev" points to the now 2nd to last node

		m_size++;
		return true;
	}
	return false;
}

bool Map::update(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value that it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
{
	Node* p = head;
	while (p != nullptr) //go through the entire list
	{
		if (p->key == key)
		{
			p->value = value;
			return true;
		}
		p = p->next;
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value that it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map and if the
// key/value pair can be added to the map, then do so and return true.
{
	if (contains(key)) //if you can update, then update and return true
	{
		update(key, value);
		return true;
	}
	else //if you can't update, then insert and return true
	{
		insert(key, value);
		return true;
	}
}

bool Map::erase(const KeyType& key)
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.
{
	Node* p = head;
	while (p != nullptr) //go through the entire list
	{
		Node* Prev = p->prev;
		Node* Next = p->next;

		if (p->key == key)
			//removing the node and making sure the prev and next pointers 
			//for the surrounding nodes are fixed           
		{
			if (Prev != nullptr) //if we're not deleting the first node
			{
				Prev->next = Next;
			}

			if (Next != nullptr) //if we're not deleting the last node
			{
				Next->prev = Prev;
			}

			if (Prev == nullptr) //if we are deleting the first node
			{
				head = Next;
			}

			delete p;
			m_size--;
			return true;
		}
		p = p->next;
	}
	return false;
}

bool Map::contains(const KeyType& key) const
// Return true if key is equal to a key currently in the map, otherwise
// false.
{
	Node* p = head;
	while (p != nullptr) //go through the entire list
	{
		if (p->key == key)
		{
			return true;
		}
		p = p->next;
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
// If key is equal to a key currently in the map, set value to the
// value in the map which that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.
{
	Node* p = head;
	while (p != nullptr) //go through the entire list
	{
		if (p->key == key)
		{
			value = p->value;
			return true;
		}
		p = p->next;
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of the key/value pair in the map whose key is strictly
// greater than exactly i keys in the map and return true.  Otherwise,
// leave the key and value parameters unchanged and return false.
{
	if ((0 <= i) && (i < size()))
	{
		//Sorting the list by key size - ascending
		//Uses a nested loop to rearrange the list

		for (int ii = 0; ii < m_size; ii++) //LOOP 1
		{
			//This creates a pointer to the (ii+1)-th node in the list
			Node* p = head;
			int temp1 = ii;
			while (temp1 > 0)
			{
				p = p->next;
				temp1--;
			}

			for (int j = ii + 1; j < m_size; j++) //LOOP 2
			{
				//This creates a pointer to the (j+1)-th node in the list
				Node* q = head;
				int temp2 = j;
				while (temp2 > 0)
				{
					q = q->next;
					temp2--;
				}

				if (p->key > q->key)
					//If key at (ii+1)-th node is greater than key at the 
					//(j+1)-th node, swap their positions
				{
					KeyType TempKey = q->key;
					ValueType TempValue = q->value;

					q->key = p->key;
					q->value = p->value;

					p->key = TempKey;
					p->value = TempValue;
				}
			}
		}

		//Now that the list is sorted, create a pointer to the (i+1)-th node
		Node* n = head;
		int r = i;
		while (r > 0)
		{
			n = n->next;
			r--;
		}

		//Set the key and value variables equal to those of the (i+1)-th node
		key = n->key;
		value = n->value;
		return true;
	}

	return false;
}

void Map::swap(Map& other)
// Exchange the contents of this map with the other one.
{
	Map temp = *this;
	*this = other;
	other = temp;
}

bool merge(const Map& m1, const Map& m2, Map& result)
//When this function returns, result must consist of pairs determined by 
//these rules: If a key appears in exactly one of m1 and m2, then result 
//must contain a pair consisting of that key and its corresponding value.
//If a key appears in both m1 and m2, with the same corresponding value in 
//both, then result must contain exactly one pair with that key and value
{
	Map merged;
	// Creating a new map to insert pairs of m1 and m2 into 
	// according to the given rules

	int isfalse = 0; //this value will increase if a key appears in both m1
					 //and m2 but with different corresponding values

	for (int i = 0; i < m1.size(); i++) //Loop through m1
	{
		//initialize variables - they will contain the key and value data
		//for each node of m1 by using the get function
		KeyType m1key;
		ValueType m1value;

		m1.get(i, m1key, m1value);
		//now m1key and m1value are equal to the key and value data of m1
		//at the (i+1)-th node (if we assume the nodes are sorted by 
		//Node1.key<Node2.key<Node3.key<...etc. -- see get function for details)

		if (m2.contains(m1key)) //if the key appears in both m1 and m2
		{
			ValueType m2value;
			m2.get(m1key, m2value);

			if (m1value == m2value) //if m1 and m2 have the exact same pair
			{
				merged.insert(m1key, m1value); //insert the pair
			}
			else if (m1value != m2value) //if the corresponding values are different
			{
				isfalse++; //do not insert the pair, instead increase isfalse by 1
			}
		}

		if (!m2.contains(m1key)) //if m1 has a unique key, insert the pair into merged
		{
			merged.insert(m1key, m1value);
		}
	}

	for (int i = 0; i < m2.size(); i++) //loop through m2
	{
		//initialize variables - they will contain the key and value data
		//for each node of m2 by using the get function
		KeyType m2key;
		ValueType m2value;

		//We already checked for pairs in m1 and m2 with the same key, so now
		//we only need to add the pairs from m2 that have unique keys

		m2.get(i, m2key, m2value);

		if (!m1.contains(m2key)) //if the key is non-repetetive (it's only in m2)
		{
			merged.insert(m2key, m2value);
		}
	}

	result = merged; //setting result equal to the new merged map

	if (isfalse > 0) //isfalse will be > 0 if there is a shared key by m1 & m2 but the 
					 //corresponding values are different
	{
		return false;
	}
	else
		return true;
}

void reassign(const Map& m, Map& result)
//When the reassign function returns, result must contain, for each pair p1 
//in m, a pair with p1's key mapping to a value copied from a different pair 
//p2 in m, and no other pair in result has its value copied from p2. (For ex, 
//if k1's original partner v1 is replaced by k2's original partner v2, then no 
//person in group K other than k1 also ends up dancing with v2.) However, if m 
//has only one pair, then result must contain simply a copy of that pair. (You 
//can't change partners if you're the only pair dancing!)
{
	Map reassigned; //We will fill this map with reassigned pairs

	if (m.size() < 2) //If there is 0 or 1 nodes, ie reassignment cannot be performed
	{
		result = m;
	}
	else
	{
		for (int i = 1; i < m.size(); i++) //Looping through m
		//We will move all values down one node to achieve the reassignment.
		{
			//initialize variables - they will contain the key and value data
			//for each node of m1 by using the get function

			KeyType key_i; //The key at the i-th node
			ValueType value_i; //The value at the i-th node
			KeyType key_ip1; //The key at the (i+1)-th node
			ValueType value_ip1; //The value at the (i+1)-th node

			m.get(i - 1, key_i, value_i); //get performed on the i-th node
			m.get(i, key_ip1, value_ip1); //get performed on the (i+1)th node

			reassigned.insert(key_i, value_ip1);
			//A pair is inserted with The i-th node's key and the (i+1)-th node's value
		}

		//Now we need to insert a pair with the last node's key and the 1st node's value

		KeyType key_1st;
		ValueType value_1st;
		KeyType key_last;
		ValueType value_last;

		m.get(0, key_1st, value_1st); //get performed on the 1st node
		m.get(m.size() - 1, key_last, value_last); //get performed on the last node

		reassigned.insert(key_last, value_1st);

		result = reassigned;
	}

}