

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

class Employee {
private:
    std::string name;
    int id;
    
public:
    Employee(const std::string& name, const int& id) : name(name), id(id){}
    std::string getName()const         { return name; }
    int getId() const                  { return id; }
    void setName(const std::string name) { this->name = name; }


    void setId(const int id) { this->id = id; }


    void displayEmployees() {
        std::cout << "Name: " << name << " ID: " << id;
    }

    
};




class employeeManagement {
private:
    std::vector<Employee>employee;
public:
    
        const std::vector<Employee>& getEmployees() const {
            return employee;
        }




        static std::string trim(const std::string& str) {
           
            size_t first = str.find_first_not_of(" \t\n\r\f\v");
            if (first == std::string::npos) {
                return "";
            }

            
            size_t last = str.find_last_not_of(" \t\n\r\f\v");
            std::string result = str.substr(first, last - first + 1);

           
            std::transform(result.begin(), result.end(), result.begin(), ::tolower); 

            return result;
        }
    




        static bool verifyEmployee(std::string enteredname, int enteredid) {
            
            enteredname = trim(enteredname);
            std::transform(enteredname.begin(), enteredname.end(), enteredname.begin(), ::tolower);

            
            std::ifstream inFile("user.txt");
            std::string line;

            if (!inFile) {
                std::cerr << "Error opening the file" << '\n';
                return false;
            }

            
            while (getline(inFile, line)) {
                std::string fileName;
                int fileId;

                size_t nameStart = line.find("Name: ") + 6; 
                size_t nameEnd = line.find(" ID: ");
                size_t idStart = nameEnd + 5; 

                fileName = line.substr(nameStart, nameEnd - nameStart);
                fileId = std::stoi(line.substr(idStart));

                
                fileName = trim(fileName);
                std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::tolower);

                
                if (enteredname == fileName && enteredid == fileId) {
                    return true; 
                }
            }

           
            std::cout << "Employee verification failed." << std::endl;
            return false;
        }







    void addEmployee() {
        std::string name;
        std::string i;
        int id;
        std::cout << "Enter the name of the employee" << std::endl;
        getline(std::cin, name);
        std::cout << "Enter the id of the employee " << std::endl;
        getline(std::cin, i);
        id = std::stoi(i);
        
        employee.emplace_back(name, id );
        std::ofstream outFile("user.txt", std::ios::app);
        if (outFile.is_open()) {
            outFile << "Name: " << name << " ID: " << id << "\n";
            outFile.close();
            std::cout << "An employee has been added successfully and saved to the file." << std::endl;
        }
        else {
            std::cout << "Error opening the file!" << std::endl;
        }
    }




    void removeEmployee() {
        if (employee.empty()) {
            std::cout << "There are no employees." << std::endl;
            return;
        }

        std::cout << "Employees:" << std::endl;
        for (auto i = 0; i < employee.size(); i++) {
            std::cout << i + 1 << ". " << employee[i].getName() << std::endl;
        }

        std::cout << "Enter the number of the employee you want to REMOVE: ";
        int num;
        std::cin >> num;

        if (num >= 1 && num <= employee.size()) {
            
            employee.erase(employee.begin() + num - 1);
            std::cout << "Employee has been removed successfully!" << std::endl;

      
            std::ofstream outFile("user.txt", std::ios::trunc);
            if (outFile.is_open()) {
                for (const auto& emp : employee) {
                    outFile << "Name: " << emp.getName() << " ID: " << emp.getId() << "\n";
                }
                outFile.close();
                std::cout << "Updated employee list saved to file." << std::endl;
            }
            else {
                std::cout << "Error opening the file to save the updated list!" << std::endl;
            }
        }
        else {
            std::cout << "Invalid number." << std::endl;
        }
    }




    void displayEmployeesFromFile() {
        std::ifstream file("user.txt");
        if (!file) {
            std::cout << "Error: Could not open user.txt!" << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }

        file.close();
    }








};






