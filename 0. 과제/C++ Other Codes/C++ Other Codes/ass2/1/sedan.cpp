#include "Sedan.h"
#include "Trailer.h"

namespace assignment2
{
	Sedan::Sedan()
		: Vehicle(4)
		, mTrailer(nullptr)
	{
	}

	Sedan::Sedan(const Sedan& other)
		: Vehicle(other)
		, mTrailer(nullptr)
	{
		if (other.GetTrailer() != nullptr)
		{
			mTrailer = new Trailer(other.GetTrailer()->GetWeight());
		}
	}

	Sedan& Sedan::operator=(const Sedan& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		delete mTrailer;

		if (rhs.GetTrailer() == nullptr)
		{
			mTrailer = nullptr;
		}
		else
		{
			mTrailer = new Trailer(rhs.GetTrailer()->GetWeight());
		}

		Vehicle::operator=(rhs);

		return *this;
	}

	Sedan::~Sedan()
	{
		delete mTrailer;
	}

	bool Sedan::AddTrailer(const Trailer* trailer)
	{
		if (mTrailer == nullptr)
		{
			mTrailer = trailer;
			return true;
		}
		return false;
	}

	bool Sedan::RemoveTrailer()
	{
		if (mTrailer == nullptr)
		{
			return false;
		}

		delete mTrailer;
		mTrailer = nullptr;

		return true;
	}

	const Trailer* Sedan::GetTrailer() const
	{
		return mTrailer;
	}

	unsigned Sedan::GetDriveSpeed() const
	{
		const unsigned PASSENGERS_TOTAL_WEIGHT = GetPassengersTotalWeight();
		const unsigned TOTAL_WEIGHT_WITH_TRAILER = (mTrailer != nullptr) ? PASSENGERS_TOTAL_WEIGHT + mTrailer->GetWeight() : PASSENGERS_TOTAL_WEIGHT;

		if (TOTAL_WEIGHT_WITH_TRAILER <= 80)
		{
			return 480;
		}

		if (TOTAL_WEIGHT_WITH_TRAILER <= 160)
		{
			return 458;
		}

		if (TOTAL_WEIGHT_WITH_TRAILER <= 260)
		{
			return 400;
		}

		if (TOTAL_WEIGHT_WITH_TRAILER <= 350)
		{
			return 380;
		}

		return 300;
	}

	unsigned Sedan::GetMaxSpeed() const
	{
		return GetDriveSpeed();
	}

	unsigned Sedan::GetTravelledDistance() const
	{
		unsigned distance = 0;
		for (unsigned i = 1; i <= mTravelCount; i++)
		{
			if (mTrailer == nullptr)
			{
				if (i % 6 != 0)
				{
					distance += GetMaxSpeed();
				}
			}

			else
			{
				if (i % 7 != 0 && i % 7 != 6)
				{
					distance += GetMaxSpeed();
				}
			}
		}

		return distance;
	}
}
