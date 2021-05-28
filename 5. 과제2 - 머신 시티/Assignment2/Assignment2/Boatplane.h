#pragma once

#include "ISailable.h"
#include "IFlyable.h"
#include "Vehicle.h"

namespace assignment2
{
	class Boatplane : public Vehicle, public ISailable, public IFlyable
	{
	public:
		Boatplane(unsigned int maxPassengersCount);
		Boatplane(const Boatplane& other);
		Boatplane& operator=(const Boatplane& other);
		~Boatplane();

		unsigned int GetFlySpeed() const;
		unsigned int GetSailSpeed() const;
		unsigned int GetMaxSpeed() const;

		bool Move(unsigned int count) const;

	private:
	};
}