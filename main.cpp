//Ильминский Никита, М8О-207Б-18
//Вариант 8: 8-угольник, Треугольник, Квадрат
/*Разработать классы согласно варианту задания, классы должны наследоваться от базового класса Figure.
Фигуры являются фигурами вращения.
Все классы должны поддерживать набор общих методов:
    Вычисление геометрического центра фигуры;
    Вывод в стандартный поток вывода std::cout координат вершин фигуры;
    Вычисление площади фигуры;

Создать программу, которая позволяет:
    Вводить из стандартного ввода std::cin фигуры, согласно варианту задания.
    Сохранять созданные фигуры в динамический массив std::vector<Figure*>
    Вызывать для всего массива общие функции (1-3 см. выше).Т.е. распечатывать для каждой фигуры в массиве геометрический центр, координаты вершин и площадь.
    Необходимо уметь вычислять общую площадь фигур в массиве.
    Удалять из массива фигуру по индексу;
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

struct point {
    float x;
    float y;
};

std::ostream& operator<< (std::ostream& out, const point& p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

class Figure {
    protected:
        std::string name;
    public:
        std::string getName() {
            return name;
        }
        virtual point GeometricCenter() = 0;
        virtual void Vertices() = 0;
        virtual float Area() = 0;
        //virtual ~Figure() = default;
};

class Octagon: public Figure {
        point p1, p2, p3, p4, p5, p6, p7, p8;
        float a;
    public:
        Octagon() {
            name = "Octagon";
        }
        Octagon(const point p, const float r) {
            if(r <= 0) {
                std::cout << "Incorrect radius for an octagon! Radius is <= 0\n";
                exit(1);
            }
            name = "Octagon";

            float r2 = r / sqrt(2);
            p1.x = p.x; p1.y = p.y + r;
            p2.x = p.x + r2; p2.y = p.y + r2;
            p3.x = p.x + r; p3.y = p.y;
            p4.x = p.x + r2; p4.y = p.y - r2;
            p5.x = p.x; p5.y = p.y - r;
            p6.x = p.x - r2; p6.y = p.y - r2;
            p7.x = p.x - r; p7.y = p.y;
            p8.x = p.x - r2; p8.y = p.y + r2;

            a = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
        }
        /*Octagon(const point v1, const point v2) {
            name = "Octagon";
            p1 = v1;
            p2 = v2;
            a = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
            //b = a / sqrt(2);
            //point perp;
            //perp.x = (p2.y - p1.y) / sqrt(2);
            //perp.y = (p1.x - p2.x) / sqrt(2);
            //p3.x = p2.x + perp.x + ; p3.y = p3.y - perp.y
            p3.x = p2.x + b; p3.y = p2.y - b;
            p4.x = p3.x; p4.y = p3.y - a;
            p5.x = p4.x - b; p5.y = p4.y - b;
            p6.x = p5.x - a; p6.y = p5.y;
            p7.x = p6.x - b; p7.y = p6.y + b;
            p8.x = p7.x; p8.y = p7.y + a;
        }*/
        ~Octagon() = default;

        point GeometricCenter() override {
            point center;
            center.x = (p1.x + p5.x) / 2;
            center.y = (p1.y + p5.y) / 2;
            return center;
        }
        void Vertices() override {
            std::cout << "Octagon vertices are: " << p1 << ", " << p2 << ", "
            << p3 << ", " << p4 << ", " << p5 << ", " << p6 << ", " << p7 << ", " << p8 << std::endl;
        }
        float Area() override {
            return 2 * (1 + sqrt(2)) * pow(a, 2);
        }
};

class Triangle: public Figure {
        point p1, p2, p3;
        float a, b, c;
    public:
        Triangle() {
            name = "Triangle";
        }
        Triangle(const point v1, const point v2, const point v3) {
            name = "Triangle";
            p1 = v1;
            p2 = v2;
            p3 = v3;
            a = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
            b = sqrt(pow(p2.x - p3.x, 2) + pow(p2.y - p3.y, 2));
            c = sqrt(pow(p3.x - p1.x, 2) + pow(p3.y - p1.y, 2));
            if(Area() == 0) {
                std::cout << "Incorrect vertices for a triangle! The area is 0\n";
                exit(1);
            }
        }
        ~Triangle() = default;

        point GeometricCenter() override {
            point center;
            center.x = (p1.x + p2.x + p3.x) / 3;
            center.y = (p1.y + p2.y + p3.y) / 3;
            return center;
        }
        void Vertices() override {
            std::cout << "Triangle vertices are: " << p1 << ", " << p2 << ", " << p3 << std::endl;
        }
        float Area() override {
            float p = (a + b + c) / 2;
            return sqrt(p * (p - a) * (p - b) * (p - c));
        }
};

