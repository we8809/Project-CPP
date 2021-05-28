#include "Vehicle.h"

namespace assignment2
{
	Vehicle::Vehicle(unsigned int maxPassengersCount)
		: mMaxPassengersCount(maxPassengersCount)
		, mPassengers(nullptr)
		, mPassengersCount(0)
		, mPassengersWeight(0)
		, mTravelCount(0)
		, mTravelDistance(0)
	{
		mPassengers = new const Person * [mMaxPassengersCount];
	}

	Vehicle::Vehicle(const Vehicle& rhs)
		: Vehicle(rhs.GetMaxPassengersCount())
	{
		mTravelCount = rhs.mTravelCount;
		mTravelDistance = rhs.mTravelDistance;
		for (size_t i = 0; i < rhs.mPassengersCount; i++)
		{
			const Person* p = new const Person(rhs.mPassengers[i]->GetName().c_str(), rhs.mPassengers[i]->GetWeight());
			AddPassenger(p);
		}
	}

	Vehicle::~Vehicle()
	{
		unsigned int count = mPassengersCount;
		for (size_t i = 0; i < count; i++)
		{
			RemovePassenger(0);
		}
		delete[] mPassengers;
	}

	Vehicle& Vehicle::operator=(const Vehicle& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}
		mTravelCount = rhs.mTravelCount;
		mTravelDistance = rhs.mTravelDistance;
		unsigned int count = mPassengersCount;
		for (size_t i = 0; i < count; i++)
		{
			RemovePassenger(0);
		}
		for (size_t i = 0; i < rhs.mPassengersCount; i++)
		{
			const Person* p = new const Person(rhs.mPassengers[i]->GetName().c_str(), rhs.mPassengers[i]->GetWeight());
			AddPassenger(p);
		}
		

		return *this;
	}

	bool Vehicle::AddPassenger(const Person* person)
	{
		if (mPassengersCount >= mMaxPassengersCount || person == nullptr)
		{
			return false;
		}
		for (size_t i = 0; i < mPassengersCount; i++)
		{
			if (mPassengers[i] == person)
			{
				return false;
			}
		}
		mPassengers[mPassengersCount] = person;
		mPassengersCount++;
		mPassengersWeight += person->GetWeight();

		return true;
	}

	bool Vehicle::RemovePassenger(unsigned int i)
	{
		unsigned int index = i;

		if (index >= mPassengersCount)
		{
			return false;
		}
		mPassengersWeight -= mPassengers[i]->GetWeight();

		delete mPassengers[index];
		mPassengers[index] = nullptr;

		for (index; index < mPassengersCount; index++)
		{
			if (index == mMaxPassengersCount)
			{
				mPassengers[index] = nullptr;
				break;
			}
			mPassengers[index] = mPassengers[index + 1];
		}

		mPassengersCount--;

		return true;
	}

	void Vehicle::SetTravelCount(unsigned int num)
	{
		mTravelCount = num;
	}

	void Vehicle::SetTravelDistance(unsigned int num)
	{
		mTravelDistance = num;
	}

	unsigned int Vehicle::GetPassengersCount() const
	{
		return mPassengersCount;
	}

	unsigned int Vehicle::GetMaxPassengersCount() const
	{
		return mMaxPassengersCount;
	}

	int Vehicle::GetTravelDistance() const
	{
		return static_cast<int>(mTravelDistance);
	}

	const Person* Vehicle::GetPassenger(unsigned int i) const
	{
		if (i >= mPassengersCount)
		{
			return NULL;
		}
		return mPassengers[i];
	}
}
