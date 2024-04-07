#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Define structures for employee and payroll information
struct Employee {
    string name;
    int id;
    double hourlyRate;
    // Add more fields as needed
};

struct PayrollEntry {
    int employeeId;
    int hoursWorked;
    double deductions;
    double benefits;
    // Add more fields as needed
};

// Function to calculate salary for an employee
double calculateSalary(const Employee& employee, const PayrollEntry& entry) {
    double salary = employee.hourlyRate * entry.hoursWorked;
    salary -= entry.deductions;
    salary += entry.benefits;
    return salary;
}

// Function to add an employee
void addEmployee(vector<Employee>& employees) {
    Employee newEmployee;
    cout << "Enter employee name: ";
    getline(cin, newEmployee.name);
    cout << "Enter employee ID: ";
    cin >> newEmployee.id;
    cout << "Enter employee hourly rate: $";
    cin >> newEmployee.hourlyRate;
    cin.ignore(); // Ignore the newline character after cin
    employees.push_back(newEmployee);
}

// Function to add a payroll entry
void addPayrollEntry(vector<PayrollEntry>& entries, const vector<Employee>& employees) {
    PayrollEntry newEntry;
    cout << "Enter employee ID: ";
    cin >> newEntry.employeeId;
    bool foundEmployee = false;
    for (const auto& emp : employees) {
        if (emp.id == newEntry.employeeId) {
            foundEmployee = true;
            break;
        }
    }
    if (!foundEmployee) {
        cout << "Employee with ID " << newEntry.employeeId << " not found.\n";
        return;
    }
    cout << "Enter hours worked: ";
    cin >> newEntry.hoursWorked;
    cout << "Enter deductions: $";
    cin >> newEntry.deductions;
    cout << "Enter benefits: $";
    cin >> newEntry.benefits;
    cin.ignore(); // Ignore the newline character after cin
    entries.push_back(newEntry);
}

// Function to generate a report
void generateReport(const vector<Employee>& employees, const vector<PayrollEntry>& entries) {
    cout << "Payroll Report:\n";
    for (const auto& entry : entries) {
        // Find the corresponding employee
        const Employee* employeePtr = nullptr;
        for (const auto& emp : employees) {
            if (emp.id == entry.employeeId) {
                employeePtr = &emp;
                break;
            }
        }
        if (employeePtr) {
            double salary = calculateSalary(*employeePtr, entry);
            cout << "Employee: " << employeePtr->name << ", ID: " << entry.employeeId << ", Salary: $" << salary << endl;
        } else {
            cout << "Employee with ID " << entry.employeeId << " not found.\n";
        }
    }
}

int main() {
    vector<Employee> employees;
    vector<PayrollEntry> payrollEntries;

    char choice;
    do {
        cout << "Menu:\n";
        cout << "1. Add employee\n";
        cout << "2. Add payroll entry\n";
        cout << "3. Generate report\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character after cin
        switch (choice) {
            case '1':
                addEmployee(employees);
                break;
            case '2':
                addPayrollEntry(payrollEntries, employees);
                break;
            case '3':
                generateReport(employees, payrollEntries);
                break;
            case '4':
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '4');

    return 0;
}
