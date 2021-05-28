#pragma once

namespace assignment1
{
	class MyString
	{
	public:
		/* Constructor */
		MyString() = default;
		MyString(const char* s);
		MyString(const MyString& other);

		/* Destructor */
		~MyString();

		/* Class Method */
		unsigned int GetLength() const;
		const char* GetCString() const;
		void Append(const char* s);
		MyString operator+(const MyString& other) const;			// + ������ �������̵�
		int IndexOf(const char* s);
		int LastIndexOf(const char* s);
		void Interleave(const char* s);
		bool RemoveAt(unsigned int i);
		void PadLeft(unsigned int totalLength);
		void PadLeft(unsigned int totalLength, const char c);
		void PadRight(unsigned int totalLength);
		void PadRight(unsigned int totalLength, const char c);
		void Reverse();
		bool operator==(const MyString& rhs) const;					// �� ������
		MyString& operator=(const MyString& rhs);					// ���� ������
		void ToLower();
		void ToUpper();

	private:
		/* Private Method */
		unsigned int getStringLength(const char* aOther) const;
		void setMemoryZero(char* aThis);
		void stringCopy(char* aThis, const char* aOther, unsigned int aOtherSize);
		void swap(char& a, char& b);

		/* Private Member */
		char* mString;										
		unsigned int mCapacity;									
		unsigned int mStrSize;										
	};
}