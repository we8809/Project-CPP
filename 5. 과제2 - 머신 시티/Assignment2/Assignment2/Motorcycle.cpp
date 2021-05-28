#include "Motorcycle.h"
#include <cmath>

namespace assignment2
{
	Motorcycle::Motorcycle()
		: Vehicle(2)
	{
	}

	Motorcycle::Motorcycle(const Motorcycle& other)
		: Vehicle(other.GetMaxPassengersCount())
	{
		CopyDefaultMember(other);
	}

	Motorcycle& Motorcycle::operator=(const Motorcycle& other)
	{
		if (this == &other)
		{
			return *this;
		}

		AssignDefaultMember(other);

		return *this;
	}

	unsigned int Motorcycle::GetDriveSpeed() const
	{
		float x = 0.0f;						// Total weight
		float driveSpeed = 0.0f;

		for (unsigned int i = 0; i < GetPassengersCount(); i++)
		{
			x += static_cast<float>(GetPassenger(i)->GetWeight());
		}

		driveSpeed = (powf(-(x / 15.f), 3.f) + (2.f * x) + 400.f > 0.f) ? (powf(-(x / 15.f), 3.f) + (2.f * x) + 400.f) : 0.f;

		return static_cast<unsigned int>(driveSpeed + 0.5f);
	}

	unsigned int Motorcycle::GetMaxSpeed() const
	{
		return GetDriveSpeed();
	}

	Motorcycle::~Motorcycle()
	{
	}

	bool Motorcycle::Move(unsigned int count) const
	{
		if (count == 1)
		{
			return true;
		}

		else if ((count % 6) == 0)
		{
			return false;
		}

		return true;
	}
}