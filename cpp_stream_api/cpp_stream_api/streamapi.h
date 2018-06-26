﻿#ifndef STREAMAPI_H
#define STREAMAPI_H
#include <vector>
#include <map>
template<class T>
std::vector<T> drop(const std::vector<T>& arr, size_t pre)
{
	return vector<T>(arr.begin() + pre, arr.end());
}
template<class K, class V>
std::map<K, V> drop(const std::map<K, V>& dic, size_t pre)
{
	typename std::map<K, V>::const_iterator iter = dic.begin();
	for (size_t i = 0; i < pre; i++)++iter;
	return map<K, V>(iter, dic.end());
}

template<class T>
std::vector<T> drop_while(const std::vector<T>& arr, bool(*oper)(const T&, void*), void* other)
{
	std::vector<T> result;
	for (typename std::vector<T>::const_iterator iter = arr.begin();
		iter != arr.end(); ++iter)
		if (!oper(*iter, other))result.push_back(*iter);
	return result;
}

template<class K, class V>
std::map<K, V> drop_while(const std::map<K, V>& dic, bool(*oper)(const std::pair<K, V>&, void*), void* other)
{
	std::map<K, V> result;
	for (typename std::map<K, V>::const_iterator iter = dic.begin();
		iter != dic.end(); ++iter)
	{
		const std::pair<K, V> kv = *iter;
		if (!oper(kv, other))result[kv.first] = kv.second;
	}
	return result;
}

template<class T>
std::vector<T> filter(const std::vector<T>& arr, bool(*oper)(const T&, void*), void* other)
{
	std::vector<T> result;
	for (typename std::vector<T>::const_iterator iter = arr.begin();
		iter != arr.end(); ++iter)
	{
		if (oper(*iter, other))result.push_back(*iter);
	}
	return result;
}

template<class K, class V>
std::map<K, V> filter(const std::map<K, V>& dic, bool(*oper)(const std::pair<K, V>&, void*), void* other)
{
	std::map<K, V> result;
	for (typename std::map<K, V>::const_iterator iter = dic.begin();
		iter != dic.end(); ++iter)
	{
		const std::pair<K, V> kv = *iter;
		if (oper(kv, other)) result[kv.first] = kv.second;
	}
	return result;
}


#endif // STREAMAPI_H