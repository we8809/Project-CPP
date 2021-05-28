#include "DeusExMachina.h"

namespace assignment2
{
	DeusExMachina* DeusExMachina::mInstance = nullptr;

	DeusExMachina::DeusExMachina()
		: mVehicles()
		, mSize(0)
	{
	}

	DeusExMachina::~DeusExMachina()
	{
		for (unsigned i = 0; i < mSize; i++)
		{
			delete mVehicles[i];
		}
	}

	DeusExMachina* DeusExMachina::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new DeusExMachina();
		}
		return mInstance;
	}

	void DeusExMachina::Travel() const
	{
		for (unsigned i = 0; i < mSize; i++)
		{
			mVehicles[i]->Travel();
		}	
	}

	bool DeusExMachina::AddVehicle(Vehicle* vehicle)
	{
		if (mSize == CAPACITY)
		{
			return false;
		}

		if (vehicle == nullptr)
		{
			return false;
		}

		mVehicles[mSize] = vehicle;
		++mSize;

		return true;
	}

	bool DeusExMachina::RemoveVehicle(unsigned int i)
	{
		if (i >= mSize)
		{
			return false;
		}

		if (mSize == 0)
		{
			return false;
		}

		delete mVehicles[i];
		--mSize;

		for (; i < mSize; i++)
		{
			mVehicles[i] = mVehicles[i + 1];
		}

		return true;
	}

	const Vehicle* DeusExMachina::GetFurthestTravelled() const
	{
		if (mSize == 0)
		{
			return nullptr;
		}

		unsigned int furthestTravelledIdx = 0;

		for (unsigned i = 1; i < mSize; i++)
		{
			if (mVehicles[i]->GetTravelledDistance() > mVehicles[furthestTravelledIdx]->GetTravelledDistance())
			{
				furthestTravelledIdx = i;
			}
		}

		return mVehicles[furthestTravelledIdx];
	}
	Vehicle* DeusExMachina::GetVehicle(unsigned i) const
	{
		if (i >= mSize)
		{
			return nullptr;
		}

		return mVehicles[i];
	}
}
