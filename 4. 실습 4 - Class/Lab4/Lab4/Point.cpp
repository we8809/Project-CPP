#include "Point.h"

namespace lab4
{
	Point::Point()
		: mX(0.f)
		, mY(0.f)
	{
			
	}

	Point::Point(float x, float y)
		: mX(x)
		, mY(y)
	{

	}

	/* Copy Constructor */
	Point::Point(const Point& other)
		: mX(other.mX)
		, mY(other.mY)
	{
		
	}

	/* Assignment Constructor */
	Point& Point::operator=(const Point& other)
	{
		if (this == &other)
		{
			return *this;
		}

		mX = other.mX;
		mY = other.mY;

		return *this;
	}

	Point::~Point()
	{

	}

	Point Point::operator+(const Point& other) const
	{
		float tempX = mX + other.mX;
		float tempY = mY + other.mY;

		return Point(tempX, tempY);
	}

	Point Point::operator-(const Point& other) const
	{
		float tempX = mX - other.mX;
		float tempY = mY - other.mY;

		return Point(tempX, tempY);
	}

	/*
		두 점의 내적(dot product)을 수행한다.
	*/
	float Point::Dot(const Point& other) const
	{
		return (mX * other.mX) + (mY * other.mY);
	}

	Point Point::operator*(float operand) const
	{
		float tempX = mX * operand;
		float tempY = mY * operand;

		return Point(tempX, tempY);
	}

	// friend 전역함수 정의
	Point operator*(float operand, const Point& other)
	{
		float tempX = other.mX * operand;
		float tempY = other.mY * operand;

		return Point(tempX, tempY);
	}

	float Point::GetX() const
	{
		return mX;
	}

	float Point::GetY() const
	{
		return mY;
	}
}