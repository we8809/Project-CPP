#include "EquilateralTriangleLawn.h"
#include <cmath>

namespace lab5
{
	EquilateralTriangleLawn::EquilateralTriangleLawn(unsigned int side)
		: Lawn()
		, mSide(side)
		, mCircumference(side * 3)
	{
		double squareMeasure = (sqrt(3) * pow(mSide, 2)) / 4.0 + 0.5;

		SetSquareMeasure(static_cast<unsigned int>(squareMeasure));
	}

	unsigned int EquilateralTriangleLawn::GetArea() const
	{
		return GetSquareMeasure();
	}

	unsigned int EquilateralTriangleLawn::GetMinimumFencesCount() const
	{
		double minimumFencesCount = GetCircumference() / 0.25;
		unsigned int intVal = static_cast<unsigned int>(minimumFencesCount);

		if (minimumFencesCount == static_cast<double>(intVal))
		{
			return intVal;
		}

		return intVal + 1;
	}

	unsigned int EquilateralTriangleLawn::GetFencePrice(eFenceType fenceType) const
	{
		double fencePrice = 0.0;

		switch (fenceType)
		{
		case RED_CEDAR:
			fencePrice = GetCircumference() * 6.0;
			break;

		case SPRUCE:
			fencePrice = GetCircumference() * 7.0;
			break;

		default:
			break;
		}

		return static_cast<unsigned int>(fencePrice);
	}

	unsigned int EquilateralTriangleLawn::GetCircumference() const
	{
		return mCircumference;
	}
}