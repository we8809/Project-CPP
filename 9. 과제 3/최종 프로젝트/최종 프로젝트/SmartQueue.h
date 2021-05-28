#pragma once

#include <stack>
#include <queue>
#include <limits>
#include <cmath>

namespace assignment3
{
	template <typename T>
	class SmartQueue
	{
	public:
		SmartQueue();
		~SmartQueue() = default;

		void Enqueue(const T& data);
		T Peek(void) const;
		T Dequeue(void);
		T GetMax(void) const;
		T GetMin(void) const;
		double GetAverage(void) const;
		T GetSum(void) const;
		double GetVariance(void) const;
		double GetStandardDeviation(void) const;
		unsigned int GetCount(void) const;

	private:
		std::queue<T> mQueue;
		T mDtMax;
		T mDtMin;
		T mDtTotal;
		double mDtExpectation;
	};

	template <typename T>
	SmartQueue<T>::SmartQueue()
		: mDtMax(0)
		, mDtMin(0)
		, mDtTotal(0)
		, mDtExpectation(0.0)
	{

	}

	template <typename T>
	void SmartQueue<T>::Enqueue(const T& data)
	{
		if (mQueue.empty())
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
			if (mDtMin > data)
			{
				mDtMin = data;
			}
		}

		mQueue.push(data);

		/* Calculate total & average & expectation */
		mDtTotal += data;
		mDtExpectation += pow(static_cast<double>(data), 2.0);
	}

	template <typename T>
	T SmartQueue<T>::Peek(void) const
	{
		if (mQueue.empty())
		{
			return 0;
		}

		return mQueue.front();
	}

	template <typename T>
	T SmartQueue<T>::Dequeue(void)
	{
		T popData = mQueue.front();
		mQueue.pop();

		/* Calculate Min & Max */
		if (!mQueue.empty())
		{
			std::queue<T> copyQueue = mQueue;
			mDtMax = mQueue.front();
			mDtMin = mQueue.front();

			for (size_t i = 0; i < mQueue.size(); i++)
			{
				T temp = copyQueue.front();
				copyQueue.pop();

				if (temp >= mDtMax)
				{
					mDtMax = temp;
				}
				if (temp <= mDtMin)
				{
					mDtMin = temp;
				}
			}
		}

		/* Calculate total & average & expectation */
		mDtTotal -= popData;
		mDtExpectation -= pow(static_cast<double>(popData), 2.0);
		
		return popData;
	}

	template <typename T>
	T SmartQueue<T>::GetMax(void) const
	{
		if (mQueue.empty())
		{
			return std::numeric_limits<T>::lowest();
		}

		return mDtMax;
	}

	template <typename T>
	T SmartQueue<T>::GetMin(void) const
	{
		if (mQueue.empty())
		{
			return std::numeric_limits<T>::max();
		}

		return mDtMin;
	}

	template <typename T>
	double SmartQueue<T>::GetAverage(void) const
	{
		if (mQueue.empty())
		{
			return 0.0;
		}

		return round(static_cast<double>(mDtTotal / mQueue.size()) * 1000.0) / 1000.0;
	}

	template <typename T>
	T SmartQueue<T>::GetSum(void) const
	{
		if (mQueue.empty())
		{
			return 0;
		}

		return mDtTotal;
	}

	template <typename T>
	double SmartQueue<T>::GetVariance(void) const 
	{
		if (mQueue.empty())
		{
			return 0.0;
		}

		double variance = (mDtExpectation / mQueue.size()) - pow(static_cast<double>(mDtTotal / mQueue.size()), 2.0);

		return round(variance * 1000.0) / 1000.0;
	}

	template <typename T>
	double SmartQueue<T>::GetStandardDeviation(void) const
	{
		if (mQueue.empty())
		{
			return 0.0;
		}

		return round(sqrt(GetVariance()) * 1000.0) / 1000.0;
	}

	template <typename T>
	unsigned int SmartQueue<T>::GetCount(void) const
	{
		return mQueue.size();
	}
}