#include "TimeSheet.h"
#include <iostream>
#include <cstring>
#include <cmath>

namespace lab3
{
	TimeSheet::TimeSheet(const char* name, unsigned int maxEntries)
		: mName(name)
		, mEntryCurPtr(0)
		, mEntryCapacity(maxEntries)
	{
		mTimeEntry = new int[mEntryCapacity];
		memset((void*)mTimeEntry, 0, sizeof(mTimeEntry));
	}

	TimeSheet::~TimeSheet()
	{
		std::cout << "hi" << std::endl;
		delete[] mTimeEntry;
	}
}