#include "cached_map.hpp"
#include "employee.hpp"

int main()
{
    try
    {
        // CacheMemory<int, std::string> memory;
        CacheMemory<Employee, Employee> memory;
        // memory.add(1, "Hello");
        // //memory.add(1, "hello"); // This should throw an exception
        // memory.erase(1);
        // // memory.erase(1); // This should throw an exception

        // memory.add(1, "Hello");
        // std::shared_ptr<std::string> a = memory.get(1);
        // std::weak_ptr<std::string> a_copy = a;

        // memory.add(2, "world");
        // std::shared_ptr<std::string> b = memory.get(2);

        // std::vector<std::string> values = memory.getCacheValues();

        
        // memory.erase(1);
        // memory.erase(2);

        Employee emp1(1, 1000, 5);
        memory.add(emp1, emp1);

        std::vector<Employee> values = memory.getCacheValues();

        std::cout << "Cache values:" << std::endl;
        for (const auto& val : values)
        {
            std::cout << val << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}