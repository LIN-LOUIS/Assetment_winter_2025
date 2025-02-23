#include <iostream>
#include <stdexcept>

template <typename T>
class Stack {
private:
    T* data;       // 存储栈元素的数组
    size_t capacity; // 栈的容量
    size_t count;    // 当前元素个数

    void resize() {
        size_t newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < count; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Stack(size_t initCapacity = 4) : capacity(initCapacity), count(0) {
        data = new T[capacity];
    }

    ~Stack() {
        delete[] data;
    }

    Stack(const Stack& other) : capacity(other.capacity), count(other.count) {
        data = new T[capacity];
        for (size_t i = 0; i < count; ++i) {
            data[i] = other.data[i];
        }
    }

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            count = other.count;
            data = new T[capacity];
            for (size_t i = 0; i < count; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    void push(T value) {
        if (count == capacity) {
            resize();
        }
        data[count++] = value;
    }

    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack underflow");
        }
        --count;
    }

    T top() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return data[count - 1];
    }

    bool isEmpty() const {
        return count == 0;
    }

    size_t size() const {
        return count;
    }
};

int main() {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    std::cout << "Top element: " << s.top() << std::endl;
    s.pop();
    std::cout << "New top element: " << s.top() << std::endl;
    std::cout << "Stack size: " << s.size() << std::endl;
    return 0;
}