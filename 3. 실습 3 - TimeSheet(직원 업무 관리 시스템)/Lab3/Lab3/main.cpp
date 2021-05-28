#include <iostream>

#include "TimeSheet.h"

int main(void)
{
	lab3::TimeSheet employee1("John", 5);
	employee1.AddTime(5);    // ok
	employee1.AddTime(1);
	employee1.AddTime(2);   

	std::cout << employee1.GetStandardDeviation() << std::endl;

	return 0;
}