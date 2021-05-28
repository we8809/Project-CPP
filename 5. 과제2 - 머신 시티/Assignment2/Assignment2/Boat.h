#pragma once

#include "Vehicle.h"
#include "ISailable.h"

#include "Airplane.h"
#include "Boatplane.h"

namespace assignment2
{
	class Airplane;
	class Boatplane;

	class Boat : public Vehicle, public ISailable
	{
	public:
		Boat(unsigned int maxPassengersCount);
		Boat(const Boat& other);
		Boat& operator=(const Boat& other);
		~Boat();

		unsigned int GetMaxSpeed() const;
		unsigned int GetSailSpeed() const;

		bool Move(unsigned int count) const;

		Boatplane operator+(Airplane& plane);

	private:
	};
}