#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

struct employee {
    char name[30];
    int age;
    float salary;
};

void addRecord() {
    employee e;
    ofstream outfile("data.txt", ios::binary | ios::app);
    cout << "Enter name: ";
    cin.ignore();
    cin.getline(e.name, 30);
    cout << "Enter age: ";
    cin >> e.age;
    cout << "Enter salary: ";
    cin >> e.salary;
    outfile.write(reinterpret_cast<char*>(&e), sizeof(e));
    outfile.close();
    cout << "Record added successfully!" << endl;
}

void displayRecords() {
    ifstream infile("data.txt", ios::binary);
    if (!infile) {
        cout << "No records found!" << endl;
        return;
    }
    employee e;
    cout << "-------------------------\n";
    cout << "Name\tAge\tSalary\n";
    cout << "-------------------------\n";
    while (infile.read(reinterpret_cast<char*>(&e), sizeof(e))) {
        cout << e.name << "\t" << e.age << "\t" << e.salary << endl;
    }
    cout << "-------------------------\n";
    infile.close();
}

void searchRecord() {
    ifstream infile("data.txt", ios::binary);
    if (!infile) {
        cout << "No records found!" << endl;
        return;
    }
    char searchName[30];
    cout << "Enter name to search: ";
    cin.ignore();
    cin.getline(searchName, 30);
    employee e;
    bool found = false;
    while (infile.read(reinterpret_cast<char*>(&e), sizeof(e))) {
        if (strcmp(e.name, searchName) == 0) {
            cout << "-------------------------\n";
            cout << "Name\tAge\tSalary\n";
            cout << "-------------------------\n";
            cout << e.name << "\t" << e.age << "\t" << e.salary << endl;
            cout << "-------------------------\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Record not found!" << endl;
    }
    infile.close();
}

void deleteRecord() {
    ifstream infile("data.txt", ios::binary);
    if (!infile) {
        cout << "No records found!" << endl;
        return;
    }
    ofstream outfile("temp.txt", ios::binary);
    char searchName[30];
    cout << "Enter name to delete: ";
    cin.ignore();
    cin.getline(searchName, 30);
    employee e;
    bool found = false;
    while (infile.read(reinterpret_cast<char*>(&e), sizeof(e))) {
        if (strcmp(e.name, searchName) != 0) {
            outfile.write(reinterpret_cast<char*>(&e), sizeof(e));
        }
        else {
            found = true;
        }
    }
    infile.close();
    outfile.close();
    remove("data.txt");
    rename("temp.txt", "data.txt");
    if (found) {
        cout << "Record deleted successfully!" << endl;
    }
    else {
        cout << "Record not found!" << endl;
    }
}

int main() {
    char choice;
    while (true) {
        cout << "\nEmployee Record Management\n";
        cout << "---------------------------\n";
        cout << "1. Add Record\n";
        cout << "2. Display Records\n";
        cout << "3. Search Record\n";
        cout << "4. Delete Record\n";
        cout << "5. Exit\n";
        cout << "---------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                addRecord();
                break;
            case '2':
                displayRecords();
                break;
            case '3':
                searchRecord();
                break;
            case '4':
                deleteRecord();
                break;
            case '5':
                exit(0);
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
