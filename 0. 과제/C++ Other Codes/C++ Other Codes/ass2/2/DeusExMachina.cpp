#include "DeusExMachina.h"

namespace assignment2
{
	DeusExMachina* DeusExMachina::mInstance = nullptr;
	unsigned int DeusExMachina::mMaxVehiclesCount = 10;
	bool DeusExMachina::mbHasTravelled = false;

	DeusExMachina::DeusExMachina()
		: mVehicles(new Vehicle * [mMaxVehiclesCount])
		, mVehiclesCount(0)
	{
	}

	DeusExMachina::~DeusExMachina()
	{
		unsigned int count = mVehiclesCount;
		for (size_t i = 0; i < count; i++)
		{
			RemoveVehicle(0);
		}
		delete[] mVehicles;
	}

	DeusExMachina* DeusExMachina::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new DeusExMachina();
			return mInstance;
		}
		return mInstance;
	}

	void DeusExMachina::Travel() const
	{
		if (mVehiclesCount == 0)
		{
			return;
		}
		for (size_t i = 0; i < mVehiclesCount; i++)
		{
			mVehicles[i]->Travel();
		}
		mbHasTravelled = true;
	}

	bool DeusExMachina::AddVehicle(Vehicle* vehicle)
	{
		vehicle->SetTravelCount(0);
		vehicle->SetTravelDistance(0);
		if (mVehiclesCount == mMaxVehiclesCount || vehicle == nullptr)
		{
			return false;
		}
		for (size_t i = 0; i < mVehiclesCount; i++)
		{
			if (vehicle == mVehicles[i])
			{
				return false;
			}
		}
		mVehicles[mVehiclesCount] = vehicle;
		mVehiclesCount++;
		return true;
	}

	bool DeusExMachina::RemoveVehicle(unsigned int i)
	{
		unsigned int index = i;
		if (index >= mVehiclesCount)
		{
			return false;
		}
		delete mVehicles[index];
		mVehicles[index] = nullptr;
		for (size_t i = index; i < mVehiclesCount; i++)
		{
			mVehicles[i] = mVehicles[i + 1];
		}
		mVehiclesCount--;
		return true;
	}

	const Vehicle* DeusExMachina::GetFurthestTravelled() const
	{
		if (mVehiclesCount == 0)
		{
			return NULL;
		}
		if (mbHasTravelled == false)
		{
			return mVehicles[0];
		}
		Vehicle* result = mVehicles[0];
		int max = mVehicles[0]->GetTravelDistance();
		int temp = 0;
		for (size_t i = 0; i < mVehiclesCount; i++)
		{
			temp = mVehicles[i]->GetTravelDistance();
			if (temp > max)
			{
				result = mVehicles[i];
				max = temp;
			}
		}
		return result;
	}

	Vehicle* DeusExMachina::GetVehicle(unsigned int i)
	{
		if (i >= mVehiclesCount)
		{
			return nullptr;
		}
		return mVehicles[i];
	}

}
