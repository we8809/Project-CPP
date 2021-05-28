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
		- 각 직원은 매일 본인이 일한 시간을 기록한다. 이 때 호출하는 함수가 AddTime() 메서드!
		- 직원이 하루에 근무할 수 있는 시간은 최소 1시간, 최대 10시간이다. 만약 유효한 범위를 벗어나는
		  시간을 기록하려고 하면 AddTime() 메서드는 아무 일도 하지 않는다!
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
		- 사장님은 일 단위로 직원이 근무한 시간을 조회할 수 있다. 이 때, GetTimeEntry() 메서드를 호출!
		- GetTimeEntry() 함수는 색인 위치에 시간 값이 존재하지 않으면 -1을 반환해야 한다!
	*/
	int TimeSheet::GetTimeEntry(unsigned int index) const
	{
		/* 현재 mTimeEntry에 아무 데이터도 들어가지 않았을 경우 */
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
		- 봉급을 주려면 직원이 총 몇 시간을 일했는지 알아야겠죠? GetTotalTime() 메서드는 현재 프로젝트에서 직원이
		  그동안 기록한 총 시간을 반환해야 합니다.
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
		- 회사는 직원의 평균 근무 시간에 대한 통계를 내고자 합니다. 그러므로 GetAverageTime() 메서드는 직원이 하루에 평균 몇 시간을 일하는지 반환해야 합니다.
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
		- 회사는 직원의 근무 시간이 얼마나 들쭉날쭉 한 지 통계를 내고 싶어합니다. 표준 편차를 구하면 되겠군요?
		  GetStandardDeviation() 메서드는 근무시간 기록표에 기록된 시간의 표준 편차를 반환해야 합니다.
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
		- GetName() 함수는 해당 근무시간 기록표의 대상인 직원의 이름을 반환합니다.
	*/
	const std::string& TimeSheet::GetName() const
	{
		return mName;
	}
}