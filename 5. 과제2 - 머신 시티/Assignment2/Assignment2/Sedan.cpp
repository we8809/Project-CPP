#include "Sedan.h"

namespace assignment2
{
	Sedan::Sedan()
		: Vehicle(4)
		, mTrailer(nullptr)
	{

	}

	Sedan::~Sedan()
	{
		delete mTrailer;
	}

	Sedan::Sedan(const Sedan& other)
		: Vehicle(4)
	{
		if (other.GetPassengersCount() == 0)
		{
			mTrailer = nullptr;
			return;
		}

		CopyDefaultMember(other);

		if (other.mTrailer != nullptr)
		{
			mTrailer = new Trailer(other.mTrailer->GetWeight());
			return;
		}

		mTrailer = nullptr;
	}

	Sedan& Sedan::operator=(const Sedan& other)
	{
		if (this == &other)
		{
			return *this;
		}

		if (other.mTrailer == nullptr)
		{
			delete mTrailer;
			mTrailer = nullptr;

			return *this;
		}

		AssignDefaultMember(other);

		delete mTrailer;
		mTrailer = new Trailer(other.mTrailer->GetWeight());

		return *this;
	}

	bool Sedan::AddTrailer(const Trailer* trailer)
	{
		if (mTrailer != nullptr)
		{
			return false;
		}

		mTrailer = new Trailer(trailer->GetWeight());
		delete trailer;

		return true;
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

	unsigned int Sedan::GetMaxSpeed() const
	{
		return GetDriveSpeed();
	}

	unsigned int Sedan::GetDriveSpeed() const
	{
		float x = 0.0f;						// Total weight
		float driveSpeed = 0.0f;

		if (mTrailer != nullptr)
		{
			x += static_cast<float>(mTrailer->GetWeight());
		}

		for (unsigned int i = 0; i < GetPassengersCount(); i++)
		{
			x += static_cast<float>(GetPassenger(i)->GetWeight());
		}

		if (x <= 80.f)
			driveSpeed = 480.0f;
		else if (x > 80.f)
			driveSpeed = 458.f;
		else if (x > 160.f)
			driveSpeed = 400.f;
		else if (x > 260.f)
			driveSpeed = 380.f;
		else if (x > 350.f)
			driveSpeed = 300.f;

		return static_cast<unsigned int>(driveSpeed + 0.5f);
	}

	bool Sedan::Move(unsigned int count) const
	{
		if (count == 1)
		{
			return true;
		}
		
		if (mTrailer != nullptr)
		{
			if ((count % 6) == 0)
			{
				return false;
			}

			return true;
		}
		else
		{
			
		}
	}
}