#include "Boat.h"
#include <cmath>

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
		Boatplane bp(GetMaxPassengersCount() + plane.GetMaxPassengersCount());
		unsigned int airplanePassengersCount = plane.GetPassengersCount();
		unsigned int boatPassengersCount = GetPassengersCount();
		
		for (size_t i = 0; i < airplanePassengersCount; i++)
		{
			const Person* p = new const Person(plane.GetPassenger(0)->GetName().c_str(), plane.GetPassenger(0)->GetWeight());
			if (bp.AddPassenger(p))
			{
				plane.RemovePassenger(0);
			}
		}
		for (size_t i = 0; i < boatPassengersCount; i++)
		{
			const Person* p = new const Person(mPassengers[0]->GetName().c_str(), mPassengers[0]->GetWeight());
			if (bp.AddPassenger(p))
			{
				RemovePassenger(0);
			}
		}
		return bp;
	}
	unsigned int Boat::GetSailSpeed() const
	{
		unsigned int result = 800 - 10 * static_cast<int>(mPassengersWeight);
		if (static_cast<int>(result) > 20)
		{
			return result;
		}
		return 20;
	}

	unsigned int Boat::GetMaxSpeed() const
	{
		return GetSailSpeed();
	}

	unsigned int Boat::Travel()
	{
		unsigned int travelCycle = 3;
		mTravelCount++;
		if (mTravelCount % travelCycle == 0)
		{
			return mTravelDistance;
		}
		mTravelDistance += GetMaxSpeed();
		return mTravelDistance;
	}
}
