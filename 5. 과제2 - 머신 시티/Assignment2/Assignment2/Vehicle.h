#pragma once

#include "Person.h"

namespace assignment2
{
	class Vehicle
	{
	public:
		Vehicle(unsigned int maxPassengersCount);
		virtual ~Vehicle();

		virtual unsigned int GetMaxSpeed() const = 0;
		virtual bool Move(unsigned int count) const = 0;

		bool AddPassenger(const Person* person);
		bool RemovePassenger(unsigned int i);
		const Person* GetPassenger(unsigned int i) const;
		unsigned int GetPassengersCount() const;
		unsigned int GetMaxPassengersCount() const;

		void SetPassengerList();
		void SetPassengerCount(unsigned int count);

		const Person** GetPassengersArray(void) const;

		/* Copy Constructor */
		void CopyDefaultMember(const Vehicle& other);
		/* Assignment operator */
		void AssignDefaultMember(const Vehicle& other);

	private:
		unsigned int mSize;
		unsigned int mMaxCapacity;
		const Person** mPassengerList;
	};
}