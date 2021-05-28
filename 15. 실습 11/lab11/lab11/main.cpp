#include <iostream>
#include <string>
#include <cassert>

#include "Storage.h"

using namespace lab11;

int main()
{
	const unsigned int SIZE = 10;

	Storage<int> storage1(SIZE);
	const std::unique_ptr<int[]>& data1 = storage1.GetData();
	for (int i = 0; i < SIZE; i++)
		data1[i] = 10;

	Storage<int> storage2(100);
	storage2 = storage1;
	const std::unique_ptr<int[]>& data2 = storage2.GetData();
	for (int i = 0; i < SIZE; i++)
		std::cout << data2[i] << std::endl;
	
	return 0;
}