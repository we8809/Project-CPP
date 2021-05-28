#pragma once

#include "SmartStack.h"
#include <queue>

namespace assignment3
{
	template <typename T>
	class QueueStack
	{
	public:
		QueueStack(unsigned int maxStackSize);
		QueueStack& operator=(const QueueStack& other);
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
		std::queue<SmartStack<T> > mQueueStack;
		size_t mMaxStackSize;
		size_t mCount;
		T mDtMax;
		T mDtMin;
		T mDtTotal;
	};

	template <typename T>
	QueueStack<T>::QueueStack(unsigned int maxStackSize)
		: mMaxStackSize(maxStackSize)
		, mCount(0)
		, mDtMax(0)
		, mDtMin(0)
		, mDtTotal(0)
	{

	}

	template <typename T>
	QueueStack<T>& QueueStack<T>::operator=(const QueueStack<T>& other)
	{
		if (this == &other)
		{
			return *this;
		}

		mMaxStackSize = other.mMaxStackSize;
		mCount = other.mCount;
		mDtMax = other.mDtMax;
		mDtMin = other.mDtMin;
		mDtTotal = other.mDtTotal;

		mQueueStack = other.mQueueStack;

		return *this;
	}

	template <typename T>
	void QueueStack<T>::Enqueue(const T& data)
	{
		if (mQueueStack.empty())
		{
			SmartStack<T> ss;
			ss.Push(data);

			mQueueStack.push(ss);

			mDtMax = data;
			mDtMin = data;

			mCount++;

			mDtTotal += data;

			return;
		}

		/* 새로운 스택 생성되어 queue에 들어감 */
		else if ((mCount % mMaxStackSize == 0))
		{
			SmartStack<T> ss;
			ss.Push(data);

			mQueueStack.push(ss);

			if (mDtMax < data)
			{
				mDtMax = data;
			}
			if (mDtMin > data)
			{
				mDtMin = data;
			}

			mCount++;
		}

		/* 스택에 계속 들어감 */
		else
		{
			mQueueStack.back().Push(data);

			if (mDtMax < data)
			{
				mDtMax = data;
			}
			if (mDtMin > data)
			{
				mDtMin = data;
			}

			mCount++;
		}

		mDtTotal += data;
	}

	template <typename T>
	T QueueStack<T>::Peek(void) const
	{
		if (mQueueStack.empty())
		{
			return 0;
		}

		T peekData = mQueueStack.front().Peek();
		return peekData;
	}

	template <typename T>
	T QueueStack<T>::Dequeue(void)
	{
		T popData = mQueueStack.front().Pop();
		if (mQueueStack.front().GetCount() == 0)
		{
			mQueueStack.pop();
		}

		mCount--;

		mDtTotal -= popData;

		/* Calculate Max & Min */
		if (!mQueueStack.empty())
		{
			std::queue<SmartStack<T> > copyQueueStack = mQueueStack;
			SmartStack<T> copyStack;
			mDtMax = mQueueStack.front().GetMax();
			mDtMin = mQueueStack.front().GetMin();

			for (size_t i = 0; i < mQueueStack.size(); i++)
			{
				copyStack = copyQueueStack.front();
				copyQueueStack.pop();

				if (mDtMax < copyStack.GetMax())
				{
					mDtMax = copyStack.GetMax();
				}
				if (mDtMin > copyStack.GetMin())
				{
					mDtMin = copyStack.GetMin();
				}
			}
		}

		return popData;
	}

	template <typename T>
	T QueueStack<T>::GetMax(void) const
	{
		if (mQueueStack.empty())
		{
			return std::numeric_limits<T>::lowest();
		}

		return mDtMax;
	}

	template <typename T>
	T QueueStack<T>::GetMin(void) const
	{
		if (mQueueStack.empty())
		{
			return std::numeric_limits<T>::max();
		}

		return mDtMin;
	}

	template <typename T>
	T QueueStack<T>::GetSum(void) const
	{
		if (mQueueStack.empty())
		{
			return 0;
		}

		return mDtTotal;
	}

	template <>
	double QueueStack<double>::GetAverage(void) const
	{
		if (mQueueStack.empty())
		{
			return 0.0;
		}

		return round(static_cast<double>(mDtTotal / mCount) * 1000.0) / 1000.0;
	}

	template <typename T>
	unsigned int QueueStack<T>::GetCount(void) const
	{
		return mCount;
	}

	template <typename T>
	unsigned int QueueStack<T>::GetStackCount(void) const
	{
		return mQueueStack.size();
	}
}