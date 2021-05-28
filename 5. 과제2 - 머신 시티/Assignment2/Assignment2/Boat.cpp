#include "Boat.h"
#include <iostream>

namespace assignment2
{
	Boat::Boat(unsigned int maxPassengersCount)
		: Vehicle(maxPassengersCount)
	{
	}

	Boat::Boat(const Boat& other)
		: Vehicle(other.GetMaxPassengersCount())
	{
		if (other.GetPassengersCount() == 0)
		{
			return;
		}

		CopyDefaultMember(other);
	}

	Boat& Boat::operator=(const Boat& other)
	{
		if (this == &other)
		{
			return *this;
		}

		AssignDefaultMember(other);

		return *this;
	}

	Boat::~Boat()
	{
	}

	unsigned int Boat::GetSailSpeed() const
	{
		float e = 2.71828f;					// Euler number
		float x = 0.0f;						// Total weight
		float sailSpeed = 0.0f;

		for (unsigned int i = 0; i < GetPassengersCount(); i++)
		{
			x += static_cast<float>(GetPassenger(i)->GetWeight());
		}

		sailSpeed = (800.f - 1.7f * x > 20.f) ? (800.f - 1.7f * x) : 20.f;

		return static_cast<unsigned int>(sailSpeed);
	}

	unsigned int Boat::GetMaxSpeed() const
	{
		return GetSailSpeed();
	}

	Boatplane Boat::operator+(Airplane& plane)
	{
		unsigned int bpCapacity = GetMaxPassengersCount() + plane.GetMaxPassengersCount();

		Boatplane bp = Boatplane(bpCapacity);

		for (unsigned int i = 0; i < GetPassengersCount(); i++)
		{
			bp.AddPassenger(GetPassenger(i));
		}

		for (unsigned int i = 0; i < plane.GetPassengersCount(); i++)
		{
			bp.AddPassenger(plane.GetPassenger(i));
		}

		SetPassengerList();
		plane.SetPassengerList();

		return bp;
	}

	bool Boat::Move(unsigned int count) const
	{
		if (count == 1)
		{
			return true;
		}

		else if ((count % 3) == 0)
		{
			return false;
		}
		
		return true;
	}
}