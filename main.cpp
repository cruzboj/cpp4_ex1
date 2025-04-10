#include "cached_map.hpp"
#include "employee.hpp"

int main()
{
    std::vector<Employee> employees = load("emps.bin");
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

    // std::cout << "Employees data:" << std::endl;
    // for (const auto& emp : employees) {
    //     emp.print(); 
    // }
    

    save("newemps.bin", successfulEmployees);

    return 0;
}