#pragma once
#include <queue>

using namespace std;

namespace assignment3
{
	template <typename T>
	class SmartQueue
	{
	public:
		SmartQueue();

		void Enqueue(const T& number);
		T Peek();
		T Dequeue();

		T GetMax() const;
		T GetMin() const;
		double GetAverage() const;
		T GetSum() const;
		double GetVariance() const;
		double GetStandardDeviation() const;
		unsigned int GetCount() const;

	private:
		queue<T> mQueue;
		T mSum;
		double mSumOfSquare;
	};

	template <typename T>
	SmartQueue<T>::SmartQueue()
		: mSum(0), mSumOfSquare(0)
	{
	}

	template <typename T>
	void SmartQueue<T>::Enqueue(const T& number)
	{
		mQueue.push(number);

		mSum += number;
		mSumOfSquare += pow(number, 2);
	}

	template <typename T>
	T SmartQueue<T>::Peek()
	{
		return mQueue.front();;
	}

	template <typename T>
	T SmartQueue<T>::Dequeue()
	{
		T front = mQueue.front();
		mQueue.pop();

		mSum -= front;
		mSumOfSquare -= pow(front, 2);

		return front;
	}

	template <typename T>
	T SmartQueue<T>::GetMax() const
	{
		if (mQueue.empty())
		{
			return numeric_limits<T>().lowest();
		}

		T max = numeric_limits<T>().lowest();

		queue<T> s(mQueue);

		for (size_t i = 0; i < mQueue.size(); i++)
		{
			const T number = s.front();
			s.pop();

			if (number > max)
			{
				max = number;
			}
		}

		return max;
	}

	template <typename T>
	T SmartQueue<T>::GetMin() const
	{
		if (mQueue.empty())
		{
			return numeric_limits<T>().max();
		}

		T min = numeric_limits<T>().max();

		queue<T> s(mQueue);

		for (size_t i = 0; i < mQueue.size(); i++)
		{
			const T number = s.front();
			s.pop();

			if (number < min)
			{
				min = number;
			}
		}

		return min;
	}

	template <typename T>
	double SmartQueue<T>::GetAverage() const
	{
		const double sum = static_cast<double>(GetSum());
		const double average = sum / mQueue.size();

		return round(average * 1000) / 1000;
	}

	template <typename T>
	T SmartQueue<T>::GetSum() const
	{
		return mSum;
	}

	template <typename T>
	double SmartQueue<T>::GetVariance() const
	{
		const double count = static_cast<double>(GetCount());
		const double sum = static_cast<double>(mSum);
		const double average = sum / mQueue.size();
		const double variance = mSumOfSquare / count - pow(average, 2);
		return round(variance * 1000) / 1000;
	}

	template <typename T>
	double SmartQueue<T>::GetStandardDeviation() const
	{
		const double standardDeviation = sqrt(GetVariance());
		return round(standardDeviation * 1000) / 1000;
	}

	template <typename T>
	unsigned SmartQueue<T>::GetCount() const
	{
		return mQueue.size();
	}
}