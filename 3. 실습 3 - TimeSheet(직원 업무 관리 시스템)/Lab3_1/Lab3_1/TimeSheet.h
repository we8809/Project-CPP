#pragma once

#include <string>

/*
	POCU ACADEMY 는 임금계산을 목적으로 각 직원들의 근무 시간을 기록하는 소프트웨어를 개발 중이다. 각 직원들은
	특정 일수 동안 한 프로젝트에 배정되고 하루가 끝날 때 마다 그날 몇 시간을 일했는지 기록한다.

	본 실습은 근무 시간 기록 소프트웨어에 사용할 C++ 클래스 하나를 작성한다.
*/
namespace lab3
{
	class TimeSheet
	{
	public:
		/* Constructor */
		TimeSheet(const char* name, unsigned int maxExtries);
		//TimeSheet(const TimeSheet& other);							/* Copy Constructor */
		//TimeSheet& operator=(const TimeSheet& other);				/* Assignment Operator's overloading */

		/* Destructor */
		~TimeSheet();

		/* Public Method */
		void AddTime(int timeInHours);
		int GetTimeEntry(unsigned int index) const;
		int GetTotalTime() const;
		float GetAverageTime() const;
		float GetStandardDeviation() const;
		const std::string& GetName() const;

	private:

		/* Worker name */
		std::string mName;

		/* Worker's Work Time Entry */
		int* mTimeEntry;
		/* mTimeEntry's capacity */
		unsigned int mEntryCapacity;
		/* Worker's Work Time Entry Current Pointer */
		unsigned int mEntryCurPtr;
	};
}