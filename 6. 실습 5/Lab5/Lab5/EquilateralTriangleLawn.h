#pragma once

/* Á¤»ï°¢Çü */
#include "IFenceable.h"
#include "Lawn.h"

namespace lab5
{
	class EquilateralTriangleLawn : public Lawn, public IFenceable
	{
	public:
		EquilateralTriangleLawn(unsigned int side);

		unsigned int GetArea() const;

		unsigned int GetMinimumFencesCount() const;
		unsigned int GetFencePrice(eFenceType fenceType) const;

		unsigned int GetCircumference() const;

	private:
		unsigned int mSide;
		unsigned int mCircumference;
	};
}