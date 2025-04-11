#include <iostream>
#include <cmath>

using namespace std;

// Ерөнхий Shape класс
class Shape {
protected:
    string name;
    static int objectCount; // Бүх объектын тоо
public:
    Shape(string n) : name(n) {
        Shape::incrementCount(); // Объект үүсэхэд тоолж байна
    }

    virtual double area() const = 0;
    virtual double perimeter() const = 0;

    virtual void display() const {
        cout << ":" << this->name << endl;
    }

    virtual string getName() const {
        return this->name;
    }

    static void incrementCount() {
        ++Shape::objectCount;
    }

    static int getObjectCount() {
        return Shape::objectCount;
    }
};

// Статик хувьсагчийн анхны утга
int Shape::objectCount = 0;

// 2D Shape ангилал
class Shape2D : public Shape {
public:
    Shape2D(string n) : Shape(n) {}

    virtual double area() const override = 0;
    virtual double perimeter() const override = 0;
};

// Тойрог
class Circle : public Shape2D {
private:
    double x, y;
    double radius;
public:
    Circle(double cx, double cy, double r) : Shape2D("Тойрог"), x(cx), y(cy), radius(r) {}

    double area() const override {
        return M_PI * this->radius * this->radius;
    }

    double perimeter() const override {
        return 2 * M_PI * this->radius;
    }

    void display() const override {
        cout << "Тойрог: Төв(" << this->x << ", " << this->y << "), Радиус: " << this->radius << endl;
        cout << "Талбай: " << this->area() << ", Периметр: " << this->perimeter() << endl;
    }
};

// Квадратын класс
class Square : public Shape2D {
    private:
        double x, y;
        double side;
        double x2, y2, x3, y3;
    public:
        Square(double topLeftX, double topLeftY, double s) : Shape2D("Квадрат"), x(topLeftX), y(topLeftY), side(s) {
            this->x2 = this->x + this->side;
            this->y2 = this->y;
            this->x3 = this->x;
            this->y3 = this->y - this->side;
        }
    
        double area() const override {
            return this->side * this->side;
        }
    
        double perimeter() const override {
            return 4 * this->side;
        }
    
        void display() const override {
            cout << "Квадрат: Зүүн Дээд Орой(" << this->x << ", " << this->y << "), Тал: " << this->side << endl;
            cout << "Бусад оройнууд: (" << this->x2 << ", " << this->y2 << "), (" << this->x3 << ", " << this->y3 << ")" << endl;
            cout << "Талбай: " << this->area() << ", Периметр: " << this->perimeter() << endl;
        }
    };
    
    // Зөв гурвалжин
    class Triangle : public Shape2D {
    private:
        double x, y;
        double side;
        double x2, y2, x3, y3;
    public:
        Triangle(double topX, double topY, double s) : Shape2D("Зөв Гурвалжин"), x(topX), y(topY), side(s) {
            this->x2 = this->x - this->side / 2;
            this->y2 = this->y - (sqrt(3) / 2) * this->side;
            this->x3 = this->x + this->side / 2;
            this->y3 = this->y - (sqrt(3) / 2) * this->side;
        }
    
        double area() const override {
            return (sqrt(3) / 4) * this->side * this->side;
        }
    
        double perimeter() const override {
            return 3 * this->side;
        }
    
        void display() const override {
            cout << "Зөв Гурвалжин: Дээд Орой(" << this->x << ", " << this->y << "), Тал: " << this->side << endl;
            cout << "Бусад оройнууд: (" << this->x2 << ", " << this->y2 << "), (" << this->x3 << ", " << this->y3 << ")" << endl;
            cout << "Талбай: " << this->area() << ", Периметр: " << this->perimeter() << endl;
        }
    };
    
    // Эрэмбэлэх функц: талбай болон периметрээр
    void sortShapes(Shape* shapes[], int size) {
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                double area1 = shapes[j]->area();
                double area2 = shapes[j + 1]->area();
    
                if (area1 > area2 || (area1 == area2 && shapes[j]->perimeter() > shapes[j + 1]->perimeter())) {
                    Shape* temp = shapes[j];
                    shapes[j] = shapes[j + 1];
                    shapes[j + 1] = temp;
                }
            }
        }
    }
    
    // Гол програм
    int main() {
        Shape* shapes[3];
        double cx, cy, radius, sx, sy, side, tx, ty, tside;
    
        cout << "Тойргийн төвийн координат (x, y) болон радиусыг оруулна уу: ";
        cin >> cx >> cy >> radius;
        shapes[0] = new Circle(cx, cy, radius);
    
        cout << "Квадратын зүүн дээд оройн координат (x, y) болон талын уртыг оруулна уу: ";
        cin >> sx >> sy >> side;
        shapes[1] = new Square(sx, sy, side);
    
        cout << "Зөв гурвалжны дээд оройн координат (x, y) болон талын уртыг оруулна уу: ";
        cin >> tx >> ty >> tside;
        shapes[2] = new Triangle(tx, ty, tside);
    
        sortShapes(shapes, 3);
    
        cout << "\nТалбай болон периметрээр эрэмбэлсэн хэлбэрүүд:\n";
        for (int i = 0; i < 3; ++i) {
            shapes[i]->display();
            cout << "----------------------" << endl;
        }
    
        cout << "Нийт хэлбэрүүдийн тоо: " << Shape::getObjectCount() << endl;
    
        for (int i = 0; i < 3; ++i) {
            delete shapes[i];
        }
    
        return 0;
    }