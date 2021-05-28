#pragma once

#include <stack>
#include <queue>
#include <cmath>
#include <limits>

namespace assignment3
{
	template <typename T>
	class QueueStack
	{
	public:
		QueueStack(unsigned int maxStackSize);
		~QueueStack() = default;

		void Enqueue(const T& data);
		T Peek(void) const;
		T Dequeue(void);
		T GetMax(void) const;
		T GetMin(void) const;
		double GetAverage(void) const;
		T GetSum(void) const;
		unsigned int GetCount(void) const;
		unsigned int GetStackCount(void) const;

	private:
		std::queue<std::stack<T> > mQueueStack;
		std::stack<T> mMaxStack;
		std::stack<T> mMinStack;
		unsigned int mMaxStackSize;
		size_t mStackCount;
		size_t mCount;

		T mDtMax;
		T mDtMin;
		T mDtTotal;
		double mDtAverage;
	};

	template <typename T>
	QueueStack<T>::QueueStack(unsigned int maxStackSize)
		: mMaxStackSize(maxStackSize)
		, mCount(0)
		, mStackCount(0)
		, mDtMax(0)
		, mDtMin(0)
		, mDtTotal(0)
		, mDtAverage(0.0)
	{

	}

	template <typename T>
	void QueueStack<T>::Enqueue(const T& data)
	{
		if (mCount == 0)
		{
			std::stack<T> ss;
			ss.push(data);

			mQueueStack.push(ss);

			mDtMax = data;
			mDtMin = data;
			
			mMinStack.push(data);
			mMaxStack.push(data);

			mStackCount++;
			mCount++;

			mDtTotal += data;
			mDtAverage = mDtTotal / mCount;

			return;
		}

		else if ((mCount % mMaxStackSize == 0))
		{
			std::stack<T> ss;
			ss.push(data);

			mQueueStack.push(ss);

			if (mDtMax < ss.GetMax())
			{
				mDtMax = ss.GetMax();
				mMaxStack.push(data);

			}
			else if (mDtMin > ss.GetMin())
			{
				mDtMin = ss.GetMin();
				mMinStack.push(data);
			}

			mStackCount++;
			mCount++;
		}

		else
		{
			mQueueStack.back().push(data);

			if (mDtMax < mQueueStack.back().GetMax())
			{
				mDtMax = mQueueStack.back().GetMax();
				mMaxStack.push(data);
			}
			else if (mDtMin > mQueueStack.back().GetMin())
			{
				mDtMin = mQueueStack.back().GetMin();
				mMinStack.push(data);
			}

			mCount++;
		}

		mDtTotal += data;
		mDtAverage = mDtTotal / mCount;
	}

	template <typename T>
	T QueueStack<T>::Peek(void) const
	{
		return mQueueStack.front().top();
	}

	template <typename T>
	T QueueStack<T>::Dequeue(void)
	{

	}

	template <typename T>
	T QueueStack<T>::GetMax(void) const
	{
		return mDtMax;
	}

	template <typename T>
	T QueueStack<T>::GetMin(void) const
	{
		return mDtMin;
	}

	template <typename T>
	double QueueStack<T>::GetAverage(void) const
	{
		return static_cast<double>(roundf(static_cast<float>(mDtAverage) * 1000.f) / 1000.0);
	}

	template <typename T>
	T QueueStack<T>::GetSum(void) const
	{
		return mDtTotal;
	}

	template <typename T>
	unsigned int QueueStack<T>::GetCount(void) const
	{
		return mCount;
	}

	template <typename T>
	unsigned int QueueStack<T>::GetStackCount(void) const
	{
		return mStackCount;
	}
}