#include "Person.h"

namespace assignment2
{
	Person::Person()
		: mName("\0")
		, mWeight(0)
	{

	}

	Person::Person(const char* name, unsigned int weight)
		: mName(name)
		, mWeight(weight)
	{

	}

	Person::Person(const Person& other)
		: mName(other.mName)
		, mWeight(other.mWeight)
	{

	}

	Person& Person::operator=(const Person& other)
	{
		if (this == &other)
		{
			return *this;
		}

		mName = other.mName;
		mWeight = other.mWeight;

		return *this;
	}

	Person::~Person()
	{

	}

	const std::string& Person::GetName() const
	{
		return mName;
	}

	unsigned int Person::GetWeight() const
	{
		return mWeight;
	}
}