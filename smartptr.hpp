#ifndef SMARTPTR_HPP
#define SMARTPTR_HPP

#include <iostream>
#include <map>
#include <memory>
#include <exception>
#include <string>
#include <vector>

template <typename K, typename V>
class CacheMemory
{
    std::map<K, std::shared_ptr<V>> cache;
    std::map<K, std::weak_ptr<V>> archive;
    // std::shared_ptr<V> cache;
    // std::weak_ptr<V> archive;

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
    if (archive.find(key) != archive.end())
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
    auto it = archive.find(key);
    if (it != archive.end())
    {
        archive.erase(it);
        cache.erase(key);
    }
    else
    {
        throw std::runtime_error("ObjectNotExistException");
    }
}

template <typename K, typename V>
std::shared_ptr<V> CacheMemory<K, V>::get(const K &key)
{
    auto it = cache.find(key);
    if (it != cache.end()) // אם קיים במפת ה-shared_ptr
    {
        return it->second; // מחזיר את הערך שמאוחסן ב-shared_ptr
    }
    else // אם לא קיים במפה
    {
        // אפשר להחזיר nullptr אם לא נמצא הערך
        return nullptr;
    }
}

template <typename K, typename V>
std::vector<V> CacheMemory<K, V>::getCacheValues()
{
    std::vector<V> values;
    for (const auto &pair : cache)
    {
        values.push_back(*(pair.second));
    }
    return values;
}

#endif