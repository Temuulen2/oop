#include <iostream>
#include <vector>
using namespace std;

class Person {
protected:
    string name;
    string ssn;
    int age;
public:
    Person(string name, string ssn, int age) : name(name), ssn(ssn), age(age) {}
    virtual void print() {
        cout << "Name: " << name << ", SSN: " << ssn << ", Age: " << age << endl;
    }
};

class Spouse : public Person {
    string anniversaryDate;
public:
    Spouse(string name, string ssn, int age, string annivDate)
        : Person(name, ssn, age), anniversaryDate(annivDate) {}

    void print() override {
        cout << "  Spouse -> ";
        Person::print();
        cout << "    Anniversary Date: " << anniversaryDate << endl;
    }
};

class Child : public Person {
    string favoriteToy;
public:
    Child(string name, string ssn, int age, string toy)
        : Person(name, ssn, age), favoriteToy(toy) {}

    void print() override {
        cout << "  Child -> ";
        Person::print();
        cout << "    Favorite Toy: " << favoriteToy << endl;
    }
};

class Division {
    string divisionName;
public:
    Division(string name) : divisionName(name) {}
    string getDivisionName() { return divisionName; }
    void print() {
        cout << "Division: " << divisionName << endl;
    }
};

class JobDescription {
    string description;
public:
    JobDescription(string desc) : description(desc) {}
    void print() {
        cout << "  Job: " << description << endl;
    }
};

class Employee : public Person {
    string companyID;
    string title;
    string startDate;
    Division* division; // 1
    vector<JobDescription*> jobDescriptions; // 1..n
    Spouse* spouse; // 0..1
    vector<Child*> children; // 0..n
public:
    Employee(string name, string ssn, int age,
             string companyID, string title, string startDate,
             Division* div)
        : Person(name, ssn, age), companyID(companyID), title(title),
          startDate(startDate), division(div), spouse(nullptr) {}

    void addJobDescription(JobDescription* job) {
        jobDescriptions.push_back(job);
    }

    void setSpouse(Spouse* s) {
        spouse = s;
    }

    void addChild(Child* c) {
        children.push_back(c);
    }

    void print() override {
        cout << "Employee Information:\n";
        Person::print();
        cout << "  CompanyID: " << companyID
             << ", Title: " << title
             << ", StartDate: " << startDate << endl;
        division->print();
        for (auto job : jobDescriptions)
            job->print();
        if (spouse != nullptr)
            spouse->print();
        for (auto child : children)
            child->print();
        cout << "--------------------------------------\n";
    }
};
int main() {
    // Divisions
    Division sales("Sales");
    Division hr("Human Resources");

    // Job Descriptions
    JobDescription dev("Developer");
    JobDescription manager("Manager");
    JobDescription analyst("Analyst");

    // Employee 1
    Employee emp1("Alice", "111-22-3333", 30, "E001", "Team Lead", "2020-01-15", &sales);
    emp1.addJobDescription(&dev);
    emp1.addJobDescription(&manager);
    emp1.setSpouse(new Spouse("Bob", "444-55-6666", 32, "2018-06-21"));
    emp1.addChild(new Child("Charlie", "123-45-6789", 5, "Lego"));
    emp1.addChild(new Child("Daisy", "987-65-4321", 3, "Doll"));

    // Employee 2
    Employee emp2("John", "777-88-9999", 28, "E002", "HR Specialist", "2021-05-01", &hr);
    emp2.addJobDescription(&analyst);
    // No spouse or child for emp2

    // Print all employee info
    emp1.print();
    emp2.print();

    return 0;
}
