#include "Vehicle.h"

namespace assignment2
{
	Vehicle::Vehicle(unsigned int maxPassengersCount)
		: mMaxCapacity(maxPassengersCount)
		, mSize(0)
	{
		if (maxPassengersCount >= 100)
		{
			maxPassengersCount = 100;
		}

		mPassengerList = new const Person * [maxPassengersCount];
	}

	Vehicle::~Vehicle()
	{
		if (mPassengerList != nullptr)
		{
			for (unsigned int i = 0; i < mSize; i++)
			{
				delete mPassengerList[i];
			}

			delete mPassengerList;
		}
	}

	bool Vehicle::AddPassenger(const Person* person)
	{
		if (mSize >= mMaxCapacity)
		{
			return false;
		}

		mPassengerList[mSize] = person;
		mSize++;

		return true;
	}

	bool Vehicle::RemovePassenger(unsigned int i)
	{
		if (i >= mMaxCapacity || mSize == 0)
		{
			return false;
		}

		for (unsigned int cnt = i; cnt < mSize; cnt++)
		{
			if (cnt >= (mMaxCapacity - 1))
			{
				mPassengerList[mMaxCapacity - 1] = nullptr;
				break;
			}

			mPassengerList[cnt] = mPassengerList[cnt + 1];
		}

		mSize--;

		return true;
	}

	const Person* Vehicle::GetPassenger(unsigned int i) const
	{
		if ((mSize == 0) || (i > mSize) || (i >= mMaxCapacity))
		{
			return nullptr;
		}

		return mPassengerList[i];
	}

	unsigned int Vehicle::GetPassengersCount() const
	{
		return mSize;
	}

	unsigned int Vehicle::GetMaxPassengersCount() const
	{
		return mMaxCapacity;
	}

	void Vehicle::SetPassengerList()
	{
		if (mSize == 0)
		{
			return;
		}

		for (unsigned int i = 0; i < mSize; i++)
		{
			mPassengerList[i] = nullptr;
		}

		SetPassengerCount(0);
	}

	void Vehicle::SetPassengerCount(unsigned int count)
	{
		mSize = count;
	}

	const Person** Vehicle::GetPassengersArray(void) const
	{
		if (mPassengerList != nullptr)
		{
			return mPassengerList;
		}

		return nullptr;
	}

	/* Copy Constructor */
	void Vehicle::CopyDefaultMember(const Vehicle& other)
	{
		const Person** tempPassengers = other.mPassengerList;

		for (unsigned int i = 0; i < other.GetPassengersCount(); i++)
		{
			mPassengerList[i] = tempPassengers[i];
		}

		mSize = other.mSize;
	}

	/* Assignment operator */
	void Vehicle::AssignDefaultMember(const Vehicle& other)
	{
		const Person** tempPassengers = other.mPassengerList;

		SetPassengerCount(0);
		mMaxCapacity = other.mMaxCapacity;
		
		if (mPassengerList != nullptr)
		{
			for (unsigned int i = 0; i < mSize; i++)
			{
				delete mPassengerList[i];
			}

			delete mPassengerList;
		}
		
		mPassengerList = new const Person * [mMaxCapacity];

		for (unsigned int i = 0; i < other.GetPassengersCount(); i++)
		{
			mPassengerList[i] = tempPassengers[i];
		}

		mSize = other.mSize;
	}
}