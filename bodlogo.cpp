#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Shape {
protected:
    string name;
    static int objectCount;  // 1. Статик хувьсагч

public:
    Shape(const string& n) : name(n) {
        ++objectCount;
    }

    virtual ~Shape() {}

    static int getObjectCount() { return objectCount; }  // 2. Static функц
    static void setObjectCount(int count) { objectCount = count; }

    virtual double getPerimeter() const = 0;  // 4. Жинхэнэ хийсвэр функц
    virtual double getArea() const = 0;

    void showInfo() const {
        cout << "Name: " << this->name  // 3. this ашиглав
             << ", Perimeter: " << this->getPerimeter()
             << ", Area: " << this->getArea() << endl;
    }
};

int Shape::objectCount = 0;  // 1. Статик хувьсагчийн эхлэл утга

class Rectangle : public Shape {
    double width, height;

public:
    Rectangle(double w, double h) : Shape("Rectangle"), width(w), height(h) {}

    double getPerimeter() const override {
        return 2 * (this->width + this->height);  // 3. this ашиглав
    }

    double getArea() const override {
        return this->width * this->height;  // 3. this ашиглав
    }
};

class Circle : public Shape {
    double radius;

public:
    Circle(double r) : Shape("Circle"), radius(r) {}

    double getPerimeter() const override {
        return 2 * 3.14159 * this->radius;
    }

    double getArea() const override {
        return 3.14159 * this->radius * this->radius;
    }
};

// 5. Эрэмбэлэхэд ашиглах харьцуулалтын функцүүд
bool compareByPerimeter(const Shape* a, const Shape* b) {
    return a->getPerimeter() < b->getPerimeter();
}

bool compareByArea(const Shape* a, const Shape* b) {
    return a->getArea() < b->getArea();
}

int main() {
    vector<Shape*> shapes;
    shapes.push_back(new Rectangle(4, 6));
    shapes.push_back(new Circle(3));
    shapes.push_back(new Rectangle(2, 5));
    shapes.push_back(new Circle(5));

    cout << "Total shapes: " << Shape::getObjectCount() << endl << endl;

    cout << "Sorted by perimeter:" << endl;
    sort(shapes.begin(), shapes.end(), compareByPerimeter);
    for (auto s : shapes) s->showInfo();

    cout << "\nSorted by area:" << endl;
    sort(shapes.begin(), shapes.end(), compareByArea);
    for (auto s : shapes) s->showInfo();

    for (auto s : shapes) delete s;
    return 0;
}
