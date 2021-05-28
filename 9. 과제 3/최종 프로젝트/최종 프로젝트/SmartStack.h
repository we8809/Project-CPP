#pragma once

#include <stack>
#include <limits>
#include <cmath>

namespace assignment3
{
	template <typename T>
	class SmartStack
	{
	public:
		SmartStack();
		SmartStack& operator=(const SmartStack& other);
		~SmartStack() = default;

		void Push(T data);
		T Pop(void);
		T Peek(void) const;
		T GetMax(void) const;
		T GetMin(void) const;
		T GetSum(void) const;
		double GetAverage(void) const;
		double GetVariance(void) const;
		double GetStandardDeviation(void) const;
		unsigned int GetCount(void) const;

	private:
		std::stack<T> mStack;
		std::stack<T> mMinStack;
		std::stack<T> mMaxStack;
		T mDtMax;
		T mDtMin;
		T mDtTotal;
		double mDtExpectation;
	};

	template <typename T>
	SmartStack<T>::SmartStack() 
		: mDtMax(0)
		, mDtMin(0)
		, mDtTotal(0)
		, mDtExpectation(0.0)
	{

	}

	template <typename T>
	SmartStack<T>& SmartStack<T>::operator=(const SmartStack<T>& other)
	{
		if (this == &other)
		{
			return *this;
		}

		mDtMax = other.mDtMax;
		mDtMin = other.mDtMin;
		mDtTotal = other.mDtTotal;
		mDtExpectation = other.mDtExpectation;

		mStack = other.mStack;
		mMinStack = other.mMinStack;
		mMaxStack = other.mMaxStack;

		return *this;
	}

	template <typename T>
	void SmartStack<T>::Push(T data)
	{
		if (mStack.empty())
		{
			mDtMax = data;
			mDtMin = data;

			mMaxStack.push(data);
			mMinStack.push(data);
		}
		else
		{
			if (mDtMax <= data)
			{
				mDtMax = data;
				mMaxStack.push(data);
			}
			if (mDtMin >= data)
			{
				mDtMin = data;
				mMinStack.push(data);
			}
		}

		/* Data Insert */
		mStack.push(data);
	
		mDtTotal += data;
		mDtExpectation += pow(static_cast<double>(data), 2.0);
	}

	template <typename T>
	T SmartStack<T>::Pop(void)
	{
		T popData = mStack.top();
		mStack.pop();

		if (mMinStack.top() == popData)
		{
			if (mStack.empty())
			{
				mMinStack.pop();
			}
			else 
			{
				mMinStack.pop();
				mDtMin = mMinStack.top();
			}
		}
		if (mMaxStack.top() == popData)
		{
			if (mStack.empty())
			{
				mMaxStack.pop();
			}
			else
			{
				mMaxStack.pop();
				mDtMax = mMaxStack.top();
			}
		}

		mDtTotal -= popData;
		mDtExpectation -= pow(static_cast<double>(popData), 2.0);
		
		return popData;
	}

	template <typename T>
	T SmartStack<T>::Peek(void) const
	{
		if (mStack.empty())
		{
			return 0;
		}

		return mStack.top();
	}

	template <typename T>
	T SmartStack<T>::GetMax(void) const
	{
		if (mStack.empty())
		{
			return std::numeric_limits<T>::lowest();
		}

		return mDtMax;
	}

	template <typename T>
	T SmartStack<T>::GetMin(void) const
	{
		if (mStack.empty())
		{
			return std::numeric_limits<T>::max();
		}

		return mDtMin;
	}

	template <typename T>
	double SmartStack<T>::GetAverage(void) const
	{
		if (mStack.empty())
		{
			return 0.0;
		}

		/* 소수점 4째자리에서는 반올림 */
		return round(static_cast<double>(mDtTotal / mStack.size()) * 1000.0) / 1000.0;
	}

	template <typename T>
	T SmartStack<T>::GetSum(void) const
	{
		
		if (mStack.empty())
		{
			return 0;
		}
		
		return mDtTotal;
	}

	template <typename T>
	double SmartStack<T>::GetVariance(void) const 
	{
		if (mStack.empty())
		{
			return 0.0;
		}

		double variance = (mDtExpectation / mStack.size()) - pow(static_cast<double>(mDtTotal / mStack.size()), 2.0);

		return round(static_cast<double>(variance * 1000.0)) / 1000.0;
	}

	template <typename T>
	double SmartStack<T>::GetStandardDeviation(void) const
	{
		if (mStack.empty())
		{
			return 0.0;
		}

		return round(sqrt(GetVariance()) * 1000.0) / 1000.0;
	}

	template <typename T>
	unsigned int SmartStack<T>::GetCount(void) const
	{
		return mStack.size();
	}
}