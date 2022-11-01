//
//  Map.h
//

#ifndef Map_h
#define Map_h

#include <string>

using KeyType = char;
using ValueType = int;
//const int DEFAULT_MAX_ITEMS = 260; //Not Needed

class Map
{
public:
    Map(); //Create an empty map (i.e., one with no key/value pairs)

    ~Map();
    // Destructor - When a Map is destroyed, the nodes in the linked list 
    // must be deallocated.

    Map(const Map& src);
    //Copy constructor - When a brand new Map is created as a copy of an 
    //existing Map, enough new nodes must be allocated to hold a duplicate 
    //of the original list.

    Map& operator=(const Map& src);
    //Assignment operator - When an existing Map (the left-hand side) is 
    //assigned the value of another Map (the right-hand side), the result must 
    //be that the left-hand side object is a duplicate of the right-hand side 
    //object, with no memory leak of list nodes (i.e. no list node from the 
    //old value of the left-hand side should be still allocated yet inaccessible)

    bool empty() const;  // Return true if the map is empty, otherwise false.

    int size() const;    // Return the number of key/value pairs in the map.

    bool insert(const KeyType& key, const ValueType& value);
    // If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that either the key is already in the map, or the map has a fixed
    // capacity and is full).

    bool update(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value that it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // Otherwise, make no change to the map and return false.

    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value that it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // If key is not equal to any key currently in the map and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that the key is not already in the map and the map has a fixed
    // capacity and is full).

    bool erase(const KeyType& key);
    // If key is equal to a key currently in the map, remove the key/value
    // pair with that key from the map and return true.  Otherwise, make
    // no change to the map and return false.

    bool contains(const KeyType& key) const;
    // Return true if key is equal to a key currently in the map, otherwise
    // false.

    bool get(const KeyType& key, ValueType& value) const;
    // If key is equal to a key currently in the map, set value to the
    // value in the map which that key maps to, and return true.  Otherwise,
    // make no change to the value parameter of this function and return
    // false.

    bool get(int i, KeyType& key, ValueType& value) const;
    // If 0 <= i < size(), copy into the key and value parameters the
    // key and value of the key/value pair in the map whose key is strictly
    // greater than exactly i keys in the map and return true.  Otherwise,
    // leave the key and value parameters unchanged and return false.

    void swap(Map& other);
    // Exchange the contents of this map with the other one.

private:

    struct Node
    {
        KeyType key;
        ValueType value;
        Node* next;
        Node* prev;
    };

    int m_size;
    Node* head; // the pointer to the 1st node

};

//These are non-member functions
bool merge(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);

#endif