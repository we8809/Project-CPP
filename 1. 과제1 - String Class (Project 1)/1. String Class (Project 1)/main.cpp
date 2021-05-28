#include <iostream>
#include <cassert>
#include <string>
#include "MyString.h"

using namespace std;
using namespace assignment1;

int main(void)
{
	MyString str1("hihi");

	std::cout << str1.GetCString() << std::endl;
	std::cout << (str1 == str1) << std::endl;

	return 0;

}