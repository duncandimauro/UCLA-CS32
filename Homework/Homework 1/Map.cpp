// Map.cpp

#include <iostream>

#include "Map.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
//  Map implementations
///////////////////////////////////////////////////////////////////////////

Map::Map() // Create an empty map (i.e., one with no key/value pairs)
	: m_size(0)
{

}

bool Map::empty() const // Return true if the map is empty, otherwise false.
{
	if (m_size == 0)
		return true;
	else
		return false;
}

int Map::size() const // Return the number of key/value pairs in the map.
{
	return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
    // If key is not equal to any key currently in the map, and if the
	// key/value pair can be added to the map, then do so and return true.
	// Otherwise, make no change to the map and return false (indicating
	// that either the key is already in the map, or the map has a fixed
	// capacity and is full).
{
	if (!contains(key) && m_size < DEFAULT_MAX_ITEMS)
	{
		m_map[m_size].key = key;
		m_map[m_size].value = value;
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
	for (int i = 0; i < m_size; i++)
	{
		if (m_map[i].key == key)
		{
			m_map[i].value = value;
			return true;
		}
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value that it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that the key is not already in the map and the map has a fixed
// capacity and is full).
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_map[i].key == key)
		{
			m_map[i].value = value;
			return true;
		}
	}

	if (m_size < DEFAULT_MAX_ITEMS)
	{
		m_map[m_size].key = key;
		m_map[m_size].value = value;
		m_size++;
		return true;
	}

	return false;
}

bool Map::erase(const KeyType& key)
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_map[i].key == key)
		{
			m_map[i] = m_map[m_size - 1];
			m_size--;
			return true;
		}
	}
	return false;
}

bool Map::contains(const KeyType& key) const
// Return true if key is equal to a key currently in the map, otherwise
// false.
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_map[i].key == key)
			return true;
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
// If key is equal to a key currently in the map, set value to the
// value in the map which that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_map[i].key == key)
		{
			value = m_map[i].value;
			return true;
		}
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
		//Making temporary map
		KeyAndValue TempMap[DEFAULT_MAX_ITEMS];
		for (int j = 0; j < m_size; j++)
		{
			TempMap[j] = m_map[j];
		}

		//Sorting the temporary map by key size - ascending
		for (int ii = 0; ii < m_size; ii++)
		{
			for (int j = ii + 1; j < m_size; j++)
			{
				if (TempMap[ii].key > TempMap[j].key)
				{
					KeyType TempKey = TempMap[ii].key;
					ValueType TempValue = TempMap[ii].value;
					TempMap[ii] = TempMap[j];
					TempMap[j].key = TempKey;
					TempMap[j].value = TempValue;
				}
			}
		}

		key = TempMap[i].key;
		value = TempMap[i].value;
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