#include "MyString.h"

namespace assignment1
{
	/* Public Method Configuration */
	MyString::MyString(const char* s)
		: mStrSize(this->getStringLength(s))
		, mCapacity(1)
	{
		if ((mStrSize == 0) || (*s == '\0') || (s == nullptr))
		{
			mString = new char[mCapacity];
			mString[0] = '\0';

			return;
		}

		mCapacity = mStrSize + 1;
			
		mString = new char[mCapacity];

		this->setMemoryZero(mString);
		this->stringCopy(mString, s, mStrSize);
	}

	/* Copy Constructor */
	MyString::MyString(const MyString& other)
		: mStrSize(other.mStrSize)
		, mCapacity(other.mCapacity)
	{
		if ((mStrSize == 0) || (other.mString == nullptr))
		{
			mCapacity = 1;

			mString = new char[mCapacity];
			mString[0] = '\0';

			return;
		}

		/* Deep Copy */
		mString = new char[mCapacity];
		this->setMemoryZero(mString);
		this->stringCopy(mString, other.mString, mStrSize);
	}

	MyString::~MyString()
	{
		delete[] mString;
	}

	unsigned int MyString::GetLength() const
	{
		return mStrSize;
	}

	const char* MyString::GetCString() const
	{
		return mString;
	}

	void MyString::Append(const char* s)
	{
		if (s == nullptr)
		{
			return;
		}

		if (s == "")
		{
			return;
		}

		char* tempString = mString;
		unsigned int toAppend = getStringLength(s);
		unsigned int totalCapacity = mStrSize + getStringLength(s) + 1;
		
		/* 기존 용량의 2배보다 미달할 시 */
		if (mCapacity * 2 > totalCapacity)
			mCapacity *= 2;
		/* 기본 용량의 2배보다 크면? */
		else
			mCapacity = totalCapacity;

		mString = new char[mCapacity];

		for (unsigned int i = 0; i < mStrSize + 1; i++)
			mString[i] = tempString[i];

		for (unsigned int i = 0; i < toAppend + 1; i++)
			mString[(mStrSize) + i] = s[i];

		mStrSize = mStrSize + toAppend;
		delete[] tempString;
	}

	MyString MyString::operator+(const MyString& other) const
	{
		MyString newString(this->GetCString());
		newString.Append(other.GetCString());

		return newString;
	}

	int MyString::IndexOf(const char* s)
	{
		//! 빈 문자열일 경우
		if (s == nullptr)
		{
			return -1;
		}

		if (s == "")
		{
			return 0;
		}

		unsigned int i = 0;
		unsigned int j = 0;

		for (i = 0; i < mStrSize; i++)
		{
			if (mString[i] == s[j])
			{
				while (s[j] == mString[i + j])
				{
					j++;

					if (s[j] == '\0')
					{
						return i;
					}
				}
				j = 0;
			}
		}

		return -1;
	}

	int MyString::LastIndexOf(const char* s)
	{
		//! 빈 문자열일 경우
		if (s == nullptr)
		{
			return -1;
		}

		if (s == "")
		{
			return mStrSize;
		}

		unsigned int i = 0;
		unsigned int j = 0;
		unsigned int lastIndex = -1;

		for (i = 0; i < mStrSize; i++)
		{
			if (mString[i] == s[j])
			{
				while (s[j] == mString[i + j])
				{
					j++;
					if (s[j] == '\0')
					{
						lastIndex = i;
						break;
					}
				}
				j = 0;
			}
		}
		
		return lastIndex;
	}

	void MyString::Interleave(const char* s)
	{
		if (s == nullptr)
		{
			return;
		}

		if (s == "")
		{
			return;
		}

		char* tempString = mString;

		unsigned int i = 0;
		unsigned int j = 0;
		unsigned int n = 0;


		mStrSize += this->getStringLength(s);
		unsigned int totalCapacity = mStrSize + 1;
		
		if (mCapacity * 2 > totalCapacity)
			mCapacity *= 2;
		else
			mCapacity = totalCapacity;
	
		mString = new char[mCapacity];

		while (n < mStrSize)
		{
			if (tempString[i] != '\0')
			{
				mString[n++] = tempString[i++];
			}

			if (s[j] != '\0')
			{
				mString[n++] = s[j++];
			}
		}

		mString[mStrSize] = '\0';

		delete[] tempString;
	}

	bool MyString::RemoveAt(unsigned int index)
	{
		if (index >= mStrSize)
		{
			return false;
		}

		for (unsigned int i = index; i < mStrSize; i++)
			mString[i] = mString[i + 1];

		mStrSize--;
		
		return true;
	}

	void MyString::PadLeft(unsigned int totalLength)
	{
		if (totalLength <= mStrSize)
		{
			return;
		}

		unsigned int additionalLength = totalLength - mStrSize;

		if (additionalLength <= 0)
			return;
		
		char* prevString = mString;
		unsigned int totalCapacity = mStrSize + additionalLength + 1;

		if (mCapacity * 2 > totalCapacity)
			mCapacity *= 2;
		else
			mCapacity = totalCapacity;

		mString = new char[totalCapacity];

		for (unsigned int i = 0; i < additionalLength; i++)
			mString[i] = ' ';
		for (unsigned int i = 0; i < mStrSize + 1; i++)
			mString[additionalLength + i] = prevString[i];

		mStrSize += additionalLength;

		delete[] prevString;
	}

