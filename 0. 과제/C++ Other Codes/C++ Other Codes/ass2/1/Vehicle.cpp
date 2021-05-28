#include <cassert>
#include "Vehicle.h"


namespace assignment2
{
	Vehicle::Vehicle(unsigned int maxPassengersCount)
		: mTravelCount(0)
		, mMaxPassengersCount(maxPassengersCount)
		, mPassengersCount(0)
	{
		mPassengers = new const Person* [mMaxPassengersCount];
	}

	Vehicle::Vehicle(const Vehicle& other)
		: mTravelCount(other.mTravelCount)
		, mMaxPassengersCount(other.mMaxPassengersCount)
		, mPassengersCount(other.mPassengersCount)
	{
		mPassengers = new const Person* [mMaxPassengersCount];
		
		assert(mMaxPassengersCount >= mPassengersCount);
		for (unsigned i = 0; i < mPassengersCount; i++)
		{
			const char* name = other.mPassengers[i]->GetName().c_str();
			const unsigned weight = other.mPassengers[i]->GetWeight();
			mPassengers[i] = new Person(name, weight);
		}
	}

	Vehicle& Vehicle::operator=(const Vehicle& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		for (unsigned i = 0; i < mPassengersCount; i++)
		{
			delete mPassengers[i];
		}
		delete[] mPassengers;

		mMaxPassengersCount = rhs.GetMaxPassengersCount();
		mPassengersCount = rhs.GetPassengersCount();
		mPassengers = new const Person * [mMaxPassengersCount];

		assert(mMaxPassengersCount >= mPassengersCount);
		for (unsigned i = 0; i < mPassengersCount; i++)
		{
			const char* name = rhs.mPassengers[i]->GetName().c_str();
			const unsigned weight = rhs.mPassengers[i]->GetWeight();
			mPassengers[i] = new Person(name, weight);
		}

		return *this;
	}

	Vehicle::~Vehicle()
	{
		for (unsigned i = 0; i < mPassengersCount; i++)
		{
			delete mPassengers[i];
		}
		delete[] mPassengers;
	}

	bool Vehicle::AddPassenger(const Person* person)
	{
		if (mPassengersCount == mMaxPassengersCount)
		{
			return false;
		}

		if (person == nullptr)
		{
			return false;
		}

		for (unsigned i = 0; i < mPassengersCount; i++)
		{
			if (mPassengers[i] == person)
			{
				return false;
			}
		}

		mPassengers[mPassengersCount] = person;
		++mPassengersCount;

		return true;
	}

	bool Vehicle::RemovePassenger(unsigned int i)
	{
		if (i >= mPassengersCount)
		{
			return false;
		}

		delete mPassengers[i];
		--mPassengersCount;

		for (; i < mPassengersCount; i++)
		{
			mPassengers[i] = mPassengers[i + 1];
		}
		mPassengers[i] = nullptr;
		
		return true;
	}

	void Vehicle::TransferPassengers(Vehicle& dest)
	{
		for (unsigned i = 0; i < mPassengersCount; i++)
		{
			dest.mPassengers[dest.mPassengersCount] = mPassengers[i];
			++dest.mPassengersCount;

			mPassengers[i] = nullptr;
		}

		mPassengersCount = 0;
	}

	unsigned int Vehicle::GetPassengersCount() const
	{
		return mPassengersCount;
	}

	unsigned int Vehicle::GetMaxPassengersCount() const
	{
		return mMaxPassengersCount;
	}

	unsigned Vehicle::GetPassengersTotalWeight() const
	{
		unsigned totalWeight = 0;
		for (unsigned i = 0; i < mPassengersCount; i++)
		{
			totalWeight += mPassengers[i]->GetWeight();
		}
		return totalWeight;
	}

	void Vehicle::Travel()
	{
		++mTravelCount;
	}

	const Person* Vehicle::GetPassenger(unsigned int i) const
	{
		if (i >= mPassengersCount)
		{
			return nullptr;
		}
		return mPassengers[i];
	}
}
