#pragma once
#include <vector>
#include <unordered_map>
#include <string>

namespace rave
{
	template<typename T>
	class Codex
	{
	public:
		T* Get(const char* key)
		{
			auto it = map.find(key);
			if (it == map.end())
				return nullptr;
			return &it->second;
		}

		void Add(const char* key, const T& t)
		{
			map[key] = t;
		}

		void Remove(const char* key)
		{
			auto it = map.find(key);
			if (it == map.end())
				return;
			map.erase(it);
		}

	private:
		std::unordered_map<std::string, T> map;
	};
}