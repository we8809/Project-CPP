#pragma once

#include "Lawn.h"
#include "IFenceable.h"

namespace lab5
{
	class RectangleLawn : public Lawn, public IFenceable
	{
	public:
		RectangleLawn(unsigned int width, unsigned int height);
		virtual ~RectangleLawn() = default;

		unsigned int GetArea() const;
		unsigned int GetMinimumFencesCount() const;
		unsigned int GetFencePrice(eFenceType fenceType) const;

		unsigned int GetCircumference() const;

	private:
		unsigned int mWidth;
		unsigned int mHeight;
		unsigned int mCircumference;
	};
}