	void MyString::PadLeft(unsigned int totalLength, const char c)
	{
		if (totalLength <= mStrSize)
		{
			return;
		}

		unsigned int additionalLength = totalLength - mStrSize;

		char* prevString = mString;
		unsigned int totalCapacity = mStrSize + additionalLength + 1;

		if (mCapacity * 2 > totalCapacity)
			mCapacity *= 2;
		else
			mCapacity = totalCapacity;

		mString = new char[totalCapacity];

		for (unsigned int i = 0; i < additionalLength; i++)
			mString[i] = c;
		for (unsigned int i = 0; i < mStrSize + 1; i++)
			mString[additionalLength + i] = prevString[i];

		mStrSize += additionalLength;

		delete[] prevString;
	}

	void MyString::PadRight(unsigned int totalLength)
	{
		if (totalLength <= mStrSize)
		{
			return;
		}

		unsigned int additionalLength = totalLength - mStrSize;

		char* prevString = mString;
		unsigned int totalCapacity = mStrSize + additionalLength + 1;

		if (mCapacity * 2 > totalCapacity)
			mCapacity *= 2;
		else
			mCapacity = totalCapacity;

		mString = new char[totalCapacity];

		for (unsigned int i = 0; i < mStrSize; i++)
			mString[i] = prevString[i];
		for (unsigned int i = 0; i < additionalLength; i++)
			mString[mStrSize + i] = ' ';

		mString[mStrSize + additionalLength] = 0;
		
		mStrSize += additionalLength;

		delete[] prevString;
	}

	void MyString::PadRight(unsigned int totalLength, const char c)
	{
		if (totalLength <= mStrSize)
		{
			return;
		}
		
		unsigned int additionalLength = totalLength - mStrSize;

		char* prevString = mString;
		unsigned int totalCapacity = mStrSize + additionalLength + 1;

		if (mCapacity * 2 > totalCapacity)
			mCapacity *= 2;
		else
			mCapacity = totalCapacity;

		mString = new char[totalCapacity];

		for (unsigned int i = 0; i < mStrSize; i++)
			mString[i] = prevString[i];
		for (unsigned int i = 0; i < additionalLength; i++)
			mString[mStrSize + i] = c;

		mString[mStrSize + additionalLength] = 0;

		mStrSize += additionalLength;

		delete[] prevString;
	}

	void MyString::Reverse()
	{
		if (mString == "")
		{
			return;
		}

		if (mStrSize == 1)
		{
			return;
		}

		unsigned int reserveIdx = mStrSize - 1;

		for (unsigned int i = 0; i < mStrSize / 2; i++)
		{
			swap(mString[i], mString[reserveIdx--]);
		}
	}

	bool MyString::operator==(const MyString& rhs) const
	{
		if (mString == rhs.mString)
		{
			return true;
		}

		// 인스턴스 개체의 문자열 길이가 다를 경우
		if (rhs.mStrSize != mStrSize)
		{
			return false;
		}

		for (unsigned int i = 0; i < mStrSize; i++)
		{
			if (mString[i] != rhs.mString[i])
				return false;
		}

		return true;
	}

	MyString& MyString::operator=(const MyString& rhs)
	{
		if (*this == rhs) {
			return *this;
		}

		if ((rhs.mStrSize == 0) || (rhs.mString == nullptr))
		{
			delete[] mString;
			
			mStrSize = 0;
			mCapacity = 1;

			mString = new char[mCapacity];
			mString[0] = 0;

			return *this;
		}

		/* free mString */
		delete[] mString;

		if (mCapacity * 2 > rhs.mCapacity)
			mCapacity *= 2;
		else
			mCapacity = rhs.mCapacity;

		mStrSize = rhs.mStrSize;
		mString = new char[mCapacity];
		this->setMemoryZero(mString);
		this->stringCopy(mString, rhs.mString, mStrSize);

		return *this;
	}

	void MyString::ToLower()
	{
		for (unsigned int i = 0; i < mStrSize; i++)
		{
			if ((mString[i] >= 65) & (mString[i] <= 90))
				mString[i] += 32;
		}
	}

	void MyString::ToUpper()
	{
		for (unsigned int i = 0; i < mStrSize; i++)
		{
			if ((mString[i] >= 97) & (mString[i] <= 122))
				mString[i] -= 32;
		}
	}

	/* Private Method Configuration */
	/* Swap the Charactor */
	void MyString::swap(char& a, char& b)
	{
		char temp = a;
		a = b;
		b = temp;
	}

	/* Get the String Length */
	unsigned int MyString::getStringLength(const char* s) const
	{
		// 빈 문자열일 경우
		if (s == nullptr)
		{
			return 0;
		}

		if (*s == '\0')
		{
			return 0;
		}

		unsigned int index = 0;

		while (s[index] != '\0')
		{
			index++;
		}

		return index;
	}

	void MyString::setMemoryZero(char* aThis)
	{
		if (aThis == nullptr)
		{
			return;
		}

		if (aThis == "")
		{
			return;
		}

		for (unsigned int i = 0; i < mStrSize; i++)
		{
			aThis[i] = 0;
		}

		aThis[mStrSize] = '\0';
	}

	void MyString::stringCopy(char* aThis, const char* aOther, unsigned int aOtherSize)
	{
		// 복사하려는 문자열이 빈 문자열일 경우
		if (aOther == "")
		{
			aThis[0] = '\0';

			return;
		}

		for (unsigned int i = 0; i < aOtherSize; i++)
		{
			aThis[i] = aOther[i];
		}

		aThis[aOtherSize] = '\0';
	}
}