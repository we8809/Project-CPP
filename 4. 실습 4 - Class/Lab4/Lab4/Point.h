#pragma once

namespace lab4
{
	class Point
	{
		friend Point operator*(float operand, const Point& other);

	public:
		/* Default Constructor */
		Point();
		Point(float x, float y);
		/* Copy Constructor */
		Point(const Point& other);
		/* Assignment Constructor */
		Point& operator=(const Point& other);
		~Point();

		Point operator+(const Point& other) const;
		Point operator-(const Point& other) const;
		float Dot(const Point& other) const;
		Point operator*(float operand) const;

		float GetX() const;
		float GetY() const;

	private:
		float mX;
		float mY;
	};
}