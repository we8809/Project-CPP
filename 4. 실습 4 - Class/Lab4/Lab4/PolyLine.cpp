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
		- �� �ϳ��� PolyLine ��ü�� �߰��Ѵ�.
		- Signature�� �ٸ� �� ���� AddPoint() �޼��尡 �ִ��� ���� ����. �ϳ��� ���ڷ� float �� �� ����, �ٸ� �ϳ��� ��� ������(const pointer)�� �޴´�.
		- ���� PolyLine�� �߰��Ǹ� true�� ��ȯ�Ѵ�. �߰��� ���� ����������Ŭ(����)�� PolyLine�� ����������, PolyLine ��ü�� �Ҹ��Ű�ų� 
		RemovePoint() ���� �޼��带 ȣ���Ͽ� ���� �Ҹ��Ű�� �ʴ� �� ������ Ŭ���� �ۿ����� ���� ����Ű�� �����͸� ����� �� �ִ�.
		���� PolyLine�� ���� �߰��� �� �����ٸ� false�� ��ȯ�Ѵ�.
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