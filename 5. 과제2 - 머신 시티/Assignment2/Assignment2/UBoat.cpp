#include "UBoat.h"

namespace assignment2
{
	UBoat::UBoat()
		: Vehicle(50)
	{

	}

	UBoat::UBoat(const UBoat& other)
		: Vehicle(50)
	{
		if (other.GetPassengersCount() == 0)
		{
			return;
		}

		CopyDefaultMember(other);
	}

	UBoat& UBoat::operator=(const UBoat& other)
	{
		if (this == &other)
		{
			return *this;
		}

		AssignDefaultMember(other);

		return *this;
	}

	UBoat::~UBoat()
	{

	}

	unsigned int UBoat::GetMaxSpeed() const
	{
		unsigned int sailSpeed = GetSailSpeed();
		unsigned int diveSpeed = GetDiveSpeed();

		if (sailSpeed > diveSpeed)
		{
			return sailSpeed;
		}
		else
		{
			return diveSpeed;
		}
	}

	unsigned int UBoat::GetSailSpeed() const
	{
		float x = 0.0f;						// Total weight
		float sailSpeed = 0.0f;

		for (unsigned int i = 0; i < GetPassengersCount(); i++)
		{
			x += static_cast<float>(GetPassenger(i)->GetWeight());
		}

		sailSpeed = (550.f - x / 10.f) > 200.f ? (550.f - x / 10.f) : 200.f;

		return static_cast<unsigned int>(sailSpeed + 0.5f);
	}

	unsigned int UBoat::GetDiveSpeed() const
	{
		float x = 0.0f;						// Total weight
		float diveSpeed = 0.0f;

		for (unsigned int i = 0; i < GetPassengersCount(); i++)
		{
			x += static_cast<float>(GetPassenger(i)->GetWeight());
		}

		diveSpeed = 500 * logf((x + 150.f) / 150.f) + 30;

		return static_cast<unsigned int>(diveSpeed + 0.5f);
	}

	bool UBoat::Move(unsigned int count) const
	{
		return false;
	}
}