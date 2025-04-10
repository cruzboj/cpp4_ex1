#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

class Employee
{
    int id;
    int salary;
    int seniority;

    public:
        Employee(int id, int salary, int seniority) : id(id), salary(salary), seniority(seniority) {}
        
        bool operator<(const Employee &other) const {
            return std::tie(id, salary, seniority) < std::tie(other.id, other.salary, other.seniority);
        }

        void print() const {
            std::cout << "ID: " << (int)id << ", Salary: " << (int)salary << ", Seniority: " << (int)seniority << std::endl;
        }

        uint8_t getId() const { return id; }
        int getSalary() const { return salary; }
        int getSeniority() const { return seniority; }

};

std::vector<Employee> load(const std::string& filename);
void save(const std::string& filename, const std::vector<Employee>& employees);



#endif