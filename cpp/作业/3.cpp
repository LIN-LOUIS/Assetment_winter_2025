#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable cv;

public:
    ThreadSafeQueue() = default;
    ~ThreadSafeQueue() = default;

    void push(T value) {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(std::move(value));
        cv.notify_one();
    }

    bool pop(T& value) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !queue.empty(); });
        value = std::move(queue.front());
        queue.pop();
        return true;
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lock(mtx);
        if (queue.empty()) {
            return false;
        }
        value = std::move(queue.front());
        queue.pop();
        return true;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.empty();
    }
};

int main() {
    ThreadSafeQueue<int> tsq;
    tsq.push(1);
    tsq.push(2);
    tsq.push(3);
    
    int value;
    tsq.pop(value);
    std::cout << "Popped value: " << value << std::endl;
    
    tsq.pop(value);
    std::cout << "Popped value: " << value << std::endl;
    
    return 0;
}
