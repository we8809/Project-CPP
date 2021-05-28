#pragma once
#include <stack>

using namespace std;

namespace assignment3
{
	template <typename T>
	class SmartStack
	{
	public:
		SmartStack();

		void Push(const T& number);
		T Pop();
		T Peek();

		T GetMax() const;
		T GetMin() const;
		double GetAverage() const;
		T GetSum() const;
		double GetVariance() const;
		double GetStandardDeviation() const;
		unsigned int GetCount() const;

	private:
		stack<T> mStack;
		stack<T> mMaxStack;
		stack<T> mMinStack;
		T mSum;
		double mSumOfSquare;
	};

	template <typename T>
	SmartStack<T>::SmartStack()
		: mSum(0), mSumOfSquare(0)
	{
	}

	template <typename T>
	void SmartStack<T>::Push(const T& number)
	{
		mStack.push(number);
		if (mStack.size() == 1)
		{
			mMaxStack.push(number);
			mMinStack.push(number);
		}
		else
		{
			if (number > mMaxStack.top())
			{
				mMaxStack.push(number);
			}
			else
			{
				mMaxStack.push(mMaxStack.top());
			}

			if (number < mMinStack.top())
			{
				mMinStack.push(number);
			}
			else
			{
				mMinStack.push(mMinStack.top());
			}
		}

		mSum += number;
		mSumOfSquare += pow(number, 2);
	}

	template <typename T>
	T SmartStack<T>::Pop()
	{
		T top = mStack.top();
		mStack.pop();
		mMaxStack.pop();
		mMinStack.pop();

		mSum -= top;
		mSumOfSquare -= pow(top, 2);

		return top;
	}

	template <typename T>
	T SmartStack<T>::Peek()
	{
		return mStack.top();
	}

	template <typename T>
	T SmartStack<T>::GetMax() const
	{
		if (mStack.empty())
		{
			return numeric_limits<T>().lowest();
		}

		return mMaxStack.top();
	}

	template <typename T>
	T SmartStack<T>::GetMin() const
	{
		if (mStack.empty())
		{
			return numeric_limits<T>().max();
		}

		return mMinStack.top();
	}

	template <typename T>
	double SmartStack<T>::GetAverage() const
	{
		const double sum = static_cast<double>(mSum);
		const double average = sum / mStack.size();

		return round(average * 1000) / 1000;
	}

	template <typename T>
	T SmartStack<T>::GetSum() const
	{
		return mSum;
	}

	template <typename T>
	double SmartStack<T>::GetVariance() const
	{
		const double count = static_cast<double>(GetCount());
		const double sum = static_cast<double>(mSum);
		const double average = sum / mStack.size();
		const double variance = mSumOfSquare / count - pow(average, 2);
		return round(variance * 1000) / 1000;
	}

	template <typename T>
	double SmartStack<T>::GetStandardDeviation() const
	{
		const double standardDeviation = sqrt(GetVariance());
		return round(standardDeviation * 1000) / 1000;
	}

	template <typename T>
	unsigned SmartStack<T>::GetCount() const
	{
		return mStack.size();
	}
}
