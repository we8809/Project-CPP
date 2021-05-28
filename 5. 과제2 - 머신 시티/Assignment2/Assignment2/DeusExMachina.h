#pragma once

#include "Vehicle.h"

namespace assignment2
{
	class DeusExMachina final
	{
		const unsigned int MACHINA_MAX_SIZE = 10;
		static unsigned int mMove;

	public:
		~DeusExMachina();

		static DeusExMachina* GetInstance();
		void Travel() const;
		bool AddVehicle(Vehicle* vehicle);
		bool RemoveVehicle(unsigned int i);
		const Vehicle* GetFurthestTravelled() const;

		bool operator==(const DeusExMachina& other);

	private:
		DeusExMachina();

		static DeusExMachina* mInstance;
		Vehicle** mVehicleList;
		unsigned int mSize;
	};
}