#include "CircleLawn.h"
#include <cmath>

namespace lab5
{
	CircleLawn::CircleLawn(unsigned int round)
		: Lawn()
		, mRound(round)
	{
		double pi = 3.14;
		double squareMeasure = pow(round, 2) * pi + 0.5;

		SetSquareMeasure(static_cast<unsigned int>(squareMeasure));
	}

	unsigned int CircleLawn::GetArea() const
	{
		return GetSquareMeasure();
	}
}