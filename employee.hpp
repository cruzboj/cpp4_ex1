#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

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

        friend std::ostream& operator<<(std::ostream& os, const Employee& emp);
};

std::ostream& operator<<(std::ostream& os, const Employee& emp) {
    os << "Employee ID: " << emp.id
       << ", Salary: " << emp.salary
       << ", Seniority: " << emp.seniority;
    return os;
}

#endif