#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <ranges>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>

enum class Department {
    CONTROL,
    TAO,
    D1,
    INFRA,
    END
};

std::string toString(Department dep) {
    switch (dep) {
        case Department::CONTROL:
            return "Control";
        case Department::TAO:
            return "TAO";
        case Department::D1:
            return "D1";
        case Department::INFRA:
            return "Infra";
        default:
            throw std::runtime_error("Unsupported department");        
    }
}

Department fromString(std::string_view s) {
    if (s == "Control") 
        return Department::CONTROL;
    if (s == "TAO")
            return Department::TAO;
    if (s == "D1")
            return Department::D1;
    if (s == "INFRA")
            return Department::INFRA;
    throw std::runtime_error("No such department ");
}

struct Employee {
    std::string name;
    Department department;
    int salary;
};

void printEmployee(const Employee& employee) {
    std::cout << "Employee<" << employee.name << "," << toString(employee.department) << "," << employee.salary << ">\n";
}

void findHighestSalaryEmployee(std::vector<Employee>& employeeVector) {
    auto it = std::max_element(employeeVector.begin(), employeeVector.end(), [](const Employee& a, const Employee& b){return a.salary < b.salary;});
    const Employee& bestEmployee = *it;
    std::cout << "Best paid employee is:\n";
    printEmployee(bestEmployee);
}

void findAverageSalary(std::vector<Employee>& employeeVector) {
    int sum = std::accumulate(employeeVector.begin(), employeeVector.end(), 0, [](int total, const Employee& e){return total + e.salary;});
    std::cout << "Average salary is: " <<  sum / employeeVector.size() << "\n";
}

// Map department to employees, reduce employees to average salary and find max
void findHighestAverageSalaryDepartment(std::vector<Employee>& employeeVector) {
    std::unordered_map<Department, std::vector<Employee>> departmentToEmployee;
    std::for_each(employeeVector.begin(), employeeVector.end(),
        [&departmentToEmployee](const Employee& e){departmentToEmployee[e.department].push_back(e);});

    std::unordered_map<Department, int> departmentToAvgSalary;
    std::for_each(departmentToEmployee.begin(), departmentToEmployee.end(),
        [&departmentToAvgSalary](const std::pair<Department, std::vector<Employee>>& pair){
            departmentToAvgSalary[pair.first] = std::accumulate(pair.second.begin(), pair.second.end(), 0,
                [](int total, const Employee& e){return total + e.salary;}) / pair.second.size();
        });
    
    std::pair<Department, int> bestDepartment = *std::max_element(departmentToAvgSalary.begin(), departmentToAvgSalary.end(),
        [](const auto& a, const auto& b) {return a.second < b.second;});
    std::cout << "Best average paid department is " << toString(bestDepartment.first) << " with average salary of " << bestDepartment.second << "\n";
    
}


int main() {
    std::ifstream data("/mnt/c/Users/huber/cpp-learning/week5/example.csv");

    std::unordered_map<std::string, Employee> employeeMap; // I ended up not using it, but still created since the task requires it
    std::vector<Employee> employeeVector;
    auto view = std::views::istream<std::string>(data);

    // Didn't figure out a way to use it with ranges, so using the normal iteration pattern
    for (auto& line : view) {
        std::string str;
        std::vector<std::string> cells;
        std::istringstream iss(line);
        while (std::getline(iss, str, ',')) {
            cells.push_back(str);
        }
        Employee e {cells[0], fromString(cells[1]), std::stoi(cells[2])};
        employeeVector.push_back(e);
        employeeMap.emplace(cells[0], std::move(e));
    }

    // Research using ranges
    findHighestSalaryEmployee(employeeVector);
    findAverageSalary(employeeVector);
    findHighestAverageSalaryDepartment(employeeVector);
}
