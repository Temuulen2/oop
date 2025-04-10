#include <iostream>
#include <cmath>

using namespace std;

// Ерөнхий Shape класс (Нийтлэг шинж чанарууд)
class Shape {
protected:
    string name;
public:
    Shape(string n) : name(n) {}  // Нэр оноох байгуулагч

    virtual double area() = 0;    // Цэвэр виртуал функц (талбай)
    virtual double perimeter() = 0; // Цэвэр виртуал функц (периметр)

    virtual void display() {
        cout << "Хэлбэр: " << name << endl;
    }

    virtual string getName() const {
        return name;
    }
};

// 2DShape (хоёр хэмжээст хэлбэрүүдийн нийтлэг ангилал)
class Shape2D : public Shape {
public:
    Shape2D(string n) : Shape(n) {}  // Эцэг классын байгуулагчийг дуудаж байна
};

// Тойргийн класс
class Circle : public Shape2D {
private:
    double x, y; // Тойргийн төвийн координат
    double radius; // Радиус
public:
    Circle(double cx, double cy, double r) : Shape2D("Тойрог"), x(cx), y(cy), radius(r) {}

    double area() override {
        return M_PI * radius * radius; // Тойргийн талбай
    }

    double perimeter() override {
        return 2 * M_PI * radius; // Тойргийн периметр
    }

    void display() override {
        cout << "Тойрог: Төв(" << x << ", " << y << "), Радиус: " << radius << endl;
        cout << "Талбай: " << area() << ", Периметр: " << perimeter() << endl;
    }
};

// Квадратын класс
class Square : public Shape2D {
private:
    double x, y;  // Зүүн дээд орой
    double side;  // Талаар
    double x2, y2, x3, y3; // Үлдсэн гурван орой
public:
    Square(double topLeftX, double topLeftY, double s) : Shape2D("Квадрат"), x(topLeftX), y(topLeftY), side(s) {
        // Үлдсэн оройнуудыг тооцоолж байна
        x2 = x + side;
        y2 = y;
        x3 = x;
        y3 = y - side;
    }

    double area() override {
        return side * side; // Квадратын талбай
    }

    double perimeter() override {
        return 4 * side; // Квадратын периметр
    }

    void display() override {
        cout << "Квадрат: Зүүн Дээд Орой(" << x << ", " << y << "), Тал: " << side << endl;
        cout << "Бусад оройнууд: (" << x2 << ", " << y2 << "), (" << x3 << ", " << y3 << ")" << endl;
        cout << "Талбай: " << area() << ", Периметр: " << perimeter() << endl;
    }
};

// Зөв гурвалжны класс
class Triangle : public Shape2D {
private:
    double x, y; // Дээд орой
    double side; // Гурвалжны тал
    double x2, y2, x3, y3; // Бусад оройнууд
public:
    Triangle(double topX, double topY, double s) : Shape2D("Зөв Гурвалжин"), x(topX), y(topY), side(s) {
        // Зөв гурвалжин тул, оройнуудыг тооцоолж гаргая
        x2 = x - side / 2;
        y2 = y - (sqrt(3) / 2) * side;
        x3 = x + side / 2;
        y3 = y - (sqrt(3) / 2) * side;
    }

    double area() override {
        return (sqrt(3) / 4) * side * side; // Тэгш өнцөгт гурвалжны талбай
    }

    double perimeter() override {
        return 3 * side; // Гурвалжны периметр
    }

    void display() override {
        cout << "Зөв Гурвалжин: Дээд Орой(" << x << ", " << y << "), Тал: " << side << endl;
        cout << "Бусад оройнууд: (" << x2 << ", " << y2 << "), (" << x3 << ", " << y3 << ")" << endl;
        cout << "Талбай: " << area() << ", Периметр: " << perimeter() << endl;
    }
};

// Функц: талбайгаар эрэмблэх (Bubble Sort ашиглан)
void sortShapes(Shape* shapes[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (shapes[j]->area() > shapes[j + 1]->area()) {
                // Өөрсдийн байрлалаа солих
                Shape* temp = shapes[j];
                shapes[j] = shapes[j + 1];
                shapes[j + 1] = temp;
            }
        }
    }
}

// Гол програм
int main() {
    Shape* shapes[3];  // Массив
    double cx, cy, radius, sx, sy, side, tx, ty, tside;

    // Тойргийн мэдээллийг гараас оруулах
    cout << "Тойргийн төвийн координат (x, y) болон радиусыг оруулна уу: ";
    cin >> cx >> cy >> radius;
    shapes[0] = new Circle(cx, cy, radius);

    // Квадратын мэдээллийг гараас оруулах
    cout << "Квадратын зүүн дээд оройн координат (x, y) болон талын уртыг оруулна уу: ";
    cin >> sx >> sy >> side;
    shapes[1] = new Square(sx, sy, side);

    // Зөв гурвалжны мэдээллийг гараас оруулах
    cout << "Зөв гурвалжны дээд оройн координат (x, y) болон талын уртыг оруулна уу: ";
    cin >> tx >> ty >> tside;
    shapes[2] = new Triangle(tx, ty, tside);

    // Эрэмбэлж үзэх (Bubble Sort)
    sortShapes(shapes, 3);

    // Эцэст нь дэлгэцэнд гаргах
    cout << "\nТалбайгаар эрэмбэлсэн хэлбэрүүд:\n";
    for (int i = 0; i < 3; ++i) {
        shapes[i]->display();
        cout << "----------------------" << endl;
    }

    // Цэвэрлэгээ
    for (int i = 0; i < 3; ++i) {
        delete shapes[i];
    }

    return 0;
}