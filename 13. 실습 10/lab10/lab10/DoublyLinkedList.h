#pragma once

#include <memory>

namespace lab10
{
	template<typename T>
	class Node;

	/* 양방향 연결리스트 */
	template<typename T>
	class DoublyLinkedList
	{
	public:
		DoublyLinkedList();
		void Insert(std::unique_ptr<T> data);
		void Insert(std::unique_ptr<T> data, unsigned int index);
		bool Delete(const T& data);
		bool Search(const T& data) const;

		std::shared_ptr<Node<T>> operator[](unsigned int index) const;
		unsigned int GetLength() const;
		void PrintList() const;

	private:
		std::shared_ptr<Node<T>> mHead;
		size_t mLength;
	};

	template<typename T>
	DoublyLinkedList<T>::DoublyLinkedList()
		: mLength(0)
		, mHead(nullptr)
	{

	}

	template<typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data)
	{
		if (data == nullptr)
		{
			return;
		}

		if (mLength == 0)
		{
			mHead = std::make_shared<Node<T>>(std::move(data));
			++mLength;

			return;
		}
	
		std::shared_ptr<Node<T>> temp = std::make_shared<Node<T>>(std::move(data), (*this)[mLength - 1]);
		(*this)[mLength - 1]->Next = temp;

		++mLength;
	}

	template<typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data, unsigned int index)
	{
		if (data == nullptr)
		{
			return;
		}

		if (mLength == 0)
		{
			mHead = std::make_shared<Node<T>>(std::move(data));
		}
		else if (index == 0)
		{
			std::shared_ptr<Node<T>> temp = std::make_shared<Node<T>>(std::move(data));
			temp->Next = mHead;
			mHead->Previous = temp;
			
			mHead = temp;
		}
		else if (index >= mLength)
		{
			std::shared_ptr<Node<T>> temp = (*this)[mLength - 1];

			temp->Next = std::make_shared<Node<T>>(std::move(data), temp);
		}
		else
		{
			std::shared_ptr<Node<T>> temp = (*this)[index - 1];
			std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(std::move(data), temp);

			newNode->Next = temp->Next;
			temp->Next = newNode;

			newNode->Previous = temp;
			newNode->Next->Previous = newNode;
		}

		++mLength;
	}

	template<typename T>
	bool DoublyLinkedList<T>::Delete(const T& data)
	{
		if (mLength == 0)
		{
			return false;
		}

		size_t delIndex = 0;
		bool delFlag = false;
		std::shared_ptr<Node<T>> delNode = nullptr;

		for (size_t i = 0; i < mLength; i++)
		{
			if (*((*this)[i]->Data) == data)
			{
				delIndex = i;
				delFlag = true;
				delNode = (*this)[i];
				break;
			}
		}

		if ((delFlag == true))
		{
			if (mLength == 1)
			{
				delNode = nullptr;
				--mLength;

				return true;
			}

			if (delIndex == 0)
			{
				mHead = delNode->Next;
				delNode = nullptr;
			}
			else if (delIndex == (mLength - 1))
			{
				(delNode->Previous.lock())->Next = nullptr;
			}
			else
			{
				std::shared_ptr<Node<T>> prevNode = (delNode->Previous).lock();
				prevNode->Next = delNode->Next;
				delNode->Next->Previous = prevNode;

				delNode->Next = nullptr;
			}
			
			--mLength;

			return true;
		}

		return false;
	}

	template<typename T>
	bool DoublyLinkedList<T>::Search(const T& data) const
	{
		if (mLength == 0)
		{
			return false;
		}

		bool findFlag = false;

		for (size_t i = 0; i < mLength; i++)
		{
			if (*((*this)[i]->Data) == data)
			{
				findFlag = true;
				break;
			}
		}


		if (findFlag != false)
		{
			return true;
		}

		return false;
	}

	template<typename T>
	std::shared_ptr<Node<T>> DoublyLinkedList<T>::operator[](unsigned int index) const
	{
		if ((index >= mLength) || (mLength == 0))
		{
			return nullptr;
		}

		unsigned int count = 0;
		std::shared_ptr<Node<T>> temp = mHead;

		while (temp != nullptr)
		{
			if (count == index)
			{
				break;
			}

			temp = temp->Next;
			++count;
		}
		
		return temp;
	}

	template<typename T>
	unsigned int DoublyLinkedList<T>::GetLength() const
	{
		return mLength;
	}

	template<typename T>
	void DoublyLinkedList<T>::PrintList() const
	{
		for (size_t i = 0; i < mLength; i++)
		{
			std::cout << *((*this)[i]->Data) << ", ";
		}

		std::cout << std::endl;
	}
}
