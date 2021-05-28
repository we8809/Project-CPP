#include "Sedan.h"

namespace assignment2
{
	Sedan::Sedan()
		: Vehicle(4)
		, mConnectedTrailler(nullptr)
	{
	}

	Sedan::Sedan(const Sedan& rhs)
		: Vehicle(rhs.GetMaxPassengersCount())
		, mConnectedTrailler(nullptr)
	{
		mTravelCount = rhs.mTravelCount;
		mTravelDistance = rhs.mTravelDistance;
		for (size_t i = 0; i < rhs.mPassengersCount; i++)
		{
			const Person* p = new const Person(rhs.mPassengers[i]->GetName().c_str(), rhs.mPassengers[i]->GetWeight());
			AddPassenger(p);
		}
		if (rhs.mConnectedTrailler != nullptr)
		{
			Trailer* t = new Trailer(rhs.mConnectedTrailler->GetWeight());
			mConnectedTrailler = t;
		}
	}

	Sedan::~Sedan()
	{
		delete mConnectedTrailler;
	}

	Sedan& Sedan::operator=(const Sedan& rhs)
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
		if (mConnectedTrailler != nullptr)
		{
			delete mConnectedTrailler;
			mConnectedTrailler = nullptr;
		}
		if (rhs.mConnectedTrailler != nullptr)
		{
			Trailer* t = new Trailer(rhs.mConnectedTrailler->GetWeight());
			mConnectedTrailler = t;
		}

		return *this;
	}

	bool Sedan::AddTrailer(const Trailer* trailer)
	{
		if (mConnectedTrailler != nullptr || trailer == nullptr)
		{
			return false;
		}
		mConnectedTrailler = trailer;
		return true;
	}

	bool Sedan::RemoveTrailer()
	{
		if (mConnectedTrailler == nullptr)
		{
			return false;
		}
		delete mConnectedTrailler;
		mConnectedTrailler = nullptr;
		return true;
	}
	const Trailer* Sedan::GetTrailler() const
	{
		if (mConnectedTrailler != nullptr)
		{
			return mConnectedTrailler;
		}
		return nullptr;
	}
	unsigned int Sedan::GetMaxSpeed() const
	{
		return GetDriveSpeed();
	}
	unsigned int Sedan::GetDriveSpeed() const
	{
		unsigned int totalWeight = mPassengersWeight;
		if (mConnectedTrailler != nullptr)
		{
			totalWeight += mConnectedTrailler->GetWeight();
		}
		if (totalWeight > 350)
		{
			return 300;
		}
		else if (totalWeight > 260)
		{
			return 380;
		}
		else if (totalWeight > 160)
		{
			return 400;
		}
		else if (totalWeight > 80)
		{
			return 458;
		}
		else if (totalWeight <= 80)
		{
			return 480;
		}

		return 0;
	}
	unsigned int Sedan::Travel()
	{
		mTravelCount++;
		if (mConnectedTrailler == nullptr)
		{
			unsigned int travelCycle = 6;
			if (mTravelCount % travelCycle == 0)
			{
				return mTravelDistance;
			}
			mTravelDistance += GetMaxSpeed();
			return mTravelDistance;
		}
		else
		{
			unsigned int travelCycle = 7;
			if (mTravelCount % travelCycle == 6 || mTravelCount % travelCycle == 0)
			{
				return mTravelDistance;
			}
			mTravelDistance += GetMaxSpeed();
			return mTravelDistance;
		}
	}
}
