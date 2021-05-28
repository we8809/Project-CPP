#include "TimeSheet.h"
#include <cstring>
#include <cmath>

namespace lab3
{
	TimeSheet::TimeSheet(const char* name, unsigned int maxEntries)
		: mEntryCurPtr(0)
		, mName(name)
		, mEntryCapacity(maxEntries)
	{
		mTimeEntry = new int[mEntryCapacity + 1];
		memset((void*)mTimeEntry, 0, sizeof(mTimeEntry));
	}

	TimeSheet::TimeSheet(const TimeSheet& other)
		: mName(other.mName)
		, mEntryCurPtr(other.mEntryCurPtr)
		, mEntryCapacity(other.mEntryCapacity)
	{
		mTimeEntry = new int[mEntryCapacity + 1];
		memset((void*)mTimeEntry, 0, sizeof(mTimeEntry));

		if (mEntryCurPtr > 0)
		{
			for (unsigned int i = 0; i < mEntryCurPtr; i++)
			{
				mTimeEntry[i] = other.mTimeEntry[i];
			}
		}
	}
	TimeSheet& TimeSheet::operator=(const TimeSheet& other)
	{
		if (this == &other)
		{
			return *this;
		}

		delete[] mTimeEntry;

		mName = other.mName;
		mEntryCapacity = other.mEntryCapacity;
		mEntryCurPtr = other.mEntryCurPtr;
		mTimeEntry = new int[mEntryCapacity + 1];
		
		memset((void*)mTimeEntry, 0, sizeof(mTimeEntry));
		
		for (unsigned int i = 0; i < mEntryCurPtr; i++)
		{
			mTimeEntry[i] = other.mTimeEntry[i];
		}

		return *this;
	}

	TimeSheet::~TimeSheet()
	{
		delete[] mTimeEntry;
	}

	/*
		- �� ������ ���� ������ ���� �ð��� ����Ѵ�. �� �� ȣ���ϴ� �Լ��� AddTime() �޼���!
		- ������ �Ϸ翡 �ٹ��� �� �ִ� �ð��� �ּ� 1�ð�, �ִ� 10�ð��̴�. ���� ��ȿ�� ������ �����
		  �ð��� ����Ϸ��� �ϸ� AddTime() �޼���� �ƹ� �ϵ� ���� �ʴ´�!
	*/
	void TimeSheet::AddTime(int timeInHours)
	{
		if ((timeInHours <= 0) || (timeInHours > 10))
		{
			return;
		}
		/* Case - Overflow mEntryCapacity Value */
		if (mEntryCurPtr >= mEntryCapacity)
		{
			return;
		}
		
		
		mTimeEntry[mEntryCurPtr] = timeInHours;
		mEntryCurPtr++;
	}

	/* 
		- ������� �� ������ ������ �ٹ��� �ð��� ��ȸ�� �� �ִ�. �� ��, GetTimeEntry() �޼��带 ȣ��!
		- GetTimeEntry() �Լ��� ���� ��ġ�� �ð� ���� �������� ������ -1�� ��ȯ�ؾ� �Ѵ�!
	*/
	int TimeSheet::GetTimeEntry(unsigned int index) const
	{
		/* ���� mTimeEntry�� �ƹ� �����͵� ���� �ʾ��� ��� */
		if (mEntryCurPtr == 0)
		{
			return -1;
		}
		if (index >= mEntryCurPtr)
		{
			return -1;
		}

		return mTimeEntry[index];
	}

	/*
		- ������ �ַ��� ������ �� �� �ð��� ���ߴ��� �˾ƾ߰���? GetTotalTime() �޼���� ���� ������Ʈ���� ������
		  �׵��� ����� �� �ð��� ��ȯ�ؾ� �մϴ�.
	*/
	int TimeSheet::GetTotalTime() const
	{
		if (mEntryCurPtr == 0)
		{
			return 0;
		}

		int totalTime = 0;
		for (unsigned int i = 0; i < mEntryCurPtr; i++)
		{
			totalTime += mTimeEntry[i];
		}

		return totalTime;
	}

	/* 
		- ȸ��� ������ ��� �ٹ� �ð��� ���� ��踦 ������ �մϴ�. �׷��Ƿ� GetAverageTime() �޼���� ������ �Ϸ翡 ��� �� �ð��� ���ϴ��� ��ȯ�ؾ� �մϴ�.
	*/
	float TimeSheet::GetAverageTime() const
	{
		if (mEntryCurPtr == 0)
		{
			return 0.0f;
		}

		int totalTime = GetTotalTime();
		unsigned int entryNum = mEntryCurPtr;
		float averageTime = 0.0f;

		averageTime = static_cast<float>(totalTime) / entryNum;

		return averageTime;
	}

	/* 
		- ȸ��� ������ �ٹ� �ð��� �󸶳� ���߳��� �� �� ��踦 ���� �;��մϴ�. ǥ�� ������ ���ϸ� �ǰڱ���?
		  GetStandardDeviation() �޼���� �ٹ��ð� ���ǥ�� ��ϵ� �ð��� ǥ�� ������ ��ȯ�ؾ� �մϴ�.
	*/
	float TimeSheet::GetStandardDeviation() const
	{
		if (mEntryCurPtr == 0)
		{
			return 0.0f;	
		}

		float averageVal = 0.0f;
		float sumOfSquare = 0.0f;
		float standatdDeviation = 0.0f;
		float squareList[100] = { 0, };

		averageVal = GetAverageTime();
	
		for (unsigned int i = 0; i < mEntryCurPtr; i++)
		{
			squareList[i] = powf(static_cast<float>(mTimeEntry[i]) - averageVal, 2.0f);
			sumOfSquare += squareList[i];
		}

		standatdDeviation = sqrtf(sumOfSquare / mEntryCurPtr);

		return standatdDeviation;
	}

	/*
		- GetName() �Լ��� �ش� �ٹ��ð� ���ǥ�� ����� ������ �̸��� ��ȯ�մϴ�.
	*/
	const std::string& TimeSheet::GetName() const
	{
		return mName;
	}
}