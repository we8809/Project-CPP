#include "RectangleLawn.h"
#include <iostream>

namespace lab5
{
	RectangleLawn::RectangleLawn(unsigned int width, unsigned int height)
		: Lawn()
		, mWidth(width)
		, mHeight(height)
		, mCircumference(2 * (width + height))
	{
		/* ÀÜµð¹çÀÇ ¸éÀû ¼ÂÆÃ */
		SetSquareMeasure(mWidth * mHeight);
	}

	unsigned int RectangleLawn::GetArea() const
	{
		// m2 ¹ÝÈ¯
		return GetSquareMeasure();
	}

	unsigned int RectangleLawn::GetMinimumFencesCount() const
	{
		double minimumFencesCount = GetCircumference() / 0.25;
		unsigned int intVal = static_cast<unsigned int>(minimumFencesCount);

		if (minimumFencesCount == static_cast<double>(intVal))
		{
			return intVal;
		}

		return intVal + 1;
	}

	unsigned int RectangleLawn::GetFencePrice(eFenceType fenceType) const
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

	unsigned int RectangleLawn::GetCircumference() const
	{
		return mCircumference;
	}
}