class Payroll {
private:
    double TotalPay = 0 ,NetSalary = 0, BaseSalary = 0, HoursWorked = 0, Deduction = 0, Benefits = 150, Tax = 0;
    int HourPay = 40;
    double OverTimeRate = HourPay * 1.5;
    int OverTimeHours = 0;

public:
    Payroll() {
        
        NetSalary = 0;
        BaseSalary = 0;
        HoursWorked = 0;
        Deduction = 0;
        Tax = 0;
        OverTimeHours = 0;
        TotalPay = 0;
    }

    double getNetSalary() const           { return NetSalary; }
    double getBaseSalary() const          { return BaseSalary; }
    double getHoursWorked() const         { return HoursWorked; }
    double getOverTimeRate() const        { return OverTimeRate; }
    double getDeduction() const           { return Deduction; }
    double getBenefits() const            { return Benefits; }
    double getTax() const                 { return Tax; }
    double getTotalPay()const             { return TotalPay; }
    int getHourPay() const                { return HourPay; }

    void displayPayroll() {
        std::cout << "Net Salary: " << NetSalary << " Base Salary: " << BaseSalary
            << " Hours worked: " << HoursWorked << " Over time hours: " << OverTimeHours
            << " Over time rate:" << OverTimeRate << " Deduction: " << Deduction << " Benefits: " << Benefits << std::endl;
    }




    void workHoursTracking() {
        std::cout << "Enter your name: ";
        std::string name;
        std::getline(std::cin, name);

        std::cout << "Enter your ID: ";
        std::string idInput;
        int ID;
        std::getline(std::cin, idInput);

        try {
            ID = std::stoi(idInput);
        }
        catch (std::invalid_argument&) {
            std::cout << "Invalid ID. Please enter a numeric value." << std::endl;
            return;
        }

        std::cout << "Verifying employee with Name: " << name << " and ID: " << ID << std::endl;

        int HoursWorkedInput = 0;

        while (true) {
            std::cout << "Enter the number of hours you've worked this week: ";
            std::string hw;
            std::getline(std::cin, hw);

            try {
                HoursWorkedInput = std::stoi(hw);

                if (HoursWorkedInput < 0 || HoursWorkedInput > 168) {
                    std::cout << "Invalid input. Hours worked must be between 0 and 168." << std::endl;
                }
                else {
                    break;
                }
            }
            catch (std::invalid_argument&) {
                std::cout << "Invalid input. Please enter a numeric value." << std::endl;
            }
        }

        HoursWorked = HoursWorkedInput;

        if (HoursWorked <= 40) {
            TotalPay = HoursWorked * HourPay;
        }
        else {
            TotalPay = (40 * HourPay) + ((HoursWorked - 40) * OverTimeRate);
        }
        
        std::ofstream outFile("employee.txt", std::ios::app);
        if (outFile.is_open()) {
            outFile << "Employee: " << name << " (ID: " << ID << ") - Hours Worked: " << HoursWorked
                << " - Total Pay: $" << TotalPay << "\n";
            outFile.close();
            std::cout << "The hours and pay have been entered successfully." << std::endl;
        }
        else {
            std::cout << "Error opening the file!" << std::endl;
        }
    }





    double calcTax(double grossSalary) {
        return grossSalary * 0.001;
    }





    double calcDeductions() {
        double totalGrossSalary = calcGrossSalary();
        Tax = calcTax(totalGrossSalary);  

        Deduction = Tax; 
        std::cout << "Total Tax Deduction: $" << Tax << std::endl;

        return Deduction;
    }





    double calcGrossSalary() {
        double GrossSalary = BaseSalary + TotalPay + Benefits - Deduction;
        std::cout << "Gross Salary: $" << GrossSalary << std::endl;
        return GrossSalary;
    }





    double calcNetSalary(const std::string& name, int ID) {
        double totalGrossSalary = calcGrossSalary();
        double totalDeductions = calcTax(totalGrossSalary);

        NetSalary = totalGrossSalary - totalDeductions + Benefits;

        std::cout << "Net Salary for " << name << " (ID: " << ID << "): $" << NetSalary << std::endl;

        
       

        return NetSalary;
    }




