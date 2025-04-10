#include "employee.hpp"

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
        uint8_t salary = static_cast<uint8_t>(emp.getSalary());  // מתאם ל uint8_t
        uint8_t seniority = static_cast<uint8_t>(emp.getSeniority());  // מתאם ל uint8_t

        // כותב את הערכים לפורמט uint8_t
        file.write(reinterpret_cast<const char*>(&id), sizeof(id));
        file.write(reinterpret_cast<const char*>(&salary), sizeof(salary));
        file.write(reinterpret_cast<const char*>(&seniority), sizeof(seniority));
    }

    file.close();
}
