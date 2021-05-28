#include "Airplane.h"
#include <cmath>

#include <iostream>

namespace assignment2
{
	Airplane::Airplane(unsigned int maxPassengersCount)
		: Vehicle(maxPassengersCount)
	{
	}

	Airplane::Airplane(const Airplane& other)
		: Vehicle(other.GetMaxPassengersCount())
	{
		if (other.GetPassengersCount() == 0)
		{
			return;
		}

		CopyDefaultMember(other);
	}

	Airplane& Airplane::operator=(const Airplane& other)
	{
		if (this == &other)
		{
			return *this;
		}

		AssignDefaultMember(other);

		return *this;
	}

	Airplane::~Airplane()
	{
	}

	Boatplane Airplane::operator+(Boat& boat)
	{
		Boatplane bp = Boatplane(GetMaxPassengersCount() + boat.GetMaxPassengersCount());
		const Person** boatplanePassengers = bp.GetPassengersArray();
		const Person** airplanePassengers = GetPassengersArray();
		const Person** boatPassengers = boat.GetPassengersArray();
		unsigned int count = 0;

		for (unsigned int i = 0; i < GetPassengersCount(); i++)
		{
			bp.AddPassenger(airplanePassengers[i]);
		}

		for (unsigned int i = 0; i < boat.GetPassengersCount(); i++)
		{
			bp.AddPassenger(boatPassengers[i]);
		}

		SetPassengersCount();
		boat.SetPassengersCount();

		return bp;
	}

	unsigned int Airplane::GetFlySpeed() const
	{
		float e = 2.71828f;
		float x = 0.0f;
		float airFlySpeed = 0.0f;

		for (unsigned int i = 0; i < GetPassengersCount(); i++)
		{
			x += static_cast<float>(GetPassenger(i)->GetWeight());
		}

		airFlySpeed = 200.0f * powf(e, ((-x + 800.0f) / 500.0f));

		return static_cast<unsigned int>(airFlySpeed + 0.5f);
	}

	unsigned int Airplane::GetDriveSpeed() const
	{
		float e = 2.71828f;
		float x = 0.0f;
		float airDriveSpeed = 0.0f;

		for (unsigned int i = 0; i < GetPassengersCount(); i++)
		{
			x += static_cast<float>(GetPassenger(i)->GetWeight());
		}

		airDriveSpeed = 4.0f * powf(e, ((-x + 400.0f) / 70.0f));

		return static_cast<unsigned int>(airDriveSpeed + 0.5f);
	}

	unsigned int Airplane::GetMaxSpeed() const
	{
		unsigned int driveSpeed = GetDriveSpeed();
		unsigned int flySpeed = GetFlySpeed();

		if (driveSpeed > flySpeed)
		{
			return driveSpeed;
		}
		else
		{
			return flySpeed;
		}
	}

	bool Airplane::Move(unsigned int count) const
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