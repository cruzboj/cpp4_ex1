#include "cached_map.hpp"
#include "employee.hpp"

int main()
{
    std::vector<Employee> employees = load("emps.bin");

    //2th test
    // std::vector<Employee> employees = load("newemps.bin");

    CacheMemory<int, Employee> memory;
    std::vector<Employee> successfulEmployees;

    for (const auto& emp : employees) {
        try {
            memory.add(emp.getId(), emp);
            successfulEmployees.push_back(emp);
        }
        catch (const std::exception &e) {
            std::cerr << "Exception ID: " << (int)emp.getId() << ": " << e.what() << std::endl;
            continue;
        }
    }

    std::cout << "Cache values:" << std::endl;
    for (const auto& val : memory.getCacheValues())
    {
        val.print();
    }

    //test for newfile (newemps.bin)
    std::cout << "Employees data:" << std::endl;
    for (const auto& emp : employees) {
        emp.print(); 
    }

    save("newemps.bin", successfulEmployees);

    for (const auto& val : memory.getCacheValues()) {
        memory.erase(val.getId());  // מחיקת כל עובד מה-cache לפי ה-ID
    }
    
    return 0;
}