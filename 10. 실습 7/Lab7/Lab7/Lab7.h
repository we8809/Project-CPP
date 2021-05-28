#pragma once

#include <iostream>
#include <vector>
#include <map>	

namespace lab7
{
	template <typename K, class V>
	std::map<K, V> ConvertVectorsToMap(const std::vector<K>& keys, const std::vector<V>& values)
	{
		std::map<K, V> m;

		if (keys.size() == 0 || values.size() == 0)
		{
			return m;
		}
		
		size_t totalSize = (keys.size() >= values.size()) ? values.size() : keys.size();
		for (size_t i = 0; i < totalSize; i++)
		{
			m.insert(std::pair<K, V>(keys[i], values[i]));
		}
		
		return m;
	}

	template <typename K, class V>
	std::vector<K> GetKeys(const std::map<K, V>& m)
	{
		std::vector<K> v;
		if (m.size() == 0)
		{
			return v;
		}

		typename std::map<K, V>::const_iterator iter;
		for (iter = m.cbegin(); iter != m.cend(); ++iter)
		{
			v.push_back(iter->first);
		}
		
		return v;
	}

	template <typename K, class V>
	std::vector<V> GetValues(const std::map<K, V>& m)
	{
		std::vector<V> v;
		if (m.size() == 0)
		{
			return v;
		}

		typename std::map<K, V>::const_iterator iter;
		for (iter = m.cbegin(); iter != m.cend(); ++iter)
		{
			v.push_back(iter->second);
		}

		return v;
	}


	template <typename T>
	std::vector<T> Reverse(const std::vector<T>& v)
	{
		std::vector<T> rv;
		if (v.size() == 0)
		{
			return rv;
		}
		if (v.size() == 1)
		{
			rv.push_back(v[0]);
			return rv;
		}
		
		typename std::vector<T>::const_reverse_iterator iter;
		for (iter = v.crbegin(); iter != v.crend(); ++iter)
		{
			rv.push_back(*iter);
		}
		
		return rv;
	}

	template <typename T>
	std::vector<T> operator+(const std::vector<T>& v1, const std::vector<T>& v2)
	{
		std::vector<T> combined;
		combined.reserve(v1.size() + v2.size());

		bool chkFlag = false;
		typename std::vector<T>::const_iterator iter1, iter2;

		for (iter1 = v1.begin(); iter1 != v1.end(); ++iter1)
		{
			for (size_t i = 0; i < combined.size(); i++)
			{
				if (combined[i] == *iter1)
				{
					chkFlag = true;
					break;
				}
			}

			if (chkFlag != true)
				combined.push_back(*iter1);
			else
				chkFlag = false;
		}

		chkFlag = false;
		for (iter2 = v2.begin(); iter2 != v2.end(); ++iter2)
		{
			for (size_t i = 0; i < combined.size(); i++)
			{
				if (combined[i] == *iter2)
				{
					chkFlag = true;
					break;
				}
			}

			if (chkFlag != true)
				combined.push_back(*iter2);
			else
				chkFlag = false;
		}

		return combined;
	}

	template <typename K, class V>
	std::map<K, V> operator+(const std::map<K, V>& m1, const std::map<K, V>& m2)
	{
		std::map<K, V> combined;

		combined.insert(m1.begin(), m1.end());
		combined.insert(m2.begin(), m2.end());

		return combined;
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
	{
		/*
		typename std::vector<T>::const_iterator iter;

		for (iter = v.cbegin(); iter != v.cend(); iter++)
		{
			os << *iter << ", ";
		}
		*/
		for (size_t i = 0; i < v.size(); i++)
		{
			if (i == v.size() - 1)
			{
				os << v[i];
				break;
			}

			os << v[i] << ", ";
		}

		return os;
	}

	template <typename K, class V>
	std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m)
	{
		typename std::map<K, V>::const_iterator iter;

		for (iter = m.cbegin(); iter != m.cend(); iter++)
		{
			os << "{ " << iter->first << ", " << iter->second << " }" << "\n";
		}

		return os;
	}
}