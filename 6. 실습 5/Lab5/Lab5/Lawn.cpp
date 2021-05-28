#include "Lawn.h"

namespace lab5
{
	Lawn::Lawn()
		: mSquareMeasure(0)
	{
	}

	Lawn::~Lawn()
	{
	}

	unsigned int Lawn::GetGrassPrice(eGrassType grassType) const
	{
		unsigned int squareMeasure = GetSquareMeasure();
		double grassPrice = 0.0;

		switch (grassType)
		{
		case BERMUDA:
			grassPrice = squareMeasure * 8.0;
			break;

		case BAHIA:
			grassPrice = squareMeasure * 5.0;
			break;

		case BENTGRASS:
			grassPrice = squareMeasure * 3.0;
			break;

		case PERENNIAL_RYEGRASS:
			grassPrice = squareMeasure * 2.5 + 0.5;
			break;

		case ST_AUGUSTINE:
			grassPrice = squareMeasure * 4.5 + 0.5;

		default:
			break;
		}

		return static_cast<unsigned int>(grassPrice);
	}

	unsigned int Lawn::GetMinimumSodRollsCount() const
	{
		unsigned int squareMeasure = GetSquareMeasure();
		double minimumSodRollsCount = squareMeasure / 0.3;
		unsigned int intVal = static_cast<unsigned int>(minimumSodRollsCount);

		if (minimumSodRollsCount == static_cast<double>(intVal))
		{
			return intVal;
		}

		return intVal + 1;
	}

	unsigned int Lawn::GetSquareMeasure() const
	{
		return mSquareMeasure;
	}

	void Lawn::SetSquareMeasure(unsigned int squareMeasure)
	{
		mSquareMeasure = squareMeasure;
	}
}