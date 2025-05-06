#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

// ----- Загвар LinkedList -----
template <typename T>
class LinkedList {
    struct Node { T data; Node* next; Node(T d) : data(d), next(nullptr) {} };
    Node* head = nullptr; int size = 0;
public:
    void add(T t) {
        Node* n = new Node(t);
        if (!head) head = n;
        else { Node* temp = head; while (temp->next) temp = temp->next; temp->next = n; }
        size++;
    }
    void forEach(void (*func)(T)) {
        for (Node* t = head; t; t = t->next) func(t->data);
    }
    void bubbleSort(bool (*comp)(T, T)) {
        if (size <= 1) return;
        bool swapped;
        do {
            swapped = false;
            Node *cur = head, *prev = nullptr, *next = cur->next;
            while (next) {
                if (comp(cur->data, next->data)) {
                    if (prev) prev->next = next; else head = next;
                    cur->next = next->next; next->next = cur;
                    swapped = true; prev = next; next = cur->next;
                } else { prev = cur; cur = next; next = next->next; }
            }
        } while (swapped);
    }
};

// ----- Shape ба уламжлагчид -----
class Shape {
protected: string name;
public:
    Shape(string n) : name(n) {}
    virtual double area() = 0;
    virtual void display() = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
    double x, y, r;
public:
    Circle(double cx, double cy, double radius) : Shape("Тойрог"), x(cx), y(cy), r(radius) {}
    double area() override { return M_PI * r * r; }
    void display() override {
        cout << name << " (" << x << "," << y << "), r=" << r << ", A=" << area() << endl;
    }
};

class Square : public Shape {
    double x, y, s;
public:
    Square(double sx, double sy, double side) : Shape("Квадрат"), x(sx), y(sy), s(side) {}
    double area() override { return s * s; }
    void display() override {
        cout << name << " (" << x << "," << y << "), s=" << s << ", A=" << area() << endl;
    }
};

class Triangle : public Shape {
    double x, y, s;
public:
    Triangle(double tx, double ty, double side) : Shape("Гурвалжин"), x(tx), y(ty), s(side) {}
    double area() override { return (sqrt(3)/4) * s * s; }
    void display() override {
        cout << name << " (" << x << "," << y << "), s=" << s << ", A=" << area() << endl;
    }
};

// ----- Туслах функцүүд -----
bool compareByArea(Shape* a, Shape* b) { return a->area() > b->area(); }
void printShape(Shape* s) { s->display(); }

// ----- Main -----
int main() {
    srand(time(0));
    LinkedList<Shape*> shapes;
    int count = 20 + rand() % 11;

    for (int i = 0; i < count; i++) {
        double x = rand()%100, y = rand()%100, size = 5 + rand()%20;
        int type = rand()%3;
        if (type == 0) shapes.add(new Circle(x, y, size));
        else if (type == 1) shapes.add(new Square(x, y, size));
        else shapes.add(new Triangle(x, y, size));
    }

    cout << "=== Эх хэлбэрүүд ===\n";
    shapes.forEach(printShape);

    shapes.bubbleSort(compareByArea);

    cout << "\n=== Талбайгаар эрэмбэлсэн ===\n";
    shapes.forEach(printShape);
    return 0;
}
