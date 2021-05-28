#pragma once

#include <memory>
#include <vector>

namespace assignment4
{
	template <typename T>
	class TreeNode;

	template <typename T>
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

	template <typename T>
	void BinarySearchTree<T>::Insert(std::unique_ptr<T> data)
	{
		if (!mRootNode)
		{
			mRootNode = std::make_shared<TreeNode<T>>(std::move(data));
			return;
		}

		std::shared_ptr<TreeNode<T>> curNode = mRootNode;
		std::shared_ptr<TreeNode<T>> parentNode;

		while (curNode)
		{
			parentNode = curNode;

			if (*(parentNode->Data) >= *(data))
			{
				curNode = parentNode->Left;
			}

			else
			{
				curNode = parentNode->Right;
			}
		}

		if (*(parentNode->Data) >= *(data))
		{
			parentNode->Left = std::make_shared<TreeNode<T>>(parentNode, std::move(data));
		}
		else
		{
			parentNode->Right = std::make_shared<TreeNode<T>>(parentNode, std::move(data));
		}
	}

	template <typename T>
	const std::weak_ptr<TreeNode<T>> BinarySearchTree<T>::GetRootNode() const
	{
		return mRootNode;
	}

	template <typename T>
	bool BinarySearchTree<T>::Search(const T& data)
	{
		if (!mRootNode)
		{
			return false;
		}

		std::shared_ptr<TreeNode<T>> curNode = mRootNode;

		while (curNode)
		{
			if (*(curNode->Data) == data)
			{
				return true;
			}

			if (*(curNode->Data) >= data)
			{
				curNode = curNode->Left;
			}
			else
			{
				curNode = curNode->Right;
			}
		}

		return false;
	}

	template <typename T>
	bool BinarySearchTree<T>::Delete(const T& data)
	{
		if (!mRootNode)
		{
			return false;
		}

		std::shared_ptr<TreeNode<T>> curNode = mRootNode;
		std::shared_ptr<TreeNode<T>> parentNode;

		while (curNode)
		{
			if (*(curNode->Data) == data)
			{
				break;
			}

			parentNode = curNode;

			if (*(parentNode->Data) > data)
			{
				curNode = parentNode->Left;
			}

			else
			{
				curNode = parentNode->Right;
			}
		}

		// SEARCH FAILED
		if (!curNode)
		{
			return false;
		}

		// HAVE NO SUBTREE
		if ((curNode->Left == nullptr) && (curNode->Right == nullptr))
		{
			if (parentNode)
			{
				if (parentNode->Left == curNode)
				{
					parentNode->Left = nullptr;
				}
				else
				{
					parentNode->Right = nullptr;
				}
			}
			else
			{
				mRootNode = nullptr;
			}
		}

		// HAVE ONE SUBTREE	
		else if ((curNode->Left == nullptr) || (curNode->Right == nullptr))
		{
			std::shared_ptr<TreeNode<T>> childNode;

			if (curNode->Left)
			{
				childNode = curNode->Left;
			}
			else
			{
				childNode = curNode->Right;
			}

			if (parentNode)
			{
				if (parentNode->Left == curNode)
				{
					parentNode->Left = childNode;
				}
				else
				{
					parentNode->Right = childNode;
				}
			}
			else
			{
				mRootNode = childNode;
			}
		}
		
		// HAVE TWO SUBTREE
		else
		{
			std::shared_ptr<TreeNode<T>> subTreeParentNode = curNode;
			std::shared_ptr<TreeNode<T>> subTreeCurrentNode = curNode->Left;

			while (subTreeCurrentNode->Right)
			{
				subTreeParentNode = subTreeCurrentNode;
				subTreeCurrentNode = subTreeCurrentNode->Right;
			}

			if (subTreeCurrentNode->Left)
			{
				subTreeParentNode->Left = subTreeCurrentNode->Left;
				(subTreeCurrentNode->Left)->Parent = subTreeParentNode;
			}

			if (subTreeParentNode->Left == subTreeCurrentNode)
			{
				subTreeParentNode->Left = nullptr;
			}
			else
			{
				subTreeParentNode->Right = nullptr;
			}

			curNode->Data = nullptr;
			curNode->Data = std::move(subTreeCurrentNode->Data);
		}

		return true;
	}

	template <typename T>
	std::vector<T> BinarySearchTree<T>::TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode)
	{
		std::vector<T> v;

		if (!startNode)
		{
			return v;
		}

		if (startNode->Left)
		{
			std::vector<T> temp = std::move(TraverseInOrder(startNode->Left));
			v.insert(v.end(), temp.begin(), temp.end());
		}
		v.push_back(*(startNode->Data));
		if (startNode->Right)
		{
			std::vector<T> temp = std::move(TraverseInOrder(startNode->Right));
			v.insert(v.end(), temp.begin(), temp.end());
		}

		return v;
	}
}
