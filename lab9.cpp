#include <iostream>     // оролт гаралтын үйлдлийг хийх
#include <vector>       // vector контейнер ашиглах
using namespace std;

//  Person (Хүн) анги

class Person {
protected:
    string name; // нэр
    string ssn;  // Нийгмийн даатгалын дугаар
    int age;     // нас
public:
    // Constructor – анхны утгууд онооно
    Person(string name, string ssn, int age) : name(name), ssn(ssn), age(age) {}

    // virtual print функц – хэвлэлт хийх боломжтой, override-д зориулсан
    virtual void print() {
        cout << "Name: " << name << ", SSN: " << ssn << ", Age: " << age << endl;
    }
};


//  Spouse (нөхөр/эхнэр) анги

class Spouse : public Person {
    string anniversaryDate; // Хуримын ой
public:
    Spouse(string name, string ssn, int age, string annivDate)
        : Person(name, ssn, age), anniversaryDate(annivDate) {}

    // Override хийж өөрийн мэдээллийг нэмэлтээр хэвлэх
    void print() override {
        cout << "  Spouse -> ";
        Person::print();
        cout << "    Anniversary Date: " << anniversaryDate << endl;
    }
};


//  Child (хүүхэд) анги

class Child : public Person {
    string favoriteToy; // Дуртай тоглоом
public:
    Child(string name, string ssn, int age, string toy)
        : Person(name, ssn, age), favoriteToy(toy) {}

    void print() override {
        cout << "  Child -> ";
        Person::print();
        cout << "    Favorite Toy: " << favoriteToy << endl;
    }
};


//  Division (хэлтэс) анги

class Division {
    string divisionName; // Хэлтсийн нэр
public:
    Division(string name) : divisionName(name) {}

    string getDivisionName() { return divisionName; }

    void print() {
        cout << "Division: " << divisionName << endl;
    }
};


//  JobDescription (Ажлын тодорхойлолт) анги

class JobDescription {
    string description; // Ажлын тайлбар
public:
    JobDescription(string desc) : description(desc) {}

    void print() {
        cout << "  Job: " << description << endl;
    }
};


//  Employee (Ажилтан) анги
class Employee : public Person {
    string companyID;  // компанийн ID
    string title;      // Албан тушаал
    string startDate;  // Ажилд орсон огноо
    Division* division;                        // Хэлтсийн заалт (pointer)
    vector<JobDescription*> jobDescriptions;  // 1..n Ажлын тодорхойлолт
    Spouse* spouse;                            // 0..1 Нөхөр/эхнэр
    vector<Child*> children;                   // 0..n Хүүхдүүд
public:
    // Constructor – бүх утгуудыг оноох
    Employee(string name, string ssn, int age,
             string companyID, string title, string startDate,
             Division* div)
        : Person(name, ssn, age), companyID(companyID), title(title),
          startDate(startDate), division(div), spouse(nullptr) {}

    // Ажлын тодорхойлолт нэмэх функц
    void addJobDescription(JobDescription* job) {
        jobDescriptions.push_back(job);
    }

    // Нөхөр/эхнэр оноох
    void setSpouse(Spouse* s) {
        spouse = s;
    }

    // Хүүхэд нэмэх
    void addChild(Child* c) {
        children.push_back(c);
    }

    // Мэдээлэл хэвлэх override хийсэн функц
    void print() override {
        cout << "Employee Information:\n";
        Person::print(); // үндсэн мэдээлэл
        cout << "  CompanyID: " << companyID
             << ", Title: " << title
             << ", StartDate: " << startDate << endl;
        division->print(); // хэлтэс
        for (auto job : jobDescriptions)
            job->print(); // ажлын тодорхойлолт бүрийг хэвлэх
        if (spouse != nullptr)
            spouse->print(); // нөхөр/эхнэр байвал
        for (auto child : children)
            child->print(); // хүүхдүүдийг хэвлэх
        cout << "--------------------------------------\n";
    }
};


//  main() функц – Гүйцэтгэл эхэлнэ

int main() {
    // Хэлтсүүд үүсгэх
    Division sales("Sales");           // Борлуулалт
    Division hr("Human Resources");    // Хүний нөөц

    // Ажлын тодорхойлолтууд
    JobDescription dev("Developer");
    JobDescription manager("Manager");
    JobDescription analyst("Analyst");

    // 1-р ажилтан Alice
    Employee emp1("Alice", "111-22-3333", 30, "E001", "Team Lead", "2020-01-15", &sales);
    emp1.addJobDescription(&dev);      // Хөгжүүлэгч
    emp1.addJobDescription(&manager);  // Менежер
    emp1.setSpouse(new Spouse("Bob", "444-55-6666", 32, "2018-06-21")); // Нөхөр
    emp1.addChild(new Child("Charlie", "123-45-6789", 5, "Lego"));     // Хүүхэд 1
    emp1.addChild(new Child("Daisy", "987-65-4321", 3, "Doll"));       // Хүүхэд 2

    // 2-р ажилтан John
    Employee emp2("John", "777-88-9999", 28, "E002", "HR Specialist", "2021-05-01", &hr);
    emp2.addJobDescription(&analyst);  // Аналист
    // John нөхөр/эхнэр болон хүүхэдгүй

    // Ажилтнуудын мэдээллийг хэвлэх
    emp1.print();
    emp2.print();

    return 0;
}
