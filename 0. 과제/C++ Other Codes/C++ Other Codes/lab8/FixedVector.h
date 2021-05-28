#pragma once

#include <cassert>

namespace lab8
{
	template <typename T, size_t N>
	class FixedVector
	{
	public:
		FixedVector();
		bool Add(const T& t);
		bool Remove(const T& t);
		const T& Get(unsigned int index);
		T& operator[](unsigned int index);
		int GetIndex(const T& t) const;
		size_t GetSize() const;
		size_t GetCapacity() const;

	private:
		size_t mSize;
		T mArray[N];
	};

	template <typename T, size_t N>
	FixedVector<T, N>::FixedVector()
		: mSize(0)
	{
	}

	template <typename T, size_t N>
	bool FixedVector<T, N>::Add(const T& t)
	{
		if (mSize == GetCapacity())
		{
			return false;
		}

		mArray[mSize++] = t;

		return true;
	}

	template <typename T, size_t N>
	bool FixedVector<T, N>::Remove(const T& t)
	{
		if (mSize == 0)
		{
			return false;
		}

		for (size_t i = 0; i < mSize; i++)
		{
			if (mArray[i] == t)
			{
				for (size_t j = i; j < mSize - 1; j++)
				{
					mArray[j] = mArray[j + 1];
				}
				mSize--;
				return true;
			}
		}

		return false;
	}

	template <typename T, size_t N>
	const T& FixedVector<T, N>::Get(unsigned index)
	{
		if (index >= mSize)
		{
			assert("index exceeds size");
		}

		return mArray[index];
	}

	template <typename T, size_t N>
	T& FixedVector<T, N>::operator[](unsigned index)
	{
		if (index >= mSize)
		{
			assert("index exceeds size");
		}

		return mArray[index];
	}

	template <typename T, size_t N>
	int FixedVector<T, N>::GetIndex(const T& t) const
	{
		for (size_t i = 0; i < mSize; i++)
		{
			if (mArray[i] == t)
			{
				return i;
			}
		}
		return -1;
	}

	template <typename T, size_t N>
	size_t FixedVector<T, N>::GetSize() const
	{
		return mSize;
	}

	template <typename T, size_t N>
	size_t FixedVector<T, N>::GetCapacity() const
	{
		return N;
	}
}