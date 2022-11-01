// CarMap.cpp

#include <iostream>

#include "CarMap.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
//  CarMap implementations
///////////////////////////////////////////////////////////////////////////

CarMap::CarMap()      // Create an empty car map.
{

}

bool CarMap::addCar(std::string license)
// If a car with the given license plate is not currently in the map, 
// and there is room in the map, add an entry for that car recording
// that it has been driven 0 miles, and return true.  Otherwise,
// make no change to the map and return false.
{
	return m_car.insert(license, 0);
}

double CarMap::miles(std::string license) const
// If a car with the given license plate is in the map, return how
// many miles it has been driven; otherwise, return -1.
{
	ValueType miles = -1;
	m_car.get(license, miles);
	return miles;
}

bool CarMap::drive(std::string license, double distance)
// If no car with the given license plate is in the map or if
// distance is negative, make no change to the map and return
// false.  Otherwise, increase by the distance parameter the number
// of miles the indicated car has been driven and return true.
{
	if ((distance < 0) || (!m_car.contains(license)))
	{
		return false;
	}	

	ValueType miles = 0;
	m_car.get(license, miles);
	m_car.update(license, miles + distance);
	return true;
}

int CarMap::fleetSize() const  // Return the number of cars in the CarMap.
{
	return m_car.size();
}

void CarMap::print() const
// Write to cout one line for every car in the map.  Each line
// consists of the car's license plate, followed by one space,
// followed by the number of miles that car has been driven.  Write
// no other text.  The lines need not be in any particular order.
{
	int size = m_car.size();

	for (int i = 0; i < size; i++)
	{
		KeyType plate;
		ValueType miles;
		m_car.get(i, plate, miles);
		cout << plate << " " << miles << endl;
	}
}