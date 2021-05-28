#pragma once

#include "Vehicle.h"
#include "Boat.h"
#include "Boatplane.h"
#include "IDrivable.h"
#include "IFlyable.h"

namespace assignment2
{
	class Boat;
	
	class Airplane : public Vehicle, public IDrivable, public IFlyable
	{
	public:
		Airplane(unsigned int maxPassengersCount);
		Airplane(const Airplane& other);
		Airplane& operator=(const Airplane& other);
		~Airplane();

		Boatplane operator+(Boat& boat);

		unsigned int GetFlySpeed() const;
		unsigned int GetDriveSpeed() const;
		unsigned int GetMaxSpeed() const;

		bool Move(unsigned int count) const;

	private:
	};
}