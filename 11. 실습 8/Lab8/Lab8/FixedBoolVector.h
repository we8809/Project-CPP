#pragma once

#include <iostream>
#include <bitset>
#include "FixedVector.h"

namespace lab8
{
	template <size_t N>
	class FixedVector<bool, N>
	{
	public:
		FixedVector();
		~FixedVector() = default;
		
		bool Add(const bool& data);
		bool Remove(bool findData);
		bool Get(unsigned int idx) const;
		bool operator[](unsigned int idx);
		int GetIndex(bool findData) const;
		size_t GetSize(void) const;
		size_t GetCapacity(void) const;

		void PrintFixedVector(void) const;

	private:
		int mVector[(N/32)+1];
		size_t mCount;
	};

	template <size_t N>
	FixedVector<bool, N>::FixedVector()
		: mCount(0)
	{
		memset(mVector, 0, sizeof(mVector));
	}

	template <size_t N>
	bool FixedVector<bool, N>::Add(const bool& data)
	{
		if (mCount >= N)
		{
			return false;
		}

		uint32_t boolShiftOffset = mCount % 32;

		mVector[mCount / 32] |= (data << boolShiftOffset);
		mCount++;

		return true;
	}

	template <size_t N>
	bool FixedVector<bool, N>::Remove(bool findData)
	{
		int findBitIdx = GetIndex(findData);

		if (findBitIdx != -1)
		{
			int32_t findArrayIdx = findBitIdx / 32;
			int32_t intVectorSize = (mCount / 32) + 1;
			int32_t temp = 0;

			/* find data = true */
			if (findData != false)
			{
				for (size_t i = findBitIdx; i < 32; i++)
				{
					temp |= (1 << i);
				}

				mVector[findArrayIdx] >>= 1;
				mVector[findArrayIdx] &= temp;

				if (intVectorSize > (findArrayIdx + 1))
				{
					bool tempBit = false;
					for (int i = (findBitIdx + 1); i < intVectorSize; i++)
					{
						tempBit = (mVector[i] & (1 << 0));
						mVector[i] >>= 1;
						mVector[i - 1] |= (tempBit << 31);
					}
				}
			}
			/* find data =false */
			else
			{
				size_t bitOverflow = (mCount + (32 * findBitIdx)) % 32;
				std::cout << "findBitIdx: " << findBitIdx << std::endl;
				std::cout << "bitOverflow: " << bitOverflow << std::endl;
				for (size_t i = findBitIdx; i < bitOverflow; i++)
				{
					temp |= (mVector[findArrayIdx] & (1 << i));
				}
				temp >>= 1;


				if (intVectorSize > (findBitIdx + 1))
				{
					bool tempBit = false;
					for (size_t i = (findBitIdx + 1); i < intVectorSize; i++)
					{
						tempBit = (mVector[i] & (1 << 0));
						mVector[i] >>= 1;
						mVector[i - 1] |= (tempBit << 31);
					}
				}
			}

			mCount--;

			return true;
		}
		else
		{
			return false;
		}
	}

	template <size_t N>
	bool FixedVector<bool, N>::Get(unsigned int idx) const
	{
		if ((idx >= N) || (idx >= mCount))
		{
			return false;
		}

		unsigned int arrayOffset = idx / 32;
		unsigned int bitOffset = idx % 32;
		bool boolResult = (mVector[arrayOffset] & (1 << bitOffset)) >> bitOffset;
		
		return boolResult;
	}

	template <size_t N>
	bool FixedVector<bool, N>::operator[](unsigned int idx)
	{
		if ((idx >= N) || (idx >= mCount))
		{
			return false;
		}

		unsigned int arrayOffset = idx / 32;
		unsigned int bitOffset = idx % 32;
		bool boolResult = (mVector[arrayOffset] & (1 << bitOffset)) >> bitOffset;

		return boolResult;
	}

	template <size_t N>
	int FixedVector<bool, N>::GetIndex(bool findData) const
	{
		bool bCheckData, checkFlag = false;
		unsigned int boolVectorSize = (mCount / 32) + 1;
		unsigned int vectorEndOffset = mCount % 32;
		int findBoolIndex = 0;

		for (size_t i = 0; i < boolVectorSize; i++)
		{
			for (size_t j = 0; j < 32; j++)
			{
				if (j >= vectorEndOffset && i >= (boolVectorSize - 1))
				{
					return -1;
				}

				bCheckData = (mVector[i] & (1 << j)) >> j;
				
				if (bCheckData == findData)
				{
					return j + (32 * i);
				}
			}
		}
	}
	
	template <size_t N>
	size_t FixedVector<bool, N>::GetSize(void) const
	{
		size_t arraySize = (mCount / 32) + 1;

		if (arraySize == 1)
		{
			return mCount;
		}
		else
		{
			return (arraySize * 32) + (mCount - (arraySize * 32));
		}
	}
	template <size_t N>
	size_t FixedVector<bool, N>::GetCapacity(void) const
	{
		return N;
	}

	template <size_t N>
	void FixedVector<bool, N>::PrintFixedVector(void) const
	{
		size_t arraySize = (mCount / 32) + 1;
		std::cout << "[bit]: " << std::endl;
		for (size_t i = 0; i < arraySize; i++)
		{
			std::cout << std::bitset<32>(mVector[i]) << std::endl;
		}
		std::cout << std::endl;
	}
}