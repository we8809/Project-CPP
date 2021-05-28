#include "DeusExMachina.h"
#include <iostream>

namespace assignment2
{
	DeusExMachina* DeusExMachina::mInstance = nullptr;
	unsigned int DeusExMachina::mMove = 0;

	DeusExMachina::DeusExMachina()
		: mSize(0)
	{
		mVehicleList = new Vehicle * [MACHINA_MAX_SIZE];
	}

	DeusExMachina::~DeusExMachina()
	{
		if (DeusExMachina::mInstance != nullptr)
		{
			for (unsigned int i = 0; i < mSize; i++)
			{
				delete mVehicleList[i];
			}

			delete[] mVehicleList;
		}
	}

	/* Single Pattern ! */
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
		bool isMove = false;
		mMove++;

		for (unsigned int i = 0; i < mSize; i++)
		{
			isMove = mVehicleList[i]->Move(mMove);
			std::cout << isMove << " " << std::endl;
		}
	}

	bool DeusExMachina::AddVehicle(Vehicle* vehicle)
	{
		if (mSize >= MACHINA_MAX_SIZE)
		{
			return false;
		}

		mVehicleList[mSize] = vehicle;
		mSize++;

		return true;
	}

	bool DeusExMachina::RemoveVehicle(unsigned int i)
	{
		if ((i >= mSize) || (i >= MACHINA_MAX_SIZE))
		{
			return false;
		}

		for (unsigned int cnt = 0; cnt < mSize; cnt++)
		{
			if (cnt >= MACHINA_MAX_SIZE - 1)
			{
				mVehicleList[cnt] = nullptr;
				break;
			}

			mVehicleList[cnt] = mVehicleList[cnt + 1];
		}
		
		mSize--;

		return true;
	}

	const Vehicle* DeusExMachina::GetFurthestTravelled() const
	{
		return NULL;
	}

	bool DeusExMachina::operator==(const DeusExMachina& other)
	{
		if (this == &other)
		{
			return true;
		}
		
		return false;
	}
}