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

		~SmartStack();

		void Push(const T& data);
		T Pop(void);
		T Peek(void) const;
		bool Empty(void) const;
		T GetMax(void) const;
		T GetMin(void) const;
		double GetAverage(void) const;
		T GetSum(void) const;
		double GetVariance(void) const;
		double GetStandardDeviation(void) const;
		unsigned int GetCount(void) const;


	private:
		T* mStackList;
		T mDtMax;
		T mDtMin;
		T mDtTotal;
		double mDtAverage;
		double mDtVariance;

		size_t mSize;
		size_t mCapacity;
	};

	template <typename T>
	inline SmartStack<T>::SmartStack()
		: mDtMax(0)
		, mDtMin(0)
		, mDtTotal(0)
		, mDtAverage(0)
		, mDtVariance(0.0)
		, mSize(0)
		, mCapacity(2)
	{
		mStackList = new T[mCapacity];
		for (unsigned int i = 0; i < mCapacity; i++)
		{
			mStackList[i] = 0;
		}
	}

	template <typename T>
	inline SmartStack<T>& SmartStack<T>::operator=(const SmartStack<T>& other)
	{
		if (this == &other)
		{
			return *this;
		}

		mDtMax = other.mDtMax;
		mDtMin = other.mDtMin;
		mDtTotal = other.mDtTotal;
		mDtAverage = other.mDtAverage;
		mDtVariance = other.mDtVariance;
		mSize = other.mSize;
		mCapacity = other.mCapacity;

		delete mStackList;
		mStackList = new T[mCapacity];

		for (unsigned int i = 0; i < mSize; i++)
		{
			mStackList[i] = other.mStackList[i];
		}

		return *this;
	}

	template <typename T>
	inline SmartStack<T>::~SmartStack()
	{
		delete mStackList;
	}

	/*
	template <typename T>
	SmartStack<T>& SmartStack<T>::operator[](unsigned int idx)
	{

	}
	*/

	template <typename T>
	inline void SmartStack<T>::Push(const T& data)
	{
		if (mSize >= mCapacity)
		{
			mCapacity *= 2;
			T* temp = mStackList;
			mStackList = new T[mCapacity];

			for (size_t i = 0; i < mSize; i++)
			{
				mStackList[i] = temp[i];
			}
		}

		if (mSize == 0)
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

		/* Push the Data */
		mStackList[mSize++] = data;

		/* Calculate sum of stack & average of stack */
		mDtTotal += data;
		mDtAverage = static_cast<double>(mDtTotal) / static_cast<double>(mSize);

		/* Calculate Variance & StandardDeviation */
		float tempVariance = 0.0f;
		for (size_t i = 0; i < mSize; i++)
		{
			tempVariance += powf(static_cast<float>(mStackList[i]) - static_cast<float>(mDtAverage), 2.0f);
		}

		mDtVariance = static_cast<double>(tempVariance / mSize);
	}

	template <typename T>
	inline T SmartStack<T>::Pop(void)
	{
		T popData = Peek();

		mSize--;
		mDtMax = mStackList[0], mDtMin = mStackList[0];
		mDtTotal = 0;
		
		for (size_t i = 0; i < mSize; i++)
		{
			if (mDtMax < mStackList[i])
				mDtMax = mStackList[i];
			else if (mDtMin > mStackList[i])
				mDtMin = mStackList[i];

			mDtTotal += mStackList[i];
		}

		mDtAverage = static_cast<double>(mDtTotal) / static_cast<double>(mSize);

		float tempVariance = 0.0f;
		for (size_t i = 0; i < mSize; i++)
		{
			tempVariance += powf(static_cast<float>(mStackList[i]) - static_cast<float>(mDtAverage), 2.0f);
		}

		mDtVariance = static_cast<double>(tempVariance / mSize);

		return popData;
	}

	template <typename T>
	inline T SmartStack<T>::Peek(void) const
	{
		return mStackList[mSize - 1];
	}

	template <typename T>
	inline bool SmartStack<T>::Empty(void) const
	{
		if (mSize == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	inline T SmartStack<T>::GetMax(void) const
	{
		if (Empty())
		{
			return std::numeric_limits<T>::min();
		}

		return mDtMax;
	}

	template <typename T>
	inline T SmartStack<T>::GetMin(void) const
	{
		if (Empty())
		{
			return std::numeric_limits<T>::max();
		}

		return mDtMin;
	}

	template <typename T>
	inline double SmartStack<T>::GetAverage(void) const
	{
		if (Empty())
		{
			return 0;
		}

		/* 소수점 4째자리에서는 반올림 */
		return static_cast<double>(roundf(static_cast<float>(mDtAverage) * 1000.f) / 1000.0);
	}

	template <typename T>
	inline T SmartStack<T>::GetSum(void) const
	{
		if (Empty())
		{
			return 0;
		}

		return mDtTotal;
	}

	template <typename T>
	inline double SmartStack<T>::GetVariance(void) const
	{
		return static_cast<double>(roundf(static_cast<float>(mDtVariance) * 1000.f) / 1000.0);
	}

	template <typename T>
	inline double SmartStack<T>::GetStandardDeviation(void) const
	{
		return static_cast<double>(roundf(sqrtf(static_cast<float>(mDtVariance)) * 1000.f) / 1000.0);
	}

	template <typename T>
	inline unsigned int SmartStack<T>::GetCount(void) const
	{
		return mSize;
	}
}