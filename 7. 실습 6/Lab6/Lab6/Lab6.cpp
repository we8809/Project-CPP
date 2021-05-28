#include "Lab6.h"

#include <set>

namespace lab6
{
	int Sum(const std::vector<int>& v)
	{
		if (v.size() == 0)
		{
			return 0;
		}

		int sum = 0;
		std::vector<int>::const_iterator iter;
		for (iter = v.begin(); iter != v.end(); ++iter)
		{
			sum += *iter;
		}

		return sum;
	}

	int Min(const std::vector<int>& v)
	{
		if (v.size() == 0)
		{
			return INT_MAX;
		}

		std::vector<int>::const_iterator iter;
		int min = *(v.begin());
		
		for (iter = v.begin(); iter != v.end(); ++iter)
		{
			if (min > (*iter))
			{
				min = *iter;
			}
		}

		return min;
	}

	int Max(const std::vector<int>& v)
	{
		if (v.size() == 0)
		{
			return INT_MIN;
		}

		std::vector<int>::const_iterator iter;
		int max = *(v.begin());

		for (iter = v.begin(); iter != v.end(); ++iter)
		{
			if (max < *iter)
			{
				max = *iter;
			}
		}

		return max;
	}

	float Average(const std::vector<int>& v)
	{
		if (v.size() == 0)
		{
			return 0.0f;
		}

		if (v.size() == 1)
		{
			return static_cast<float>(v[0]);
		}

		std::vector<int>::const_iterator iter;
		float average = 0.0f;

		for (iter = v.begin(); iter != v.end(); ++iter)
		{
			average += static_cast<float>(*iter);
		}

		average /= static_cast<float>(v.size());

		return average;
	}

	int NumberWithMaxOccurrence(const std::vector<int>& v)
	{
		if (v.size() == 0)
		{
			return 0;
		}
		
		std::multiset<int> countMs;
		std::vector<int>::const_iterator iter;

		int i = 0;
		for (iter = v.begin(); iter != v.end(); ++iter)
		{
			countMs.insert(*iter);
		}

		unsigned int maxCount = countMs.count(v[0]);
		int maxOccurenceData = v[0];

		for (unsigned int i = 1; i < v.size(); i++)
		{
			if (maxCount < countMs.count(v[i]))
			{
				maxCount = countMs.count(v[i]);
				maxOccurenceData = v[i];
			}
		}

		return maxOccurenceData;
	}

	void SortDescending(std::vector<int>& v)
	{
		if (v.size() == 0)
		{
			return;
		}

		for (unsigned int i = v.size() - 1; i > 0; i--)
		{
			for (unsigned int j = 0; j < i; j++)
			{
				if (v[j] < v[j + 1])
				{
					int temp = v[j];
					v[j] = v[j + 1];
					v[j + 1] = temp;
				}
			}
		}
	}

	/*
	void Swap(std::vector<int>& v, int idx1, int idx2)
	{
		int temp = v[idx1];
		v[idx1] = v[idx2];
		v[idx2] = temp;
	}

	int Partition(std::vector<int>& v, int left, int right)
	{
		int pivot;

		int low = left + 1;
		int high = right;
		pivot = v[left];

		while (low <= high)    // 교차되지 않을 때까지 반복
		{	
			while(pivot <= v[low] && low <= right)
				low++;

			while(pivot >= v[high] && high >= (left+1))
				high--;
			

			if (low <= high)    // 교차되지 않은 상태라면 Swap 실행
				Swap(v, low, high);    // low와 high가 가리키는 대상 교환
		}


		Swap(v, left, high);

		return high;
	}

	void QuickSort(std::vector<int>& v, int left, int right)
	{
		if (left <= right)
		{
			int pivot = Partition(v, left, right);    // 둘로 나눠서
			QuickSort(v, left, pivot - 1);    // 왼쪽 영역을 정렬
			QuickSort(v, pivot + 1, right);    // 오른쪽 영역을 정렬
		}

		else
		{
			return;
		}
	}
	*/
}