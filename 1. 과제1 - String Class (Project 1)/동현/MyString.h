#pragma once
namespace assignment1
{
	class MyString
	{
	public:	//! ������, �Ҹ���
		MyString(const char* s);
		MyString(const MyString& other);
		~MyString();

		//! public �Լ�
		unsigned int GetLength() const;
		const char* GetCString() const;
		void Append(const char* s);
		MyString operator+(const MyString& other) const;
		int IndexOf(const char* s);
		int LastIndexOf(const char* s);
		void Interleave(const char* s);
		bool RemoveAt(unsigned int i);
		void PadLeft(unsigned int totalLength);
		void PadLeft(unsigned int totalLength, const char c);
		void PadRight(unsigned int totalLength);
		void PadRight(unsigned int totalLength, const char c);
		void Reverse();
		bool operator==(const MyString& rhs) const;
		MyString& operator=(const MyString& rhs);
		void ToLower();
		void ToUpper();

	private:	//! private �Լ� 
		unsigned int getStringLength(const char* aOther) const;
		void setMemoryZero(char* aThis);
		void stringCopy(char* aThis, const char* aOther, unsigned int aOtherSize);
		void expandCapacity();

	private:	//! private ����
		char* mString;
		unsigned int mCapacity;
		unsigned int mStrSize;
	};
}