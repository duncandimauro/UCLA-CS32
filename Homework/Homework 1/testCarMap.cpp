#include "CarMap.h"
#include <iostream>
#include <cassert>
#include <string>
using namespace std;

int main()
{
    CarMap m;  // maps strings to doubles
    string car1 = "12345678";
    string car2 = "87654321";
    string car3 = "tomato";
    m.addCar(car1);
    m.addCar(car2);
    m.addCar(car3);
    cout << m.miles(car1) << endl;
    m.drive(car1, 50);
    m.drive(car2, 100);
    m.drive(car3, 200);
    cout << m.fleetSize() << endl;
    m.print();

}