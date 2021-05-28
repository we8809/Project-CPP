#pragma once

#include <queue>

namespace lab9
{
	template <class T>
	class ObjectPool
	{
	public:
		ObjectPool() = delete;
		ObjectPool(size_t maxPoolSize);
		ObjectPool(const ObjectPool&) = delete;
		~ObjectPool();

		ObjectPool& operator=(const ObjectPool&) = delete;
		T* Get(void);
		void Return(T* object);
		size_t GetFreeObjectCount() const;
		size_t GetMaxFreeObjectCount() const;

	private:
		std::queue<T*> mPoolList;
		size_t mMaxPoolSize;
	};

	template <class T>
	ObjectPool<T>::ObjectPool(size_t maxPoolSize)
		: mMaxPoolSize(maxPoolSize)
	{

	}

	template <class T>
	ObjectPool<T>::~ObjectPool()
	{
		if (!mPoolList.empty())
		{
			size_t delSize = mPoolList.size();

			for (size_t i = 0; i < delSize; i++)
			{
				T* delObj = mPoolList.front();
				mPoolList.pop();

				delete delObj;
			}
		}
	}

	template <class T>
	T* ObjectPool<T>::Get(void)
	{
		if (!mPoolList.empty())
		{
			T* retObj = mPoolList.front();
			mPoolList.pop();

			return retObj;
		}

		T* retObj = new T();
		return retObj;
	}

	template <class T>
	void ObjectPool<T>::Return(T* object)
	{
		if (mPoolList.size() == mMaxPoolSize)
		{
			delete object;
			return;
		}

		mPoolList.push(object);
	}

	template <class T>
	size_t ObjectPool<T>::GetFreeObjectCount() const
	{
		return mPoolList.size();
	}

	template <class T>
	size_t ObjectPool<T>::GetMaxFreeObjectCount() const
	{
		return mMaxPoolSize;
	}
}