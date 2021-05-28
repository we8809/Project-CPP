#include <cstring>
#include <cmath>	
#include "PolyLine.h"

namespace lab4
{
	PolyLine::PolyLine()
		: mListCapacity(10)
		, mListCount(0)
	{
		mPointList = new Point[mListCapacity];
	}

	PolyLine::PolyLine(const PolyLine& other)
		: mListCapacity(other.mListCapacity)
		, mListCount(other.mListCount)
	{
		if (mListCount == 0)
		{
			mPointList = new Point[mListCapacity];
			return;
		}

		mPointList = new Point[mListCapacity + 1];

		for (unsigned int i = 0; i < mListCount; i++)
		{
			mPointList[i] = other.mPointList[i];
		}
	}
	
	PolyLine& PolyLine::operator=(const PolyLine& other)
	{
		if (this == &other)
		{
			return *this;
		}

		mListCapacity = other.mListCapacity;
		mListCount = other.mListCount;
		
		if (mListCount == 0)
		{
			return *this;
		}

		for (unsigned int i = 0; i < mListCount; i++)
		{
			mPointList[i] = other.mPointList[i];
		}
		for (unsigned int i = mListCount; i < mListCapacity; i++)
		{
			mPointList[i] = Point(0.f, 0.f);
		}

		return *this;
	}
	

	// Destructor
	PolyLine::~PolyLine()
	{
		delete[] mPointList;
	}

	/*
		- 점 하나를 PolyLine 개체에 추가한다.
		- Signature가 다른 두 개의 AddPoint() 메서드가 있더는 점에 유의. 하나는 인자로 float 값 두 개를, 다른 하나는 상수 포인터(const pointer)를 받는다.
		- 점이 PolyLine에 추가되면 true를 반환한다. 추가된 점의 라이프사이클(수명)은 PolyLine이 관리하지만, PolyLine 개체를 소멸시키거나 
		RemovePoint() 같은 메서드를 호출하여 점을 소멸시키지 않는 한 여전히 클래스 밖에서도 점을 가리키는 포인터를 사용할 수 있다.
		만약 PolyLine에 점을 추가할 수 없었다면 false를 반환한다.
	*/
	bool PolyLine::AddPoint(float x, float y)
	{
		if (mListCount >= mListCapacity)
		{
			return false;
		}

		mPointList[mListCount] = Point(x, y);
		mListCount++;

		return true;
	}

	bool PolyLine::AddPoint(const Point* point)
	{
		if (point == nullptr)
		{
			return false;
		}
		if (mListCount >= mListCapacity)
		{
			return false;
		}

		mPointList[mListCount] = *point;
		mListCount++;

		delete point;

		return true;
	}

	bool PolyLine::RemovePoint(unsigned int i)
	{
		if (i >= mListCapacity || i >= mListCount)
		{
			return false;
		}

		--mListCount;

		for (unsigned int j = i; j < mListCount ; j++)
		{
			if (j == (mListCapacity - 1))
			{
				mPointList[j] = Point(0.f, 0.f);
				break;
			}
			mPointList[j] = mPointList[j+1];
		}
		
		return true;
	}

	bool PolyLine::TryGetMinBoundingRectangle(Point* outMin, Point* outMax) const
	{
		if (mListCount == 0 || mListCount < 4)
		{
			return false;
		}

		float minX = mPointList[0].GetX(), minY = mPointList[0].GetY(), maxX = mPointList[0].GetX(), maxY = mPointList[0].GetY();

		for (unsigned int i = 1; i < mListCount; i++)
		{
			if (mPointList[i].GetX() < minX)
				minX = mPointList[i].GetX();
			if (mPointList[i].GetX() > maxX)
				maxX = mPointList[i].GetX();
			if (mPointList[i].GetY() < minY)
				minY = mPointList[i].GetY();
			if (mPointList[i].GetY() > maxY)
				maxY = mPointList[i].GetY();
		}

		if ((minX == maxX) || (minY == maxY))
		{
			return false;
		}

		*outMin = Point(minX, minY);
		*outMax = Point(maxX, maxY);

		return true;
	}

	const Point* PolyLine::operator[](unsigned int i) const
	{
		if (i >= mListCapacity || i >= mListCount)
		{
			return nullptr;
		}

		return new Point(mPointList[i].GetX(), mPointList[i].GetY());
	}
}