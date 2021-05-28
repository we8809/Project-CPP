#pragma once

#include "IDrivable.h"
#include "Vehicle.h"
#include "Trailer.h"

namespace assignment2
{
	class Trailer;

	class Sedan : public Vehicle, public IDrivable
	{
		const unsigned int TRAILER_CNT = 10;
	public:
		Sedan();
		Sedan(const Sedan& other);
		Sedan& operator=(const Sedan& other);
		~Sedan();

		bool AddTrailer(const Trailer* trailer);
		bool RemoveTrailer();

		unsigned int GetMaxSpeed() const;
		unsigned int GetDriveSpeed() const;

		bool Move(unsigned int count) const;
		
	private:
		Trailer* mTrailer;
	};
}