#include <iostream>
#include <memory>
#include <string>

struct Location {
    Location(const std::string& street, const std::string& city, int suite)
        : street(street), city(city), suite(suite) {}

    std::string street;
    std::string city;
    int suite;
};

struct Employee {
    Employee(const std::string& name, const Location& location)
        : name(name), location(location) {}

    std::string name;
    Location location;
};

class EmployeeCreator {
public:
    static Employee prototypeMain;
    static Employee prototypeAux;

    static std::unique_ptr<Employee> CreateMainOfficeEmployee(const std::string& name, int suite) {
        return CreateEmployee(name, suite, prototypeMain);
    }

    static std::unique_ptr<Employee> CreateAuxOfficeEmployee(const std::string& name, int suite) {
        return CreateEmployee(name, suite, prototypeAux);
    }

private:
    static std::unique_ptr<Employee> CreateEmployee(const std::string& name, int suite, const Employee& prototype) {
        auto newEmployee = std::make_unique<Employee>(prototype);
        newEmployee->name = name;
        newEmployee->location.suite = suite;
        return newEmployee;
    }
};

Employee EmployeeCreator::prototypeMain = Employee("Alice Johnson", Location("Baker Street", "London", 101));
Employee EmployeeCreator::prototypeAux = Employee("Bob Smith", Location("Main St", "New York", 202));

int main() {
    std::unique_ptr<Employee> alice = EmployeeCreator::CreateMainOfficeEmployee("Alice Johnson", 1);
    std::unique_ptr<Employee> bob = EmployeeCreator::CreateAuxOfficeEmployee("Bob Smith", 2);
    std::unique_ptr<Employee> charlie = EmployeeCreator::CreateMainOfficeEmployee("Charlie Brown", 3);
    std::unique_ptr<Employee> diana = EmployeeCreator::CreateAuxOfficeEmployee("Diana Prince", 4);

    std::cout << "Employee: " << alice->name << ", City: " << alice->location.city << ", Street: " << alice->location.street << ", Suite: " << alice->location.suite << std::endl;
    std::cout << "Employee: " << bob->name << ", City: " << bob->location.city << ", Street: " << bob->location.street << ", Suite: " << bob->location.suite << std::endl;
    std::cout << "Employee: " << charlie->name << ", City: " << charlie->location.city << ", Street: " << charlie->location.street << ", Suite: " << charlie->location.suite << std::endl;
    std::cout << "Employee: " << diana->name << ", City: " << diana->location.city << ", Street: " << diana->location.street << ", Suite: " << diana->location.suite << std::endl;

    return 0;
}
