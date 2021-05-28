#include <iostream>
#include <cassert>

#include "QueueStack.h"

using namespace assignment3;

int main(void)
{
	QueueStack<int> qs(3);
	qs.Enqueue(1); // [ [ 1 ] ]
	qs.Enqueue(2); // [ [ 1, 2 ] ]
	qs.Enqueue(3); // [ [ 1, 2, 3 ] ]
	qs.Enqueue(4); // [ [ 1, 2, 3 ], [ 4 ] ]
	qs.Enqueue(5); // [ [ 1, 2, 3 ], [ 4, 5 ] ]

	int max = qs.GetMax(); // 5
	int min = qs.GetMin();
	int total = qs.GetSum();
	int average = qs.GetAverage();

	std::cout << "max: " << max << ", " << "min: " << min << std::endl;
	std::cout << "sum: " << total << std::endl;
	std::cout << "average: " << average << std::endl;

	return 0;
}