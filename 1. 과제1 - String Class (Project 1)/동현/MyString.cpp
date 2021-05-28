#include "MyString.h"

namespace assignment1
{
	MyString::MyString(const char* s)
		: mCapacity(50)
		, mStrSize(this->getStringLength(s))
	{
		while (mStrSize >= mCapacity)
		{
			mCapacity *= 2;
		}

		mString = new char[mCapacity];

		this->setMemoryZero(mString);
		this->stringCopy(mString, s, mStrSize);
	}

	MyString::MyString(const MyString& other)
		: mCapacity(other.mCapacity)
		, mStrSize(other.mStrSize)
	{
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
		//! 빈 문자열을 전달할 경우
		if (s == nullptr)
		{
			return;
		}

		if (s == "")
		{
			return;
		}

		unsigned int strSize = this->getStringLength(s);
		unsigned int totalSize = mStrSize + strSize;

		unsigned int index = 0;

		while (totalSize >= mCapacity)
		{
			mCapacity *= 2;
		}
		this->expandCapacity();

		while (mStrSize < totalSize)
		{
			mString[mStrSize++] = s[index++];
		}
		mString[mStrSize] = '\0';
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

		//! 찾지 못할 경우
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
		//! 빈문자열이 전달될 경우
		if (s == nullptr)
		{
			return;
		}

		if (s == "")
		{
			return;
		}

		char* tempString = new char[mCapacity];
		this->setMemoryZero(tempString);
		this->stringCopy(tempString, mString, mStrSize);

		unsigned int i = 0;
		unsigned int j = 0;
		unsigned int n = 0;

		unsigned int sSize = this->getStringLength(s);
		mStrSize = mStrSize + sSize;

		//! 문자열의 용량이 부족할 경우
		if (mStrSize >= mCapacity)
		{
			this->expandCapacity();
		}

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
		{
			mString[i] = mString[i + 1];
		}

		mStrSize--;

		return true;
	}

	void MyString::PadLeft(unsigned int totalLength)
	{
		//! 총 길이가 원본 길이보다 작거나 같을 경우
		if (totalLength <= mStrSize)
		{
			return;
		}

		unsigned int blankLength = totalLength - mStrSize;
		int j = 0;

		char* tempString = new char[totalLength];
		mStrSize = totalLength;

		for (unsigned int i = 0; i < blankLength; i++)
		{
			tempString[i] = ' ';
		}

		for (unsigned int i = blankLength; i < totalLength; i++)
		{
			tempString[i] = mString[j++];
		}

		//! 질문
		//tempString[totalLength] = '\0';

		this->stringCopy(mString, tempString, totalLength);

		delete[] tempString;
	}

	void MyString::PadLeft(unsigned int totalLength, const char c)
	{
		if (totalLength <= mStrSize)
		{
			return;
		}

		unsigned int blankLength = totalLength - mStrSize;
		int j = 0;

		char* tempString = new char[totalLength];
		mStrSize = totalLength;

		for (unsigned int i = 0; i < blankLength; i++)
		{
			tempString[i] = c;
		}

		for (unsigned int i = blankLength; i < totalLength; i++)
		{
			tempString[i] = mString[j++];
		}
		//tempString[totalLength] = '\0';

		this->stringCopy(mString, tempString, totalLength);

		delete[] tempString;
	}

	void MyString::PadRight(unsigned int totalLength)
	{
		if (totalLength <= mStrSize)
		{
			return;
		}

		char* tempString = new char[totalLength];
		mStrSize = totalLength;

		for (unsigned int i = 0; i < mStrSize; i++)
		{
			tempString[i] = mString[i];
		}

		for (unsigned int i = mStrSize; i < totalLength; i++)
		{
			tempString[i] = ' ';
		}
		//tempString[totalLength] = '\0';

		this->stringCopy(mString, tempString, totalLength);

		delete[] tempString;
	}

	void MyString::PadRight(unsigned int totalLength, const char c)
	{
		if (totalLength <= mStrSize)
		{
			return;
		}

		char* tempString = new char[totalLength];
		mStrSize = totalLength;

		for (unsigned int i = 0; i < mStrSize; i++)
		{
			tempString[i] = mString[i];
		}

		for (unsigned int i = mStrSize; i < totalLength; i++)
		{
			tempString[i] = c;
		}
		//tempString[totalLength] = '\0';

		this->stringCopy(mString, tempString, totalLength);

		delete[] tempString;

	}

	void MyString::Reverse()
	{
		//! 빈문자열일 경우
		if (mString == "")
		{
			return;
		}

		//! 문자열의 개수가 1일 경우
		if (mStrSize == 1)
		{
			return;
		}

		char* first = mString;
		char* last = mString + (mStrSize - 1);
		char temp;

		while (first < last)
		{
			temp = *first;
			*first = *last;
			*last = temp;

			first++;
			last--;
		}
	}

	bool MyString::operator==(const MyString& rhs) const
	{
		//! 전달된 개체의 길이가 다를 경우
		if (mStrSize != rhs.mStrSize)
		{
			return false;
		}

		//! 전달되 개체의 길이가 빈문자열일 경우
		if (rhs.mString == "") 
		{
			return true;
		}

		//! 전달된 개체의 길이가 같을 경우
		for (unsigned int i = 0; i < mStrSize; i++)
		{
			if (mString[i] == rhs.mString[i])
			{
				return true;
			}
		}

		return false;
	}

	MyString& MyString::operator=(const MyString& rhs)
	{
		//! 나 자신을 전달할 경우
		if (rhs == *this)
		{
			return *this;
		}

		mCapacity = rhs.mCapacity;
		mStrSize = rhs.mStrSize;

		char* delString = mString;

		//! 깊은 복사 설정
		mString = new char[mCapacity];
		this->setMemoryZero(mString);
		this->stringCopy(mString, rhs.mString, mStrSize);

		//! 기존 메모리 삭제
		delete[] delString;

		return *this;
	}

	void MyString::ToLower()
	{
		for (unsigned int i = 0; i < mStrSize; i++)
		{
			if (mString[i] >= 65 && mString[i] <= 90)
			{
				mString[i] += 32;
			}
		}
	}

	void MyString::ToUpper()
	{
		for (unsigned int i = 0; i < mStrSize; i++)
		{
			if (mString[i] >= 97 && mString[i] <= 122)
			{
				mString[i] -= 32;
			}
		}
	}

	//! private 함수
	unsigned int MyString::getStringLength(const char* aOther) const
	{
		//! 빈 문자열일 경우
		if (aOther == nullptr)
		{
			return -1;
		}

		//! 필요 없을 수도!
		if (aOther == "")
		{
			return 0;
		}

		unsigned int index = 0;

		//! 문자열 길이 반환, 
		while (aOther[index] != '\0')
		{
			index++;
		}

		return index;
	}

	void MyString::setMemoryZero(char* aThis)
	{
		//! 빈 문자열일 경우
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
	}

	void MyString::stringCopy(char* aThis, const char* aOther, unsigned int aOtherSize)
	{
		//! 복사하려는 문자열이 빈 문자열일 경우
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

	void MyString::expandCapacity()
	{
		while (mStrSize >= mCapacity)
		{
			mCapacity *= 2;
		}

		char* deleteStr = mString;
		char* expandStr = new char[mCapacity];
		this->setMemoryZero(expandStr);

		for (unsigned int i = 0; i < mStrSize; i++)
		{
			expandStr[i] = mString[i];
		}

		mString = expandStr;

		delete[] deleteStr;
	}
}