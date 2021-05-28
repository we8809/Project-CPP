#include "Boatplane.h"
#include <cmath>

#include <iostream>

namespace assignment2
{
	Boatplane::Boatplane(unsigned int maxPassengersCount)
		: Vehicle(maxPassengersCount)
	{

	}

	Boatplane::Boatplane(const Boatplane& other)
		: Vehicle(other.GetMaxPassengersCount())
	{
		if (other.GetPassengersCount() == 0)
		{
			return;
		}

		CopyDefaultMember(other);
	}

	Boatplane::~Boatplane()
	{

	}

	Boatplane& Boatplane::operator=(const Boatplane& other)
	{
		if (this == &other)
		{
			return *this;
		}

		AssignDefaultMember(other);

		return *this;
	}

	unsigned int Boatplane::GetFlySpeed() const
	{
		float e = 2.71828f;					// Euler number
		float x = 0.0f;						// Total weight
		float flySpeed = 0.0f;

		for (unsigned int i = 0; i < GetPassengersCount(); i++)
		{
			x += static_cast<float>(GetPassenger(i)->GetWeight());
		}

		flySpeed = 150 * powf(e, ((-x + 500) / 300));

		return static_cast<unsigned int>(flySpeed + 0.5f);
	}

	unsigned int Boatplane::GetSailSpeed() const
	{
		float e = 2.71828f;					// Euler number
		float x = 0.0f;						// Total weight
		float sailSpeed = 0.0f;

		for (unsigned int i = 0; i < GetPassengersCount(); i++)
		{
			x += static_cast<float>(GetPassenger(i)->GetWeight());
		}

		sailSpeed = (800.f - 1.7f * x > 20.f) ? (800.f - 1.7f * x) : 20.f;

		return static_cast<unsigned int>(sailSpeed + 0.5f);
	}

	unsigned int Boatplane::GetMaxSpeed() const
	{
		unsigned int flySpeed = GetFlySpeed();
		unsigned int sailSpeed = GetSailSpeed();

		if (flySpeed > sailSpeed)
		{
			return flySpeed;
		}
		else
		{
			return sailSpeed;
		}
	}

	bool Boatplane::Move(unsigned int count) const
	{
		if (count == 1)
		{
			return true;
		}

		else if ((count - 1) % 4 == 0)
		{
			return true;
		}

		return false;
	}
}