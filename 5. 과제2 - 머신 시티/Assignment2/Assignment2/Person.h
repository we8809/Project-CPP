#pragma once

#include <string>

namespace assignment2
{
	class Person
	{
	public:
		Person();
		Person(const char* name, unsigned int weight);
		Person(const Person& other);
		Person& operator=(const Person& other);
		~Person();

		const std::string& GetName() const;
		unsigned int GetWeight() const;

	private:
		std::string mName;
		unsigned int mWeight;
	};
}