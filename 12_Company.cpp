#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

const char* fileName = "Employee.txt";

class Employee {
private:
    int EmpID;
    char EmpName[50], Post[50], Department[10];
    float Salary;

public:
    void ReadData();
    int GetID();
    void DisplayRecord();
    char* GetDepartment();
};

void Employee::ReadData() {
    cout << endl << "Employee ID: ";
    cin >> EmpID;
    cout << "Employee Name: ";
    cin >> EmpName;
    cout << "Employee's Post: ";
    cin >> Post;
    cout << "Employee's Department: ";
    cin >> Department;
    cout << "Salary: ";
    cin >> Salary;
}

void Employee::DisplayRecord() {
    cout << endl << "_______________________________";
    cout << endl << setw(5) << EmpID << setw(15) << EmpName << setw(15) << Post << setw(15) << Department << setw(8) << Salary;
}

int Employee::GetID() {
    return EmpID;
}

char* Employee::GetDepartment() {
    return Department;
}

int main() {
    Employee emp, e;
    char option, ch, Dept[50];
    int ID, isFound;

    fstream file;
    file.open(fileName, ios::ate | ios::in | ios::out | ios::binary);
    
    do {
        cout << "******Menu*******" << endl;
        cout << "Enter your option" << endl;
        cout << "1 => Add a new record" << endl;
        cout << "2 => Search record from employee id" << endl;
        cout << "3 => List Employee of particular department" << endl;
        cout << "4 => Display all employees" << endl;
        cout << "5 => Update record of an employee" << endl;
        cout << "6 => Delete record of particular employee" << endl;
        cout << "7 => Exit from the program" << endl;
        cout << "********************" << endl;
        
        cin >> option;

        switch (option) {
            case '1':
                emp.ReadData();
                file.seekg(0, ios::beg);
                isFound = 0;
                
                file.read((char*)&e, sizeof(e));
                while (!file.eof()) {
                    if (e.GetID() == emp.GetID()) {
                        cout << "This ID already exists... Try another ID" << endl;
                        isFound = 1;
                        break;
                    }
                    file.read((char*)&e, sizeof(e));
                }
                
                if (isFound == 1)
                    break;
                
                file.clear();
                file.seekp(0, ios::end);
                file.write((char*)&emp, sizeof(emp));
                cout << "New record has been added successfully..." << endl;
                break;

            case '2':
                isFound = 0;
                cout << "Enter ID of an employee to be searched: ";
                cin >> ID;
                file.seekg(0, ios::beg);
                file.read((char*)&e, sizeof(e));
                
                while (!file.eof()) {
                    if (e.GetID() == ID) {
                        cout << "The record found...." << endl;
                        cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Post" << setw(15) << "Department" << setw(8) << "Salary";
                        e.DisplayRecord();
                        isFound = 1;
                        break;
                    }
                    file.read((char*)&e, sizeof(e));
                }
                file.clear();
                
                if (isFound == 0)
                    cout << "Data not found for employee ID#" << ID << endl;
                
                break;

            case '3':
                isFound = 0;
                cout << "Enter department name to list employees within it: ";
                cin >> Dept;
                file.seekg(0, ios::beg);
                file.read((char*)&e, sizeof(e));
                
                while (!file.eof()) {
                    if (strcmp(e.GetDepartment(), Dept) == 0) {
                        cout << "The record found for this department" << endl;
                        cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Post" << setw(15) << "Department" << setw(8) << "Salary";
                        e.DisplayRecord();
                        isFound = 1;
                        break;
                    }
                    file.read((char*)&e, sizeof(e));
                }
                file.clear();
                
                if (isFound == 0)
                    cout << "Data not found for department " << Dept << endl;
                
                break;

            case '4':
                cout << "Record for employees" << endl;
                file.clear();
                file.seekg(0, ios::beg);
                int counter = 0;
                file.read((char*)&e, sizeof(e));
                
                while (!file.eof()) {
                    counter++;
                    if (counter == 1) {
                        cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Post" << setw(15) << "Department" << setw(8) << "Salary";
                    }
                    e.DisplayRecord();
                    file.read((char*)&e, sizeof(e));
                }
                cout << counter << " records found." << endl;
                file.clear();
                break;

            case '5':
                int recordNo = 0;
                cout << "File is being modified..." << endl;
                cout << "Enter employee ID to be updated: ";
                cin >> ID;
                isFound = 0;
                file.seekg(0, ios::beg);
                file.read((char*)&e, sizeof(e));
                
                while (!file.eof()) {
                    recordNo++;
                    if (e.GetID() == ID) {
                        cout << "The old record of employee having ID " << ID << " is:" << endl;
                        e.DisplayRecord();
                        isFound = 1;
                        break;
                    }
                    file.read((char*)&e, sizeof(e));
                }
                
                if (isFound == 0) {
                    cout << "Data not found for employee ID#" << ID << endl;
                    break;
                }
                file.clear();
                
                int location = (recordNo - 1) * sizeof(e);
                file.seekp(location, ios::beg);
                cout << "Enter new record for employee having ID " << ID << endl;
                e.ReadData();
                file.write((char*)&e, sizeof(e));
                break;

            case '6':
                recordNo = 0;
                cout << "Enter employment ID to be deleted: ";
                cin >> ID;
                isFound = 0;
                file.seekg(0, ios::beg);
                file.read((char*)&e, sizeof(e));
                
                while (!file.eof()) {
                    recordNo++;
                    if (e.GetID() == ID) {
                        cout << "The old record of employee having ID " << ID << " is: ";
                        e.DisplayRecord();
                        isFound = 1;
                        break;
                    }
                    file.read((char*)&e, sizeof(e));
                }
                
                char tempFile[] = "temp.txt";
                fstream temp(tempFile, ios::out | ios::binary);
                
                if (isFound == 0) {
                    cout << "Data not found for employee ID#" << ID << endl;
                    break;
                } else {
                    file.clear();
                    file.seekg(0, ios::beg);
                    file.read((char*)&e, sizeof(e));
                    
                    while (!file.eof()) {
                        if (e.GetID() != ID)
                            temp.write((char*)&e, sizeof(e));
                        file.read((char*)&e, sizeof(e));
                    }
                    
                    file.close();
                    temp.close();
                    temp.open(tempFile, ios::in | ios::binary);
                    file.open(fileName, ios::out | ios::binary);
                    
                    temp.read((char*)&e, sizeof(e));
                    while (!temp.eof()) {
                        file.write((char*)&e, sizeof(e));
                        temp.read((char*)&e, sizeof(e));
                    }
                }
                
                temp.close();
                file.close();
                remove(tempFile);
                file.open(fileName, ios::ate | ios::in | ios::out | ios::binary);
                break;

            case '7':
                exit(0);
                break;

            default:
                cout << "Invalid option" << endl;
                break;
        }
        
        cout << "Do you want to continue? (y/n): ";
        cin >> ch;
    } while (ch != 'n');

    return 0;
}
