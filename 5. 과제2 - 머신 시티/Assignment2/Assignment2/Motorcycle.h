#pragma once

#include "Vehicle.h"
#include "IDrivable.h"

namespace assignment2
{
	class Motorcycle : public Vehicle, public IDrivable
	{
	public:
		Motorcycle();
		Motorcycle(const Motorcycle& other);
		Motorcycle& operator=(const Motorcycle& other);
		~Motorcycle();

		unsigned int GetMaxSpeed() const;
		unsigned int GetDriveSpeed() const;

		bool Move(unsigned int count) const;
	};
}