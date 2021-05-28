#pragma once
#include <queue>
#include <stack>
using namespace std;

namespace assignment3
{
	template <typename T>
	class QueueStack
	{
	public:
		QueueStack(unsigned int maxStackSize);
		void Enqueue(const T& number);
		T Peek();
		T Dequeue();

		T GetMax() const;
		T GetMin() const;
		double GetAverage() const;
		T GetSum() const;
		unsigned int GetCount() const;
		unsigned int GetStackCount() const;

	private:
		queue<stack<T>> mQueue;
		unsigned int mMaxStackSize;
		unsigned int mCount;
		T mSum;
	};

	template <typename T>
	QueueStack<T>::QueueStack(unsigned int maxStackSize)
		: mMaxStackSize(maxStackSize), mCount(0), mSum(0)
	{
	}

	template <typename T>
	void QueueStack<T>::Enqueue(const T& number)
	{
		const unsigned stackCount = GetStackCount();
		bool bEnqueued = false;

		if (mCount % mMaxStackSize == 0)
		{
			stack<T> s;

			s.push(number);
			mQueue.push(s);

			mSum += number;
			++mCount;

			return;
		}

		for (size_t i = 0; i < stackCount; i++)
		{
			stack<T> s(mQueue.front());
			mQueue.pop();

			if (bEnqueued == false && s.size() < mMaxStackSize)
			{
				s.push(number);
				mSum += number;
				++mCount;
				bEnqueued = true;
			}

			mQueue.push(s);
		}
	}

	template <typename T>
	T QueueStack<T>::Peek()
	{
		stack<T>& frontStack = mQueue.front();
		return frontStack.top();
	}

	template <typename T>
	T QueueStack<T>::Dequeue()
	{
		const unsigned stackCount = GetStackCount();
		bool bDequeued = false;
		T frontTop;

		for (size_t i = 0; i < stackCount; i++)
		{
			stack<T> s = mQueue.front();

			if (bDequeued == false)
			{
				bDequeued = true;
				frontTop = s.top();
				s.pop();
				mSum -= frontTop;
				--mCount;
			}

			if (!s.empty())
			{
				mQueue.push(s);
			}

			mQueue.pop();
		}

		return frontTop;
	}

	template <typename T>
	T QueueStack<T>::GetMax() const
	{
		if (mQueue.empty())
		{
			return numeric_limits<T>().lowest();
		}

		T max = numeric_limits<T>().lowest();

		const unsigned stackCount = GetStackCount();
		queue<stack<T>> q(mQueue);

		for (size_t i = 0; i < stackCount; i++)
		{
			stack<T>& s = q.front();

			const size_t stackSize = s.size();

			for (size_t j = 0; j < stackSize; j++)
			{
				T top = s.top();
				s.pop();

				if (max < top)
				{
					max = top;
				}
			}

			q.pop();
		}

		return max;
	}

	template <typename T>
	T QueueStack<T>::GetMin() const
	{
		if (mQueue.empty())
		{
			return numeric_limits<T>().max();
		}

		T min = numeric_limits<T>().max();

		const unsigned stackCount = GetStackCount();
		queue<stack<T>> q(mQueue);

		for (size_t i = 0; i < stackCount; i++)
		{
			stack<T>& s = q.front();

			const size_t stackSize = s.size();

			for (size_t j = 0; j < stackSize; j++)
			{
				T top = s.top();
				s.pop();

				if (min > top)
				{
					min = top;
				}
			}

			q.pop();
		}

		return min;
	}

	template <typename T>
	double QueueStack<T>::GetAverage() const
	{
		const double sum = static_cast<double>(mSum);
		const double average = sum / mCount;

		return round(average * 1000) / 1000;
	}

	template <typename T>
	T QueueStack<T>::GetSum() const
	{
		return mSum;
	}

	template <typename T>
	unsigned QueueStack<T>::GetCount() const
	{
		return mCount;
	}

	template <typename T>
	unsigned QueueStack<T>::GetStackCount() const
	{
		return mQueue.size();
	}
}
