#pragma once

#include <memory>

namespace lab11
{
	template<typename T>
	class Storage
	{
	public:
		Storage(unsigned int length);
		Storage(unsigned int length, const T& initialValue);

		/* copy instructor */
		Storage(const Storage& other);
		/* copy assignment */
		Storage& operator=(const Storage& other);
		/* move instructor */
		Storage(Storage&& other);
		/* move assignment*/
		Storage& operator=(Storage&& other);

		bool Update(unsigned int index, const T& data);
		const std::unique_ptr<T[]>& GetData() const;
		unsigned int GetSize() const;

	private:
		std::unique_ptr<T[]> mDataList;
		size_t mSize;
	};

	template<typename T>
	Storage<T>::Storage(unsigned int length)
		: mDataList(std::make_unique<T[]>(length))
		, mSize(length)
	{
		for (size_t i = 0; i < length; i++)
			mDataList[i] = T();
	}

	template<typename T>
	Storage<T>::Storage(unsigned int length, const T& initialValue)
		: mDataList(std::make_unique<T[]>(length))
		, mSize(length)
	{
		for (size_t i = 0; i < length; i++)
			mDataList[i] = initialValue;
	}

	/* copy instructor */
	template<typename T>
	Storage<T>::Storage(const Storage<T>& other)
		: mDataList(std::make_unique<T[]>(other.mSize))
		, mSize(other.mSize)
	{
		for (size_t i = 0; i < mSize; i++)
		{
			mDataList[i] = other.mDataList[i];
		}
	}

	/* copy assignment */
	template<typename T>
	Storage<T>& Storage<T>::operator=(const Storage<T>& other)
	{
		if (this == &other)
		{
			return *this;
		}

		mDataList.reset(nullptr);
		mDataList = std::make_unique<T[]>(other.mSize);
		mSize = other.mSize;

		for (size_t i = 0; i < mSize; i++)
		{
			mDataList[i] = other.mDataList[i];
		}

		return *this;
	}

	/* move constructor */
	template<typename T>
	Storage<T>::Storage(Storage<T>&& other)
		: mDataList(std::move(other.mDataList))
		, mSize(other.mSize)
	{
		other.mSize = 0;
	}

	/* move assignment */
	template<typename T>
	Storage<T>& Storage<T>::operator=(Storage<T>&& other)
	{
		if (this == &other)
		{
			return *this;
		}

		mDataList.reset(nullptr);
		mDataList = std::move(other.mDataList);
		mSize = other.mSize;

		other.mSize = 0;

		return *this;
	}

	template<typename T>
	bool Storage<T>::Update(unsigned int index, const T& data)
	{
		if (index >= mSize)
			return false;

		mDataList[index] = data;
		return true;
	}

	template<typename T>
	const std::unique_ptr<T[]>& Storage<T>::GetData() const
	{
		return std::move(mDataList);
	}

	template<typename T>
	unsigned int Storage<T>::GetSize() const
	{
		return mSize;
	}
}