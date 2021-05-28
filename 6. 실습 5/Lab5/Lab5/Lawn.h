#pragma once

#include "eGrassType.h"

namespace lab5
{
	class Lawn
	{
	public:
		Lawn();
		virtual ~Lawn();

		virtual unsigned int GetArea() const = 0;

		unsigned int GetGrassPrice(eGrassType grassType) const;
		unsigned int GetMinimumSodRollsCount() const;

		unsigned int GetSquareMeasure() const;
		void SetSquareMeasure(unsigned int squareMeasure);

	private:
		unsigned int mSquareMeasure;						// ÀÜµğ¹ç ¸éÀû.
	};
}