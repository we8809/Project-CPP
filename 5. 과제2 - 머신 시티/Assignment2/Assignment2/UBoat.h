#pragma once

#include "Vehicle.h"
#include "ISailable.h"
#include "IDivable.h"

namespace assignment2
{
	class UBoat : public Vehicle, public ISailable, public IDivable
	{
	public:
		UBoat();
		UBoat(const UBoat& other);
		UBoat& operator=(const UBoat& other);
		~UBoat();

		unsigned int GetMaxSpeed() const;
		unsigned int GetSailSpeed() const;
		unsigned int GetDiveSpeed() const;

		bool Move(unsigned int count) const;
	};
}