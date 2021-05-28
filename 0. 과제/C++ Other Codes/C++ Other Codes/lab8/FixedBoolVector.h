#pragma once

#include <cassert>

namespace lab8
{
	template <size_t N>
	class FixedVector<bool, N>
	{
	public:
		FixedVector();
		bool Add(bool b);
		bool Remove(bool b);
		const bool Get(unsigned int index) const;
		const bool operator[](unsigned int index) const;
		int GetIndex(bool b) const;
		size_t GetSize() const;
		size_t GetCapacity() const;

	private:
		size_t mSize;
		int32_t mContainer[1 + (N - 1) / 32] = {0,};
	};

	template <size_t N>
	FixedVector<bool, N>::FixedVector()
		: mSize(0)
	{
	}

	template <size_t N>
	bool FixedVector<bool, N>::Add(bool b)
	{
		if (mSize == GetCapacity())
		{
			return false;
		}
		if (b)
		{
			mContainer[mSize / 32] ^= 0x1 << mSize % 32;
		}
		else
		{
			mContainer[mSize / 32] &= ~(0x1 << mSize % 32);
		}
		++mSize;

		return true;
	}

	template <size_t N>
	bool FixedVector<bool, N>::Remove(bool b)
	{
		if (mSize == 0)
		{
			return false;
		}

		const int removeIndex = GetIndex(b);

		if (removeIndex == -1)
		{
			return false;
		}

		for (size_t i = removeIndex; i < mSize - 1; ++i)
		{
			if (Get(i + 1))
			{
				mContainer[i / 32] |= 0x1 << i % 32;
			}
			else
			{
				mContainer[i / 32] &= ~(0x1 << i % 32);
			}
		}
		--mSize;
		return true;
	}

	template <size_t N>
	const bool FixedVector<bool, N>::Get(unsigned index) const
	{
		if (index >= mSize)
		{
			assert("index exceeds size");
		}

		return mContainer[index / 32] & 0x1 << (index % 32);
	}

	template <size_t N>
	const bool FixedVector<bool, N>::operator[](unsigned index) const
	{
		return Get(index);
	}

	template <size_t N>
	int FixedVector<bool, N>::GetIndex(bool b) const
	{
		for (unsigned index = 0; index < mSize; ++index)
		{
			if (Get(index) == b)
			{
				return static_cast<int>(index);
			}
		}
		return -1;
	}

	template <size_t N>
	size_t FixedVector<bool, N>::GetSize() const
	{
		return mSize;
	}

	template <size_t N>
	size_t FixedVector<bool, N>::GetCapacity() const
	{
		return N;
	}
}