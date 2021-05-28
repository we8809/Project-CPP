#pragma once

#include <cmath>

namespace assignment3
{
	template <typename T>
	class SmartQueue
	{
	public:
		SmartQueue();
		~SmartQueue();

		void Enqueue(const T& data);
		T Peek(void) const;
		T Back(void) const;
		T Dequeue(void);
		T GetMax(void) const;
		T GetMin(void) const;
		double GetAverage(void) const;
		T GetSum(void) const;
		double GetVariance(void) const;
		double GetStandardDeviation(void) const;
		unsigned int GetCount(void) const;

	private:
		T* mQueueList;
		size_t mSize;
		size_t mCapacity;
		T mDtMax;
		T mDtMin;
		T mDtTotal;
		double mDtAverage;
		double mDtVariance;
	};

	template <typename T>
	inline SmartQueue<T>::SmartQueue()
		: mSize(0)
		, mCapacity(2)
		, mDtMax(0)
		, mDtMin(0)
		, mDtTotal(0)
		, mDtAverage(0)
		, mDtVariance(0.0)
	{
		mQueueList = new T[mCapacity];
	}

	template <typename T>
	inline SmartQueue<T>::~SmartQueue()
	{
		delete mQueueList;
	}

	template <typename T>
	inline void SmartQueue<T>::Enqueue(const T& data)
	{
		if (mSize >= mCapacity)
		{
			mCapacity *= 2;
			T* temp = mQueueList;
			mQueueList = new T[mCapacity];

			for (size_t i = 0; i < mSize; i++)
			{
				mQueueList[i] = temp[i];
			}
		}

		mQueueList[mSize++] = data;

		if (mSize == 1)
		{
			mDtMax = data;
			mDtMin = data;
		}
		else
		{
			if (mDtMax < data)
			{
				mDtMax = data;
			}
			else if (mDtMin > data)
			{
				mDtMin = data;
			}
		}

		mDtTotal += data;
		mDtAverage = static_cast<double>(mDtTotal) / static_cast<double>(mSize);

		/* Calculate Variance & StandardDeviation */
		float tempVariance = 0.0f;
		for (size_t i = 0; i < mSize; i++)
		{
			tempVariance += powf(static_cast<float>(mQueueList[i]) - static_cast<float>(mDtAverage), 2.0f);
		}

		mDtVariance = static_cast<double>(tempVariance / mSize);
	}

	template <typename T>
	inline T SmartQueue<T>::Peek(void) const
	{
		return mQueueList[0];
	}

	template <typename T>
	inline T SmartQueue<T>::Back(void) const
	{
		return mQueueList[mSize - 1];
	}

	template <typename T>
	inline T SmartQueue<T>::Dequeue(void)
	{
		T delData = mQueueList[0];
		for (size_t i = 0; i < mSize; i++)
		{
			if (i >= (mSize - 1))
			{
				mQueueList[i] = 0;
				break;
			}

			mQueueList[i] = mQueueList[i + 1];
		}
		
		mSize--;
		mDtMax = mQueueList[0], mDtMin = mQueueList[0];
		mDtTotal = 0; mDtAverage = 0;

		for (size_t i = 0; i < mSize; i++)
		{
			if (mDtMax < mQueueList[i])
			{
				mDtMax = mQueueList[i];
			}
			else if (mDtMin > mQueueList[i])
			{
				mDtMin = mQueueList[i];
			}
			
			mDtTotal += mQueueList[i];
		}

		mDtAverage = static_cast<double>(mDtTotal) / static_cast<double>(mSize);

		/* Calculate Variance & StandardDeviation */
		float tempVariance = 0.0f;
		for (size_t i = 0; i < mSize; i++)
		{
			tempVariance += powf(static_cast<float>(mQueueList[i]) - static_cast<float>(mDtAverage), 2.0f);
		}

		mDtVariance = static_cast<double>(tempVariance / mSize);

		return delData;
	}

	template <typename T>
	T SmartQueue<T>::GetMax(void) const
	{
		if (mSize == 0)
		{
			return std::numeric_limits<T>::min();
		}

		return mDtMax;
	}

	template <typename T>
	T SmartQueue<T>::GetMin(void) const
	{
		if (mSize == 0)
		{
			return std::numeric_limits<T>::max();
		}

		return mDtMin;
	}

	template <typename T>
	inline double SmartQueue<T>::GetAverage(void) const
	{
		/* 소수점 4째자리에서는 반올림 */
		return static_cast<double>(roundf(static_cast<float>(mDtAverage) * 1000.f) / 1000.0);
	}

	template <typename T>
	inline T SmartQueue<T>::GetSum(void) const
	{
		return mDtTotal;
	}

	template <typename T>
	inline double SmartQueue<T>::GetVariance(void) const
	{
		return static_cast<double>(roundf(static_cast<float>(mDtVariance) * 1000.f) / 1000.0);
	}

	template <typename T>
	inline double SmartQueue<T>::GetStandardDeviation(void) const
	{
		return static_cast<double>(roundf(sqrtf(static_cast<float>(mDtVariance)) * 1000.f) / 1000.0);
	}

	template <typename T>
	unsigned int SmartQueue<T>::GetCount(void) const
	{
		return mSize;
	}
}