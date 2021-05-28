#pragma once

#include <memory>
#include <vector>
#include <stack>

namespace assignment4
{
	template<typename T>
	class TreeNode;

	template<typename T>
	class BinarySearchTree final
	{
	public:
		void Insert(std::unique_ptr<T> data);
		bool Search(const T& data);
		bool Delete(const T& data);
		const std::weak_ptr<TreeNode<T>> GetRootNode() const;

		static std::vector<T> TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode);

	private:
		std::shared_ptr<TreeNode<T>> mRootNode;
	};

	template<typename T>
	void BinarySearchTree<T>::Insert(std::unique_ptr<T> data)
	{
		std::shared_ptr<TreeNode<T>> pNode = nullptr;		// parent node
		std::shared_ptr<TreeNode<T>> cNode = mRootNode;		// current node	
		std::shared_ptr<TreeNode<T>> nNode = nullptr;		// new node

		while (cNode != nullptr)
		{
			pNode = cNode;

			if (*data <= *(cNode->Data))
				cNode = cNode->Left;
			else
				cNode = cNode->Right;
		}

		// Create new node.
		

		// pNode�� �ڽ� ���� �� ��带 �߰�
		if (pNode != nullptr)
		{
			if (*data <= *(pNode->Data))
			{
				nNode = std::make_shared<TreeNode<T>>(pNode, std::move(data));
				pNode->Left = nNode;
			}
			else
			{
				nNode = std::make_shared<TreeNode<T>>(pNode, std::move(data));
				pNode->Right = nNode;
			}
		}
		else
		{
			mRootNode = std::make_shared<TreeNode<T>>(std::move(data));//nNode;
		}
	}

	template<typename T>
	const std::weak_ptr<TreeNode<T>> BinarySearchTree<T>::GetRootNode() const
	{
		return mRootNode;
	}

	template<typename T>
	bool BinarySearchTree<T>::Search(const T& data)
	{
		if (mRootNode == nullptr)
		{
			return false;
		}

		std::shared_ptr<TreeNode<T>> cNode = mRootNode;
		T cData;

		while (cNode != nullptr)
		{
			cData = *(cNode->Data);

			if (data == cData)
			{
				return true;
			}
			else if (data <= cData)
			{
				cNode = cNode->Left;
			}
			else
			{
				cNode = cNode->Right;
			}
		}

		return false;
	}

	template<typename T>
	bool BinarySearchTree<T>::Delete(const T& data)
	{
		if (mRootNode == nullptr)
		{
			return false;
		}
		
		std::shared_ptr<TreeNode<T>> pVRoot = std::make_shared<TreeNode<T>>(std::make_unique<T>(0));
		std::shared_ptr<TreeNode<T>> pNode = pVRoot;			// parent node
		std::shared_ptr<TreeNode<T>> cNode = mRootNode;			// current node
		std::shared_ptr<TreeNode<T>> dNode = nullptr;			// delete node

		pVRoot->Right = mRootNode;
		mRootNode->Parent = pVRoot;

		// find delNode data
		while (cNode != nullptr && *(cNode->Data) != data)
		{
			pNode = cNode;

			if (data <= *(cNode->Data))
				cNode = cNode->Left;
			else
				cNode = cNode->Right;
		}

		if (cNode == nullptr)
			return false;

		dNode = cNode;

		// 1: ���� ����� �ܸ� ����� ���
		if (dNode->Left == nullptr && dNode->Right == nullptr)
		{
			if (pNode->Left == dNode)
				pNode->Left = nullptr;
			else
				pNode->Right = nullptr;

			if (dNode == mRootNode)
				mRootNode = nullptr;
		}

		// 2: ���� ����� �ϳ��� �ڽ� ��带 ���� ���
		else if (dNode->Left == nullptr || dNode->Right == nullptr)
		{
			std::shared_ptr<TreeNode<T>> dcNode;

			if (dNode->Left != nullptr)
				dcNode = dNode->Left;
			else
				dcNode = dNode->Right;

			if (pNode->Left == dNode)
			{
				pNode->Left = dcNode;
				dcNode->Parent = pNode;
			}
			else
			{
				pNode->Right = dcNode;
				dcNode->Parent = pNode;
			}

			if (dNode == mRootNode)
			{
				mRootNode = dcNode;
			}
		}

		// 3: �� ���� �ڽ� ��带 ��� ���� ���
		else
		{
			std::shared_ptr<TreeNode<T>> mNode = dNode->Right;			// ��ü ���
			std::shared_ptr<TreeNode<T>> mpNode = dNode;				// ��ü ����� �θ� ���

			// dNode�� �������� �� �� �ڸ��� ä�� ū Data�� ���� ��带 ã�ƾ� ��!
			while (mNode->Left != nullptr)
			{
				mpNode = mNode;
				mNode = mNode->Left;
			}

			// ��ü ��尡 ������ dNode�� ����Ų�ٸ�?
			if (mpNode == dNode && mpNode != mRootNode)
			{
				if (mpNode->Left != nullptr)
				{
					mNode->Left = mpNode->Left;
				}

				mNode->Parent = (mpNode->Parent).lock();
				if (((mpNode->Parent).lock())->Left == mpNode)
				{
					((mpNode->Parent).lock())->Left = mNode;
				}
				else
				{
					((mpNode->Parent).lock())->Right = mNode;
				}
			}
			else if (mpNode == dNode && mpNode == mRootNode)
			{
				mNode->Left = mRootNode->Left;
				mNode->Parent = pVRoot;

				pVRoot->Right = mNode;
				mRootNode = mNode;
			}
			// ��ü ��尡 dNode�� ����Ű�� ���� �� 
			else
			{
				if (mNode->Right == nullptr)
					mpNode->Left = nullptr;
				else
					mpNode->Left = mNode->Right;

				mNode->Left = dNode->Left;
				mNode->Right = dNode->Right;

				mNode->Parent = (dNode->Parent).lock();
				if (((dNode->Parent).lock())->Left == dNode)
				{
					((dNode->Parent).lock())->Left = mNode;
				}
				else
				{
					((dNode->Parent).lock())->Right = mNode;
				}

				if (dNode == mRootNode)
				{
					mRootNode = mNode;
					mRootNode->Left->Parent = mRootNode;
					mRootNode->Right->Parent = mRootNode;
				}
			}
		}

		pVRoot = nullptr;
		return true;
	}

	template<typename T>
	std::vector<T> BinarySearchTree<T>::TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode)
	{
		std::vector<T> v;
		std::stack<std::shared_ptr<TreeNode<T>>> orderStack;
		std::shared_ptr<TreeNode<T>> cur = startNode;
		std::shared_ptr<TreeNode<T>> popPtr = nullptr;

		while (1)
		{
			for (; cur; cur = cur->Left)
				orderStack.push(cur);

			if (!orderStack.empty())
			{
				cur = orderStack.top();
				orderStack.pop();
			}

			if (cur == nullptr) break;

			v.push_back(*(cur->Data));
			cur = cur->Right;
		}

		return v;
	}
}