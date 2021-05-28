#pragma once

#include <string>

/*
	POCU ACADEMY �� �ӱݰ���� �������� �� �������� �ٹ� �ð��� ����ϴ� ����Ʈ��� ���� ���̴�. �� ��������
	Ư�� �ϼ� ���� �� ������Ʈ�� �����ǰ� �Ϸ簡 ���� �� ���� �׳� �� �ð��� ���ߴ��� ����Ѵ�.

	�� �ǽ��� �ٹ� �ð� ��� ����Ʈ��� ����� C++ Ŭ���� �ϳ��� �ۼ��Ѵ�.
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