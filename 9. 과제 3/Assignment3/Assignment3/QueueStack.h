#pragma once

#include "SmartStack.h"
#include <iostream>
#include <cmath>

namespace assignment3
{
	/*
	template <typename T>
	class SmartStack;
	*/

	template <typename T>
	class QueueStack 
	{
	public:
		QueueStack() = delete;
		QueueStack(unsigned int maxStackSize);
		~QueueStack();

		void Enqueue(const T& data);
		T Peek(void) const;
		//T Dequeue(void);
		T GetMax(void) const;
		T GetMin(void) const;
		double GetAverage(void) const;
		T GetSum(void) const;
		unsigned int GetCount(void) const;
		unsigned int GetStackCount(void) const;

	private:

		SmartStack<T>* mQueueStack;
		unsigned int mCapacity;
		unsigned int mMaxStackSize;
		unsigned int mStackCount;
		unsigned int mSize;

		T mDtMax;
		T mDtMin;
		T mDtTotal;
		double mDtAverage;
	};

	template <typename T>
	inline QueueStack<T>::QueueStack(unsigned int maxStackSize)
		: mMaxStackSize(maxStackSize)
		, mCapacity(2)
		, mSize(0)
		, mStackCount(0)
		, mDtMax(0)
		, mDtMin(0)
		, mDtTotal(0)
		, mDtAverage(0.0)
	{
		mQueueStack = new SmartStack<T>[mCapacity];
	}

	template <typename T>
	inline QueueStack<T>::~QueueStack()
	{
		if (mQueueStack != nullptr)
		{
			delete[] mQueueStack;
		}
	}

	template <typename T>
	inline void QueueStack<T>::Enqueue(const T& data)
	{
		
		if (mStackCount >= mCapacity)
		{
			mCapacity *= 2;
			SmartStack<T>* temp = mQueueStack;

			delete mQueueStack;

			mQueueStack = new SmartStack<T>[mCapacity];

			for (size_t i = 0; i < mStackCount; i++)
			{
				mQueueStack[i] = temp[i];
			}
		}

		if (mSize == 0 && mStackCount == 0)
		{
			mDtMax = data;
			mDtMin = data;
		}
		
		/* Data Inserting */
		if (mSize >= mMaxStackSize)
		{
			mSize = 0;
			mStackCount++;

			mQueueStack[mStackCount].Push(data);
			mSize++;
		}
		else
		{
			mQueueStack[mStackCount].Push(data);
			mSize++;
		}

		T sum = 0;
		unsigned int count = 0;
		for (size_t i = 0; i < GetStackCount(); i++)
		{
			if (mDtMax < mQueueStack[i].GetMax())
			{
				mDtMax = mQueueStack[i].GetMax();
			}
			else if (mDtMin > mQueueStack[i].GetMin())
			{
				mDtMin = mQueueStack[i].GetMin();
			}

			sum += mQueueStack[i].GetSum();
			count += mQueueStack[i].GetCount();
		}

		mDtTotal = sum;
		mDtAverage = static_cast<double>(mDtTotal / count);
	}

	template <typename T>
	inline T QueueStack<T>::Peek(void) const
	{
		return mQueueStack[mStackCount].Peek();
	}

	template <typename T>
	inline T QueueStack<T>::GetMax(void) const
	{
		return mDtMax;
	}

	template <typename T>
	inline T QueueStack<T>::GetMin(void) const
	{
		return mDtMin;
	}

	template <typename T>
	double QueueStack<T>::GetAverage(void) const
	{
		return mDtAverage;
	}

	template <typename T>
	T QueueStack<T>::GetSum(void) const
	{
		return mDtTotal;
	}

	template <typename T>
	unsigned int QueueStack<T>::GetCount(void) const
	{
		return mSize;
	}

	template <typename T>
	unsigned int QueueStack<T>::GetStackCount(void) const
	{
		return mStackCount + 1;
	}
}