    void saveNetSalary(const std::string& name, int ID) {
        double totalGrossSalary = calcGrossSalary();
        double totalDeductions = calcTax(totalGrossSalary);

        NetSalary = totalGrossSalary - totalDeductions + Benefits;

        std::ofstream outFile("payroll.txt", std::ios::app);
        if (outFile.is_open()) {
            outFile << name << " " << ID << " $" << NetSalary << "\n";
            outFile.close();
            std::cout << "Net Salary has been saved to payroll.txt" << std::endl;
        }
        else {
            std::cout << "Error opening payroll.txt!" << std::endl;
        }
    }

};















class Report {
private:

public:
    void vector(employeeManagement& manager) {
        const std::vector<Employee>& empList = manager.getEmployees();
    }
    



    void salaryBreakDown(employeeManagement& manager, Payroll& payroll) {
        std::cout << "Enter your name: ";
        std::string name;
        std::getline(std::cin, name);

        std::cout << "Enter your ID: ";
        std::string idInput;
        int ID;
        std::getline(std::cin, idInput);

        try {
            ID = std::stoi(idInput);
        }
        catch (std::invalid_argument&) {
            std::cout << "Invalid ID. Please enter a numeric value." << std::endl;
            return;
        }

        if (manager.verifyEmployee(name, ID)) {
            std::cout << "Employee verified. Displaying salary breakdown..." << std::endl;

            double GrossSalary = payroll.calcGrossSalary();
            std::cout << "Base Salary: " << GrossSalary << std::endl;
            std::cout << "Benefits: " << payroll.getBenefits() << std::endl;
            double deductions = payroll.calcDeductions();
            std::cout << "Deductions: " << deductions << std::endl;
            std::cout << "------------------------------------" << std::endl;
            double NetSalary = payroll.calcNetSalary(name, ID);  

            std::cout << "Net Salary: " << NetSalary << std::endl;
        }
        else {
            std::cout << "Employee verification failed. Please check your name or ID." << std::endl;
        }
    }    
    
    


    void showPayrollHistory(Payroll& payroll) {
        std::cout << "Enter your name: ";
        std::string name;
        std::getline(std::cin, name);

        std::cout << "Enter your ID: ";
        std::string idInput;
        int ID;
        std::getline(std::cin, idInput);

        try {
            ID = std::stoi(idInput);
        }
        catch (std::invalid_argument&) {
            std::cout << "Invalid ID. Please enter a numeric value." << std::endl;
            return;
        }

        double NetSalary = payroll.calcNetSalary(name, ID);

        payroll.saveNetSalary(name, ID);

        std::ifstream inFile("payroll.txt");
        if (!inFile.is_open()) {
            std::cout << "Error opening the file." << std::endl;
            return;
        }

        std::string fileName;
        int fileID;
        double fileSalary;
        int weekCount = 0;
        bool found = false;

        std::cout << "Payroll History for " << name << " (ID: " << ID << "):\n";

        while (inFile >> fileName >> fileID >> fileSalary) {
            if (fileName == name && fileID == ID) {  
                weekCount++;
                std::cout << "Week " << weekCount << ": Net Salary: $" << fileSalary << std::endl;
                found = true;
            }
        }

        inFile.close();

        if (!found) {
            std::cout << "No payroll history found for " << name << " (ID: " << ID << ")." << std::endl;
        }
    }






    
};




int main()
{

    employeeManagement manager;
    Payroll payroll;
    Report report;

    int choice;
    bool running = true;

    while (running) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Employee\n";
        std::cout << "2. Remove Employee\n";
        std::cout << "3. Display Employees\n";
        std::cout << "4. Track Working Hours\n";
        std::cout << "5. Show Payroll History\n";
        std::cout << "6. Show Salary Breakdown\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            manager.addEmployee();
            break;
        case 2:
            manager.removeEmployee();
            break;
        case 3:
            manager.displayEmployeesFromFile();
            break;
        case 4:
            payroll.workHoursTracking();
            break;
        case 5:
            report.showPayrollHistory(payroll);
            break;
        case 6:
            report.salaryBreakDown(manager, payroll);
            break;
        case 7:
            running = false;  
            std::cout << "Exiting program...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
};
    




