#include <iostream>
#include <cassert>

#include "Vehicle.h"
#include "Person.h"
#include "Airplane.h"
#include "Boat.h"
#include "Boatplane.h"
#include "Trailer.h"
#include "Motorcycle.h"
#include "Sedan.h"
#include "UBoat.h"
#include "DeusExMachina.h"

using namespace assignment2;

int main(void)
{
	Person* p = new Person("Bob", 85);

	assert(p->GetName() == std::string("Bob"));
	assert(p->GetWeight() == 85);

	Person* p2 = new Person("James", 75);
	Person* p3 = new Person("Tina", 52);

	Person* p4 = new Person("Peter", 78);
	Person* p5 = new Person("Jane", 48);
	Person* p6 = new Person("Steve", 88);

	Airplane a(5);
	a.AddPassenger(p);
	a.AddPassenger(p2);
	a.AddPassenger(p3);

	assert(a.GetMaxPassengersCount() == 5);
	assert(a.GetPassengersCount() == 3);
	assert(a.GetPassenger(1) == p2);
	assert(a.GetFlySpeed() == 648);
	assert(a.GetDriveSpeed() == 59);
	assert(a.GetMaxSpeed() == 648);

	Boat b(5);
	b.AddPassenger(p4);
	b.AddPassenger(p5);
	b.AddPassenger(p6); 
	
	Boatplane bp = a + b;

	std::cout << "bp's Address : " << &bp << std::endl;

	assert(bp.GetPassengersCount() == 6);
	assert(bp.GetMaxPassengersCount() == 10);

	assert(a.GetPassengersCount() == 0);
	assert(b.GetPassengersCount() == 0);

	std::cout << "hihi" << std::endl;
	
	return 0;
}