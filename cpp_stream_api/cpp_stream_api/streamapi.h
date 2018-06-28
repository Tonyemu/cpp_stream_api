#ifndef STREAMAPI_H
#define STREAMAPI_H
#include <vector>
#include <map>
#include <algorithm>

class StreamAPI
{

public:
	template<class T>
	static 	std::vector<T> drop(const std::vector<T>& arr, size_t pre)
	{
		return vector<T>(arr.begin() + pre, arr.end());
	}
	template<class K, class V>
	static 	std::map<K, V> drop(const std::map<K, V>& dic, size_t pre)
	{
		typename std::map<K, V>::const_iterator iter = dic.begin();
		for (size_t i = 0; i < pre; i++)++iter;
		return map<K, V>(iter, dic.end());
	}

	template<class T>
	static 	std::vector<T> drop_while(const std::vector<T>& arr, bool(*oper)(const T&, const void*), const void* other)
	{
		std::vector<T> result;
		for (typename std::vector<T>::const_iterator iter = arr.begin();
			iter != arr.end(); ++iter)
			if (!oper(*iter, other))result.push_back(*iter);
		return result;
	}

	template<class K, class V>
	static 	std::map<K, V> drop_while(const std::map<K, V>& dic, bool(*oper)(const std::pair<K, V>&, const void*), const void* other)
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
	static 	std::vector<T> filter(const std::vector<T>& arr, bool(*oper)(const T&, const void*), const void* other)
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
	static 	std::map<K, V> filter(const std::map<K, V>& dic, bool(*oper)(const std::pair<K, V>&, const void*), const void* other)
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

	template<class K, class V>
	static 	bool contains_key(const std::map<K, V>& dic, const K& k)
	{
		return dic.find(k) != dic.end();
	}



	template<class K, class V>
	static 	bool contains_value(const std::map<K, V>& dic, const V& v)
	{
		for (typename std::map<K, V>::const_iterator iter = dic.begin();
			iter != dic.end(); ++iter)
		
			if (iter->second == v)return true;
		return false;
	}

	template<class T>
	static bool contains(const std::vector<T>& arr, const T& t)
	{
		// std::vector<T> sorted(arr);
		// std::sort(sorted.begin(), sorted.end());
		return std::find(arr.begin(), arr.end(), t) != arr.end();
		for (typename std::vector<T>::const_iterator iter = arr.begin();
			iter != arr.end(); ++iter)
			if (*iter == t)return true;
		return false;
	}
	template<class T>
	static bool contains1(const std::vector<T>& arr, const T& t)
	{
		for (typename std::vector<T>::const_iterator iter = arr.begin();
			iter != arr.end(); ++iter)
			if (*iter == t)return true;
		return false;
	}

	template<class T>
	static int index_fist(const std::vector<T>& arr, const T& t)
	{
		for (typename std::vector<T>::const_iterator iter = arr.begin();
			iter != arr.end(); ++iter)
			if (*iter == t)return iter - arr.begin();
		return -1;
	}

	template<class T>
	static T* find(const std::vector<T>& arr, const T& t, bool(*oper)(const T& it, const void* other))
	{
		
	}

	template<class K, class V, class T>
	static 	std::map<K, V> vector_to_map(const std::vector<T>& src, std::pair<K, V>(*gn)(size_t, T&, const void*), const void*other)
	{
		std::map<K, V> result;
		size_t index = 0;
		for (typename std::vector<T>::const_iterator iter = src.begin();
			iter != src.end(); ++iter, index++)
		{
			result.insert(gn(index, *iter, other));
		}
		return result;
	}

	template<class K, class V, class T>
	static 	std::vector<T> map_to_vector(const std::map<K, V>& src, T(*gn)(K&, V&, const void*), const void*other)
	{
		std::vector<T> result;
		for (typename std::map<K, V>::const_iterator iter = src.begin();
			iter != src.end(); ++iter)
		{
			std::pair<K, V> p = *iter;
			result.push_back(gn(p.first, p.second, other));
		}
		return result;
	}

	template<class T, class I>
	static 	std::vector<I> vector_to_vector(const std::vector<T>& src, I(*gn)(const T&, const void*), const void*other)
	{
		std::vector<I>result;
		for (typename std::vector<T>::const_iterator iter = src.begin();
			iter != src.end(); ++iter)
		{
			result.push_back(gn(*iter, other));
		}
		return result;
	}

#ifdef STREAMAPI_CPP_11

	template<class T, class... Args>
	static 	std::vector<T> array_of(const Args&... args)
	{
		T arr[] = { expand(args)... };

		const size_t args_size = sizeof...(args);
		std::vector<T> result(arr, arr + args_size);
		
		// for (size_t i = 0; i < args_size; ++i)
		// {
		// 	result.push_back(arr[i]);
		// }
		return result;
	}

	template<class K, class V, class... Args>
	static 	std::map<K, V> map_of(const Args&... args)
	{
		
		std::pair<K, V> pairs[] = { expand(args)... };
		const size_t args_size = sizeof...(args);
		std::map<K, V> result(pairs,pairs+args_size);
		// for (size_t i = 0; i < args_size; ++i)
		// {
		// 	result.insert(pairs[i]);
		// }
		return result;
	}

#endif
private:
	template<class T>
	static 	T expand(const T& t)
	{
		return t;
	}

	template<class K,class V>
	static bool filter_opter(const std::pair<K, V>& p, const void*other)
	{
		V v = *static_cast<const V*>(other);
		return p.second == v;
	}
};

#endif // STREAMAPI_H
