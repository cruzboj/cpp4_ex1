#include <iostream>
#include <map>
#include <memory>
#include <exception>
#include <string>
#include <vector>

// using namespace std;

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

    //tester
    ~CacheMemory(){ std::cout << "caceh memory destructor" << std::endl; }
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
        else{
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

    // main for testing
    int main()
    {
        try
        {
            CacheMemory<int, std::string> memory;
            memory.add(1, "Hello");
            //cache.add(1, "hello"); // This should throw an exception
            memory.erase(1);
            //cache.erase(1); // This should throw an exception

            memory.add(1, "Hello");
            std::shared_ptr<std::string> a = memory.get(1);
            std::weak_ptr<std::string> a_copy = a;

            memory.add(2, "world");
            std::shared_ptr<std::string> b = memory.get(2);

            std::vector<std::string> values = memory.getCacheValues();

            std::cout << "Cache values:" << std::endl;
            for (const auto &val : values)
            {
                std::cout << val << std::endl;
            }
            memory.erase(1);
            memory.erase(2);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
        return 0;
    }
