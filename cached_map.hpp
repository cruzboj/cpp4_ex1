#ifndef CACHED_MAP_HPP
#define CACHED_MAP_HPP

#include <iostream>
#include <map>
#include <memory>
#include <exception>
#include <string>
#include <vector>

template <typename K, typename V>
class CacheMemory
{
    std::map<K, std::shared_ptr<V>> archive;
    std::map<K, std::weak_ptr<V>> cache;
public:
    void add(const K &key, const V &value);
    void erase(const K &key);
    std::shared_ptr<V> get(const K &key);
    std::vector<V> getCacheValues();

    // tester
    ~CacheMemory() { std::cout << "caceh memory destructor" << std::endl; }
};

template <typename K, typename V>
void CacheMemory<K, V>::add(const K &key, const V &value)
{
    if (cache.find(key) != cache.end())
    {
        throw std::runtime_error("DuplicateKeyException");
    }

    std::shared_ptr<V> ptr = std::make_shared<V>(value);
    cache[key] = ptr;
    archive[key] = ptr;
}

template <typename K, typename V>
void CacheMemory<K, V>::erase(const K &key)
{
    auto it = cache.find(key);
    if (it != cache.end())
    {
        cache.erase(it);
        archive.erase(key);
    }
    else
    {
        throw std::runtime_error("ObjectNotExistException");
    }
}

template <typename K, typename V>
std::shared_ptr<V> CacheMemory<K, V>::get(const K &key)
{
    // 1. אם הערך קיים ב-cache (weak_ptr):
    auto it_cache = cache.find(key);
    if (it_cache != cache.end())
    {
        if (auto ptr_shared = it_cache->second.lock()) {
            return ptr_shared;  // מחזיר את ה-shared_ptr אם הוא עדיין חי
        }
    }

    // 2. אם הערך לא קיים ב-cache, חפש ב-archive:
    auto it_archive = archive.find(key);
    if (it_archive != archive.end())
    {
        // שמור את ה-shared_ptr ב-cache כדי להשתמש בו בעתיד
        auto ptr_shared = it_archive->second;
        cache[key] = ptr_shared;  // הוסף ל-cache כ-weak_ptr
        return ptr_shared;        // החזר את ה-shared_ptr
    }

    // 3. אם לא נמצא ב-cache וגם לא ב-archive, החזר nullptr
    return nullptr;
}

template <typename K, typename V>
std::vector<V> CacheMemory<K, V>::getCacheValues()
{
    std::vector<V> values;
    for (const auto &pair : cache)
    {
        if (auto sp = pair.second.lock()) {
            values.push_back(*sp);
        }
    }
    return values;
}

#endif