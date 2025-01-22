#include <iostream>
using namespace std;

class Rectangle {
private:
    double width;  // 宽度
    double height; // 高度

public:
    // 构造函数
    Rectangle(double w = 1.0, double h = 1.0) : width(w), height(h) {
        if (w <= 0 || h <= 0) {
            throw invalid_argument("输错了");
        }
    }

    // 拷贝构造函数
    Rectangle(const Rectangle& other) : width(other.width), height(other.height) {}

    // 赋值运算符重载
    Rectangle& operator=(const Rectangle& other) {
        if (this != &other) { // 防止自赋值
            width = other.width;
            height = other.height;
        }
        return *this;
    }

    // 计算矩形面积
    double area() const {
        return width * height;
    }

    // 按比例缩放矩形的宽度和高度
    void resize(double scale) {
        if (scale <= 0) {
            throw invalid_argument("输错了");
        }
        width *= scale;
        height *= scale;
    }

    // 声明友元函数
    friend bool isSquare(const Rectangle& rect);

    // 显示矩形信息（辅助函数）
    void display() const {
        cout << "Rectangle(width: " << width << ", height: " << height << ")" << endl;
    }
};

// 判断矩形是否为正方形（友元函数）
bool isSquare(const Rectangle& rect) {
    return rect.width == rect.height;
}

// 测试代码
int main() {
    try {
        Rectangle rect1(4.0, 5.0);
        rect1.display();
        cout << "Area: " << rect1.area() << endl;

        Rectangle rect2 = rect1; // 拷贝构造
        rect2.resize(2.0);
        rect2.display();
        cout << "Is square: " << (isSquare(rect2) ? "Yes" : "No") << endl;

        Rectangle rect3(6.0, 6.0);
        cout << "Is square: " << (isSquare(rect3) ? "Yes" : "No") << endl;

        rect3 = rect1; // 赋值操作
        rect3.display();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
