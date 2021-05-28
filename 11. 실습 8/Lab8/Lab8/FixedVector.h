#pragma once

namespace lab8
{
	template <typename T, size_t N>
	class FixedVector
	{
	public:
		FixedVector();
		~FixedVector() = default;

		bool Add(const T& data);
		bool Remove(T findData);
		const T& Get(unsigned int idx) const;
		T& operator[](unsigned int idx);
		int GetIndex(T findData) const;
		size_t GetSize(void) const;
		size_t GetCapacity(void) const;

		void PrintFixedVector(void) const;

	private:
		T mVector[N];
		size_t mCount;
	};

	template <typename T, size_t N>
	FixedVector<T, N>::FixedVector()
		: mCount(0)
	{
		memset(mVector, 0, sizeof(mVector));
	}

	template <typename T, size_t N>
	bool FixedVector<T, N>::Add(const T& data)
	{
		if (mCount >= N)
		{
			return false;
		}

		mVector[mCount] = data;
		mCount++;

		return true;
	}

	template <typename T, size_t N>
	bool FixedVector<T, N>::Remove(T findData)
	{
		size_t findIdx = 0;
		bool chkFlag = false;

		for (size_t i = 0; i < N; i++)
		{
			if (findData == mVector[i])
			{
				findIdx = i;
				chkFlag = true;

				break;
			}
		}

		if (chkFlag != false)
		{
			for (size_t i = findIdx; i < mCount; i++)
			{
				if (i == mCount - 1)
				{
					mVector[i] = 0;
					break;
				}

				mVector[i] = mVector[i + 1];
			}

			mCount--;
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T, size_t N>
	const T& FixedVector<T, N>::Get(unsigned int idx) const
	{
		/* out of range */

		return mVector[idx];
	}

	template <typename T, size_t N>
	T& FixedVector<T, N>::operator[](unsigned int idx)
	{
		return mVector[idx];
	}

	template <typename T, size_t N>
	int FixedVector<T, N>::GetIndex(T findData) const
	{
		bool chkFlag = false;
		int findIdx = 0;

		for (size_t i = 0; i < mCount; i++)
		{
			if (findData == mVector[i])
			{
				findIdx = i;
				chkFlag = true;

				break;
			}
		}

		if (chkFlag != false)
		{
			return findIdx;
		}
		else
		{
			return -1;
		}
	}

	template <typename T, size_t N>
	size_t FixedVector<T, N>::GetSize(void) const
	{
		return mCount;
	}

	template <typename T, size_t N>
	size_t FixedVector<T, N>::GetCapacity(void) const
	{
		return N;
	}

	template <typename T, size_t N>
	void FixedVector<T, N>::PrintFixedVector(void) const
	{
		std::cout << "[ ";
		for (size_t i = 0; i < mCount; i++)
		{
			std::cout << mVector[i] << ", ";
		}
		std::cout << " ]" << std::endl;
	}
}