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

std::vector<Employee> load(const std::string& filename) {
    std::vector<Employee> employees;
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open binary file");
    }

    uint8_t id, salary, seniority;
    while (file.read(reinterpret_cast<char*>(&id), sizeof(id)) &&
           file.read(reinterpret_cast<char*>(&salary), sizeof(salary)) &&
           file.read(reinterpret_cast<char*>(&seniority), sizeof(seniority))) {
        employees.push_back(Employee(id, salary, seniority));
    }

    file.close();
    return employees;
}

void save(const std::string& filename, const std::vector<Employee>& employees) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for writing");
    }

    for (const auto& emp : employees) {
        uint8_t id = emp.getId();
        int salary = emp.getSalary();
        int seniority = emp.getSeniority();

        file.write(reinterpret_cast<char*>(&id), sizeof(id));
        file.write(reinterpret_cast<const char*>(&salary), sizeof(salary));
        file.write(reinterpret_cast<const char*>(&seniority), sizeof(seniority));
    }

    file.close();
}



#endif