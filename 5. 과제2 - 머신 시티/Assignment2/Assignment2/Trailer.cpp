#include "Trailer.h"

namespace assignment2
{
	Trailer::Trailer()
		: mWeight(0)
	{
		
	}

	Trailer::Trailer(unsigned int weight)
		: mWeight(weight)
	{

	}

	Trailer::Trailer(const Trailer& other)
		: mWeight(other.mWeight)
	{

	}

	Trailer& Trailer::operator=(const Trailer& other)
	{
		if (this == &other)
		{
			return *this;
		}

		mWeight = other.mWeight;

		return *this;
	}

	Trailer::~Trailer()
	{

	}

	unsigned int Trailer::GetWeight() const
	{
		return mWeight;
	}
}