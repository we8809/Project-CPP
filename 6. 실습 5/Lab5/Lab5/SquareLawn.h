#pragma once

#include "IFenceable.h"
#include "RectangleLawn.h"

namespace lab5
{
	class SquareLawn : public RectangleLawn
	{
	public:
		SquareLawn(unsigned int width);
		virtual ~SquareLawn() = default;

	};
}