class Square: public Figure {
        point p1, p2, p3, p4;
        float a;
    public:
        Square() {
            name = "Square";
        }
        Square(const point v1, const point v2) {
            if(v1.x == v2.x && v1.y == v2.y) {
                std::cout << "Incorrect vertices for a square! Coordinates are equal\n";
                exit(1);
            }
            name = "Square";
            p1 = v1;
            p3 = v2;
            a = sqrt((pow(p3.x - p1.x, 2) + pow(p3.y - p1.y, 2)) / 2);

            point c = GeometricCenter();
            point perp;
            perp.x = (p3.y - p1.y) / 2;
            perp.y = (p1.x - p3.x) / 2;
            p2.x = c.x - perp.x;
            p2.y = c.y - perp.y;
            p4.x = c.x + perp.x;
            p4.y = c.y + perp.y;
        }
        point GeometricCenter() override {
            point center;
            center.x = (p1.x + p3.x) / 2;
            center.y = (p1.y + p3.y) / 2;
            return center;
        }
        void Vertices() override {
            std::cout << "Square vertices are: " << p1 << ", " << p2 << ", " << p3 << ", " << p4 << std::endl;
        }
        float Area() override {
            return a * a;
        }
};

inline void menu() {
    std::cout << "List of operations with figures:\n";
    std::cout << "0. \"menu\" to print this menu;\n";
    std::cout << "1. \"add\" to add a new figure;\n";
    std::cout << "2. \"center\" to get the geometric center for each figure;\n";
    std::cout << "3. \"vertices\" to get the vertices of each figure;\n";
    std::cout << "4. \"area\" to get the area of each figure;\n";
    std::cout << "5. \"total\" to get the total area of all figures;\n";
    std::cout << "6. \"delete\" to erase a figure by an index;\n";
    std::cout << "7. \"quit\" to exit the program;\n";
    std::cout << "Enter the needed operation:\n";
}

int main()
{
    std::vector<Figure*> v;
    Figure* f = nullptr;

    std::string action;
    menu();
    char figure;

    while(std::cin >> action) {
        if(action == "menu") {
            menu();
        }
        if(action == "add") {
            std::cout << "Enter O for an octagon, T for a triangle, S for a square:\n";
            std::cin >> figure;
            point p1, p2, p3;
            float r;
            switch(figure) {
                case 'O':
                    std::cout << "Enter the coordinate of a center and the radius of a circle: ";
                    std::cin >> p1.x >> p1.y >> r;
                    f = new Octagon(p1, r);
                    v.push_back(f);
                    std::cout << "Octagon added at index " << v.size() - 1 << std::endl;
                    break;
                case 'T':
                    std::cout << "Enter three vertices for a triangle: ";
                    std::cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
                    f = new Triangle(p1, p2, p3);
                    v.push_back(f);
                    std::cout << "Triangle added at index " << v.size() - 1 << std::endl;
                    break;
                case 'S':
                    std::cout << "Enter two opposite vertices of square: ";
                    std::cin >> p1.x >> p1.y >> p2.x >> p2.y;
                    f = new Square(p1, p2);
                    v.push_back(f);
                    std::cout << "Square added at index " << v.size() - 1 << std::endl;
                    break;
                default:
                    std::cout << "\'" << figure << "\' is invalid figure\n";
                    break;
            }
        }
        if(action == "center") {
            for(size_t i = 0; i < v.size(); i++) {
                std::cout << "Center of " << v[i]->getName() << " is " << v[i]->GeometricCenter() << std::endl;
            }
        }
        if(action == "vertices" || action == "vert") {
            for(size_t i = 0; i < v.size(); i++) {
                v[i]->Vertices();
            }
        }
        if(action == "area") {
            for(size_t i = 0; i < v.size(); i++) {
                std::cout << "The area of " << v[i]->getName() << " is " << v[i]->Area() << std::endl;
            }
        }
        if(action == "total") {
            float s = 0;
            for(size_t i = 0; i < v.size(); i++) {
                s += v[i]->Area();
            }
            std::cout << "The total area of all figures is: " << s << std::endl;
        }
        if(action == "delete") {
            size_t idx;
            std::cout << "Enter the index of a figure you want to erase: ";
            std::cin >> idx;
            if(idx >= v.size()) {
                std::cout << "Wrong index! Vector size is " << v.size() << std::endl;
                continue;
            }
            v.erase(v.begin() + idx);
            std::cout << "Element erased.\n";
        }
        if(action == "quit") {
            delete f;
            break;
        }
    }
    return 0;
}
