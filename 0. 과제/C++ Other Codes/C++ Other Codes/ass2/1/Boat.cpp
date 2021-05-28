#include "Boat.h"
#include "Airplane.h"
#include "Boatplane.h"

namespace assignment2
{
	Boat::Boat(unsigned int maxPassengersCount)
		: Vehicle(maxPassengersCount)
	{
	}

	Boat::~Boat()
	{
	}

	Boatplane Boat::operator+(Airplane& plane)
	{
		Boatplane bp(plane.GetMaxPassengersCount() + GetMaxPassengersCount());
		plane.TransferPassengers(bp);
		TransferPassengers(bp);

		return bp;
	}

	unsigned Boat::GetSailSpeed() const
	{
		const unsigned TOTAL_WEIGHT = GetPassengersTotalWeight();
		const int SPEED = 800 - 10 * static_cast<int>(TOTAL_WEIGHT);

		return SPEED > 20 ? static_cast<unsigned>(SPEED) : 20;
	}

	unsigned Boat::GetMaxSpeed() const
	{
		return GetSailSpeed();
	}

	unsigned Boat::GetTravelledDistance() const
	{
		unsigned distance = 0;
		for (unsigned i = 1; i <= mTravelCount; i++)
		{
			if (i % 3 != 0)
			{
				distance += GetMaxSpeed();
			}
		}
		return distance;
	}
}
